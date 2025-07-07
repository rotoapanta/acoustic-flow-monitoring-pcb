//Programa para tarjeta DAFM2007IG
//programa para tarjeta de AFM con PIC18 y AD7706
//TR 9600 (RS232), xtal = 19.6608MHz
//Primer programa general

#include <htc.h>
#include <stdio.h>
#include <pic18f4550.h>
#include "serial.h"
#include "serial.c"
#include "delay.h"
#include "delay.c"
#include "timer.h"
#include "spi.h"
#include "adc.h"

// ya definido
#define	SCLK RB1	//SCK
#define	SDI  RB0	//SDI
#define	SDO  RC7	//SDO
#define	DRDY RB2	//DATA READY
#define LTX	 RB4	//led de transmision
#define LFN  RB3	//led de fuincionamiento normal

//----------------------------------------------------------------------------------
//para el conversor y promedio
		 unsigned char i=0,j=0,k=0;
		 unsigned int  dato_spi_temp=0;		//variable temporal para lectura de datos		 
volatile unsigned long dato_spi_full_band=0;		//variables de almacenamiento temporal de 
volatile unsigned long dato_spi_low_band=0;		//los datos de cada canal
volatile unsigned long dato_spi_high_band=0;
//----------------------------------------------------------------------------------

// Variables para lecctura del dip-switchs
// Numero de estacion e intervalo de transmision de datos
volatile uint8_t frec_tx_datos = 0;
volatile uint8_t num_de_estacion = 0;

//----------------------------------------------------------------------------------
volatile unsigned int nivel_bateria_decimal=0;
volatile        float nivel_bateria_flotante=0;
volatile unsigned int lectura_sensor_full_band=0;
volatile unsigned int lectura_sensor_low_band=0;
volatile unsigned int lectura_sensor_high_band=0;
volatile         char datos_sensores_afm[60]=0;
volatile unsigned int check_sum_valor_calculado=0;
//----------------------------------------------------------------------------------
//tareas
volatile unsigned int      TIEMPO_TX = 0;
volatile unsigned int CONT_TIEMPO_TX = 0;
//-----------------------------------------------------------------------------
#define 	     	  TAREA_ADQ 50   			// 0.7s			
		 unsigned int CONT_TAREA_ADQ = 0;
//-----------------------------------------------------------------------------
#define           	  TIEMPO_UMBRAL 30			//  0.4s tareas de ADQ			
		 unsigned int CONT_TIEMPO_UMBRAL = 0;
//-----------------------------------------------------------------------------
#define           	  TIEMPO_CHEKEO (70*40)		// 36s verifica que la senal 			
		 unsigned int CONT_TIEMPO_CHEKEO = 0;	// se mantenga mas de 30s
//-----------------------------------------------------------------------------
#define  			   VALOR_MAXIMO_16B 0xffff
volatile unsigned long UNBRAL_500MV = 0;

//-----------------------------------------------------------------------------
//permisos
volatile bool HABILITAR_TX = false;
volatile bool HABILITAR_PRIMERA_TX = false;
		 bool VERIFICAR_UMBRAL = false;
//----------------------------------------------------------------------------
void main(void)
{

    Inicializar_Sistema();
	
	// TAREA_ADQ = 50, 0.6s, 10s, 20s, 40s, 3m:20s, 6m:40s, 10 min
	frec_tx_datos = Lectura_Frecuencia_tx();
	
	ADCON1=0x0F;		//config AN0 ... AN12 todos I/O	

	frec_tx_datos   = Lectura_Frecuencia_tx();    
    num_de_estacion = Lectura_Numero_Est(); 

	// Variable para crear cadena de caracteres
	datos_sensores_afm[0]='0';
	
	datos_sensores_afm[1,2]= num_de_estacion;				
	
	//definir el umbral
	UNBRAL_500MV=6554;				//500mV
	
	//dar tiempo de transmision
	//printf("PIC18F2550... conectado...!\n");

	// Serial Port Enable bit
	// 1 = Serial port enabled. Configures RX/DT and TX/CK pins as serial port pins
	// RCSTAbits.SPEN = 0;	 //Serial port disabled (held in Reset)
	Puerto_Serie_232_Deshabilitado();
	
	//para transmitir luego de arrancar el sistema
	HABILITAR_PRIMERA_TX = 1;		
	
	// Requerido por el ADC
	spi_putch1(0xFF); spi_putch1(0xFF); 
	spi_putch1(0xFF); spi_putch1(0xFF); spi_putch1(0xFF);
	
    // Habilita las interrupciones globales    
    Interrupcion_Global_Habilitar();
    // Habilita las interrupciones periféricas
    Interrupcion_Periferica_Habilitar();

	// Recomendacion encender timers
	
	// permite una sola lectura
    Habilitar_Lectura_ADC_Ch0();

	while(1)
	{
		//CLRWDT();
	}
}

//-----------------------------------------------------------------------------------------
//   interrupciones
//-----------------------------------------------------------------------------------------

static void interrupt isr(void)
{
	GIE=0;
	if(TMR1IF)
	{   
		TMR1IF=0;
		
		CONT_TAREA_ADQ++;
		
		// TAREA_ADQ = 50, 0.6s, 10s, 20s, 40s, 3m:20s, 6m:40s, 10 min
		if(TAREA_ADQ<=CONT_TAREA_ADQ)			//operar cada 0.7 segundo
		 {
			Puerto_Serie_232_Deshabilitado();	//deshabilitar rs232 para usar el SPI
			
			Timer1_Apagar();					//apagar timer 1
			
			CONT_TAREA_ADQ = 0;					//encerar contador

			LFN=!LFN;							// LED, apagado/encendido
			
			//lectura de bateria
			Habilitar_Lectura_ADC_Ch0();

			nivel_bateria_decimal = resultado_lecturas_adc_ch0;

			nivel_bateria_flotante=(nivel_bateria_decimal*15/1023.00)*250.00;

			datos_sensores_afm[21...26]=' ''+'nivel_bateria_decimal[0...3];

			//configurar canal 1
			spi_putch(0x20);	// CH 1, prox. op escribir en clock register
			spi_putch(0x0F);	// CLKDIV=1, CLK=1, 375 mps
			spi_putch(0x10);	// CH 1, prox. op escribir a setup register
			spi_putch(0x40); 	// ganancia=1, autocalibración, bipolar, BUF=0.
			while(DRDY)
				continue;		// esperar que Data Ready sea cero
			dato_spi_full_band=0;			// para tomar nueva conversion
			for(i=0;i<50;i++)
			{
				spi_putch(0x38);			//ir al registro de datos
				while(DRDY)
					continue;

				dato_spi_temp=0;
				dato_spi_temp =spi_getch()<<8;
				dato_spi_temp+=spi_getch();									
				dato_spi_full_band+=dato_spi_temp;
				
			}
			//------------------------------------------------------------------------------
			//configurar canal 2
			spi_putch(0x21);				//CH 2, prox. op escribir en clock register
			spi_putch(0x0F);				//CLKDIV=1, CLK=1, 375 mps
			spi_putch(0x11);				//CH 2, prox. op escribir a setup register
			spi_putch(0x40); 				//ganancia=1, autocalibración, bipolar, BUF=0.
			while(DRDY) continue;

			dato_spi_low_band=0;						//para tomar nueva conversion

			for(i=0;i<50;i++)
			{
				spi_putch(0x39);			//ir al registro de datos
				while(DRDY)
					continue;
				dato_spi_temp=0;
				dato_spi_temp =spi_getch()<<8;
				dato_spi_temp+=spi_getch();			
				dato_spi_low_band+=dato_spi_temp;
			}
			//------------------------------------------------------------------------------
			//configurar adc canal3
			spi_putch(0x23);				//CH 3, prox. op escribir en clock register
			spi_putch(0x0F);				//CLKDIV=1, CLK=1, 375 mps
			spi_putch(0x13);				//CH 3, prox. op escribir a setup register
			spi_putch(0x40); 				//ganancia=1, autocalibración, bipolar, BUF=0.
			while(DRDY)
				continue;
			dato_spi_high_band=0;			//para tomar nueva conversion
			for(i=0;i<50;i++)
			{
				spi_putch(0x3B);			//ir al registro de datos
				while(DRDY)
					continue;
				dato_spi_temp=0;
				dato_spi_temp =spi_getch()<<8;
				dato_spi_temp+=spi_getch();									
				dato_spi_high_band+=dato_spi_temp;
			}
			//------------------------------------------------------------------------------
			
			lectura_sensor_full_band=dato_spi_full_band/50;		
			lectura_sensor_low_band =dato_spi_low_band/50;		
			lectura_sensor_high_band=dato_spi_high_band/50;
			
			// tomar este dato para verificar el umbral
			dato_spi_low_band=lectura_sensor_low_band;
			
			lectura_sensor_full_band/=13.107;
			lectura_sensor_low_band/= 13.107;
			lectura_sensor_high_band/=13.107;
			
			
			datos_sensores_afm[3]=' '; datos_sensores_afm[4]='+';
			datos_sensores_afm[5,6,7,8]=lectura_sensor_full_band[0...3];

			datos_sensores_afm[9,10]=' ','+';
			datos_sensores_afm[11,12,13,14]=lectura_sensor_low_band[0...3];
			datos_sensores_afm[15,16]=' ','+';
			datos_sensores_afm[17,18,19,20]=((lectura_sensor_high_band[0...3];

			TMR1ON=1;				//encender timer 1

			HABILITAR_TX = true;			//luz verde para transmitir datos

			VERIFICAR_UMBRAL = true;		//para verificar el umbral
			if(HABILITAR_PRIMERA_TX)
			{
				CONT_TIEMPO_TX = 0xFFFF;
				HABILITAR_PRIMERA_TX = 0;
			}
		}
		//----------------------------------------------------------------------------------
		//transmitir datos 
		CONT_TIEMPO_TX++;
		if(TIEMPO_TX<=CONT_TIEMPO_TX)
		{
			CONT_TIEMPO_TX=0;
			if(HABILITAR_TX)
			{

				HABILITAR_TX = false;

				//envio de datos, el USART debe 
				Puerto_Serie_232_Habilitado(); 			//habilitar USART (rs232)

				LTX=1;  // LED ON				
				

				datos_sensores_afm[27...29]=' ''c''+';

				datos_sensores_afm[30...33] = check_sum_valor_calculado(datos_sensores_afm[0...29]);
				datos_sensores_afm[34]=13;				// retorno de carro 13 o 0x0D
				datos_sensores_afm[35]='\0';				// caracter fin de cadena

				UART_Enviar_Cadena(datos_sensores_afm[0...35]);
				UART_Enviar_Caracter(0x0A);  // salto de linea 10 o 0x0A

				// fin del encio de datos

				// inicializar las variable
				lectura_sensor_full_band=0; 
				lectura_sensor_high_band=0; 
				lectura_sensor_low_band=0; 
				check_sum_valor_calculado=0;
				
				//deshabilitar el usart
				// se puede utilizar el SPI
				Puerto_Serie_232_Deshabilitado();	

				LTX=0;	// LED OFF, 
			}	
		}
		//----------------------------------------------------------------------------------
		//verificar umbral
		if(VERIFICAR_UMBRAL)
		{
			VERIFICAR_UMBRAL = false;
			if(UNBRAL_500MV<=dato_spi_low_band)
			{
				CONT_TIEMPO_UMBRAL++;
				if(TIEMPO_UMBRAL<=CONT_TIEMPO_UMBRAL)   // TIEMPO_UMBRAL fija 0.4s
				{
					CONT_TIEMPO_UMBRAL=0;
					
					// asignar menor intervalo
					TIEMPO_TX=50*60; 					// 3000, 40s
					
					// cumple condicion y transmite a cada ov del Timer
					CONT_TIEMPO_TX = 0xFFFF;
					
					//activar alerta
					datos_sensores_afm[0]='1';		
					
					//luz verde para transmitir datos
					HABILITAR_TX = true;			
				}
			}
			else {
				datos_sensores_afm[0]='0';			//desactivar alerta
				//lectura del dip-sw	
				frec_tx_datos = Lectura_Frecuencia_tx();
				// TIEMPO_TX=TAREA_ADQ*x*y;
				// 0.6s, 10s, 20s, 40s, 3m:20s, 6m:40s, 10 min, 
				// TIEMPO_TX=65535 = 14m:34s 		
				}	
			}
		}
		//----------------------------------------------------------------------------------
		//verificar tiempo de mantenimiento de senal
		//permite verificar que la senal se mantiene 
		//sobre el umbral mas de 30 seg
		if(CONT_TIEMPO_UMBRAL!=0)
			CONT_TIEMPO_CHEKEO++;
		if(TIEMPO_CHEKEO<=CONT_TIEMPO_CHEKEO)
		{
			CONT_TIEMPO_CHEKEO=0;
			CONT_TIEMPO_UMBRAL=0;		//no permite entrar en alerta
		}
		//----------------------------------------------------------------------------------
		//tarea 3
		//----------------------------------------------------------------------------------
	}	
	//habilitar interrupciones globales
	GIE=1;
}