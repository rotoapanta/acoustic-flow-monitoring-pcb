/* Archivo de cabecera del gestor de interrupciones generado */
 
#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

/* Sección: Archivos Incluidos */

#include <xc.h>
#include <stdbool.h>

// variable puerto serial
volatile uint8_t dato_recibido = 0;

// Variable para cuantas de pluviometro
static uint8_t contador_pluviometro = 0;

 // cuentas ov para un segundo: 30.517578125
 // cuentas ov para un minuto: 1,831.0546875

/* variable para el timer 0*/
#define CUENTAS_DE_UN_SEGUNDO_T0  15        // 15, 1:2  para 1 segundo timer 0
#define CUENTAS_DE_UN_MINUTO_T0  915        // 915, 1:2  para 1 minuto timer 0
volatile uint16_t contador_segundos_t0=0;   // Contador de desbordamiento del timer 0
volatile uint16_t contador_minutos_t0=0;    // Contador de desbordamiento del timer 0
volatile uint16_t NUM_SEGUNDOS_T0 = 0;      // Numero de minutos poner aqui por ejemplo:
volatile uint16_t NUM_MINUTOS_T0 = 0;       // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_segundos_t0=0;      // NUM_MINUTO = 3; estos creando un intervalo
volatile float temp_num_minutos_t0=0;       // NUM_MINUTO = 3; estos creando un intervalo

/* variable para el timer 1*/
//#define CUENTAS_DE_UN_MINUTO  229         // 228.8818836, 1:8  para 1 minuto timer 1
#define CUENTAS_DE_UN_MINUTO  1831          // 1831, 1:1  para 1 minuto timer 1
volatile uint16_t contador_un_minutos=0;    // Contador de desbordamiento del timer 1
volatile uint16_t NUM_MINUTO = 0;           // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_minutos=0;          // NUM_MINUTO = 3; estos creando un intervalo

/* variable para el timer 2*/
#define CUENTAS_DE_UN_MINUTO_T2  1831       // 228.8818836, 1:16  para 1 minuto timer 1
volatile uint16_t contador_un_minutos_t2=0; // Contador de desbordamiento del timer 1
volatile uint16_t NUM_MINUTO_T2 = 0;        // Numero de minutos poner aqui por ejemplo:
volatile float temp_num_minutos_t2=0;       // NUM_MINUTO = 3; estos creando un intervalo

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

// funciones de interrpciones
#define Interrupcion_Global_Habilitar()         (INTCONbits.GIE = 1)
#define Interrupcion_Global_Deshabilitar()      (INTCONbits.GIE = 0)
#define Interrupcion_Periferica_Habilitar()     (INTCONbits.PEIE = 1)
#define Interrupcion_Periferica_Deshabilitar()  (INTCONbits.PEIE = 0)

// funcion para manejar todas las interupciones
void __interrupt() Manejador_de_Interrupciones (void);

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Atencion_Int_Timer_0(void);

// Rutina de interrupción de Timer 1 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_1(void);

// Rutina de interrupción de Timer 2 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_2(void);

// configurar interrupcion externa sobre puerto b
void Configurar_Interrupcion_Ext (void);

#endif  // INTERRUPT_MANAGER_H

/* Fin del documento */
 