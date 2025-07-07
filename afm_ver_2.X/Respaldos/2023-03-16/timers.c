#include "timers.h"
#include "pin_manager.h"

// Configuración de oscilador interno a 8MHz
// #define SYS_FREQ 8000000L
// #define FCY SYS_FREQ/4

// Función para generar intervalos de tiempo con Timer 0 utilizando interrupciones para generar de 1 a 100 segundos

// Configuracion del Timer 0 para intervalos de tiempo de 1 a 100 segundos
void Configurar_Tiempo_Timer0(uint8_t segundos) {
    if (segundos < 1 || segundos > 30) {
        return; // Valida que los segundos estén en el rango de 1 a 30
    }
    T0CONbits.T08BIT = 0;    // Timer 0 en modo 16 bits
    T0CONbits.T0CS = 0;      // Utiliza el reloj interno (Fosc/4) como fuente de reloj
    T0CONbits.PSA = 0;       // Asigna el preescaler a Timer 0
    T0CONbits.T0PS = 0b111;  // Preescaler a 256

    // Frecuencia del reloj: 8 MHz
    // Frecuencia del reloj interno (FOSC/4): 8 MHz / 4 = 2 MHz
    // Frecuencia después del preescalador: 2 MHz / 256 = 7812.5 Hz
    // Tiempo entre cuentas: 1 / 7812.5 Hz = 128 us
    // Cuentas para 10 segundos: 10 s / 128 us = 78,125 cuentas
    // Valor inicial de TMR0: 2^16 - 78,125 = 65,536 - 78,125 = 57,411 (0xE17B)

    uint32_t cuentas = (uint32_t)segundos * 1000000 / 128; // Calcula las cuentas necesarias
    uint32_t valor_inicial = 65536 - cuentas; // Calcula el valor inicial de TMR0

    TMR0H = (uint8_t)(valor_inicial >> 8); // Carga el valor inicial del contador en TMR0H (parte alta)
    TMR0L = (uint8_t)(valor_inicial & 0xFF); // Carga el valor inicial del contador en TMR0L (parte baja)
    
    T0CONbits.TMR0ON = 1; // Enciende Timer 0

    INTCONbits.TMR0IF =0; // Limpia la bandera de interrupción de Timer 0
    
    INTCONbits.TMR0IE = 1; // Habilita las interrupciones por Timer 0
}

// Función para generar intervalos de tiempo con Timer 1 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Tiempo_Timer1(uint8_t minutos) {
    if (minutos < 1 || minutos > 30) {
       return; // Valida que los minutos estén en el rango de 1 a 30
   }
    NUM_MINUTO = minutos;
    
    T1CON = 0; // Limpia el registro T1CON
    T1CONbits.TMR1ON = 0; // Desactiva el Timer 1
    T1CONbits.TMR1CS = 0; // Selecciona el reloj interno (FOSC/4)
    //T1CONbits.T1CKPS = 0b11; // Configura el preescalador a 1:8
    T1CONbits.T1CKPS = 0b00; // Configura el preescalador a 1:1

    // Frecuencia del reloj: 8 MHz
    // Frecuencia del reloj interno (FOSC/4): 8 MHz / 4 = 2 MHz
    // Frecuencia después del preescalador: 2 MHz / 8 = 250,000 Hz
    // Tiempo entre cuentas: 1 / 250,000 Hz = 4 us

    //uint32_t cuentas = (uint32_t)minutos * 60 * 1000000 / 4; // Calcula las cuentas necesarias para los minutos
    //uint32_t valor_inicial = 65536 - (cuentas % 65536); // Calcula el valor inicial de TMR1
    
    // 228.8818836  cuentas para 1 minuto 1:8

    // 1831.05469  cuentas para 1 minuto 1:8

    //TMR1H = (uint8_t)(valor_inicial >> 8); // Carga el valor inicial del contador en TMR1H (parte alta)
    //TMR1L = (uint8_t)(valor_inicial & 0xFF); // Carga el valor inicial del contador en TMR1L (parte baja)
    TMR1H = 0x00;
    TMR1L = 0x00;

    T1CONbits.TMR1ON = 1; // Activa el Timer 1

    PIR1bits.TMR1IF = 0; // Limpia la bandera de interrupción por Timer 1
    
    PIE1bits.TMR1IE = 1; // Habilita las interrupciones por Timer 1
}

// Función para generar intervalos de tiempo con Timer 2 utilizando interrupciones para generar de 1 a 30 minutos
void Configurar_Tiempo_Timer2(uint8_t minutos){
if (minutos < 1 || minutos > 30) {
        return; // Valida que los minutos estén en el rango de 1 a 30
    }

    // Asignar intervalo a T2
     NUM_MINUTO_T2 = minutos;

    T2CON = 0; // Limpia el registro T2CON
    T2CONbits.TMR2ON = 0; // Desactiva el Timer 2
    T2CONbits.T2CKPS = 0b11; // Configura el preescalador a 1:16

    // Frecuencia del reloj: 8 MHz
    // Frecuencia del reloj interno (FOSC/4): 8 MHz / 4 = 2 MHz
    // Frecuencia después del preescalador: 2 MHz / 16 = 125,000 Hz
    // Tiempo entre cuentas: 1 / 125,000 Hz = 8 us

    uint8_t postscaler = (uint8_t)(minutos * 60* 1000 / 8) - 1; // Calcula el valor del postscaler para los minutos

    // Configurar PR2
    //uint8_t valor_PR2 = 255; // Establece el valor de PR2 en 255
    PR2 = 255;  //valor_PR2;

    
    // numero de desvordamiento del timer 2 para un minuto
    //
    
    // Configurar postscaler
    T2CONbits.TOUTPS = 0b1111; // Establece el valor del postscaler a 16

    PIR1bits.TMR2IF = 0; // Limpia la bandera de interrupción por Timer 2
    
    PIE1bits.TMR2IE = 1; // Habilita las interrupciones por Timer 2
   
    T2CONbits.TMR2ON = 1; // Activa el Timer 2
}

