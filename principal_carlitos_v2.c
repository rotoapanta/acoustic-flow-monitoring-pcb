//Programa para tarjeta DAFM2007IG
//programa para tarjeta de AFM con PIC18 y AD7706
//TR 9600 (RS232), xtal = 19.6608MHz
//Primer programa general
//----------------------------------------------------------------------------------
//uso de la memoria
//--------------------------
//H3	2^0	vel tx dat	0
//--------------------------
//H2	2^1	int tx 		0
//H1	2^2	int tx 		1
//H0	2^3	int tx 		2
//--------------------------
//F3	2^4	nun est 	0
//F2	2^5	nun est 	1
//F1	2^6	nun est 	2
//F0	2^7	nun est 	3
//--------------------------
//designacion de pines
//H0->RC0	DIN ->RC7
//H1->RC1	DOUT->RB0
//H2->RC2	DRDY->RB2
//H3->RC5	SCLK->RB1
//F0->RC4	BAT ->RA0
//F1->RA1	B1  ->RB3
//F2->RA4	B2  ->RB4
//F3->RA5	
//--------------------------
//----------------------------------------------------------------------------------

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
         void config_spi(void);
unsigned char spi_putch(unsigned char);
unsigned char spi_putch1(unsigned char);
unsigned char spi_getch(void);

// se configurara en el puerto serial
// pasado al xc8

//----------------------------------------------------------------------------------
//para el conversor y promedio
		 unsigned char i=0;
		 unsigned int  j=0;
		 unsigned char k=0;
		 unsigned int  temp1=0;		//variable temporal para lectura de datos		 
volatile unsigned long dato1=0;		//variables de almacenamiento temporal de 
volatile unsigned long dato2=0;		//los datos de cada canal
volatile unsigned long dato3=0;
volatile unsigned long dato4=0;
volatile unsigned char A=0;			//babdera de alerta
//----------------------------------------------------------------------------------

// variables para lecctura del dip-switchs
// para fijar numero de estacion y 
// intervalo de transmision de datos
volatile uint8_t frec_tx_datos = 0;
volatile uint8_t num_de_estacion = 0;
//volatile unsigned char temp2 = 0;

//----------------------------------------------------------------------------------
volatile unsigned int Bateria=0;
volatile float fBateria=0;
volatile unsigned int FullBand=0;
volatile unsigned int LowBand=0;
volatile unsigned int HighBand=0;
volatile char DATA[60]=0;
volatile unsigned int CheckSum=0;
//----------------------------------------------------------------------------------
//tareas
volatile unsigned int      TIEMPO_TX = 0;
volatile unsigned int CONT_TIEMPO_TX = 0;
//-----------------------------------------------------------------------------
#define 	     	  TAREA_ADQ 50   			//para 1 min aprox			
		 unsigned int CONT_TAREA_ADQ = 0;
//-----------------------------------------------------------------------------
#define           	  TIEMPO_UMBRAL 30			// tareas de ADQ			
		 unsigned int CONT_TIEMPO_UMBRAL = 0;
//-----------------------------------------------------------------------------
#define           	  TIEMPO_CHEKEO (70*40)		// verifica que la senal 			
		 unsigned int CONT_TIEMPO_CHEKEO = 0;	// se mantenga mas de 30s
//-----------------------------------------------------------------------------
volatile unsigned long UNBRAL = 0;

#define  				ValorMaximo 50000

//-----------------------------------------------------------------------------
//permisos
volatile unsigned char HABILITAR_TX=0;
volatile unsigned char HABILITAR_PRIMERA_TX=0;
		 unsigned char VERIFICAR_UMBRAL=0;
		 unsigned char HABILITAR_PREAMBULO=0; 
//----------------------------------------------------------------------------
void main(void)
{
	
	DelayMs(250);
	TRISA=0xFF;
	TRISB2=1;					//DRDY
	TRISB3=0;					//LFN
	TRISB4=0;					//LTX
	TRISA5=1;					//select slave input
	CMCON=0x07;					//comparador apagado
	USBEN=0;					//USB Module Enable bit
	//configuracion de puerto para dip-sw
	TRISC0=1;
	TRISC1=1;
	TRISC2=1;
	UTRDIS=1;		//hacer TRISC4=1 y TRISC5=1
	TRISA1=1;
	TRISA4=1;
	TRISA5=1;
	init_comms();				//configurar rs232
	config_spi();				//configurar spi
	config_tmr1();				//habilitar timer1
	config_adc();
	
	//lectura del dip-sw
	
	frec_tx_datos = F0*1 + F1*2 + F2*4 + F3*8; 

	// TAREA_ADQ = 50, 50tov = 0.67s
	// 
	switch(frec_tx_datos)
	{
		case 0:
			TIEMPO_TX=TAREA_ADQ*1*0; // 0.013 s, 13.33ms
		break;
		case 1:
			TIEMPO_TX=TAREA_ADQ*1*15; // 0.2 s
		break;
		case 2:
			TIEMPO_TX=TAREA_ADQ*1*30; // 0.4 s
		break;
		case 3:
			TIEMPO_TX=TAREA_ADQ*1*60; // 0.8 s
		break;
		case 4:
			TIEMPO_TX=TAREA_ADQ*5*60; // 4.0 s
		break;
		case 5:
			TIEMPO_TX=TAREA_ADQ*10*60; // 8s
		break;
		case 6:
			TIEMPO_TX=TAREA_ADQ*15*60; //
		break;
		case 7:
			TIEMPO_TX=65535;		
		break;
	}	
	ADCON1=0x0F;		//cambiar para leer la bateria

	num_de_estacion = H0*1 + H1*2 + H2*4 + H3*8;

	frec_tx_datos = F0*1 + F1*2 + F2*4 + F3*8; 

	DATA[1]=((num_de_estacion/10)+'0');	

	num_de_estacion = num_de_estacion % 10;
	
	DATA[2]=((num_de_estacion/1 )+'0');				
	
	//definir el umbral
	UNBRAL=6554;				//500mV
	//dar tiempo de transmision
	//printf("PIC18F2550... conectado...!\n");
	SPEN=0;						//deshabilitar rs232
	DelayMs(10);
	HABILITAR_PRIMERA_TX=1;		//para transmitir luego de arrancar el sistema
	spi_putch1(0xFF);
	spi_putch1(0xFF);
	spi_putch1(0xFF);
	spi_putch1(0xFF);
	spi_putch1(0xFF);
	DATA[0]='0';			//desactivar alerta
	GIE=1;
	PEIE=1;
	TMR1ON=1;					//encender timer 1 de 16 bits
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
		//----------------------------------------------------------------------------------
		if(TAREA_ADQ<=CONT_TAREA_ADQ)		//operar cada 5 segundo
		 {
			SPEN=0;							//deshabilitar rs232 para usar el SPI
			TMR1ON=0;						//apagar timer 1
			CONT_TAREA_ADQ=0;				//encerar contador
			LFN=!LFN;
			//------------------------------------------------------------------------------
			//lectura de bateria
			for(i=0;i<10;i++)
			{
				ADCON0=0x01;	//GODONE=1 y ADON=1;
				ADCON1=0x3B;	//habilitar referencias y entrada analogica
				GODONE=1;
				while(GODONE)
					continue;
			}
			Bateria=0;
			Bateria=(ADRESH<<8)+ADRESL;
			fBateria=Bateria*15;
			fBateria/=1023.00;
			Bateria=fBateria*250.00;
			DATA[21]=' ';
			DATA[22]='+';
			DATA[23]=((Bateria/1000)+'0');	Bateria%=1000;
			DATA[24]=((Bateria/100)+'0');	Bateria%=100;
			DATA[25]=((Bateria/10)+'0');	Bateria%=10;
			DATA[26]=((Bateria/1)+'0');
			//------------------------------------------------------------------------------
			//configurar canal 1
			spi_putch(0x20);				//canal 1, prox. op escribir en clock register
			spi_putch(0x0F);				//CLKDIV=1, CLK=1, 375 mps
			spi_putch(0x10);				//canal 1, prox. op escribir a setup register
			spi_putch(0x40); 				//ganancia=1, autocalibración, bipolar, BUF=0.
			while(DRDY)
				continue;					//esperar que Data Ready sea cero
			dato1=0;				//para tomar nueva conversion
			for(i=0;i<50;i++)
			{
				spi_putch(0x38);			//ir al registro de datos
				while(DRDY)
					continue;
				temp1=0;
				temp1 =spi_getch()<<8;
				temp1+=spi_getch();									
				dato1+=temp1;
			}
			//------------------------------------------------------------------------------
			//configurar canal 2
			spi_putch(0x21);				//canal 2, prox. op escribir en clock register
			spi_putch(0x0F);				//CLKDIV=1, CLK=1, 375 mps
			spi_putch(0x11);				//canal 2, prox. op escribir a setup register
			spi_putch(0x40); 				//ganancia=1, autocalibración, bipolar, BUF=0.
			while(DRDY)
				continue;
			dato2=0;						//para tomar nueva conversion
			for(i=0;i<50;i++)
			{
				spi_putch(0x39);			//ir al registro de datos
				while(DRDY)
					continue;
				temp1=0;
				temp1 =spi_getch()<<8;
				temp1+=spi_getch();			
				dato2+=temp1;
			}
			//------------------------------------------------------------------------------
			//configurar adc canal3
			spi_putch(0x23);				//canal 3, prox. op escribir en clock register
			spi_putch(0x0F);				//CLKDIV=1, CLK=1, 375 mps
			spi_putch(0x13);				//canal 3, prox. op escribir a setup register
			spi_putch(0x40); 				//ganancia=1, autocalibración, bipolar, BUF=0.
			while(DRDY)
				continue;
			dato3=0;						//para tomar nueva conversion
			for(i=0;i<50;i++)
			{
				spi_putch(0x3B);			//ir al registro de datos
				while(DRDY)
					continue;
				temp1=0;
				temp1 =spi_getch()<<8;
				temp1+=spi_getch();									
				dato3+=temp1;
			}
			//------------------------------------------------------------------------------
			//promedio
			FullBand=dato1/50;		
			LowBand =dato2/50;		
			HighBand=dato3/50;
			dato2=LowBand;
			FullBand/=13.107;
			LowBand/= 13.107;
			HighBand/=13.107;
			SPEN=1;					//habilitar USART (rs232)
			DATA[3]=' ';
			DATA[4]='+';
			DATA[5]=((FullBand/1000)+'0');	FullBand%=1000;
			DATA[6]=((FullBand/100)+'0');	FullBand%=100;
			DATA[7]=((FullBand/10)+'0');	FullBand%=10;
			DATA[8]=((FullBand/1)+'0');
			DATA[9]=' ';
			DATA[10]='+';
			DATA[11]=((LowBand/1000)+'0');	LowBand%=1000;
			DATA[12]=((LowBand/100)+'0');	LowBand%=100;
			DATA[13]=((LowBand/10)+'0');	LowBand%=10;
			DATA[14]=((LowBand/1)+'0');
			DATA[15]=' ';
			DATA[16]='+';
			DATA[17]=((HighBand/1000)+'0');	HighBand%=1000;
			DATA[18]=((HighBand/100)+'0');	HighBand%=100;
			DATA[19]=((HighBand/10)+'0');	HighBand%=10;
			DATA[20]=((HighBand/1)+'0');
			TMR1ON=1;				//encender timer 1
			HABILITAR_TX=1;			//luz verde para transmitir datos
			VERIFICAR_UMBRAL=1;		//para verificar el umbral
			if(HABILITAR_PRIMERA_TX)
			{
				CONT_TIEMPO_TX=ValorMaximo;
				HABILITAR_PRIMERA_TX=0;
			}
			//if(TIEMPO_TX>=750)	//mayor o igual que 15 seg
			//	HABILITAR_PREAMBULO=1;
		}
		//----------------------------------------------------------------------------------
		//transmitir datos 
		CONT_TIEMPO_TX++;
		if(TIEMPO_TX<=CONT_TIEMPO_TX)
		{
			CONT_TIEMPO_TX=0;
			if(HABILITAR_TX)
			{
				HABILITAR_TX=0;
				//-----------------------------------------------
				LTX=1;				
				if(HABILITAR_PREAMBULO)
				{
					TMR1ON=0;
					HABILITAR_PREAMBULO=0;
					for(j=0;j<9600;j++)	
					{
						putch(0xFF);
						CLRWDT();
					}
					for(j=0;j<9600;j++)	
					{
						putch(0x00);
						CLRWDT();
					}
					for(j=0;j<9600;j++)	
					{
						putch(0xAA);
						CLRWDT();
					}
					TMR1ON=1;
				}
				
				//-----------------------------------------------				
				//envio de datos, el USART debe 
				//estar habilitado (SPEN=1)
				DATA[27]=' ';
				DATA[28]='c';
				DATA[29]='+';
				for(k=0;k<29;k++)
					CheckSum+=DATA[k];

				DATA[30]=((CheckSum/1000)+'0');	CheckSum%=1000;
				DATA[31]=((CheckSum/100)+'0');	CheckSum%=100;
				DATA[32]=((CheckSum/10)+'0');	CheckSum%=10;
				DATA[33]=((CheckSum/1)+'0');
				DATA[34]=13;
				DATA[35]='\0';
				
				for(k=0;k<35;k++)
					putch(DATA[k]);
				
				putch(10);

				FullBand=0;
				HighBand=0;
				LowBand=0;
				CheckSum=0;
				SPEN=0;			//deshabilitar el usart
				LTX=0;			//se puede utilizar el SPI
			}	
		}
		//----------------------------------------------------------------------------------
		//verificar umbral
		if(VERIFICAR_UMBRAL)
		{
			VERIFICAR_UMBRAL=0;
			if(UNBRAL<=dato2)
			{
				CONT_TIEMPO_UMBRAL++;
				// v_umbral 500 mv, 40 seg, para lazar la alarma
				// si se verifica q permanece mas de 45s sobre el voltaje umbral
				// empezamos a transmitir cada 1 minuto
				// generalmente cada 10 min
				
				if(TIEMPO_UMBRAL<=CONT_TIEMPO_UMBRAL)
				{
					CONT_TIEMPO_UMBRAL=0;
					TIEMPO_TX=TAREA_ADQ*1*60;
					CONT_TIEMPO_TX=ValorMaximo;
					DATA[0]='1';		//activar alerta
 					HABILITAR_TX=1;			//luz verde para transmitir datos
				}
			}
			else
			{
				DATA[0]='0';			//desactivar alerta
				frec_tx_datos = F0*1 + F1*2 + F2*4 + F3*8; 
				switch(frec_tx_datos)
				{						
					case 0:
						TIEMPO_TX=TAREA_ADQ*1*0; // 0.013 s, 13.33ms
					break;
					case 1:
						TIEMPO_TX=TAREA_ADQ*1*15; // 0.2 s
					break;
					case 2:
						TIEMPO_TX=TAREA_ADQ*1*30; // 0.4 s
					break;
					case 3:
						TIEMPO_TX=TAREA_ADQ*1*60; // 0.8 s
					break;
					case 4:
						TIEMPO_TX=TAREA_ADQ*5*60;
					break;
					case 5:
						TIEMPO_TX=TAREA_ADQ*10*60;
					break;
					case 6:
						TIEMPO_TX=TAREA_ADQ*15*60;
					break;
					case 7:
						TIEMPO_TX=65535;		
					break;
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