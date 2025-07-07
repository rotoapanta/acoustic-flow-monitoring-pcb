#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>

// Codigo para configurar el oscilador interno a 8MHz y 
// deshabilitar el USB en la seccion config.h:

// Configuración de bits de cada registro

// CONFIG1L
#pragma config PLLDIV = 1           // Divisor de PLL 1 (4MHz)
#pragma config CPUDIV = OSC1_PLL2   // Divisor de CPU 1:2 (2MHz)
#pragma config USBDIV = 1           // La fuente directa del osc  primario sin posescala
//#pragma config PLLCFG = OFF       // PLL desactivado

// CONFIG1H
#pragma config FOSC = INTOSC_EC     // Oscilador interno
#pragma config FCMEN = OFF          // Monitor de fallos de OSC2 desactivado
#pragma config IESO = OFF           // Oscilador de baja frecuencia desactivado

// CONFIG2L
#pragma config PWRT = OFF       // Power-up timer desactivado
#pragma config BOR = OFF        // Brown-out reset desactivado
#pragma config BORV = 3         // Brown-out Reset a 2.5V
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)
//#pragma config WDTEN = OFF    // Watchdog Timer deshabilitado

// CONFIG3H
//#pragma config CCP2MX = OFF   // CCP2 en RB3)
#pragma config CCP2MX = ON      // CCP2 en RC1
#pragma config PBADEN = OFF     // Pins are configured as digital I/O on Reset (PORTB A/D Enable bit (PORTB<4:0> )
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Instrucciones extendidas deshabilitadas

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG5
//#pragma config USBLSCLK = 48MHz // USB a 48MHz
//#pragma config PLLUSB = OFF    // PLL para USB deshabilitado
//#pragma config USBDIV = 2      // Divisor de frecuencia de 2 para USB
//#pragma config ICPRT = OFF     // Puerto de depuración/programación desactivado

// CONFIG6L
#pragma config WRT0 = OFF       // Escritura en memoria desactivada
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Protección de memoria de arranque desactivada
#pragma config EBTR1 = OFF      //
#pragma config EBTR2 = OFF      // 
#pragma config EBTR3 = OFF      //

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)


// Configuración de oscilador interno a 8MHz
#define SYS_FREQ 8000000L
#define FCY SYS_FREQ/4

// Configuración del oscilador interno a 8MHz y desactivacion del puerto USB
void Inicializar_Oscilador(void);


// Last

//// CONFIG1L
//#pragma config PLLDIV = 1
//#pragma config CPUDIV = OSC1_PLL2
//#pragma config USBDIV = 2
//
//// CONFIG1H
//#pragma config FOSC = INTOSCIO_EC
//#pragma config FCMEN = OFF
//#pragma config IESO = OFF
//
//// CONFIG2L
//#pragma config PWRT = OFF
//#pragma config BOR = ON
//#pragma config BORV = 3
//#pragma config VREGEN = OFF
//
//// CONFIG2H
//#pragma config WDT = OFF
//#pragma config WDTPS = 32768
//
//// CONFIG3H
//#pragma config PBADEN = OFF
//#pragma config LPT1OSC = OFF
//#pragma config MCLRE = ON
//
//// CONFIG4L
//#pragma config STVREN = ON
//#pragma config LVP = OFF
//#pragma config XINST = OFF
//
//// CONFIG5L
//#pragma config CP0 = OFF
//#pragma config CP1 = OFF
//#pragma config CP2 = OFF
//#pragma config CP3 = OFF
//
//// CONFIG5H
//#pragma config CPB = OFF
//#pragma config CPD = OFF
//
//// CONFIG6L
//#pragma config WRT0 = OFF
//#pragma config WRT1 = OFF
//#pragma config WRT2 = OFF
//#pragma config WRT3 = OFF
//
//// CONFIG6H
//#pragma config WRTC = OFF
//#pragma config WRTB = OFF
//#pragma config WRTD = OFF
//
//// CONFIG7L
//#pragma config EBTR0 = OFF
//#pragma config EBTR1 = OFF
//#pragma config EBTR2 = OFF
//#pragma config EBTR3 = OFF
//
//// CONFIG7H
//#pragma config EBTRB = OFF




#endif	/* CONFIG_H */
