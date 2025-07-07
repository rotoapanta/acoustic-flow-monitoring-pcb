#include "mcc.h"

//para el conversor y promedio
uint16_t dato_spi_temp = 0;         //variable temporal para lectura de datos		 
uint32_t dato_spi_full_band = 0;    //variables de almacenamiento temporal de 
uint32_t dato_spi_low_band = 0;		//los datos de cada canal
uint32_t dato_spi_high_band = 0;
uint16_t lectura_sensor_full_band = 0;
uint16_t lectura_sensor_low_band = 0;
uint16_t lectura_sensor_high_band = 0;
uint16_t check_sum_valor_calculado = 0;

// Variables para lecctura del dip-switchs
uint8_t frecuencia_tx_datos_pc = 0;
bool HABILITAR_PRIMERA_TX = false;

// Variable para lectuda de canal 0 del ADC del PIC
float medida_nivel_bateria = 0;
uint16_t medida_nivel_bateria_dec = 0;

//volatile uint8_t numero_de_estacion_pc = 0;
char datos_sensores_afm[60] = "0";

//definir el umbral
uint16_t UNBRAL_500MV = 6554;   //500mV

void main(void)
{  
    // inicializamos el dispositivo
    Inicializar_Sistema();

    //ADCON1=0x0F;		//config AN0 ... AN12 todos I/O	
    
    // Deshabilitar UART
    
    Puerto_Serie_232_Deshabilitado();
    
    //para transmitir luego de arrancar el sistema
	HABILITAR_PRIMERA_TX = true;

    // Requerido por el ADC
//	SPI_Enviar_Caracter(0xFF); 
//	SPI_Enviar_Caracter(0xFF); 
//	SPI_Enviar_Caracter(0xFF); 
//	SPI_Enviar_Caracter(0xFF); 
//	SPI_Enviar_Caracter(0xFF); 
//    
    // Habilita las interrupciones globales
    Interrupcion_Global_Habilitar();
    
    // Habilita las interrupciones periféricas
    Interrupcion_Periferica_Habilitar();
    
    while (true)
     {
        // t = x minutos
        if(HABILITAR_TAREA_MINUTOS_SOL){ 
            HABILITAR_TAREA_MINUTOS_SOL = false;
            UART_Enviar_Cadena(" TASK MIN \r\n");
            
        }

        // t = X s
        if(HABILITAR_TAREA_SEGUNDOS_SOL){
            HABILITAR_TAREA_SEGUNDOS_SOL = false;
            
        }

        // 0.131 s -------------------------------------------------------------
        if(HABILITAR_TASK0) {
            HABILITAR_TASK0 = false;
            // lectura temporal del pluviometro
            if (!ENT_PLUVIO) {
                // Comprobar si la transición fue de positivo a negativo en RB5
                if (!FLANCO_NEG) { 
                    // Incrementar contador_pluviometro
                    contador_pluviometro++; 
                    FLANCO_NEG = true;
                }
            } else{ FLANCO_NEG = false; }             
        }        
        
        // 0.262 s -------------------------------------------------------------
        if (HABILITAR_TASK1){ 
            HABILITAR_TASK1 = false;
            // Lectura de nivel de voltaje de bateria
            // Lectura de canal 0 del adc
            suma_lectura_adc += Leer_ADC();
            if (contador_lectura_adc >= NUM_MUESTRAS){
                contador_lectura_adc = 0;
                resultado_adc_flotante = (float)suma_lectura_adc / (float)NUM_MUESTRAS;
                Lectura_ADC_CH0 = (uint16_t)(resultado_adc_flotante);
                suma_lectura_adc = 0;
            }
            ADCON0bits.GO = 1;          // Iniciar la conversión
            contador_lectura_adc++; 
            // Lectura del sensores de AFM
        }
        
        // 0.524 s -------------------------------------------------------------
        if(HABILITAR_TASK2){
            HABILITAR_TASK2 = false;
            //Puerto_Serie_232_Deshabilitado();
            uint8_t i = 0;
            LED1 = 1;
//			//configurar canal 1
//            dato_spi_full_band = 0;     //para tomar nueva conversion
//			SPI_Enviar_Caracter(0x20);	// CH 1, prox. op escribir en clock register
//			SPI_Enviar_Caracter(0x0F);	// CLKDIV=1, CLK=1, 375 mps
//			SPI_Enviar_Caracter(0x10);	// CH 1, prox. op escribir a setup register
//			SPI_Enviar_Caracter(0x40); 	// ganancia=1, autocalibración, bipolar, BUF=0.
//
//			while(DRDY);               // esperar que Data Ready sea cero
//            LED2 = 1;  
//
//
//			for(i=0;i<NUM_MUESTRAS;i++)
//			{
//				SPI_Enviar_Caracter(0x38);	//ir al registro de datos
//				while(DRDY);
//				dato_spi_temp=0;
//				dato_spi_temp =(uint16_t)(SPI_Recibir_Caracter()<<8);
//				dato_spi_temp+=SPI_Recibir_Caracter();									
//				dato_spi_full_band+=dato_spi_temp;	
//			}
//            
//            LED3 = 1; 
//
//			//configurar canal 2
//            dato_spi_low_band = 0;      //para tomar nueva conversion
//			SPI_Enviar_Caracter(0x21);	//CH 2, prox. op escribir en clock register
//			SPI_Enviar_Caracter(0x0F);	//CLKDIV=1, CLK=1, 375 mps
//			SPI_Enviar_Caracter(0x11);	//CH 2, prox. op escribir a setup register
//			SPI_Enviar_Caracter(0x40); 	//ganancia=1, autocalibración, bipolar, BUF=0.
//			while(DRDY);
//			for(i=0;i<NUM_MUESTRAS;i++)
//			{
//				SPI_Enviar_Caracter(0x39);	//ir al registro de datos
//				while(DRDY);
//				dato_spi_temp=0;
//				dato_spi_temp =(uint16_t)(SPI_Recibir_Caracter()<<8);
//				dato_spi_temp+=SPI_Recibir_Caracter();			
//				dato_spi_low_band+=dato_spi_temp;
//			}
//			
//			//configurar adc canal3
//            dato_spi_high_band = 0;         //para tomar nueva conversion
//			SPI_Enviar_Caracter(0x23);		//CH 3, prox. op escribir en clock register
//			SPI_Enviar_Caracter(0x0F);		//CLKDIV=1, CLK=1, 375 mps
//			SPI_Enviar_Caracter(0x13);		//CH 3, prox. op escribir a setup register
//			SPI_Enviar_Caracter(0x40); 		//ganancia=1, autocalibración, bipolar, BUF=0.
//			while(DRDY);
//			for(i=0;i<NUM_MUESTRAS;i++)
//			{
//				SPI_Enviar_Caracter(0x3B);	//ir al registro de datos
//				while(DRDY);
//				dato_spi_temp=0;
//				dato_spi_temp =(uint16_t)(SPI_Recibir_Caracter()<<8);
//				dato_spi_temp+=SPI_Recibir_Caracter();									
//				dato_spi_high_band+=dato_spi_temp;
//			}
//
//            lectura_sensor_full_band=(uint16_t)(dato_spi_full_band / 50);		
//			lectura_sensor_low_band =(uint16_t)(dato_spi_low_band / 50);		
//			lectura_sensor_high_band=(uint16_t)(dato_spi_high_band / 50);
//			
//			// tomar este dato para verificar el umbral
//			dato_spi_low_band = lectura_sensor_low_band;
//			
//			lectura_sensor_full_band/=13.107;
//			lectura_sensor_low_band/= 13.107;
//			lectura_sensor_high_band/=13.107;  
            
            LED1 = 0;
        }

        //  1.049 s ------------------------------------------------------------
        if(HABILITAR_TASK3){
            HABILITAR_TASK3 = false;
            // Deshabilitar UART
            Puerto_Serie_232_Habilitado();
            num_de_estacion = Lectura_Numero_Est();             
            frec_tx_datos = Lectura_Frecuencia_tx();
            frecuencia_tx_datos_pc = (uint8_t)((float)(frec_tx_datos)*(float)(3.0));
            
            //medida_nivel_bateria = (float)((float)resultado_lecturas_adc_ch0 * 15.0 * 250/ 1023.0);
            medida_nivel_bateria = (float)((float)Lectura_ADC_CH0 * 15.0 * 1.1 / 1023.0);
            
            if(frec_tx_datos == 0){
                // HABILITAR_TAREA_MINUTOS_SOL
                Asignar_Minutos_Timer2(0.0164);
            }
            else{
                // HABILITAR_TAREA_MINUTOS_SOL
                Asignar_Minutos_Timer2(frecuencia_tx_datos_pc);
                Asignar_Segundos_Timer0(frec_tx_datos);
            }
            sprintf(datos_sensores_afm,"PLV: %d BAT: %.1f FTD:%02d NE:%02d T:%.0f T:%.0f %lu\r\n",
                    contador_pluviometro, medida_nivel_bateria,frecuencia_tx_datos_pc,
                    num_de_estacion, temp_num_minutos_t2,NUM_MINUTO_T2,contador_minutos_t2);
            UART_Enviar_Cadena(datos_sensores_afm);
            
        }
        /* Fin Tarea 3*/
    }
}

/* Fin del documento */