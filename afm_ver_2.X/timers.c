 #include "timers.h"

// Prescaler 1:8 y xtal de 19.6608MHz, tov = 106.666667 ms, 9,375tov = 1s, 562,5tov = 1 min
// capacidad de 0 a 100 minutos
void Configurar_Timer0(void) {
    T0CONbits.T08BIT = 0;       // Timer 0 en modo 16 bits
    T0CONbits.T0CS = 0;         // Utiliza el reloj interno (Fosc/4) como fuente de reloj
    T0CONbits.PSA = 0;          // Asigna el preescaler a Timer 0
    T0CONbits.T0PS = 0b010;     // Preescaler 1 : 2    
    TMR0H = 0x00;
    TMR0L = 0x00;  
    T0CONbits.TMR0ON = 1;       // Enciende Timer 0
    INTCONbits.TMR0IF =0;       // Limpia la bandera de interrupción de Timer 0
    //INTCONbits.TMR0IE = 1;    // Habilita las interrupciones por Timer 
    INTCONbits.T0IE = 1;        // Habilitar interrupción del Timer 0
    INTCON2bits.TMR0IP = 0;     // Configurar TMR1 como interrupción de baja prioridad
    //TMR0IP: TMR0 Overflow Interrupt Priority bit
    //1 = High priority
    //0 = Low priority    
}

// Asignar tiempo en minutos a timer 0
void Asignar_Minutos_Timer0(double minutos){
    // Cantidad de minutos a contar en timer 0
    NUM_MINUTOS_T0 = minutos;
}

// Xtal de 19.6608MHz, tov = 13.33333333 ms, 75tov = 1s, 4500tov = 1 min
// 0 a 15 minutos, timer 2 no usar para minutos
// timer 2 usar para tareas
void Configurar_Timer2(void){
    T2CON = 0;                  // Limpia el registro T2CON
    T2CONbits.TMR2ON = 0;       // Desactiva el Timer 2
    T2CONbits.T2CKPS = 0b11;    // Configura el preescalador a 1:16
    PR2 = 255; 
    T2CONbits.TOUTPS = 0b1111;  // Establece el valor del postscaler a 16
    PIR1bits.TMR2IF = 0;        // Limpia la bandera de interrupción por Timer 2
    PIE1bits.TMR2IE = 1;        // Habilitar interrupción del Timer 2
    T2CONbits.TMR2ON = 1;       // Activa el Timer 2
    IPR1bits.TMR2IP = 0;        // baja prioridad en atencion a la interrupcion
    TMR2 = 0;                  // Limpiar registro TMR2
}
