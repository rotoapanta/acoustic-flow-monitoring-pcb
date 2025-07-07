#include <xc.h>
#include "device_config.h"

// Configuración del oscilador interno a 8MHz y desactivacion del puerto USB

void Inicializar_Oscilador(void){
    //OSCCONbits.IRCF = 0b111;    // Frecuencia de oscilación: 8 MHz
    OSCCONbits.IRCF = 0b000;    // Frecuencia de oscilación: 31 kHz
    UCFGbits.UTRDIS = 1;        // Desactivar puerto USB
    UCONbits.USBEN = 0;         // Deshabilitar módulo USB
}
