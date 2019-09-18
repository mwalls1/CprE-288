#include "UART.h"
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "movement.h"
#include "open_interface.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

void uart_init(void)
{

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //enable clock to UART1, R1 = UART1. ***Must be done before setting Rx and Tx (See DataSheet)
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
    //enable alternate functions on port b pins 0 and 1
    GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);
    //enable Rx and Tx on port B on pins 0 and 1
    GPIO_PORTB_PCTL_R |= 0x00000011;
    //set pin 0 and 1 to digital
    GPIO_PORTB_DEN_R |= (BIT0 | BIT1);
    //set pin 0 to Rx or input
    GPIO_PORTB_DIR_R &= ~BIT0;
    //set pin 1 to Tx or output
    GPIO_PORTB_DIR_R |= BIT1;
    uint16_t iBRD = 8; //use equations
    uint16_t fBRD = 44; //use equations
    //turn off uart1 while we set it up
    UART1_CTL_R &= ~(UART_CTL_UARTEN);
    //set baud rate
    UART1_IBRD_R = iBRD;
    UART1_FBRD_R = fBRD;
    //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
    UART1_LCRH_R = UART_LCRH_WLEN_8;
    //use system clock as source
    UART1_CC_R = UART_CC_CS_SYSCLK;
    //re-enable enable RX, TX, and uart1
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

}

void uart_sendChar(char data)
{
    while (UART1_FR_R & 0x20)
    {
    }
    //send data
    UART1_DR_R = data;
}
void init_uart_interrupts()
{
    //turn off uart1 while we set it up
    UART1_CTL_R &= ~(UART_CTL_UARTEN);
    //clear interrupt flags
    UART1_ICR_R = (UART_ICR_TXIC | UART_ICR_RXIC);
    //enable send and receive raw interrupts
    UART1_IM_R |= UART_IM_TXIM | UART_IM_RXIM;
    //set priority of usart1 interrupt to 1. group 1 bits 21-23
    NVIC_PRI1_R |= 0x00200000;
    //enable interrupt for IRQ 6 set bit 6
    NVIC_EN0_R |= 0x00000040;
    //tell cpu to use ISR handler for uart1
    IntRegister(INT_UART1, UART1_Handler);
    //enable global interrupts
    IntMasterEnable();

    //re-enable enable RX, TX, and uart1
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
}
char uart_receive(void)
{
    char data = 0;
    //wait to receive
    while (UART1_FR_R & UART_FR_RXFE)
    {

    }
    //mask the 4 error bits and grab only 8 data bits
    data = (char) (UART1_DR_R & 0xFF);

    return data;

}
void uart_sendStr(const char *data)
{
    //until we reach a null character
    while (*data != '\0')
    {
        //send the current character
        uart_sendChar(*data);
        // increment the pointer.
        data++;
    }

}
void UART1_Handler(void)
{
    //received a byte
    if (UART1_MIS_R & UART_MIS_RXMIS)
    {
        //do something
        char arr[21] = "                    "; //Initalizing an array of characters
        int i = 0; //incrementing int
        char x; //x to check
        while (1)
        {
            x = uart_receive();
            if (i <= 19 && x != 0x0D)
            {
                arr[i] = x;
                i++;
                uart_sendChar(x);
            }
            if (i == 20 || x == 0x0D)
            {
                arr[i] = '\0';
                lcd_printf("%s", arr);
                uart_sendChar('\r');
                uart_sendChar('\n');
                i = 0;
            }

        }
        UART1_ICR_R |= UART_ICR_RXIC; //clear interrupt
    }
    //sent a byte
    else if (UART1_MIS_R & UART_MIS_TXMIS)
    {
        //Do something
        char arr[21] = "                    "; //Initalizing an array of characters
        int i = 0; //incrementing int
        char x; //x to check
        while (1)
        {
            x = uart_receive();
            if (i <= 19 && x != 0x0D)
            {
                arr[i] = x;
                i++;
                uart_sendChar(x);
            }
            if (i == 20 || x == 0x0D)
            {
                arr[i] = '\0';
                lcd_printf("%s", arr);
                uart_sendChar('\r');
                uart_sendChar('\n');
                i = 0;
            }
        }
        UART1_ICR_R |= UART_ICR_TXIC; //clear interrupt
    }
}
