/* Archivo de administrador de PIN generado */

#include "pin_manager.h"

/* Inicializacion de los registros de LAT y TRIS de los puertos GPIO 
 * (General Purpose Input/Output) */

// Funcion para configurar los pines como entradas o salidas
                               
void PIN_MANAGER_Initialize(void)
{
// Configuracion de puertos como entrada/salida
    
    // Configuración de los puertos RC6 y RC7
    TRISCbits.TRISC6 = 0;   // RC6 como salida (TX)
    TRISCbits.TRISC7 = 1;   // RC7 como entrada (RX)
    
    // Configuración de los puertos RB3, RB4 y RB5
    TRISBbits.TRISB3 = 0;   // RB3 como salida
    TRISBbits.TRISB4 = 0;   // RB4 como salida
    //TRISBbits.TRISB5 = 1;   // RB5 como entrada
    TRISBbits.TRISB5 = 0;   // RB5 como salida
    
    // Configuración de los puertos RC0, RC1, RC2 y RC5
    TRISCbits.TRISC0 = 1;   // RC0 como entrada
    TRISCbits.TRISC1 = 1;   // RC1 como entrada
    TRISCbits.TRISC2 = 1;   // RC2 como entrada
    UCFGbits.UTRDIS = 1;    // Deshabilita las interrupciones no mascarables NMI
    //Hace que TRISCbits.TRISC5 = 1;   // RC5 como entrada
    
    // Configuración de los puertos RC4, RA1, RA4 y RA5
    
    // hace que TRISCbits.TRISC4 = 1;   // RC4 como entrada    
    TRISAbits.TRISA1 = 1;   // RA1 como entrada
    TRISAbits.TRISA4 = 1;   // RA4 como entrada
    TRISAbits.TRISA5 = 1;   // RA5 como entrada
    
    // Configuración del puerto RA0 para canal AN0 del ADC
    TRISAbits.TRISA0 = 1;   // RA0 como entrada
    
    // Configuracion de puertos analogicos

}

/* Fin del documento */
