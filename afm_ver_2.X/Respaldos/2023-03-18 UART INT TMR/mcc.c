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
    Config_Interrupcion_de_Pluvio();
    
    // Timer 0 en segundo y minutos
    // 3 TASK, 
    Configurar_Timer0();
    
    // Contar 12 segundos
    Asignar_Segundos_Timer0(6);
    
    // Contar 3 minutos
    Asignar_Minutos_Timer0(1);
    
    // timer 2 en minutos
    //Configurar_Tiempo_Timer2(1);  //  minutos
    
    // Inicializar el puerto UART para la comunicacion serial
    Inicializar_UART(); 
    
    
    // Configurar interrupciones
    //  
    
    //RCONbits.IPEN = 1;   // Habilitar prioridades en interrupciones
    //INTCONbits.GIEH = 1; // Habilitar interrupciones de alta prioridad
    //INTCONbits.GIEL = 1; // Habilitar interrupciones de baja prioridad
    
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

/* Fin del documento */

