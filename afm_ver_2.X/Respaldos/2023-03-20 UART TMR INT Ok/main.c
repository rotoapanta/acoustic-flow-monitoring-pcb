#include "mcc.h"

/* programa principal del afm v2 */

// "%03u" 
// 0 especifica que se completar� con ceros a la izquierda
// 3 indica el ancho m�nimo del valor a insertar en la cadena resultante
// u es un especificador de formato para un entero sin signo.
// ejemplo: "005", "042", "255".
// sprintf(buffer, "%03u", contador_pluviometro); 
// UART_Enviar_Cadena(buffer);

void main(void)
{  
    // inicializamos el dispositivo
    Inicializar_Sistema();

    // Funci�n de retardo de 1 ms sin timers
    //DelayMs(1);
    
    

    // Habilita las interrupciones globales
    
    Interrupcion_Global_Habilitar();
    
    // Habilita las interrupciones perif�ricas
    
    Interrupcion_Periferica_Habilitar();
    
    // Saludo puerto serial
    UART_Enviar_Cadena("Hola Mundo! \n");
    
    char buffer[3];
    
    
    while (1)
    {
       
        if(HABILITAR_TASK3){
            HABILITAR_TASK3 = false;
            // tareas 3
            
            //UART_Enviar_Caracter('A');
            //UART_Enviar_Caracter(dato_recibido);
            
            
            
            sprintf(buffer, "%04u", contador_pluviometro); 
            
            
            UART_Enviar_Cadena(buffer);

            LED_LTM = !LED_LTM;
        }
        
        if(HABILITAR_TASK2){
            HABILITAR_TASK2 = false;

            // tareas 2
            //UART_Enviar_Caracter(contador_pluviometro);
            
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