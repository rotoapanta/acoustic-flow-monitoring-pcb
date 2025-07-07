/* Archivo de encabezado del administrador de PIN  */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/* Sección: Archivos Incluidos */

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG  1
#define DIGITAL 0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

/* variable para el timer 1*/
#define CUENTAS_DE_UN_MINUTO  229           // 228.8818836, 1:8  para 1 minuto timer 1
#define CUENTAS_DE_UN_MINUTO  1831           // 228.8818836, 1:1  para 1 minuto timer 1
volatile uint16_t contador_un_minutos=0;    // Contador de desbordamiento del timer 1
volatile uint16_t NUM_MINUTO = 0;           // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_minutos=0;          // NUM_MINUTO = 3; estos creando un intervalo
                                            // de tiempo de 3 minutos


/* variable para el timer 2*/
#define CUENTAS_DE_UN_MINUTO_T2  1831           // 228.8818836, 1:16  para 1 minuto timer 1
volatile uint16_t contador_un_minutos_t2=0;    // Contador de desbordamiento del timer 1
volatile uint16_t NUM_MINUTO_T2 = 0;           // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_minutos_t2=0;          // NUM_MINUTO = 3; estos creando un intervalo



//8_t frec_tx_datos = 0;



/* Control de los LEDs */

#define LED_LFN     LATBbits.LATB3
#define LED_LTX     LATBbits.LATB4

// led temporal borrar para usar rs-232
#define LED_TMP     LATBbits.LATB5


#define	SCLK LATBbits.LATB1     //SCK
#define	SDI  LATBbits.LATB0     //SDI
#define	SDO  LATBbits.LATC7     //SDO
#define	DRDY LATBbits.LATB2     //DATA READY

#define LFN  LATBbits.LATB3     //led de fuincionamiento normal
#define LTX	 LATBbits.LATB4     //led de transmision

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


// get/set D2_LED aliases
/*
#define D2_LED_TRIS                 TRISAbits.TRISA4
#define D2_LED_LAT                  LATAbits.LATA4
#define D2_LED_PORT                 PORTAbits.RA4
#define D2_LED_WPU                  WPUAbits.WPUA4
#define D2_LED_OD                   ODCONAbits.ODCA4
#define D2_LED_ANS                  ANSELAbits.ANSA4
#define D2_LED_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define D2_LED_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define D2_LED_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define D2_LED_GetValue()           PORTAbits.RA4
#define D2_LED_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define D2_LED_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define D2_LED_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define D2_LED_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define D2_LED_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define D2_LED_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define D2_LED_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define D2_LED_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
*/

/* Inicialización de E/S periférica y GPIO */
// Funcion para configurar los pines como entradas o salidas

void PIN_MANAGER_Initialize (void);

#endif // PIN_MANAGER_H
/* Fin de documento */