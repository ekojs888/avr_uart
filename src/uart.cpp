#include "uart.h"

void serial::Begin()
{
    UART_Init(9600);
}
void serial::Begin(uint16_t baud)
{
    UART_Init(baud);
}

void serial::Print(unsigned char data)
{
    UART_Write(data);
}

void serial::Print(const char *data)
{
    while (*data > 0)
        UART_Write(*data++);
}
void serial::Println()
{
    Print(0x0A);
    Print(0x0D);
}
void serial::Println(const char *data)
{
    Print(data);
    Print(0x0A);
    Print(0x0D);
}
uint8_t serial::Read()
{
    return UART_Read();
}
// private
//===================
void serial::UART_Write(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    };
    UDR0 = data;
}
uint8_t serial::UART_Read()
{
    while ((UCSR0A & (1 << RXC0)) == 0)
    {
    };           // Do nothing until data have been received
    return UDR0; // OK, return it.
}
void serial::UART_Init(uint16_t baud)
{
    uint16_t b = (((F_CPU / (baud * 16UL))) - 1);
    UBRR0H = (b >> 8);
    UBRR0L = (b & 0xff);

    // #if USE_2X
    //     UCSR0A |= (1 << U2X0);
    // #endif

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // 8-bit, 1 stop bit, no pariAty, asynchronous UART
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (0 << USBS0) |
             (0 << UPM01) | (0 << UPM00) | (0 << UMSEL01) |
             (0 << UMSEL00);
}