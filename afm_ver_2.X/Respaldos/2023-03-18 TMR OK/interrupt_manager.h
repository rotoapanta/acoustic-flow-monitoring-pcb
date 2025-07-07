/* Archivo de cabecera del gestor de interrupciones generado */
 
#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

/* Sección: Archivos Incluidos */

//#include <xc.h>

#define Interrupcion_Global_Habilitar()         (INTCONbits.GIE = 1)
#define Interrupcion_Global_Deshabilitar()      (INTCONbits.GIE = 0)
#define Interrupcion_Periferica_Habilitar()     (INTCONbits.PEIE = 1)
#define Interrupcion_Periferica_Deshabilitar()  (INTCONbits.PEIE = 0)

// funcion para manejar todas las interupciones
void __interrupt() Manejador_de_Interrupciones (void);

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Atencion_Int_Timer_0(void);

// Rutina de interrupción de Timer 1 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_1(void);

// Rutina de interrupción de Timer 2 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_2(void);

#endif  // INTERRUPT_MANAGER_H

/* Fin del documento */
 