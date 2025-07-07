/* Archivo fuente del gestor de interrupciones generado */

#include "interrupt_manager.h"
#include "mcc.h"

// funcion que maneja todas las interrupciones

void __interrupt() Manejador_de_Interrupciones (void)
{
    if (INTCONbits.TMR0IF) { // Verifica si la bandera de interrupción de Timer 0 está activa
        Interrupcion_de_Timer_0(); // Llama a la rutina de interrupción de Timer 0
    }
    else if (PIR1bits.TMR1IF) { // Verifica si la bandera de interrupción de Timer 1 está activa
        Interrupcion_de_Timer_1(); // Llama a la rutina de interrupción de Timer 1
    }
    else if (PIR1bits.TMR2IF) { // Verifica si la bandera de interrupción de Timer 2 está activa
        Interrupcion_de_Timer_2(); // Llama a la rutina de interrupción de Timer 2
    }
}



// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Interrupcion_de_Timer_0(void) {
    
    TMR0L = 0; // Reinicializa el contador de Timer 0

    INTCONbits.TMR0IF =0; // Limpia la bandera de interrupción de Timer 0
    
    // Inserta aquí el código que se ejecutará cada intervalo de tiempo de Timer 0
    
     //LED_LTX = !LED_LTX;
     LED_LFN = !LED_LFN;
     //LED_TMP = !LED_TMP;
    
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
                
     LED_LTX = !LED_LTX;
     //LED_LFN = !LED_LFN;
     //LED_TMP = !LED_TMP;
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
                
     //LED_LTX = !LED_LTX;
     //LED_LFN = !LED_LFN;
     LED_TMP = !LED_TMP;
    }
    else{
        contador_un_minutos_t2++;
    }
}


/* Fin del documento */