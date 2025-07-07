#include <xc.h>
#include "device_config.h"

// Configuración del oscilador interno a 8MHz y desactivacion del puerto USB

void Inicializar_Oscilador(void){
    OSCCONbits.IRCF = 0b111;    // Frecuencia de oscilación: 8MHz
    //OSCCON = 0b01110000;      // Configura el oscilador interno a 8MHz
    UCFGbits.UTRDIS = 1;        // Desactivar puerto USB
    UCONbits.USBEN  = 0;        // Deshabilita el modulo USB 
}
