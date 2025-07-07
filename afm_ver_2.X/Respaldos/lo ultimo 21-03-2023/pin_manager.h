/* Archivo de encabezado del administrador de PIN  */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h> // incluir archivos de procesador 
#include <stdbool.h>

/* Sección: Archivos Incluidos */

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG  1
#define DIGITAL 0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

/* Control de los LEDs */

#define LED_LFN     LATBbits.LATB3
#define LED_LTX     LATBbits.LATB4
#define LED_LTM     LATAbits.LATA6

// Forzar transmision rs-232

#define ENT_PLUVIO  LATBbits.LATB5

#define	SCLK LATBbits.LATB1         //SCK
#define	SDI  LATBbits.LATB0         //SDI
#define	SDO  LATBbits.LATC7         //SDO
#define	DRDY LATBbits.LATB2         //DATA READY

#define LFN  LATBbits.LATB3         //led de fuincionamiento normal
//#define LTX	 LATBbits.LATB4     //led de transmision

// Leer los pines RC0, RC1, RC2 y RC5, almacenarlos en frec_tx_datos
//frec_tx_datos = 
#define	F0 PORTCbits.RC0
#define	F1 PORTCbits.RC1
#define	F2 PORTCbits.RC2 
#define	F3 PORTCbits.RC5
                              
// Leer los pines RC4, RA1, RA4 y RA5, almacenarlos en num_de_estacion
//num_de_estacion = 
#define	H0 PORTCbits.RC4
#define	H1 PORTAbits.RA1
#define	H2 PORTAbits.RA4
#define	H3 PORTAbits.RA5
                        
//LATBbits.LATB2 = !LATBbits.LATB2;
//LATBbits.LATB2 ^= 1; // Alterna el estado del bit correspondiente en el registro LATB
//LED_DS1 ^= 1; // Alterna el estado del bit correspondiente en el registro LATB

/* Inicialización de E/S periférica y GPIO */
// Funcion para configurar los pines como entradas o salidas

void Inicializar_Administrador_PIN (void);

#endif // PIN_MANAGER_H
/* Fin de documento */