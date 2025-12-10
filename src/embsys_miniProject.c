
// #include "driverlib.h"
// #include <stdint.h>
// #include <stdio.h>
// #include "LCD.h"



// #define TRIGGER_PORT GPIO_PORT_P2
// #define TRIGGER_PIN GPIO_PIN3 // P2.3
// #define ECHO_PORT GPIO_PORT_P6
// #define ECHO_PIN GPIO_PIN6 // P6.6


// void stop_f();
// void start_f();
// void measure_f();
// typedef enum
// {
//     stop = 0,
//     start,
//     measure
// } State_Type;
// State_Type curr_state; // current state variable
// void (*state_table[])() = {stop_f, start_f, measure_f};



// volatile uint32_t rising_edge = 0;
// volatile uint32_t falling_edge = 0;
// volatile uint8_t capture_done = 0;
// volatile uint8_t rising_edge_finished = 0;
// volatile uint8_t uart_rx_data = 0;
// volatile RTC_C_Calendar rtcTime;
// volatile uint32_t ticks;
// volatile uint32_t distance_cm = 0;


// // RTC current time initialization
// // Example: 3 Dec 2025, 21:00:00
// const RTC_C_Calendar currentTime =
//     {
//         0x00,  // Seconds
//         0x00,  // Minutes
//         0x21,  // Hours (24h format)
//         0x03,  // day of week
//         0x03,  // Day of Month
//         0x12,  // Month
//         0x2025 // Year
// };

// //----------------------------------------------------------
// // Timer_A Capture Mode Config
// //----------------------------------------------------------
// const Timer_A_CaptureModeConfig echoCaptureConfig = {
//     TIMER_A_CAPTURECOMPARE_REGISTER_1, // CCR1
//     TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE,
//     TIMER_A_CAPTURE_INPUTSELECT_CCIxB, // input pin = CCI1B (P2.4)
//     TIMER_A_CAPTURE_SYNCHRONOUS,
//     TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,
//     TIMER_A_OUTPUTMODE_OUTBITVALUE};

// //----------------------------------------------------------
// // Timer_A Continuous Mode (counter always running)
// //----------------------------------------------------------
// const Timer_A_ContinuousModeConfig timerConfig = {
//     TIMER_A_CLOCKSOURCE_SMCLK,
//     TIMER_A_CLOCKSOURCE_DIVIDER_1, // 3 MHz
//     TIMER_A_TAIE_INTERRUPT_DISABLE,
//     TIMER_A_DO_CLEAR // Start from 0
// };



// //----------------------------------------------------------
// // Rtc Init
// //----------------------------------------------------------
// void RTC_init(void)
// {
//     // Configure LFXT pins for 32.768 kHz crystal
//     GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1,
//         GPIO_PRIMARY_MODULE_FUNCTION);

//     // Start LFXT in non-bypass mode
//     CS_setExternalClockSourceFrequency(32000, 48000000);
//     CS_startLFXT(false);

//     // Initialize RTC calendar
//     RTC_C_initCalendar(&currentTime, RTC_C_FORMAT_BCD);

//     // Start RTC
//     RTC_C_startClock();
// }

// //----------------------------------------------------------
// // Initialize Timer_A for Echo Measurement
// //----------------------------------------------------------
// void timerA_init(void)
// {
//     // Configure P2.4 as TA0.1 input (CC1) ***echo input
//     GPIO_setAsPeripheralModuleFunctionInputPin(ECHO_PORT, ECHO_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
//     // Configure P2.0 as                   ***trigger output
//     GPIO_setAsOutputPin(TRIGGER_PORT, TRIGGER_PIN);

//     // Configure capture on CCR1
//     Timer_A_initCapture(TIMER_A0_BASE, &echoCaptureConfig);

//     // Configure continuous mode
//     Timer_A_configureContinuousMode(TIMER_A0_BASE, &timerConfig);

//     // Enable interrupts
//     Interrupt_enableInterrupt(INT_TA0_N);
//     Interrupt_enableMaster();

//     // Start Timer_A
//     Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
// }

// //----------------------------------------------------------
// // Initialize Uart
// //----------------------------------------------------------
// void UART_init(void)
// {
//     /* Configure UART pins (P1.2 = RX, P1.3 = TX) */
//     GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3,
//         GPIO_PRIMARY_MODULE_FUNCTION);

//     /* UART configuration for SMCLK = 3 MHz, baud = 9600 */
//     const eUSCI_UART_Config uartConfig =
//         {
//             EUSCI_A_UART_CLOCKSOURCE_SMCLK,
//             19,
//             8,
//             85,
//             EUSCI_A_UART_NO_PARITY,
//             EUSCI_A_UART_LSB_FIRST,
//             EUSCI_A_UART_ONE_STOP_BIT,
//             EUSCI_A_UART_MODE,
//             EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION};
//     /* Initialize and enable UART  with Intrrupts */
//     UART_initModule(EUSCI_A0_BASE, &uartConfig);
//     UART_enableModule(EUSCI_A0_BASE);
//     UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
//     Interrupt_enableInterrupt(INT_EUSCIA0);
// }


// void UART_sendChar(uint8_t c)
// {
//     UART_transmitData(EUSCI_A0_BASE, c);
// }

// void UART_sendString(const char *str)
// {
//     while (*str)
//     {
//         UART_transmitData(EUSCI_A0_BASE, *str++);
//     }
// }

// //----------------------------------------------------------
// // Function to retrieve pulse width (in timer ticks)
// // Blocks until measurement is done
// //----------------------------------------------------------
// uint32_t ultrasonic_getPulseWidth(void)
// {
//     capture_done = 0;

//     // Wait for ISR to capture rising & falling edges
//     while (!capture_done);
    
//     if (falling_edge >= rising_edge)
//         return falling_edge - rising_edge;
//     else
//         return (0xFFFF - rising_edge) + falling_edge;
// }

// void ultrasonic_triggerPulse(void)
// {
//     // Ensure LOW first for at least 2 µs
//     GPIO_setOutputLowOnPin(TRIGGER_PORT, TRIGGER_PIN);
//     delay_us(2); //  2 µs

//     // HIGH for 10 µs
//     GPIO_setOutputHighOnPin(TRIGGER_PORT, TRIGGER_PIN);
//     delay_us(10); //   ≈ 10 µs

//     // Back to LOW
//     GPIO_setOutputLowOnPin(TRIGGER_PORT, TRIGGER_PIN);
// }

// //----------------------------------------------------------
// // Timer_A ISR
// //----------------------------------------------------------
// void TA0_N_IRQHandler(void)
// {
//     uint32_t status = Timer_A_getCaptureCompareInterruptStatus(TIMER_A0_BASE,
//                       TIMER_A_CAPTURECOMPARE_REGISTER_1,
//                       TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG );


//     if (status & TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)
//     {
//         uint32_t value = Timer_A_getCaptureCompareCount(TIMER_A0_BASE,
//             TIMER_A_CAPTURECOMPARE_REGISTER_1);

//         // Detect rising or falling edge
//         if (GPIO_getInputPinValue(ECHO_PORT, ECHO_PIN) == 1)
//         {
//             rising_edge = value;
//             rising_edge_finished = 1;
//         }
//         else if(rising_edge_finished)
//         {
//             falling_edge = value;
//             capture_done = 1;
//             rising_edge_finished = 0;
//         }
//     }

//     Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
// }

// //----------------------------------------------------------
// // UART ISR
// //----------------------------------------------------------
// void EUSCIA0_IRQHandler(void)
// {
//     uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
//     UART_clearInterruptFlag(EUSCI_A0_BASE, status);

//     if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
//     {
//         uart_rx_data = UART_receiveData(EUSCI_A0_BASE);
//         if (uart_rx_data == 's' || uart_rx_data == 'S')
//         {
//             curr_state = start;
//         }
//         else if (uart_rx_data == 'x' || uart_rx_data == 'X')
//         {
//             curr_state = stop;
//         }
//         else
//         {
//             UART_sendString("Wrong Command\r\n");
//         }
//     }
// }

// void stop_f()
// {
//     LCD_Comd(LCD_CLR); // clear screen, move cursor to home;
//     UART_sendString("STOP\r\n");
//     LCD_DataStr("Stopped");
// }

// void start_f()
// {
//     curr_state = measure;
//     rtcTime = RTC_C_getCalendarTime();
//     char buffer[50], line1[30], line2[30];
//     sprintf(buffer, "%02x:%02x:%02x %02x/%02x/%04x Distance = %02lu cm\r\n",
//             rtcTime.hours, rtcTime.minutes, rtcTime.seconds,
//             rtcTime.dayOfmonth, rtcTime.month, rtcTime.year, distance_cm);
//     sprintf(line1, "%02x:%02x:%02x %02x/%02x/%04x",
//             rtcTime.hours, rtcTime.minutes, rtcTime.seconds,
//             rtcTime.dayOfmonth, rtcTime.month, rtcTime.year);
//     sprintf(line2, "Distance = %02lu cm", distance_cm);
//     UART_sendString(buffer);
//     LCD_Comd(LCD_CLR);
//     LCD_DataStr(line1);
//     LCD_Comd(LCD_2_LINE);
//     LCD_DataStr(line1);
//     delay_ms(200);
// }

// void measure_f()
// {
//     ultrasonic_triggerPulse();
//     while (capture_done != 1)
//         ;
//     ticks = ultrasonic_getPulseWidth();
//     distance_cm = ticks / (58 * 3); // 3 for 3Mhz and 58 for sound distance
//     curr_state = start;
// }
// void main(void)
// {

//     WDT_A_holdTimer(); // stop watchdog timer
//     LCD_Init();
//     RTC_init();
//     UART_init();
//     timerA_init();
//     curr_state = stop;
//     LCD_Comd(LCD_CLR); // clear screen, move cursor to home;
//     while (1)
//     {
//         state_table[curr_state]();
//     }
// }