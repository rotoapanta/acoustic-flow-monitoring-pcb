/* configurador de códigos mplab */

#ifndef MCC_H
#define	MCC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "device_config.h"
#include "pin_manager.h" 
#include "interrupt_manager.h"
#include "timers.h"
#include "serial.h"
#include "adc.h"

/* Inicializa el dispositivo a los estados predeterminados configurados 
   en la GUI de MCC */
void Inicializar_Sistema(void);

// Función de retardo de 1 ms sin timers
void DelayMs(uint16_t tiempo_ms);

// Asignar tiempo en segundos a timer 0
void Asignar_Segundos_Timer0(uint8_t segundos);

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer0(uint8_t minutos);

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer2(uint8_t minutos);



#endif	/* MCC_H */

/* Fin del documento */
 
 
