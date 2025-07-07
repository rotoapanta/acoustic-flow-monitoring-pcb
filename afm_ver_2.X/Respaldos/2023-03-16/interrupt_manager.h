/* Archivo de cabecera del gestor de interrupciones generado */
 
#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)


#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)


// funcion para manejar todas las interupciones
void __interrupt() Manejador_de_Interrupciones (void);

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Interrupcion_de_Timer_0(void);

// Rutina de interrupción de Timer 1 para generar intervalos de tiempo de 1 a 30 minutos
void Interrupcion_de_Timer_1(void);

// Rutina de interrupción de Timer 2 para generar intervalos de tiempo de 1 a 30 minutos
void Interrupcion_de_Timer_2(void);

#endif  // INTERRUPT_MANAGER_H

/* Fin del documento */
