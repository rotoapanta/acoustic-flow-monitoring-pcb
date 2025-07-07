#include "serial.h"

// Funcion para inicializar el puerto UART
void Inicializar_UART(void) {
 
    // Configurar el baud rate a 9600
    // SPBRG es el registro que guarda el valor para calcular el baud rate
    // Para un reloj de 8 MHz, el valor de SPBRG es 51 para un baud rate de 9600
    SPBRG = 51;
    
    // Configurar el registro TXSTA (Transmit Status and Control)
    // TXEN = 1 (Transmit Enable)
    // BRGH = 1 (High Baud Rate Select)
    TXSTA = 0x24;
    
    // Configurar el registro RCSTA (Receive Status and Control)
    // SPEN = 1 (Serial Port Enable)
    // CREN = 1 (Continuous Receive Enable)
    RCSTA = 0x90;
    
    // Configurar interrupcion de recepcion
    IPR1bits.RCIP = 1; // Alta prioridad
    PIE1bits.RCIE = 1; // Habilitar interrupcion de recepcion
     
}

// Funcion para enviar un solo caracter por el puerto UART
void UART_Enviar_Caracter(uint8_t dato) {
    // Esperar a que la transmision anterior termine
    // TXIF es el flag de transmision, se pone en 1 cuando se puede transmitir
    while (!TXIF);
    
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
    while (!RCIF);
    // Leer y retornar el caracter recibido del registro RCREG
    return RCREG;
}
