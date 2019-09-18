#include "ping.h"


volatile enum
{
    LOW, HIGH, DONE
} state;

volatile int data = 0;
volatile int OF = 0;
volatile int OFN = 0;

volatile unsigned int rising_time = 0;
volatile unsigned int falling_time = 0;


void ping_init(void) {

       SYSCTL_RCGCGPIO_R |= 0x2;     //enable Clock on PortB
       GPIO_PORTB_DEN_R |= 0x8;     // set pin 3
       GPIO_PORTB_AFSEL_R |= 0x8; //turning on alternative function
       GPIO_PORTB_PCTL_R |= 0x7000; //enable TX and RX on pin 3

       SYSCTL_RCGCTIMER_R |= 0x8; //enable timer 3 clock
       TIMER3_CTL_R &= 0xEFF; //sets TBEN to 0, have to disable before you can change settings
       TIMER3_CTL_R |= 0xC00; //sets TBEvent to 11
       TIMER3_CFG_R |= 0x4; //set to 16 bit timer
       TIMER3_TBMR_R |= (0x3 | 0x4 | 0x10); //capture mode
       TIMER3_TBILR_R |= 0xFFFFFFFF;  //Set upper bound.
       TIMER3_TBPR_R |= 0xFF;//prescale value

       TIMER3_ICR_R |= 0xF00; // clear interrupts
       TIMER3_IMR_R |= 0x400; //enable capture interrupt.
       NVIC_EN1_R |= 0x10; //enable bit 5
       IntRegister(INT_TIMER3B, TIMER3B_Handler); //register TIMER3B interrupt handler
       IntMasterEnable(); //intialize global interrupts
       //TIMER3_CTL_R |= 0x100; //sets TBEN to 1, enables timer3B


    state = LOW;// to wait for a rising edge
}

void clock_timer_init(void) {



}

void TIMER3B_Handler(void)
{

    unsigned int overflow = 0;

   //TIMER3_ICR_R |= 0x00000400;//CLEARING THE INTRUPPT


   // lcd_printf("%s", "ISR");

    // If the current state is LOW, then this is the positive edge of the pulse.
    // Store the time of the event in rising_time and move to the next state (HIGH)
    if (state == LOW)
    {
        // Read the time of the last edge event from TIMER3_TBR_R and store the value in rising_time
        rising_time = TIMER3_TBR_R;

        // Move to the next state
        state = HIGH;
    }
    // If the current state is HIGH, then this is the negative edge of the pulse.
    // Store the time of the event in falling_time and move to the next state (DONE)
    else if (state == HIGH)
    {
        // Read the time of the last edge event from TIMER3_TBR_R and store the value in falling_time
        falling_time = TIMER3_TBR_R;

        // Move to the next state
        state = DONE;

        TIMER3_CTL_R |= 0x0;//STOP THE TIMER
    }

    if (state == DONE)
    {
        int d = 0;

        d = falling_time - rising_time;
        data = falling_time - rising_time;

        if(d < 0)
        {
            overflow = 1;
            OF = 1;

            data = 6.25*pow(10,-6) - (rising_time - falling_time);
        }
        else
        {
            overflow = 0;
            OF = 0;
        }

       // lcd_printf("time is: %d\noverflow: %d", d, overflow);
        //timer_waitMicros(1000);
        state = LOW;
    }

    //CLEAR INTERRUPT STATE
   TIMER3_ICR_R |= 0x400; //clear interrupts BIT 10
}

void pulse(void)
{
       // state = LOW;


        GPIO_PORTB_DIR_R |= 0x8; // set PB3 as output
        GPIO_PORTB_AFSEL_R &= 0xFFF7; // turn off alternative function
        GPIO_PORTB_DATA_R |= 0x8; // set PB3 to high

        timer_waitMicros(5); // wait at least 15 microseconds based on data sheet

        GPIO_PORTB_DATA_R &= 0x7; // set PB3 to low
        GPIO_PORTB_AFSEL_R |= 0x0008; //turn off alternative function


        GPIO_PORTB_DIR_R &= 0x7; // set PB3 as input
        TIMER3_CTL_R |= 0x100; //sets TBEN to 1, enables timer3B

        timer_waitMillis(100);
}

void dist_time(void)
{
    double dist = 0.0;


    if(OF == 1 )
    {
        OFN++;
    }


    dist = data * 34/32000;


    lcd_printf("Distance: %lf\n overflows: %d", dist, OFN);//work

}
