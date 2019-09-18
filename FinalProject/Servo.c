
#include "movement.h"
#include "open_interface.h"
#include "Servo.h"
double currentDeg = 0;
void servo_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0b10;     //enable Clock on PortB
    GPIO_PORTB_DEN_R |= 0b00100000;     // set pin 3
    GPIO_PORTB_AFSEL_R |= 0b00100000; //turning on alternative function
    GPIO_PORTB_PCTL_R |= 0x700000; //enable TX and RX on pin 3
    //GPIO_PORTB_DIR_R |= 0b00100000;
    SYSCTL_RCGCTIMER_R |= 0b10; //enable timer 3 clock
    TIMER1_CTL_R &= 0b011111111; //sets TBEN to 0, have to disable before you can change settings
    TIMER1_CFG_R |= 0x4; //set to 16 bit timer
    TIMER1_TBMR_R |= 0b01010; //Periodic count down
    TIMER1_CTL_R |= 0b011111011111111;
    TIMER1_TBPR_R = 0x0004;
    TIMER1_TBILR_R = 0xE200;
    TIMER1_TBPMR_R = 0x0004;
    TIMER1_TBMATCHR_R = 0xBED8;
    TIMER1_CTL_R |= 0b111111111;
}
void servo_move(double degrees)
{
    SYSCTL_RCGCGPIO_R |= 0b10;     //enable Clock on PortB
    GPIO_PORTB_DEN_R |= 0b00100000;     // set pin 3
    GPIO_PORTB_AFSEL_R |= 0b00100000; //turning on alternative function
    GPIO_PORTB_PCTL_R |= 0x700000; //enable TX and RX on pin 3
    //GPIO_PORTB_DIR_R |= 0b00100000;
    SYSCTL_RCGCTIMER_R |= 0b10; //enable timer 3 clock
    TIMER1_CTL_R &= 0b011111111; //sets TBEN to 0, have to disable before you can change settings
    TIMER1_CFG_R |= 0x4; //set to 16 bit timer
    TIMER1_TBMR_R |= 0b01010; //Periodic count down
    TIMER1_CTL_R |= 0b011111011111111;
    TIMER1_TBPR_R = 0x0004;
    TIMER1_TBILR_R = 0xE200;
    TIMER1_TBPMR_R = 0x0004;
    TIMER1_TBMATCHR_R = ((-155.56*degrees)+311000);
    TIMER1_CTL_R |= 0b111111111;
}

