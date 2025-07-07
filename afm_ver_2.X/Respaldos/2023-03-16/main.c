#include "mcc.h"

/* programa principal del afm v2 */

void main(void)
{  
    // inicializamos el dispositivo
    SYSTEM_Initialize();

    // Función de retardo de 1 ms sin timers
    //DelayMs(1);
  
      // Configura los timers con los intervalos de tiempo deseados
    Configurar_Tiempo_Timer0(12); // 1 segundos

      // Configura los timers con los intervalos de tiempo deseados
    Configurar_Tiempo_Timer1(3); // 1 minutos
  
    Configurar_Tiempo_Timer2(2); // 1 minutos
    
    // Habilita las interrupciones globales
    
    INTERRUPT_GlobalInterruptEnable();
    
    // Habilita las interrupciones periféricas
    
    INTERRUPT_PeripheralInterruptEnable();
    
    while (1)
    {
       
        //DelayMs(1000);
        
        // Add your application code
    }
}

/* Fin del documento */