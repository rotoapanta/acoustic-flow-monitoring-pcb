#include "mcc.h"

/* programa principal del afm v2 */

void main(void)
{  
    // inicializamos el dispositivo
    Inicializar_Sistema();

    // Función de retardo de 1 ms sin timers
    //DelayMs(1);
    
    // Función para generar intervalos de tiempo con Timer 0 utilizando interrupciones para generar de 1 a 100 segundos
    //Configurar_Timer0();

    // Función para generar intervalos de tiempo con Timer 1 utilizando interrupciones para generar de 1 a 30 minutos
    //Configurar_Tiempo_Timer1();

    // timer 0, opera cada 3 segundos
    //Asignar_Segundos_Timer0(3);

    // timer 0, opera cada 2 minutos
    //Asignar_Minutos_Timer0(2);
        
    // timer 2 se activa cada 3 min
    //Configurar_Tiempo_Timer2(3);

    // Habilita las interrupciones globales
    
    Interrupcion_Global_Habilitar();
    
    // Habilita las interrupciones periféricas
    
    Interrupcion_Periferica_Habilitar();
    
    // Saludo puerto serial
    
    //UART_Enviar_Cadena("Hola Mundo! \n");
    
    while (1)
    {
       
        if(HABILITAR_TASK3){
            HABILITAR_TASK3 = false;
            // tareas 3
            
            
            LED_LTM = !LED_LTM;
        }
        
        if(HABILITAR_TASK2){
            HABILITAR_TASK2 = false;
            // tareas 2
            
            LED_LTX = !LED_LTX; 
        
        }
        //DelayMs(1000);

        if(HABILITAR_TASK1){
            HABILITAR_TASK1 = false;
            // tareas 1
            LED_LFN = !LED_LFN; 
        
        }
        
        // Add your application code
    }
}

/* Fin del documento */