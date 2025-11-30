#include <Arduino.h>
typedef struct
{
    volatile uint8_t DIR; // Offset 0x00
    volatile uint8_t OUT; // Offset 0x01
    volatile uint8_t IN;  // Offset 0x02
    volatile uint8_t SEL; // Offset 0x03
} P_Type;

typedef struct
{
    volatile uint32_t CTRL;  // Offset 0x00
    volatile uint32_t LOAD;  // Offset 0x04
    volatile uint32_t VAL;   // Offset 0x08
    volatile uint32_t CALIB; // Offset 0x0C
} SysTick_Type;

#define P2 ((P_Type *)0x20C0)                // Base address for Port 2
#define P3 ((P_Type *)0x20E0)                // Base address for Port 3
#define SysTick ((SysTick_Type *)0xE000E010) // SysTick Base Address
void main_Example_Keypad(void)
{
    char keyCode, keyNum;

    P3->DIR |= BIT2 | BIT3; // set P3.2 & P3.3 as output pins (LED0-LED1)
    P2->DIR |= BIT5 | BIT4; // set P2.5 & P2.4 as output pins (LED2-LED3)
    uint8_t counter = 0;
    while (1)
    {
        //         P3.2 -> led0 URXD PB0
        // P3.3 -> led1 UTXD PB1
        // P2.5 -> led2 PWM PB2
        // P2.4 -> led3 PWM PB3

        counter -= 1;
        uint8_t led1, led2, led3, led4;
        led1 = (counter >> 1) & 0x01;
        led2 = (counter >> 2) & 0x01;
        led3 = (counter >> 3) & 0x01;
        led4 = (counter >> 4) & 0x01;
        P3->OUT ^= (BIT3 & (led2 << 3)) | (BIT2 & (led1 << 2));
        P2->OUT ^= (BIT4 & (led4 << 3)) | (BIT5 & (led3 << 2));
        SysTick_Wait10ms(100); // wait 1 sec
    }
}

// Initilise SysTick for maximum delay without interrupts
void SysTick_Init(void)
{
    SysTick->CTRL = 0;          // 1) disable SysTick during setup
    SysTick->LOAD = 0x00FFFFFF; // 2) maximum reload value
    SysTick->VAL = 0;           // 3) any write to current clears it
    SysTick->CTRL = 0x00000005; // 4) enable SysTick with core clock
}
// The delay parameter is in units of the 48 MHz clock. (20.83 ns)
void SysTick_Wait(uint32_t delay)
{
    SysTick->LOAD = delay - 1; // number of counts to wait
    SysTick->VAL = 0;          // any value written to counter clears
    while ((SysTick->CTRL & 0x00010000) == 0)
    {
    } // Polling: wait for count flag
}
// delay with 10ms units
void SysTick_Wait10ms(uint32_t delay)
{
    uint32_t i;
    for (i = 0; i < delay; i++)
    {
        SysTick_Wait(480000); // wait 10ms
    }
}