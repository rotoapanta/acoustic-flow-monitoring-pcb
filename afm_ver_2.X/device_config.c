#include <xc.h>
#include "device_config.h"

// Configuraci�n del oscilador interno a 8MHz y desactivacion del puerto USB

void Inicializar_Oscilador(void){
    //OSCCONbits.IRCF = 0b111;    // Frecuencia de oscilaci�n: 8 MHz
    OSCCONbits.IRCF = 0b000;    // Frecuencia de oscilaci�n: 31 kHz
    UCFGbits.UTRDIS = 1;        // Desactivar puerto USB
    UCONbits.USBEN = 0;         // Deshabilitar m�dulo USB
}
