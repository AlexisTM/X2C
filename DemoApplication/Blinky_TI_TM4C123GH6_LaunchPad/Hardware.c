/*
 * $LastChangedRevision: 1013 $
 * $LastChangedDate:: 2016-03-04 13:14:00 +0100#$
 *
 * Copyright (c) 2016, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include "Target.h"
#include "Main.h"
#include "Hardware.h"

/* Linker variable that marks the top of the stack */
extern uint32_t __STACK_TOP;
/*External declaration for the reset handler that is to be called when the processor is started */
extern void _c_int00(void);

/* private prototypes */
static void sendSerial(tSerial* serial, uint8 data);
static uint8 receiveSerial(tSerial* serial);
static uint8 isReceiveDataAvailable(tSerial* serial);
static uint8 isSendReady(tSerial* serial);

interrupt void UnusedISR(void);
interrupt void ResetISR(void);
interrupt void Timer0IntHandler(void);

/**
 * @brief Initialization of hardware.
 */
void initHardware(void)
{
	/** - Configuration of system clock:
	 *    - 16MHz external quartz
	 *    - PLL
	 *    - 2.5 frequency divider
	 *    - -> 80 MHz system clock
	 *    .
	 */
    /* Set the clocking to run at 80 MHz (200 MHz / 2.5) using the PLL */
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    /* Enable GPIO port A which is used for UART0 pins */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    /* Enable GPIO port A which is used for LEDs and buttons */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    /* Enable UART0 which is used for serial connection */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    /* Enable TIMER0 which is used for cyclic interrupt generation */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    /* Enable WDOG0 timer */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);


    /* Configure the pin muxing for UART0 */
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);

    /* Select the alternate (UART) function for these pins. */
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Use the internal 16MHz oscillator as the UART0 clock source */
    ROM_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);


    /** - Configuration of serial interface:
     *    - UART0
     *    - 115200 baud
     *    - 8 data bits
     *    - 1 stop bit
     *    - no parity
     *    .
     */
    ROM_UARTConfigSetExpClk(UART0_BASE, 16000000, 115200,
    (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE | UART_CONFIG_WLEN_8));

    ROM_UARTEnable(UART0_BASE);

    /** - Configuration of I/O-ports:
     *    - PF1, PF2 & PF3 as outputs for LEDs
     *    - PF0 & PF4 as inputs for switch buttons
     *    .
     */
    /* Enable the GPIO pins for the LEDs (PF1, PF2 & PF3) */
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    /* configure GPIO pins of switch 1 & 2 */
    /* change GPIO F0 to GPIO function (originally JTAG mode!!!) */
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_AFSEL) &= 0xfe;

    ROM_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
    ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0, GPIO_PIN_TYPE_STD_WPU);

    /* Enable watchdog */
    ROM_WatchdogUnlock(WATCHDOG0_BASE);
    ROM_WatchdogStallEnable(WATCHDOG0_BASE);
    ROM_WatchdogReloadSet(WATCHDOG0_BASE, (uint32)400000);
    ROM_WatchdogResetEnable(WATCHDOG0_BASE);
    // TODO watchdog currently disabled because random resets (Hard Fault IRQ) will occur with enabled watchdog
    //ROM_WatchdogEnable(WATCHDOG0_BASE);
    ROM_WatchdogLock(WATCHDOG0_BASE);


    /** - Configuration of 32-bit timer 0 for interrupt generation:
     *    - periodic mode
     *    - 5 kHz
     *    .
     */
    ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, 16000);

    /** - Enable processor interrupts */
    ROM_IntMasterEnable();

    /* Setup the interrupt for the timer timeouts */
    ROM_IntEnable(INT_TIMER0A);
    ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    /** - Enable timers */
    ROM_TimerEnable(TIMER0_BASE, TIMER_A);

}

/**
 * @brief Initialization of serial interface.
 *
 * @param serialP Serial object
 */
void initSerial(tSerial* serialP)
{
    serialP->send = (void (*)(tInterface*, uint8))sendSerial;
    serialP->receive = (uint8 (*)(tInterface*))receiveSerial;
    serialP->isReceiveDataAvailable = (uint8 (*)(tInterface*))isReceiveDataAvailable;
    serialP->isSendReady = (uint8 (*)(tInterface*))isSendReady;
}


static void sendSerial(tSerial* serial, uint8 data)
{
	ROM_UARTCharPut(UART0_BASE, data);
}

static uint8 receiveSerial(tSerial* serial)
{
    return ((uint8)ROM_UARTCharGetNonBlocking(UART0_BASE));
}

static uint8 isReceiveDataAvailable(tSerial* serial)
{
    return (ROM_UARTCharsAvail(UART0_BASE));
}

static uint8 isSendReady(tSerial* serial)
{
    return (!ROM_UARTBusy(UART0_BASE));
}

/*
 * Interrupt vector table.
 */
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
                                            // The initial stack pointer
    ResetISR,                              // The reset handler
    UnusedISR,                              // The NMI handler
    UnusedISR,                              // The hard fault handler
    UnusedISR,                      // The MPU fault handler
    UnusedISR,                      // The bus fault handler
    UnusedISR,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    UnusedISR,                      // SVCall handler
    UnusedISR,                      // Debug monitor handler
    0,                                      // Reserved
    UnusedISR,                      // The PendSV handler
    UnusedISR,                      // The SysTick handler
    UnusedISR,                      // GPIO Port A
    UnusedISR,                      // GPIO Port B
    UnusedISR,                      // GPIO Port C
    UnusedISR,                      // GPIO Port D
    UnusedISR,                      // GPIO Port E
    UnusedISR,                      // UART0 Rx and Tx
    UnusedISR,                      // UART1 Rx and Tx
    UnusedISR,                      // SSI0 Rx and Tx
    UnusedISR,                      // I2C0 Master and Slave
    UnusedISR,                      // PWM Fault
    UnusedISR,                      // PWM Generator 0
    UnusedISR,                      // PWM Generator 1
    UnusedISR,                      // PWM Generator 2
    UnusedISR,                      // Quadrature Encoder 0
    UnusedISR,                      // ADC Sequence 0
    UnusedISR,                      // ADC Sequence 1
    UnusedISR,                      // ADC Sequence 2
    UnusedISR,                      // ADC Sequence 3
    UnusedISR,                      // Watchdog timer
    Timer0IntHandler,                      // Timer 0 subtimer A
    UnusedISR,                      // Timer 0 subtimer B
    UnusedISR,                      // Timer 1 subtimer A
    UnusedISR,                      // Timer 1 subtimer B
    UnusedISR,                      // Timer 2 subtimer A
    UnusedISR,                      // Timer 2 subtimer B
    UnusedISR,                      // Analog Comparator 0
    UnusedISR,                      // Analog Comparator 1
    UnusedISR,                      // Analog Comparator 2
    UnusedISR,                      // System Control (PLL, OSC, BO)
    UnusedISR,                      // FLASH Control
    UnusedISR,                      // GPIO Port F
    UnusedISR,                      // GPIO Port G
    UnusedISR,                      // GPIO Port H
    UnusedISR,                      // UART2 Rx and Tx
    UnusedISR,                      // SSI1 Rx and Tx
    UnusedISR,                      // Timer 3 subtimer A
    UnusedISR,                      // Timer 3 subtimer B
    UnusedISR,                      // I2C1 Master and Slave
    UnusedISR,                      // Quadrature Encoder 1
    UnusedISR,                      // CAN0
    UnusedISR,                      // CAN1
    UnusedISR,                      // CAN2
    0,                                      // Reserved
    UnusedISR,                      // Hibernate
    UnusedISR,                      // USB0
    UnusedISR,                      // PWM Generator 3
    UnusedISR,                      // uDMA Software Transfer
    UnusedISR,                      // uDMA Error
    UnusedISR,                      // ADC1 Sequence 0
    UnusedISR,                      // ADC1 Sequence 1
    UnusedISR,                      // ADC1 Sequence 2
    UnusedISR,                      // ADC1 Sequence 3
    0,                                      // Reserved
    0,                                      // Reserved
    UnusedISR,                      // GPIO Port J
    UnusedISR,                      // GPIO Port K
    UnusedISR,                      // GPIO Port L
    UnusedISR,                      // SSI2 Rx and Tx
    UnusedISR,                      // SSI3 Rx and Tx
    UnusedISR,                      // UART3 Rx and Tx
    UnusedISR,                      // UART4 Rx and Tx
    UnusedISR,                      // UART5 Rx and Tx
    UnusedISR,                      // UART6 Rx and Tx
    UnusedISR,                      // UART7 Rx and Tx
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    UnusedISR,                      // I2C2 Master and Slave
    UnusedISR,                      // I2C3 Master and Slave
    UnusedISR,                      // Timer 4 subtimer A
    UnusedISR,                      // Timer 4 subtimer B
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    UnusedISR,                      // Timer 5 subtimer A
    UnusedISR,                      // Timer 5 subtimer B
    UnusedISR,                      // Wide Timer 0 subtimer A
    UnusedISR,                      // Wide Timer 0 subtimer B
    UnusedISR,                      // Wide Timer 1 subtimer A
    UnusedISR,                      // Wide Timer 1 subtimer B
    UnusedISR,                      // Wide Timer 2 subtimer A
    UnusedISR,                      // Wide Timer 2 subtimer B
    UnusedISR,                      // Wide Timer 3 subtimer A
    UnusedISR,                      // Wide Timer 3 subtimer B
    UnusedISR,                      // Wide Timer 4 subtimer A
    UnusedISR,                      // Wide Timer 4 subtimer B
    UnusedISR,                      // Wide Timer 5 subtimer A
    UnusedISR,                      // Wide Timer 5 subtimer B
    UnusedISR,                      // FPU
    0,                                      // Reserved
    0,                                      // Reserved
    UnusedISR,                      // I2C4 Master and Slave
    UnusedISR,                      // I2C5 Master and Slave
    UnusedISR,                      // GPIO Port M
    UnusedISR,                      // GPIO Port N
    UnusedISR,                      // Quadrature Encoder 2
    0,                                      // Reserved
    0,                                      // Reserved
    UnusedISR,                      // GPIO Port P (Summary or P0)
    UnusedISR,                      // GPIO Port P1
    UnusedISR,                      // GPIO Port P2
    UnusedISR,                      // GPIO Port P3
    UnusedISR,                      // GPIO Port P4
    UnusedISR,                      // GPIO Port P5
    UnusedISR,                      // GPIO Port P6
    UnusedISR,                      // GPIO Port P7
    UnusedISR,                      // GPIO Port Q (Summary or Q0)
    UnusedISR,                      // GPIO Port Q1
    UnusedISR,                      // GPIO Port Q2
    UnusedISR,                      // GPIO Port Q3
    UnusedISR,                      // GPIO Port Q4
    UnusedISR,                      // GPIO Port Q5
    UnusedISR,                      // GPIO Port Q6
    UnusedISR,                      // GPIO Port Q7
    UnusedISR,                      // GPIO Port R
    UnusedISR,                      // GPIO Port S
    UnusedISR,                      // PWM 1 Generator 0
    UnusedISR,                      // PWM 1 Generator 1
    UnusedISR,                      // PWM 1 Generator 2
    UnusedISR,                      // PWM 1 Generator 3
    UnusedISR                       // PWM 1 Fault
};


/*
 * Timer 0 interrupt starts main control task.
 */
interrupt void Timer0IntHandler(void)
{
	ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	mainTask();
}

/*
 * Unused ISR.
 */
interrupt void UnusedISR(void)
{
	while (1)
	{
		/* resets target if watchdog is being enabled */
	}
}

/*
 * Reset ISR.
 * Jump to the CCS C initialization routine.
 * This will enable the floating-point unit as well, so that does not need to be done here.
 */
interrupt void ResetISR(void)
{

    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}
