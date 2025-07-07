#include "serial.h"

// Funcion para inicializar el puerto UART
// Configurar el baud rate a 9600, para un reloj de 19.6608 MHz
void Inicializar_UART(void) {
    
    //BAUDCONbits.BRG16 = 0;
    //SPBRG = 127;         // 9600 Generador de velocidad en baudios
    // Asignar el valor 4095 a SPBRG (SPBRGH:SPBRG) para obtener
    // 300 bauds

    // Habilitar el generador de velocidad en baudios de 16 bits
    BAUDCONbits.BRG16 = 1;
    SPBRGH = 0x3F;
    SPBRG  = 0xFF;
    
    // Configurar el módulo UART
    TXSTAbits.BRGH = 1;     // Modo de alta velocidad
    TXSTAbits.TXEN = 1;     // Habilitar la transmisión
    RCSTAbits.SPEN = 1;     // Habilitar el módulo UART  
    // Configurar interrupcion de recepcion
    IPR1bits.RCIP = 0;      // Baja prioridad
    PIE1bits.RCIE = 1;      // Habilitar interrupcion de recepcion    
}

// Funcion para enviar un solo caracter por el puerto UART
void UART_Enviar_Caracter(uint8_t dato) {
    // Esperar a que la transmision anterior termine
    // TXIF es el flag de transmision, se pone en 1 cuando se puede transmitir
    while (!PIR1bits.TXIF);
    // Enviar el caracter
    TXREG = dato;
}

// Funcion para enviar una cadena de caracteres por el puerto UART
void UART_Enviar_Cadena(const char *cadena) {
    // Iterar a traves de la cadena de caracteres
    while (*cadena) {
        // Enviar cada caracter de la cadena
        UART_Enviar_Caracter(*cadena);
        // Avanzar al siguiente caracter
        cadena++;
    }
}

// Funcion para recibir un caracter por el puerto UART
uint8_t UART_Recibir_Caracter(void) {
    // Esperar a que haya datos disponibles en el buffer
    // RCIF es el flag de recepcion, se pone en 1 cuando hay datos en el buffer
    while (!PIR1bits.RCIF);
    // Leer y retornar el caracter recibido del registro RCREG
    return RCREG;
}
