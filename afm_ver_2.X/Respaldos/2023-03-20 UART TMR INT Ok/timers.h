#ifndef TIMERS_H
#define	TIMERS_H

/* Sección: Archivos Incluidos */

#include <xc.h>
//#include <stdint.h>
//#include <stdbool.h>

// Funciones para configurar cada timer del PIC18F2550 

// Función para generar intervalos de tiempo con Timer 0 utilizando interrupciones para generar de 1 a 100 segundos
void Configurar_Timer0(void);

// Asignar tiempo en segundos a timer 0
void Asignar_Segundos_Timer0(uint8_t segundos);

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer0(uint8_t minutos);

// Función para generar intervalos de tiempo con Timer 1 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Timer1(void);

// Función para generar intervalos de tiempo con Timer 2 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Timer2();

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer2(uint8_t minutos);


#endif // TIMERS_H
/* Fin de documento */


