#include "ping.h"
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "movement.h"
#include "open_interface.h"
volatile int numEdges = 0;
volatile int time1;
volatile int time2;
void ping_init(void)
{
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | 0b000010; // port b enable
    GPIO_PORTB_DEN_R |= 0b00001000;
    SYSCTL_RCGCTIMER_R |= 0b00001000; // Enable Timer 3’s clock
    GPIO_PORTB_AFSEL_R |= 0b00001000;
    GPIO_PORTB_PCTL_R |= 0x00007000;
    GPIO_PORTB_DIR_R &= 0b11110111;
    TIMER3_CTL_R &=0b011111111;
    // Configure Timer 1A functionality
    TIMER3_CFG_R = 0x4; // Set to 16-bit mode
    TIMER3_TBMR_R = 0b10111; //Count up, edge-time, capture mode
    TIMER3_CTL_R = 0b110100000000; // Detect positive edges (3:2=00)
    TIMER3_TBPR_R = 0xFF; // Use prescaler extension to 24 bits
    TIMER3_TBILR_R = 0xFFFF; // Load max 24-bit value
    TIMER3_ICR_R |= 0b10000000000;   //Clear capture event interrupt status
    TIMER3_IMR_R |= 0b00001000; // Enable capture event interrupts
    // 3. NVIC setup
    // A) Configure NVIC to allow Timer 1A interrupts (use priority=1)
    NVIC_PRI9_R |= 0b00100000;            //Timer1A IRQ pri=1, bits 15-13
    NVIC_EN1_R |= 0b00010000; //Enable Timer1A IRQ (21), bit 21

    // B) Bind Timer 1A interrupt requests to user’s interrupt handler
    IntRegister(52, TIMER3B_Handler);
    // Re-enable Timer 1A
    TIMER3_CTL_R |= 0b100000000;

}
void send_pulse()
{
    //GPIO_PORTB_AFSEL_R &= 0b11110111;
    GPIO_PORTB_PCTL_R &= 0x0FFF;
    GPIO_PORTB_DIR_R |= 0b00001000;
    GPIO_PORTB_DATA_R |= 0b00001000;
    timer_waitMillis(5);
    GPIO_PORTB_DATA_R &= 0b11110111;
    GPIO_PORTB_DIR_R &= 0b11110111;
   // GPIO_PORTB_AFSEL_R |= 0b00001000;
    GPIO_PORTB_PCTL_R |= 0x7000;
}
void TIMER3B_Handler()
{
    if(numEdges==1)
    {
        time2 = TIMER3_TBV_R;
        numEdges=0;
    }
    else
    {
        numEdges++;
        time1 = TIMER3_TBV_R;
    }
}
void getData(int *timeOne, int *timeTwo)
{
    *timeOne = time1;
    *timeTwo = time2;
}

