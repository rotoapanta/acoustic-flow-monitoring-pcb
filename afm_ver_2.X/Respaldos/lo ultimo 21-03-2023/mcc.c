/* configurador de códigos mplab */

#include "mcc.h"

/* Inicializa el dispositivo a los estados predeterminados configurados 
   en la GUI de MCC */
void Inicializar_Sistema(void)
{
    /* Interrupcion en la rutina de manejo de cambios */
    Inicializar_Administrador_PIN();
    
    // Configuración del oscilador interno a 8MHz y deshabilitación del USB
    Inicializar_Oscilador();
    
    // Espera a que el oscilador interno se estabilice 
    while(!OSCCONbits.IOFS);

    // Configurar interrupción externa en RB5
    //Config_Interrupcion_de_Pluvio();
    
    // Timer 0 da retardos en segundo y minutos
    Configurar_Timer0();
    
    // Contar 6 segundos
    Asignar_Segundos_Timer0(6);
    
    // Contar 3 minutos
    //Asignar_Minutos_Timer0(3);
    
    // timer 2 en minutos
    Configurar_Timer2();
    
    // medir 3 minutos en timer 2
    Asignar_Minutos_Timer2(3);

    // configurar interrupciones externas
    
    //Configurar_Interrupcion_Ext();
    
    
    // Configurar adc para canal 0, RA2 = ref-, RA3 = ref+ (+2.5)
    Configurar_ADC();
            
    // Inicializar el puerto UART para la comunicacion serial
    Inicializar_UART(); 
    
}

// Función de retardo de 1 ms sin timers
void DelayMs(uint16_t tiempo_ms) {
    uint16_t i, j;
    for (i = 0; i < tiempo_ms; i++) {
        for (j = 0; j < 165; j++) {
            Nop();
            Nop();
            Nop();
        }
    }
}

// Asignar tiempo en segundos a timer 0
void Asignar_Segundos_Timer0(uint8_t segundos){
    // Cantidad de segundo a contar en timer 0
    NUM_SEGUNDOS_T0 = segundos;
}

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer0(uint8_t minutos){
    // Cantidad de minutos a contar en timer 0
    NUM_MINUTOS_T0 = minutos;
}

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer2(uint8_t minutos){
    // Cantidad de minutos a contar en timer 0
    NUM_MINUTO_T2 = minutos;    // Asignar intervalo a T2
}



/* Fin del documento */

