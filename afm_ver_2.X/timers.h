#ifndef TIMERS_H
#define	TIMERS_H

/* Secci�n: Archivos Incluidos */
#include <xc.h>
//#include <stdint.h>
//#include <stdbool.h>


/* variable para el timer 0*/
volatile double   NUM_MINUTOS_T0 = 0;       // Numero de minutos poner aqui por ejemplo:

// Funciones para configurar cada timer del PIC18F2550 

// Funci�n para generar intervalos de tiempo con Timer 0 utilizando interrupciones para generar de 1 a 100 segundos
void Configurar_Timer0(void);

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer0(double minutos);

// Funci�n para generar intervalos de tiempo con Timer 2 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Timer2(void);


#endif // TIMERS_H
/* Fin de documento */


