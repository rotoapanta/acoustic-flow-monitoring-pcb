/* Archivo fuente del gestor de interrupciones generado */

#include "interrupt_manager.h"
#include "pin_manager.h"

//#include <xc.h> // incluir archivos de procesador 

//#include "mcc.h"

// funcion que maneja todas las interrupciones

void __interrupt() Manejador_de_Interrupciones (void)
{
    if (INTCONbits.TMR0IF) { // Verifica si la bandera de interrupción de Timer 0 está activa
        Atencion_Int_Timer_0(); // Llama a la rutina de interrupción de Timer 0
    }
    
    if (PIR1bits.TMR1IF) { // Verifica si la bandera de interrupción de Timer 1 está activa
        Atencion_Int_Timer_1(); // Llama a la rutina de interrupción de Timer 1
    }
    
    if (PIR1bits.TMR2IF) { // Verifica si la bandera de interrupción de Timer 2 está activa
        Atencion_Int_Timer_2(); // Llama a la rutina de interrupción de Timer 2
    }
    
    if (PIR1bits.RCIF && PIE1bits.RCIE) {
        // Leer y almacenar el dato recibido en la variable global
        dato_recibido = RCREG;
        // Limpiar la bandera de interrupcion
        PIR1bits.RCIF = 0;
    }
    
    if (INTCONbits.RBIF) { // Verificar si la interrupción fue causada por cambio de estado en Puerto B
        if (!PORTBbits.RB5) { // Comprobar si la transición fue de positivo a negativo en RB5
            contador_pluviometro++; // Incrementar contador_pluviometro
        }
        INTCONbits.RBIF = 0; // Limpiar la bandera de interrupción
    }
    
    
}

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 segundos
void Atencion_Int_Timer_0(void) {
    
    TMR0L = 0; // Reinicializa el contador de Timer 0
    INTCONbits.TMR0IF =0; // Limpia la bandera de interrupción de Timer 0
    
     // tarea 1, 0.131 s
    if( cont_task1 >= TASK1 ) { 
        cont_task1 = 0; 
        HABILITAR_TASK1 = true; 
    }
    else{ cont_task1++;}

    // tarea 2, 0.262 s
    if( cont_task2 >= TASK2 ) { 
        cont_task2 = 0; 
        HABILITAR_TASK2 = true; 
    }
    else{ cont_task2++;}

    // tarea 3, 0.524 s
    if( cont_task3 >= TASK3 ) { 
        cont_task3 = 0; 
        HABILITAR_TASK3 = true; 
        //UART_Enviar_Cadena("Hola Mundo! \n");
        //LED_LTM = !LED_LTM; 
    }
    else{ cont_task3++; }

    // Calcular tiempo en segundos
    temp_num_segundos_t0 = CUENTAS_DE_UN_SEGUNDO_T0*NUM_SEGUNDOS_T0;
    
    if(contador_segundos_t0 >= (uint16_t)(temp_num_segundos_t0)){
        contador_segundos_t0 = 0;
         //LED_LFN = !LED_LFN;   //LED_TMP = !LED_TMP;
    }
    else{ contador_segundos_t0++; }

        // Calcular tiempo en minutos
    temp_num_minutos_t0 = CUENTAS_DE_UN_MINUTO_T0*NUM_MINUTOS_T0;
    
    if(contador_minutos_t0 >= (uint16_t)(temp_num_minutos_t0)){
        contador_minutos_t0 = 0;
         //LED_LTX = !LED_LTX;   //LED_TMP = !LED_TMP;
    }
    else{ contador_minutos_t0++; }


    
    
}

// Rutina de interrupción de Timer 0 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_1(void) {
//    //TMR1L = 0;               // Inicializa el contador de Timer 1
//    //TMR1H = 0;               // Inicializa el contador de Timer 1
//    PIR1bits.TMR1IF = 0; // Limpia la bandera de interrupción de Timer 0
//    // Inserta aquí el código que se ejecutará cada intervalo de tiempo de Timer 0
//    // Calcular tiempo en minutos
//    temp_num_minutos = CUENTAS_DE_UN_MINUTO*NUM_MINUTO;
//    if(contador_un_minutos >= (uint16_t)(temp_num_minutos)){
//        contador_un_minutos = 0;
//     //LED_LTX = !LED_LTX;
//     //LED_LFN = !LED_LFN;
//     //LED_TMP = !LED_TMP;
//    }
//    else{
//        contador_un_minutos++;
//    }
}

// Rutina de interrupción de Timer 2 para generar intervalos de tiempo de 1 a 30 minutos
void Atencion_Int_Timer_2(void){
    
     PIR1bits.TMR2IF = 0; // Limpia la bandera de interrupción por Timer 2
     
     // Calcular tiempo en minutos
    temp_num_minutos_t2 = CUENTAS_DE_UN_MINUTO_T2*NUM_MINUTO_T2;
    
    if(contador_un_minutos_t2 >= (uint16_t)(temp_num_minutos_t2)){
        contador_un_minutos_t2 = 0;
                
        //LED_LTX = !LED_LTX; 
        //LED_LFN = !LED_LFN; LED_TMP = !LED_TMP;
    }
    else{
        contador_un_minutos_t2++;
    }
}

void Configurar_Interrupcion_Ext (void)
{
    INTCON2bits.RBPU = 0;   // Habilitar pull-up interno en Puerto B
    INTCON2bits.RBIP = 0;   // Interrupción por cambio de estado en Puerto B en baja prioridad
    INTCONbits.RBIE = 1;    // Habilitar interrupción por cambio de estado en Puerto B
    //INTCONbits.GIE = 1;     // Habilitar interrupciones globales
}


/* Fin del documento */