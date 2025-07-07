#include "pin_manager.h"

// Funcion para configurar los pines como entradas o salidas

// lectura de dip switches

// frec_tx_datos
uint8_t Lectura_Frecuencia_tx(void){
    return (F0*1 + F1*2 + F2*4 + F3*8); 
}

// num_de_estacion
uint8_t Lectura_Numero_Est(void){
    return (H0*1 + H1*2 + H2*4 + H3*8);
}

void Inicializar_Administrador_PIN(void)
{
// Configuracion de puertos como entrada/salida

    // Puerto SPI
    TRISBbits.TRISB0 = 1;       // Entrada SDI  SPI 
    TRISBbits.TRISB1 = 0;		// Salida  SCK  SPI
    TRISBbits.TRISB2 = 1;		// Entrada DRDY SPI
    // LED1
    TRISBbits.TRISB3 = 0;       // RB3 como salida
    // LED2
    TRISBbits.TRISB4 = 0;       // RB4 como salida
    TRISBbits.TRISB5 = 1;       // RB5 como entrada KBI1
    //TRISBbits.TRISB5 = 0;     // RB5 como salida
        
    // Configuración de los puertos RC0, RC1, RC2 y RC5
    TRISCbits.TRISC0 = 1;       // F0 RC0 como entrada
    TRISCbits.TRISC1 = 1;       // F1 RC1 como entrada
    TRISCbits.TRISC2 = 1;       // F2 RC2 como entrada

    // Deshabilita las interrupciones no mascarables NMI
    UCFGbits.UTRDIS  = 1;       // TRISCbits.TRISC5 y TRISCbits.TRISC4 = 1;     
                                // F3 RC5 como entrada
                                // H0 RC4 como entrada
    // Configuración de los puertos RC6 y RC7
    TRISCbits.TRISC6 = 1;       // TX como salida del UART
    TRISCbits.TRISC7 = 1;       // SDO del SPI y   RX UART
    

    // Configuracion de puertos analogicos
    TRISAbits.TRISA0 = 1;       // Configurar RA0 como entrada (AN0)
    TRISAbits.TRISA1 = 1;       // H1 Configurar RA1 como entrada digital
    TRISAbits.TRISA2 = 1;       // Configurar RA2 como entrada (Vref-)
    TRISAbits.TRISA3 = 1;       // Configurar RA3 como entrada (Vref+)
    TRISAbits.TRISA4 = 1;       // H2 Configurar RA4 como entrada digital
    TRISAbits.TRISA5 = 1;       // H3 Configurar RA5 como entrada digital
    // LED3
    TRISAbits.TRISA6 = 0;       // Configurar RA6 como entrada digital
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ cambiar a entrada para	
}

//#define	SCLK PORTBbits.RB1     //SCK salida
//#define	SDI  LATBbits.LATB0     //SDI  entrada
//#define	SDO  LATCbits.LATC7     //SDO salida
//#define	DRDY PORTBbits.RB2     //DATA READY entrada