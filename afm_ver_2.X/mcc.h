/* configurador de códigos mplab */

#ifndef MCC_H
#define	MCC_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "device_config.h"
#include "pin_manager.h" 
#include "interrupt_manager.h"
#include "timers.h"
#include "serial.h"
#include "adc.h"
#include "spi.h"

/* Inicializa el dispositivo a los estados predeterminados configurados 
   en la GUI de MCC */
void Inicializar_Sistema(void);

// Función de retardo de 1 ms sin timers
void DelayMs(uint16_t tiempo_ms);

#endif	/* MCC_H */

/* Fin del documento */
