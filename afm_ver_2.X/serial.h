#ifndef SERIAL_H
#define	SERIAL_H

#include <xc.h> 

// Prototipos de funciones

// habilitar o deshabilitar pierto UART
//Puerto_Serie_232_Habilitado()
//Puerto_Serie_232_Deshabilitado()

#define UART_Habilitado()     (RCSTAbits.SPEN = 1)
#define SPI_Deshabilitado()  (SSPCON1bits.SSPEN = 0)

#define SPI_Habilitado()     (SSPCON1bits.SSPEN = 1)
#define UART_Deshabilitado()  (RCSTAbits.SPEN = 0)

// variable puerto serial
volatile uint8_t dato_recibido = 0;

// Funcion para inicializar el puerto UART
void Inicializar_UART(void);

// Funcion para enviar un solo caracter por el puerto UART
void UART_Enviar_Caracter(uint8_t dato); 

// Funcion para enviar una cadena de caracteres por el puerto UART
void UART_Enviar_Cadena(const char *cadena); 

// Funcion para recibir un caracter por el puerto UART
uint8_t UART_Recibir_Caracter(void);


#endif	/* SERIAL_H */
