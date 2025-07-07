#include "mcc.h"

/* programa principal del afm v2 */

// "%03u" 
// 0 especifica que se completará con ceros a la izquierda
// 3 indica el ancho mínimo del valor a insertar en la cadena resultante
// u es un especificador de formato para un entero sin signo.
// ejemplo: "005", "042", "255".
// sprintf(buffer, "%03u", contador_pluviometro); 
// UART_Enviar_Cadena(buffer);

void main(void)
{  
    // inicializamos el dispositivo
    Inicializar_Sistema();

    // Función de retardo de 1 ms sin timers
    //DelayMs(1);

    // Habilita las interrupciones globales
    
    Interrupcion_Global_Habilitar();
    
    // Habilita las interrupciones periféricas
    
    Interrupcion_Periferica_Habilitar();
    
    // Imprimir datos de adc
    char str_bateria[3];

    // Imprimir datos de pluviometro
    char str_pluviometro[3];
    
    //char buffer[3];
    
    while (1)
    {
       
        if(HABILITAR_TASK3){
            HABILITAR_TASK3 = false;
            // tareas 3
            LED_LTM = !LED_LTM;
            //sprintf(str_bateria, "%03u", Lectura_ADC_CH0); 
            sprintf(str_pluviometro, "%03u", contador_pluviometro); 
            UART_Enviar_Cadena(str_pluviometro);
            
        }
        
        if(HABILITAR_TASK2){
            HABILITAR_TASK2 = false;
            // tareas 2
            //UART_Enviar_Caracter(contador_pluviometro);
            LED_LTX = !LED_LTX; 
        }
        
//        //DelayMs(1000);
//
//        if(HABILITAR_TASK1){
//            HABILITAR_TASK1 = false;
//            // tareas 1
//            LED_LFN = !LED_LFN;         
//        }
    }
}

/* Fin del documento */