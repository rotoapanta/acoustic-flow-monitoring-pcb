#ifndef TIMERS_H
#define	TIMERS_H

/* Sección: Archivos Incluidos */

#include <xc.h>
//#include <stdint.h>
//#include <stdbool.h>

// Funciones para configurar cada timer del PIC18F2550 

// Función para generar intervalos de tiempo con Timer 0 utilizando interrupciones para generar de 1 a 100 segundos
void Configurar_Tiempo_Timer0(uint8_t segundos);

// Función para generar intervalos de tiempo con Timer 1 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Tiempo_Timer1(uint8_t minutos);

// Función para generar intervalos de tiempo con Timer 2 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Tiempo_Timer2(uint8_t minutos);


#endif // TIMERS_H
/* Fin de documento */


