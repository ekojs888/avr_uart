#pragma once

#include <avr/io.h>
#define RX_READY (UCSR0A & UDRE0) // check bit7 of UCSRA0
#define TX_READY (UCSR0A & 0x20)  // check bit5 of UCSRA0

// #define BAUD_PRESCALE ((F_CPU / (16UL * 9600)) - 1)

class serial
{
private:
    void UART_Write(uint8_t data);
    uint8_t UART_Read();
    void UART_Init(uint16_t baud);
    void UART_Init();

public:
    void Begin();
    void Begin(uint16_t baud);
    void Print(unsigned char data);
    void Print(const char *data);
    void Println();
    void Println(const char *data);
    uint8_t Read();
};
