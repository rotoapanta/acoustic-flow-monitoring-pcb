#include "mcc.h"



/* programa principal del afm v2 */

void main(void)
{  
    // inicializamos el dispositivo
    Inicializar_Sistema();

    // Función de retardo de 1 ms sin timers
    //DelayMs(1);
    

    // Habilita las interrupciones globales
    
    Interrupcion_Global_Habilitar();
    
    // Habilita las interrupciones periféricas
    
    Interrupcion_Periferica__Habilitar();
    
    // Saluda
    
    UART_Enviar_Cadena("Hola Mundo! \n");
    
    
    //char *buffer;
    
    while (1)
    {
        if(HABILITAR_TASK3){
            HABILITAR_TASK3 = false;
            // Enviar datos utilizando las funciones creadas
            
            // Enviar el caracter 'A'
            
            UART_Enviar_Caracter('A');
            
            UART_Enviar_Caracter(contador_pluviometro+'0');
            
            //UART_Enviar_Caracter(' ');

            LED_LFN = !LED_LFN;
            // Recibir datos
            // Almacena el dato recibido en la variable dato_recibido
            //dato_recibido = UART_Recibir_Caracter();

            //sprintf(buffer, "%s", contador_pluviometro);

            // Enviar la cadena de caracteres "Hola mundo!"
            //UART_Enviar_Cadena(buffer);
        }
        //
    }
}

// funcion que maneja todas las interrupciones

void __interrupt() Manejador_de_Interrupciones (void)
{
    Interrupcion_Global_Dehabilitar();
            
    // Interrupciones de los timer 0 ¡, 1 y 2
    
    if (INTCONbits.TMR0IF) {        // Verifica si la bandera de interrupción de Timer 0 está activa
        Interrupcion_de_Timer_0();  // Llama a la rutina de interrupción de Timer 0
    }
    
    if (PIR1bits.TMR1IF) {     // Verifica si la bandera de interrupción de Timer 1 está activa
        Interrupcion_de_Timer_1();  // Llama a la rutina de interrupción de Timer 1
    }
    
    if (PIR1bits.TMR2IF) {     // Verifica si la bandera de interrupción de Timer 2 está activa
        Interrupcion_de_Timer_2();  // Llama a la rutina de interrupción de Timer 2
    
    }
    
    // recibir datos por el puerto serial
    
    if (PIR1bits.RCIF && PIE1bits.RCIE) {
        // Leer y almacenar el dato recibido en la variable global
        dato_recibido = RCREG;
        // test enviar por las mismas
        UART_Enviar_Cadena("\nDato recibido: \n");
        UART_Enviar_Caracter(dato_recibido);
        UART_Enviar_Cadena("\n ");
        
        // Limpiar la bandera de interrupcion
        PIR1bits.RCIF = 0;
        
    } 
    
    // Interrupción externa en RB5 (INT2)
    if (!INTCONbits.RBIF && ENT_PLUVIO) {
        
        contador_pluviometro++;
        
        UART_Enviar_Caracter('6');
        
        INTCONbits.RBIF = 0;    //Habilita la interrupción de cambio de puerto RB
        
    }
    
    Interrupcion_Global_Habilitar() ;
    
} // Fin de atencion a interrupciones
  



/* Fin del documento */