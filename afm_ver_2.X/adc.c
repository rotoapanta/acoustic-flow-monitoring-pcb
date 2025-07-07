
#include "adc.h"
#include <stdbool.h>

void Configurar_ADC(void) {
    
    // Configurar ADC
    ADCON1bits.VCFG0 = 1;       // Configurar Vref- como VSS
    ADCON1bits.VCFG1 = 1;       // Configurar Vref+ como Vref+ externo (RA3)
    ADCON1bits.PCFG = 0b1110;   // Configurar AN0 como entrada analógica, el resto como digital

    // Configurar el módulo ADC
    ADCON2bits.ADFM = 1;        // Resultado justificado a la derecha
                                //101 = 12 TAD
                                //011 = 6 TAD
                                //111 = 20 TAD  
    ADCON2bits.ACQT = 0b110;    // Tiempo de adquisición de 16 TAD
    ADCON2bits.ADCS = 0b101;    // Tiempo de oscilación del TAD: Fosc/16 (TAD = 13us con Fosc = 19.6608MHz)    
   
    ADCON0bits.CHS0 = 0;        // Seleccionar canal 0 (AN0/RA0)    
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
  
    // Habilitar interrupción del ADC
    //PIE1bits.ADIE = 1;      // Habilitar interrupción del ADC
    //IPR1bits.ADIP = 1;      // Prioridad alta para la interrupción del ADC
    //PIR1bits.ADIF = 0;      // Limpiar la bandera de interrupción ADC

    ADCON0bits.ADON = 1;        // Encender el módulo ADC    
    ADCON0bits.GO = 1; // Iniciar la conversión
}

// Función de lectura ADC
uint16_t Leer_ADC(void) {
    ADCON0bits.GO_DONE = 1;         // Iniciar la conversión
    while (ADCON0bits.GO_DONE);     // Esperar a que la conversión se complete
    return (uint16_t)(ADRESH << 8) | ADRESL;  // Devolver el resultado de la conversión
}

// bit 1 GO/DONE: A/D Conversion Status bit
// When ADON = 1:
// 1 = A/D conversion in progress
// 0 = A/D Idle
// bit 0 ADON: A/D On bit
// 1 = A/D converter module is enabled
// 0 = A/D converter module is disabled

// PIR1bits.ADIF = 0/1;
// ADIF: A/D Converter Interrupt Flag bit
// 1 = An A/D conversion completed (must be
// 0 = The A/D conversion is not complete

// PIE1bits.ADIE = 0/1;
// ADIE: A/D Converter Interrupt Enable bit
// 1 = Enables the A/D interrupt
// 0 = Disables the A/D interrupt
    

