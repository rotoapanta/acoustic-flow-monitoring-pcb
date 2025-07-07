#include <xc.h>
#include <stdint.h>
#include "spi.h"

// Función para configurar el módulo SPI
void Configurar_SPI(void) {
    // Configuración del registro SSPSTAT para modo SPI maestro con CKP = 1, 
    // CKE = 1 y modo de transferencia SPI de 8 bits
    SSPSTAT = 0x3F;
    // Configuración del registro SSPCON1 para modo SPI maestro con Fosc/16 y 
    // habilitación del módulo SSP
    SSPCON1 = 0x00;
    SSPCON1bits.CKP = 1;        // Polaridad del reloj en estado inactivo en alto
    SSPSTATbits.SMP = 0;        // Muestreo de datos en la mitad del tiempo de salida de datos
    SSPSTATbits.CKE = 0;        // Transmisión de datos en el flanco ascendente de SCK (para CKP = 1)
    SSPCON1bits.WCOL = 0;       // No hay colisión
    //SSPCON1bits.SSPEN = 1;      // Habilitar puerto serie sincrono
    //SSPCON1 |= 0x02;        
    //SSPCON1bits.SSPM = 0b0010;  // Modo maestro SPI, reloj = FOSC/64    
    //SSPCON1bits.SSPM = 0b0001;  // Modo maestro SPI, reloj = FOSC/16    
    SSPCON1bits.SSPM0 = 1;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM3 = 0;
}

//	SSPSTAT=0x3F;
//	SSPCON1=0x00;
//	CKP=1;			//Clock Polarity Select bit, Idle state for clock is a high level
//	SMP=0;			//Input data sampled at middle of data output time
//	CKE=0;			//For KPE=1, Data transmitted on rising edge of SCK
//	WCOL=0;			//No collision
//	SSPEN=1;		//Synchronous Serial Port Enable bit
//	SSPCON1|=0x02;	//SPI Master mode, clock = FOSC/64

//0010 = SPI Master mode, clock = FOSC/64(3)
//0001 = SPI Master mode, clock = FOSC/16(3)
//0000 = SPI Master mode, clock = FOSC/4(3)



// Función para enviar un byte a través del SPI y devolver el byte recibido
uint8_t SPI_Enviar_Caracter(uint8_t spi_tx){
    SSPBUF = spi_tx;
    while (!SSPSTATbits.BF); // Espera hasta que la transferencia esté completa
    return SSPBUF;
}

// Función para recibir un byte a través del SPI enviando un byte 0xFF
uint8_t SPI_Recibir_Caracter(void) {
    SSPBUF = 0xFF;
    while (!SSPSTATbits.BF); // Espera hasta que la transferencia esté completa
    return SSPBUF;
}