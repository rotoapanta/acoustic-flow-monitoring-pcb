#include "mcc.h"

//para el conversor y promedio
uint16_t dato_spi_temp_f = 0;         //variable temporal para lectura de datos		 
uint16_t dato_spi_temp_l = 0;         //variable temporal para lectura de datos		 
uint16_t dato_spi_temp_h = 0;         //variable temporal para lectura de datos		 

uint32_t dato_spi_full_band = 0;    //variables de almacenamiento temporal de 
uint32_t dato_spi_low_band = 0;		//los datos de cada canal
uint32_t dato_spi_high_band = 0;

uint16_t lectura_sensor_full_band = 0;
uint16_t lectura_sensor_low_band = 0;
uint16_t lectura_sensor_high_band = 0;

uint16_t check_sum_valor_calculado = 0;
uint8_t ALARMA_ACTIVA = 0;
uint16_t lectura_sensor_low_band_test = 0;

// Variables para lecctura del dip-switchs
uint8_t frecuencia_tx_datos_pc = 0;
bool HABILITAR_TX_DATOS_AFM = false;

bool HABILITAR_LECTURA_SENSOR = false;

bool HABILITAR_VERIFICAR_UMBRAL = false;


#define TIEMPO_UMBRAL 111           // 44.4s
uint16_t CONT_TIEMPO_UMBRAL = 0;

#define TIEMPO_CHEKEO 111
uint16_t CONT_TIEMPO_CHEKEO = 0;

uint8_t longitud_paq_datos = 0;

// Datos listos
bool DATOS_LISTOS_ADC_BAT = false;
bool DATOS_LISTOS_SENSOR_AFM = false;
bool DATOS_LISTOS_EMPAQUEADO = false;

// Variable para lectuda de canal 0 del ADC del PIC
double medida_nivel_bateria_flt = 0;
uint16_t medida_nivel_bateria_pc = 0;
uint16_t medida_nivel_bateria_dec = 0;

//volatile uint8_t numero_de_estacion_pc = 0;
char datos_sensores_afm_radio[60];
char datos_sensores_afm_pc[60];
char check_sum_str[9];

//definir el umbral
uint16_t NIVEL_UNBRAL_500MV = 6554;   //500mV

void main(void)
{  
    // inicializamos el dispositivo
    Inicializar_Sistema();

    //habilitar SPI
    SPI_Habilitado();
    UART_Deshabilitado();
    //RC7_Asignar_Como_RX()     //(TRISCbits.TRISC7 = 1)
    RC7_Asignar_Como_SDO();      //(TRISCbits.TRISC7 = 0)

	// Requerido por el ADC
	SPI_Enviar_Caracter(0xFF); 
	SPI_Enviar_Caracter(0xFF); 
	SPI_Enviar_Caracter(0xFF); 
	SPI_Enviar_Caracter(0xFF); 
	SPI_Enviar_Caracter(0xFF);
    
    // Para transmitir luego de arrancar el sistema
	HABILITAR_TX_DATOS_AFM = true;
    DATOS_LISTOS_ADC_BAT = false;
    DATOS_LISTOS_SENSOR_AFM = false;
    DATOS_LISTOS_EMPAQUEADO = false;

    SPI_Deshabilitado();
    UART_Habilitado();
    RC7_Asignar_Como_RX();     //(TRISCbits.TRISC7 = 1)
    ////RC7_Asignar_Como_SDO();      //(TRISCbits.TRISC7 = 0)

    // Habilita las interrupciones globales
    Interrupcion_Global_Habilitar();
    
    // Habilita las interrupciones periféricas
    Interrupcion_Periferica_Habilitar();
    
    // Tarea de transmision de datos
    HABILITAR_TAREA_MINUTOS_SOL = true;
    
    // habilitado unicamente para pruebas
    // desabilitar
    bool HABILITAR_ENVIAR_DATOS_PC = false;
    //
    while (true)
     {
        // t = x minutos
        if(HABILITAR_TAREA_MINUTOS_SOL && DATOS_LISTOS_EMPAQUEADO){ 
            HABILITAR_TAREA_MINUTOS_SOL = false;
            DATOS_LISTOS_EMPAQUEADO = false;
            
            uint8_t j = 0;
            // Habilitar UART
            SPI_Deshabilitado();
            UART_Habilitado();
            RC7_Asignar_Como_RX();
            
            for(j=0;j<29;j++){
                UART_Enviar_Caracter(datos_sensores_afm_radio[j]);
            }
            
            for(j=0;j<8;j++){
                UART_Enviar_Caracter(check_sum_str[j]);
            } 
            
            UART_Enviar_Cadena("\n");
            UART_Enviar_Cadena("\r");
                    
                    
            //UART_Enviar_Cadena(datos_sensores_afm_radio);            
            //UART_Enviar_Cadena(check_sum_str);

            //UART_Enviar_Cadena("\r");

            
            // habilitar cuando se este programando
            if(HABILITAR_ENVIAR_DATOS_PC){
                UART_Enviar_Cadena(datos_sensores_afm_pc);
                UART_Enviar_Cadena("\r");
            }
            DATOS_LISTOS_ADC_BAT = false;
            DATOS_LISTOS_SENSOR_AFM = false;
        }

        // 0.040 s -------------------------------------------------------------
        if(HABILITAR_TASK0) {
            HABILITAR_TASK0 = false;
            // lectura temporal del pluviometro FLANCO POSITIVO
            if (ENT_PLUVIO) {
                // Comprobar si la transición fue de positivo a negativo en RB5
                if (FLANCO_NEG) { 
                    // Incrementar contador_pluviometro
                    contador_pluviometro++; 
                    FLANCO_NEG = false;
                }
            } else{ FLANCO_NEG = true; }
            
            if(HABLILITAR_LECTURA_CH0) {
                // Lectura de nivel de voltaje de bateria
                // Lectura de canal 0 del adc
                suma_lectura_adc += Leer_ADC();
                if (contador_lectura_adc >= NUM_MUESTRAS) {
                    contador_lectura_adc = 0;
                    resultado_adc_flotante = (float)suma_lectura_adc / (float)NUM_MUESTRAS;
                    Lectura_ADC_CH0 = (uint16_t)(resultado_adc_flotante);
                    suma_lectura_adc = 0;                    
                
                    medida_nivel_bateria_flt = (float)((float)Lectura_ADC_CH0 * 15.0 / 1024.0);
                    // Para la pc, empaquetar en datos de afm
                    medida_nivel_bateria_dec = (uint16_t)(medida_nivel_bateria_flt * 250.0);

                    HABLILITAR_LECTURA_CH0 = false;
                    DATOS_LISTOS_ADC_BAT = true;


                }
                ADCON0bits.GO = 1;          // Iniciar la conversión
                contador_lectura_adc++; 
            }
            
            if(HABILITAR_LECTURA_SENSOR) {
                HABILITAR_LECTURA_SENSOR = false;
                SPI_Habilitado();
                UART_Deshabilitado();
                //RC7_Asignar_Como_RX()     //(TRISCbits.TRISC7 = 1)
                RC7_Asignar_Como_SDO();      //(TRISCbits.TRISC7 = 0)

                // Lectura del sensores de AFM
                uint8_t i = 0;              // para el for
                //configurar canal 1
                dato_spi_full_band = 0;     //para tomar nueva conversion
                SPI_Enviar_Caracter(0x20);	// CH 1, prox. op escribir en clock register
                SPI_Enviar_Caracter(0x0F);	// CLKDIV=1, CLK=1, salida 374Hz, cada 2.67ms 
                SPI_Enviar_Caracter(0x10);	// CH 1, prox. op escribir a setup register
                SPI_Enviar_Caracter(0x40); 	// ganancia=1, autocalibración, bipolar, BUF=0.
                while(DRDY);                // esperar que Data Ready sea cero
                for(i=0;i<NUM_MUESTRAS;i++){
                    SPI_Enviar_Caracter(0x38);	//ir al registro de datos
                    while(DRDY);               // esperar que Data Ready sea cero
                    dato_spi_temp_f=0;
                    dato_spi_temp_f =(uint16_t)(SPI_Recibir_Caracter()<<8);
                    dato_spi_temp_f+=(uint16_t)SPI_Recibir_Caracter();									
                    dato_spi_full_band+=dato_spi_temp_f;	
                }
                //configurar canal 2
                dato_spi_low_band = 0;      //para tomar nueva conversion
                SPI_Enviar_Caracter(0x21);	//CH 2, prox. op escribir en clock register
                SPI_Enviar_Caracter(0x0F);	//CLKDIV=1, CLK=1, 375 mps
                SPI_Enviar_Caracter(0x11);	//CH 2, prox. op escribir a setup register
                SPI_Enviar_Caracter(0x40); 	//ganancia=1, autocalibración, bipolar, BUF=0.
                while(DRDY);                // esperar que Data Ready sea cero
                for(i=0;i<NUM_MUESTRAS;i++){
                    SPI_Enviar_Caracter(0x39);	//ir al registro de datos
                    while(DRDY);               // esperar que Data Ready sea cero
                    dato_spi_temp_l=0;
                    dato_spi_temp_l = (uint16_t)SPI_Recibir_Caracter()<<8;
                    dato_spi_temp_l+= (uint16_t)SPI_Recibir_Caracter();			
                    dato_spi_low_band+=dato_spi_temp_l;
                }
                //configurar adc canal3
                dato_spi_high_band = 0;         //para tomar nueva conversion
                SPI_Enviar_Caracter(0x23);		//CH 3, prox. op escribir en clock register
                SPI_Enviar_Caracter(0x0F);		//CLKDIV=1, CLK=1, 375 mps
                SPI_Enviar_Caracter(0x13);		//CH 3, prox. op escribir a setup register
                SPI_Enviar_Caracter(0x40); 		//ganancia=1, autocalibración, bipolar, BUF=0.
                while(DRDY);                    // esperar que Data Ready sea cero
                for(i=0;i<NUM_MUESTRAS;i++) {
                    SPI_Enviar_Caracter(0x3B);	//ir al registro de datos
                    while(DRDY);               // esperar que Data Ready sea cero
                    dato_spi_temp_h=0;
                    dato_spi_temp_h = (uint16_t)SPI_Recibir_Caracter()<<8;
                    dato_spi_temp_h+= (uint16_t)SPI_Recibir_Caracter();									
                    dato_spi_high_band+=dato_spi_temp_h;
                }
                lectura_sensor_full_band= (uint16_t)(dato_spi_full_band / NUM_MUESTRAS);		
                lectura_sensor_low_band = (uint16_t)(dato_spi_low_band  / NUM_MUESTRAS);		
                lectura_sensor_high_band= (uint16_t)(dato_spi_high_band / NUM_MUESTRAS);

                // tomar este dato para verificar el umbral
                lectura_sensor_low_band_test = lectura_sensor_low_band;
                
                //lectura_sensor_low_band_test = 1000; // borrar linea solo test

                lectura_sensor_full_band = (uint16_t)((float)lectura_sensor_full_band / 13.107);
                lectura_sensor_low_band  = (uint16_t)((float)lectura_sensor_low_band  / 13.107);
                lectura_sensor_high_band = (uint16_t)((float)lectura_sensor_high_band / 13.107);
                
                // Datos listos de afm
                DATOS_LISTOS_SENSOR_AFM = true;
                
                // Datos leidos de sensor de afm, luego obligatorio
                // comprobar alguna alerta de lahar
                HABILITAR_VERIFICAR_UMBRAL = true;
                LED1 = !LED1;
            }
        }        
        
        // 0.106 s -------------------------------------------------------------
        if (HABILITAR_TASK1){
            HABILITAR_TASK1 = false;
            
            // Mostrar lectura del sensor de afm 
            LED2 = DRDY;
        }

        // 0.200 s -------------------------------------------------------------
        if(HABILITAR_TASK2){
            HABILITAR_TASK2 = false;
            
            num_de_estacion = Lectura_Numero_Est();             
            frec_tx_datos = Lectura_Frecuencia_tx();
            
            frecuencia_tx_datos_pc = (uint8_t)((float)(frec_tx_datos)*(float)(3.0));
            
            uint8_t k = 0;
            // empaquetar datos       
            if(DATOS_LISTOS_ADC_BAT && DATOS_LISTOS_SENSOR_AFM){
                
                check_sum_valor_calculado = 0;
                sprintf(datos_sensores_afm_radio,"%01d%02d +%04u +%04u +%04u +%04u c",
                    ALARMA_ACTIVA, num_de_estacion, 
                        lectura_sensor_full_band,
                        lectura_sensor_low_band,
                        lectura_sensor_high_band,
                        medida_nivel_bateria_dec);
                
                // Calculo de checksum
                for(k=0;k<29;k++){
                    check_sum_valor_calculado+= datos_sensores_afm_radio[k];
                }
                
                // Imprimir checksum
                sprintf(check_sum_str,"+%04u \n\r",check_sum_valor_calculado);                
                
                /*sprintf(datos_sensores_afm_pc," A:%01d P:%02d B:%2.1f B:%04d F:%02d N:%02u L:%04u H:%04u F:%04u",
                    ALARMA_ACTIVA, contador_pluviometro, medida_nivel_bateria_flt,
                    medida_nivel_bateria_pc, frecuencia_tx_datos_pc, num_de_estacion, 
                    lectura_sensor_low_band, 
                    lectura_sensor_high_band, 
                    lectura_sensor_full_band);*/
            }
            DATOS_LISTOS_EMPAQUEADO = true;   
        }

        // 0.400 s ------------------------------------------------------------
        // 111ciclos = 44.4s
        if(HABILITAR_TASK3){
            HABILITAR_TASK3 = false;
            // Habilitar lectura de nivel de bateria
            HABLILITAR_LECTURA_CH0 = true;
            // Habilitar lectura de sensor de afm
            HABILITAR_LECTURA_SENSOR = true;
            
            //verificar umbral
            if(HABILITAR_VERIFICAR_UMBRAL){
                HABILITAR_VERIFICAR_UMBRAL = false;   // LowBand
                if(NIVEL_UNBRAL_500MV<=lectura_sensor_low_band_test){
                    CONT_TIEMPO_UMBRAL++;
                    // verificar si se mantiene 44.4s sobre el valor umbral
                    if(TIEMPO_UMBRAL<=CONT_TIEMPO_UMBRAL){
                        CONT_TIEMPO_UMBRAL = 0;
                        // transmision de datos de afm cada 1s                
                        Asignar_Minutos_Timer0(0.0164);
                        // Activar bandera de alarma
                        ALARMA_ACTIVA = 1;
                    }
                }
                else{// Desactivar bandera de alarma
                    ALARMA_ACTIVA = 0;
                    CONT_TIEMPO_UMBRAL = 0;
                     frec_tx_datos = Lectura_Frecuencia_tx();
                     
                    if(frec_tx_datos == 0){ // HABILITAR_TAREA_MINUTOS_SOL
                        Asignar_Minutos_Timer0(0.0164);
                    }
                    else{                   // HABILITAR_TAREA_MINUTOS_SOL
                        Asignar_Minutos_Timer0(frecuencia_tx_datos_pc);
                    }
                }
            }
            //verificar tiempo de mantenimiento de senal
            //permite verificar que la senal se mantiene 44.4 s
//            if(CONT_TIEMPO_UMBRAL!=0){
//                CONT_TIEMPO_CHEKEO++;
//            }
//            if(TIEMPO_CHEKEO<=CONT_TIEMPO_CHEKEO){
//                CONT_TIEMPO_CHEKEO=0;
//                CONT_TIEMPO_UMBRAL=0;		//no permite entrar en alerta
//            }
        }

        // 0.800 s ------------------------------------------------------------
        if(HABILITAR_TASK4){
            HABILITAR_TASK4 = false;
            
//            if(DATOS_LISTOS_EMPAQUEADO){
//                DATOS_LISTOS_EMPAQUEADO = false;
//                // Habilitar UART
//                SPI_Deshabilitado();
//                UART_Habilitado();
//                RC7_Asignar_Como_RX();     //(TRISCbits.TRISC7 = 1)
//                UART_Enviar_Cadena(datos_sensores_afm_pc);
//                UART_Enviar_Cadena("\r");                
//            }
        }
        /* Fin Tarea 3*/
    }
}

/* Fin del documento */