#ifndef SERIAL_H
#define	SERIAL_H

#include <xc.h> // incluir archivos de procesador 

// Prototipos de funciones

// Funcion para inicializar el puerto UART
void Inicializar_UART(void);

// Funcion para enviar un solo caracter por el puerto UART
void UART_Enviar_Caracter(uint8_t dato); 

// Funcion para enviar una cadena de caracteres por el puerto UART
void UART_Enviar_Cadena(const char *cadena); 

// Funcion para recibir un caracter por el puerto UART
uint8_t UART_Recibir_Caracter(void);


#endif	/* SERIAL_H */
