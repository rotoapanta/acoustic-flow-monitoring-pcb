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

    
    // Inicializar el puerto UART para la comunicacion serial
    //Inicializar_UART(); 
    
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

