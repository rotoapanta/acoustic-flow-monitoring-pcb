#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>

// variables para el adc
#define  NUM_MUESTRAS_ADC_CH0 9
//static uint8_t      contador_de_muestras = 0;
//static uint32_t     suma_lecturas_adc_ch0 = 0;
//volatile uint16_t   resultado_lecturas_adc_ch0 = 0;

void Configurar_ADC(void);

uint16_t Leer_ADC(void);

#endif	/* ADC_H */