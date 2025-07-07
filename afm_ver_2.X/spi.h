#ifndef SPI_H
#define	SPI_H

#include <xc.h> 
#include <stdint.h>

// SPI 
#define	SDI  PORTBbits.RB0      //SDI
#define	SCLK LATBbits.LATB1     //SCK
#define	DRDY PORTBbits.RB2      //DATA READY
//#define	DRDY LATBbits.LATB2     //SCK
#define	SDO  LATCbits.LATC7     //SDO

// PORTCbits.RC7

// Configura el modulo SPI como maestro y define los pines SCK, SDI y SDO
void Configurar_SPI(void);

// Envía un byte a través del SPI y devuelve el byte recibido
uint8_t SPI_Enviar_Caracter(uint8_t spi_tx);

// Recibe un byte a través del SPI enviando un byte 0xFF
uint8_t SPI_Recibir_Caracter(void);

#endif	/* SPI_H */
