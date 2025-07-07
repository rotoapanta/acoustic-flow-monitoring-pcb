/* Archivo fuente del gestor de interrupciones generado */

#include "mcc.h"
#include "interrupt_manager.h"
//#include <stdbool.h>


// subrutinas de interrupciones

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Interrupcion_de_Timer_0(void) {
    
    TMR0L = 0; // Reinicializa el contador de Timer 0
    INTCONbits.TMR0IF =0; // Limpia la bandera de interrupción de Timer 0
    
    // tarea 1, 0.131 s
    if( cont_task1 >= TASK1 ) { cont_task1 = 0; HABILITAR_TASK1 = true; }
    else{ cont_task1++;}

    // tarea 2, 0.262 s
    if( cont_task2 >= TASK2 ) { cont_task2 = 0; HABILITAR_TASK2 = true; }
    else{ cont_task2++;}

    // tarea 3, 0.524 s
    if( cont_task3 >= TASK3 ) { cont_task3 = 0; HABILITAR_TASK3 = true; 
     //UART_Enviar_Cadena("Hola Mundo! \n");
    }  //LED_LFN = !LED_LFN; }
    else{ cont_task3++; }

    // Calcular tiempo en minutos
    temp_num_segundos_t0 = CUENTAS_DE_UN_SEGUNDO_T0*NUM_SEGUNDOS_T0;
    
    if(contador_segundos_t0 >= (uint16_t)(temp_num_segundos_t0)){
        contador_segundos_t0 = 0;
         //LED_LTX = !LED_LTX;   //LED_TMP = !LED_TMP;
    }
    else{ contador_segundos_t0++; }

}

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 minutos
void Interrupcion_de_Timer_1(void) {
    //TMR1L = 0;               // Inicializa el contador de Timer 1
    //TMR1H = 0;               // Inicializa el contador de Timer 1
    
    PIR1bits.TMR1IF = 0; // Limpia la bandera de interrupción de Timer 0
    
    // Inserta aquí el código que se ejecutará cada intervalo de tiempo de Timer 0
    
    // Calcular tiempo en minutos
    temp_num_minutos = CUENTAS_DE_UN_MINUTO*NUM_MINUTO;
    
    if(contador_un_minutos >= (uint16_t)(temp_num_minutos)){
        contador_un_minutos = 0;
        //LED_LTX = !LED_LTX;
    }
    else{
        contador_un_minutos++;
    }
}

// Rutina de interrupción de Timer 2 para generar intervalos de tiempo de 1 a 30 minutos
void Interrupcion_de_Timer_2(void){
    
     PIR1bits.TMR2IF = 0; // Limpia la bandera de interrupción por Timer 2
     
     // Calcular tiempo en minutos
    temp_num_minutos_t2 = CUENTAS_DE_UN_MINUTO_T2*NUM_MINUTO_T2;
    
    if(contador_un_minutos_t2 >= (uint16_t)(temp_num_minutos_t2)){
        contador_un_minutos_t2 = 0;
        
        //LED_LTX = !LED_LTX;  //LED_LFN = !LED_LFN; //LED_TMP = !LED_TMP;
    }
    else{
        contador_un_minutos_t2++;
    }
}


// Rutina de interrupcion para pluviometro en RB5
void Config_Interrupcion_de_Pluvio(void){

    // Configurar interrupción externa en RB5
    
    contador_pluviometro = 0;   // contador del pluvio
    
    INTCON2bits.RBPU = 0;   // Los pull-ups de PORTB están habilitados por 
                            // valores de pestillo de puerto individuales
    
    //INTCON2bits.INTEDG0 = 0;    // Interrupción en transición negativa
    //INTCON2bits.INTEDG1 = 0;    // Interrupción en transición negativa
    //INTCON2bits.INTEDG2 = 0;    // Interrupción en transición negativa
        
    INTCONbits.RBIF = 0;    // Al menos uno de los pines RB7:RB4 cambió de estado  

    // Configurar KBI1 (RB5)
    //INTCON3bits.INT1IE = 1; // Habilitar interrupción KBI1 en RB5
    //INTCON2bits.INTEDG1 = 0; // Generar interrupción en flanco descendente
    //INTCON3bits.INT1IF = 0; // Borrar bandera de interrupción

    INTCONbits.RBIE = 1;    //Habilita la interrupción de cambio de puerto RB

    
}




/* Fin del documento */



