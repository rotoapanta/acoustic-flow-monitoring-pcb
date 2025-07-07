/* configurador de c�digos mplab */

#include "mcc.h"

/* Inicializa el dispositivo a los estados predeterminados configurados 
   en la GUI de MCC */
void SYSTEM_Initialize(void)
{
    /* Interrupcion en la rutina de manejo de cambios */
    PIN_MANAGER_Initialize();
    
     // Configuraci�n del oscilador interno a 8MHz y deshabilitaci�n del USB
    OSCILLATOR_Initialize();

    // Espera a que el oscilador interno se estabilice 
    while(!OSCCONbits.IOFS);
   
}

// Funci�n de retardo de 1 ms sin timers
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

