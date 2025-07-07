
#include "adc.h"

void Configurar_ADC(void) {
    ADCON1bits.VCFG0 = 0; // Referencia negativa de voltaje en VSS (RA2)
    ADCON1bits.VCFG1 = 1; // Referencia positiva de voltaje en VREF+ (RA3)

    ADCON0bits.ADON = 1;    // Habilitar ADC
    
    ADCON0bits.CHS0 = 0;    // Seleccionar canal 0 (AN0/RA0)    
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    
    ADCON2bits.ADFM = 1;    // Resultado justificado a la derecha
    
    //ADCON2bits.ACQT = 1;  // Tiempo de adquisici�n 2Tad
    //ADCON2bits.ADCS = 2;  // Reloj de conversi�n Fosc/32

    ADCON2bits.ACQT = 0b111; // Tiempo de adquisici�n de 20 TAD
    ADCON2bits.ADCS = 0b110; // Tiempo de oscilaci�n del TAD: Fosc/64 (TAD = 8us con Fosc = 8MHz)

    // Habilitar interrupci�n del ADC
    PIE1bits.ADIE = 1;      // Habilitar interrupci�n del ADC
    IPR1bits.ADIP = 0;      // Prioridad baja para la interrupci�n del ADC
    PIR1bits.ADIF = 0;      // Limpiar la bandera de interrupci�n ADC
    
}

// Funci�n de lectura ADC
uint16_t Leer_ADC(void) {
    ADCON0bits.GO_DONE = 1;         // Iniciar la conversi�n
    while (ADCON0bits.GO_DONE);     // Esperar a que la conversi�n se complete
    return (uint16_t)(ADRESH << 8) | ADRESL;  // Devolver el resultado de la conversi�n
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
    
    