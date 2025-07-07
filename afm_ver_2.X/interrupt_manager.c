/* Archivo fuente del gestor de interrupciones generado */
#include "interrupt_manager.h"
#include "timers.h"
#include "serial.h"
#include "pin_manager.h"

void __interrupt(high_priority) high_isr(void){
}

void __interrupt(low_priority) low_isr(void){
    Interrupcion_Global_Deshabilitar();   

    // verificar interrupcion en timer 0
    if (INTCONbits.TMR0IF) { // Verifica si la bandera de interrupción de Timer 0 está activa
        Atencion_Int_Timer_0(); // Llama a la rutina de interrupción de Timer 0
    }

    // verificar interrupcion en timer 2       
    if (PIR1bits.TMR2IF) { // Verifica si la bandera de interrupción de Timer 2 está activa
        Atencion_Int_Timer_2(); // Llama a la rutina de interrupción de Timer 2
    }
            
    // Recibir caracter por puerto UART
    if (PIR1bits.RCIF && PIE1bits.RCIE) {
        // Leer y almacenar el dato recibido en la variable global
        dato_recibido = RCREG;
        //UART_Enviar_Caracter(dato_recibido);
        // Limpiar la bandera de interrupcion
        PIR1bits.RCIF = 0;
    }
    Interrupcion_Global_Habilitar();
}

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Atencion_Int_Timer_0(void) {
    
    TMR0L = 0; // Reinicializa el contador de Timer 0
    INTCONbits.TMR0IF =0; // Limpia la bandera de interrupción de Timer 0
    
    // Calcular tiempo en minutos
    temp_num_minutos_t0 = (double)(CUENTAS_DE_UN_MINUTO_T0*NUM_MINUTOS_T0);
    if(contador_minutos_t0 >= (uint16_t)(temp_num_minutos_t0)){
        contador_minutos_t0 = 0;
        HABILITAR_TAREA_MINUTOS_SOL = true;
        // LED2 = !LED2;
    }
    else{ contador_minutos_t0++; }
}

// Rutina de interrupción de Timer 2 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_2(void){    
     PIR1bits.TMR2IF = 0; // Limpia la bandera de interrupción por Timer 2
     // Calcular tiempo en minutos

     // tarea 0, 0.04 s
    if( cont_task0 >= TASK0 ) {
        cont_task0 = 0;
        HABILITAR_TASK0 = true; 
    }
    else{ cont_task0++;}
    
     // tarea 1, // 0.106 s
    if( cont_task1 >= TASK1 ) {
        cont_task1 = 0;
        HABILITAR_TASK1 = true;
    }
    else{ cont_task1++;}

    // tarea 2, 0.200 s
    if( cont_task2 >= TASK2 ) {
        cont_task2 = 0; 
        HABILITAR_TASK2 = true;
    }
    else{ cont_task2++;}

    // tarea 3, 0.400 s
    if( cont_task3 >= TASK3 ) { 
        cont_task3 = 0; 
        HABILITAR_TASK3 = true;
    }
    else{ cont_task3++; }

     // tarea 4, 0.800 s
    if( cont_task4 >= TASK4 ) { 
        cont_task4 = 0; 
        HABILITAR_TASK4 = true;
    }
    else{ cont_task4++; }

}

//void Config_Interrupcion_de_Pluvio (void)
//{
//    INTCONbits.GIE = 0;     // Desactivar todas las interrupciones
//    INTCON2bits.RBPU = 0;   // Habilitar pull-up interno en Puerto B
//    //INTCONbits.RBIE = 1;    // Habilitar interrupción por cambio en el puerto B
//    INTCONbits.RBIF = 0;    // Limpiar flag de interrupción del puerto B
//    INTCON2bits.RBIP = 0;   // Configurar interrupción del puerto B como baja prioridad
//    INTCONbits.GIE = 1;     // Habilitar interrupciones globales
//
//}

//void Atencion_Int_RB(void){
//    if (INTCONbits.RBIF) { // Verificar si la interrupción fue causada por cambio de estado en Puerto B
//        if (!ENT_PLUVIO) { // Comprobar si la transición fue de positivo a negativo en RB5
//            contador_pluviometro++; // Incrementar contador_pluviometro
//        }
//        INTCONbits.RBIF = 0; // Limpiar la bandera de interrupción
//    }
//}

/* Fin del documento */

        