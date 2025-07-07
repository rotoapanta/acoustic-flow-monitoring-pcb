#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  

// variables para el adc

//#define NUM_MUESTRAS 6
//static uint16_t Lectura_ADC_CH0 = 0;
//static uint8_t contador_lectura_adc = 0;
//static uint32_t suma_lectura_adc = 0;
//static float resultado_adc_flotante = 0;

void Configurar_ADC(void);



uint16_t Leer_ADC(void);

#endif	/* ADC_H */

