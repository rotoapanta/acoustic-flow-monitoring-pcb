#include "timers.h"
#include "pin_manager.h"

// Configuración de oscilador interno a 8MHz
// #define SYS_FREQ 8000000L
// #define FCY SYS_FREQ/4

// Función para generar intervalos de tiempo con Timer 0 utilizando interrupciones para generar de 1 a 100 segundos

// Configuracion del Timer 0 para intervalos de tiempo de 1 a 100 segundos
// cuentas ov 1 s: 15.2587890625, cuentas 1 min:  915.52734375
// Frecuencia del reloj: 8 MHz
// Frecuencia del reloj interno (FOSC/4): 8 MHz / 4 = 2 MHz
// Frecuencia después del preescalador: 2 MHz / 256 = 7812.5 Hz
// Tiempo entre cuentas: 1 / 7812.5 Hz = 128 us

void Configurar_Timer0(void) {
    T0CONbits.T08BIT = 0;    // Timer 0 en modo 16 bits
    T0CONbits.T0CS = 0;      // Utiliza el reloj interno (Fosc/4) como fuente de reloj
    T0CONbits.PSA = 0;       // Asigna el preescaler a Timer 0
    //T0CONbits.T0PS = 0b111;  // Preescaler a 256
    T0CONbits.T0PS = 0b000;  // Preescaler 1 : 2
    
    TMR0H = 0x00;
    TMR0L = 0x00;  
    T0CONbits.TMR0ON = 1; // Enciende Timer 0
    INTCONbits.TMR0IF =0; // Limpia la bandera de interrupción de Timer 0
    INTCONbits.TMR0IE = 1; // Habilita las interrupciones por Timer 0
}

// Función para generar intervalos de tiempo con Timer 1 utilizando interrupciones para generar de 1 a 30 minutos
// Frecuencia del reloj: 8 MHz
// Frecuencia del reloj interno (FOSC/4): 8 MHz / 4 = 2 MHz
// Frecuencia después del preescalador: 2 MHz / 8 = 250,000 Hz
// Tiempo entre cuentas: 1 / 250,000 Hz = 4 us

void Configurar_Tiempo_Timer1(void) {
    
    T1CON = 0; // Limpia el registro T1CON
    T1CONbits.TMR1ON = 0; // Desactiva el Timer 1
    T1CONbits.TMR1CS = 0; // Selecciona el reloj interno (FOSC/4)
    //T1CONbits.T1CKPS = 0b11; // Configura el preescalador a 1:8
    T1CONbits.T1CKPS = 0b00; // Configura el preescalador a 1:1

    TMR1H = 0x00;
    TMR1L = 0x00;

    T1CONbits.TMR1ON = 0;   // 0 Desactiva el Timer 1
                            // 1 Activa el Timer 1
    PIR1bits.TMR1IF = 0;    // Limpia la bandera de interrupción por Timer 1
    PIE1bits.TMR1IE = 0;    // 0 Deshabilita las interrupciones por Timer 1
                            // 1 Habilita las interrupciones por Timer 1
}

// Función para generar intervalos de tiempo con Timer 2 utilizando interrupciones para generar de 1 a 30 minutos

// Frecuencia del reloj: 8 MHz
// Frecuencia del reloj interno (FOSC/4): 8 MHz / 4 = 2 MHz
// Frecuencia después del preescalador: 2 MHz / 16 = 125,000 Hz
// Tiempo entre cuentas: 1 / 125,000 Hz = 8 us

  
void Configurar_Tiempo_Timer2(uint8_t minutos){
if (minutos < 1 || minutos > 30) {
        return; // Valida que los minutos estén en el rango de 1 a 30
    }

    // Asignar intervalo a T2
     NUM_MINUTO_T2 = minutos;

    T2CON = 0; // Limpia el registro T2CON
    T2CONbits.TMR2ON = 0; // Desactiva el Timer 2
    T2CONbits.T2CKPS = 0b11; // Configura el preescalador a 1:16

    // Configurar PR2
    PR2 = 255;

    // 1831 es el numero de desvordamiento del timer 2 para un minuto
   
    // Configurar postscaler
    T2CONbits.TOUTPS = 0b1111; // Establece el valor del postscaler a 16
    PIR1bits.TMR2IF = 0; // Limpia la bandera de interrupción por Timer 2
    PIE1bits.TMR2IE = 1; // Habilita las interrupciones por Timer 2
    T2CONbits.TMR2ON = 1; // Activa el Timer 2
}

// Asignar tiempo en segundos a timer 0

void Asignar_Segundos_Timer0(uint8_t segundos){
    
    // Cantidad de segundo a contar en timer 0
    NUM_SEGUNDOS_T0 = segundos;
}

// Asignar tiempo en minutos a timer 0

void Asignar_Minutos_Timer0(uint8_t minutos){
    
    // Cantidad de minutos a contar en timer 0
    NUM_MINUTOS_T0 = minutos;
}
