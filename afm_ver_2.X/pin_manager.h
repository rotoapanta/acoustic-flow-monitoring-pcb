/* Archivo de encabezado del administrador de PIN  */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>
#include <stdbool.h>

// Control de los LEDs
#define LED1    LATBbits.LATB3
#define LED2    LATBbits.LATB4
#define LED3    LATAbits.LATA6

// UART
#define RC7_Asignar_Como_RX() (TRISCbits.TRISC7 = 1)
#define RC7_Asignar_Como_SDO() (TRISCbits.TRISC7 = 0)

// Leer los pines RC0, RC1, RC2 y RC5
//num_de_estacion = 
#define	H0 PORTCbits.RC0
#define	H1 PORTCbits.RC1
#define	H2 PORTCbits.RC2 
#define	H3 PORTCbits.RC5
                              
// Leer los pines RC4, RA1, RA4 y RA5
//frec_tx_datos = 
#define	F0 PORTCbits.RC4
#define	F1 PORTAbits.RA1
#define	F2 PORTAbits.RA4
#define	F3 PORTAbits.RA5

volatile uint8_t frec_tx_datos = 0;

volatile uint8_t num_de_estacion = 0;

// lectura de dip switches

uint8_t Lectura_Frecuencia_tx(void);

uint8_t Lectura_Numero_Est(void);


void Inicializar_Administrador_PIN (void);

#endif // PIN_MANAGER_H
/* Fin de documento */