/* Archivo de encabezado del administrador de PIN  */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/* Sección: Archivos Incluidos */

#include <xc.h>
#include <stdbool.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG  1
#define DIGITAL 0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0
 
 // cuentas ov para un segundo: 30.517578125
 // cuentas ov para un minuto: 1,831.0546875

/* variable para el timer 0*/
//#define CUENTAS_DE_UN_SEGUNDO_T0  15            // 30, 1:2  para 1 segundo timer 0
#define CUENTAS_DE_UN_MINUTO_T0  915            // 915, 1:2  para 1 minuto timer 0
volatile uint16_t contador_segundos_t0=0;       // Contador de desbordamiento del timer 0
volatile uint16_t contador_minutos_t0=0;        // Contador de desbordamiento del timer 0
volatile uint16_t NUM_SEGUNDOS_T0 = 0;           // Numero de minutos poner aqui por ejemplo:
volatile uint16_t NUM_MINUTOS_T0 = 0;           // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_segundos_t0=0;          // NUM_MINUTO = 3; estos creando un intervalo
volatile float temp_num_minutos_t0=0;          // NUM_MINUTO = 3; estos creando un intervalo


/* variable para el timer 1*/
//#define CUENTAS_DE_UN_MINUTO  229           // 228.8818836, 1:8  para 1 minuto timer 1
#define CUENTAS_DE_UN_MINUTO  1831           // 1831, 1:1  para 1 minuto timer 1
volatile uint16_t contador_un_minutos=0;    // Contador de desbordamiento del timer 1
volatile uint16_t NUM_MINUTO = 0;           // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_minutos=0;          // NUM_MINUTO = 3; estos creando un intervalo
                                            // de tiempo de 3 minutos

/* variable para el timer 2*/
#define CUENTAS_DE_UN_MINUTO_T2  1831           // 1831, 1:16  para 1 minuto timer 1
volatile uint16_t contador_un_minutos_t2=0;    // Contador de desbordamiento del timer 1
volatile uint16_t NUM_MINUTO_T2 = 0;           // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_minutos_t2=0;          // NUM_MINUTO = 3; estos creando un intervalo

// multi tasking con timer 0
// Declaración de banderas como volatile
// para el control de la tareas
volatile bool HABILITAR_TASK1 = false;
volatile bool HABILITAR_TASK2 = false;
volatile bool HABILITAR_TASK3 = false;
volatile bool HABILITAR_TASK4 = false;
volatile bool HABILITAR_TASK5 = false;
volatile bool HABILITAR_TASK6 = false;
volatile bool HABILITAR_TASK7 = false;
volatile bool HABILITAR_TASK8 = false;
volatile bool HABILITAR_TASK9 = false;
volatile bool HABILITAR_TASK10 = false;
volatile bool HABILITAR_TASK11 = false;

#define TASK1     2       // 0.131 s
#define TASK2     4       // 0.262 s
#define TASK3     8       // 0.524 s
#define TASK4     16      // 1.049 s
#define TASK5     32      // 2.097 s
#define TASK6     64      // 4.194 s
#define TASK7     128     // 8.389 s
#define TASK8     256     // 16.777 s
#define TASK9     512     // 33.554 s 
#define TASK10    1024    // 67.109 s 
#define TASK11    2048    // 134.218 s

// contador de desbordamiento del timer para calcular
// el tiempo de cada tarea
volatile uint16_t   cont_task1 = 0;
volatile uint16_t   cont_task2 = 0;
volatile uint16_t   cont_task3 = 0;
volatile uint16_t   cont_task4 = 0;
volatile uint16_t   cont_task5 = 0;
volatile uint16_t   cont_task6 = 0;
volatile uint16_t   cont_task7 = 0;
volatile uint16_t   cont_task8 = 0;
volatile uint16_t   cont_task9 = 0;
volatile uint16_t   cont_task11 = 0;
volatile uint16_t   cont_task12 = 0;

// variable puerto serial

volatile uint8_t dato_recibido = 0;

// Variable para cuantas de pluviometro
volatile uint8_t contador_pluviometro = 0;


/* Control de los LEDs */

#define LED_LFN     LATBbits.LATB3
//#define LED_LTX     LATBbits.LATB4

// Forzar transmision rs-232

#define ENT_PLUVIO  LATBbits.LATB5


#define	SCLK LATBbits.LATB1     //SCK
#define	SDI  LATBbits.LATB0     //SDI
#define	SDO  LATBbits.LATC7     //SDO
#define	DRDY LATBbits.LATB2     //DATA READY

#define LFN  LATBbits.LATB3     //led de fuincionamiento normal
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
                        

/* Inicialización de E/S periférica y GPIO */
// Funcion para configurar los pines como entradas o salidas

void Inicializar_Administrador_PIN (void);

#endif // PIN_MANAGER_H
/* Fin de documento */