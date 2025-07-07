#ifndef TIMERS_H
#define	TIMERS_H

/* Secci�n: Archivos Incluidos */

#include <xc.h>
//#include <stdint.h>
//#include <stdbool.h>




// Funciones para configurar cada timer del PIC18F2550 

// Funci�n para generar intervalos de tiempo con Timer 0 utilizando interrupciones para generar de 1 a 100 segundos
void Configurar_Timer0(void);

// Funci�n para generar intervalos de tiempo con Timer 1 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Timer1(void);

// Funci�n para generar intervalos de tiempo con Timer 2 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Timer2();


#endif // TIMERS_H
/* Fin de documento */


