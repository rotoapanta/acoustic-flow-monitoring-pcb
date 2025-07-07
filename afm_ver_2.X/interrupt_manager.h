/* Archivo de cabecera del gestor de interrupciones generado */

#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

/* Sección: Archivos Incluidos */

#include <xc.h>
#include <stdbool.h>

// variables para el ADC del PIC
#define NUM_MUESTRAS 15
volatile uint16_t Lectura_ADC_CH0 = 0;
static uint8_t  contador_lectura_adc = 0;
static uint32_t suma_lectura_adc = 0;
static float    resultado_adc_flotante = 0;
volatile bool   HABLILITAR_LECTURA_CH0 = false;

// Variables para el pluviometro
#define ENT_PLUVIO  PORTBbits.RB5
volatile bool FLANCO_NEG = false;
// Variable para cuantas de pluviometro
volatile uint8_t contador_pluviometro = 0;

// multi tasking con timer 0
// Declaración de banderas como volatile
// para el control de la tareas
volatile bool HABILITAR_TASK0 = false;
volatile bool HABILITAR_TASK1 = false;
volatile bool HABILITAR_TASK2 = false;
volatile bool HABILITAR_TASK3 = false;
volatile bool HABILITAR_TASK4 = false;
volatile bool HABILITAR_TASK5 = false;
volatile bool HABILITAR_TASK6 = false;
volatile bool HABILITAR_TASK7 = false;
volatile bool HABILITAR_TASK8 = false;
volatile bool HABILITAR_TASK9  = false;
volatile bool HABILITAR_TASK10 = false;

// Contador de minutos
volatile bool HABILITAR_TAREA_MINUTOS_SOL = false;
#define CUENTAS_DE_UN_MINUTO_T0  562        // 562, 1:8  para 1 minuto timer 0
volatile double temp_num_minutos_t0 = 0;    //
volatile uint16_t contador_minutos_t0=0;    // Contador de desbordamiento del timer 0

// Xtal de 19.6608MHz, tov = 13.33333333 ms, 75tov = 1s, 4500tov = 1 min
// 0 a 15 minutos, timer 2 no usar para minutos
// timer 2 usar para tareas


#define TASK0    3         // 0.040 s
#define TASK1    8         // 0.106 s
#define TASK2    15        // 0.200 s
#define TASK3    30        // 0.400 s
#define TASK4    60        // 0.800 s
#define TASK5    120       // 1.600 s
#define TASK6    240       // 3.200 s
#define TASK7    480       // 6.400 s
#define TASK8    960       //  s 
#define TASK9    1920      //  s 

// contador de desbordamiento del timer para calcular
// el tiempo de cada tarea
volatile uint16_t   cont_task0 = 0;
volatile uint16_t   cont_task1 = 0;
volatile uint16_t   cont_task2 = 0;
volatile uint16_t   cont_task3 = 0;
volatile uint16_t   cont_task4 = 0;
volatile uint16_t   cont_task5 = 0;
volatile uint16_t   cont_task6 = 0;
volatile uint16_t   cont_task7 = 0;
volatile uint16_t   cont_task8 = 0;
volatile uint16_t   cont_task9  = 0;
volatile uint16_t   cont_task10 = 0;

#define Interrupcion_Global_Habilitar()         (INTCONbits.GIE = 1)
#define Interrupcion_Global_Deshabilitar()      (INTCONbits.GIE = 0)
#define Interrupcion_Periferica_Habilitar()     (INTCONbits.PEIE = 1)
#define Interrupcion_Periferica_Deshabilitar()  (INTCONbits.PEIE = 0)

// funcion para manejar todas las interupciones
void __interrupt(high_priority) high_isr(void);
void __interrupt(low_priority) low_isr(void);

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Atencion_Int_Timer_0(void);

// Rutina de interrupción de Timer 2 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_2(void);

// configurar interrupcion externa sobre puerto b
//void Config_Interrupcion_de_Pluvio (void);

//void Atencion_Int_RB(void);


#endif  // INTERRUPT_MANAGER_H

/* Fin del documento */
 