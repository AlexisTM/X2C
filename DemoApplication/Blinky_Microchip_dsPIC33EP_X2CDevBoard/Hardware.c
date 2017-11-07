/* $LastChangedRevision: 874 $
 * $LastChangedDate:: 2016-02-18 14:43:14 +0100#$
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

#include "Target.h"
#include "Main.h"
#include "Hardware.h"

/* private prototypes */
static void sendSerial(tSerial* serial, uint8 data);
static uint8 receiveSerial(tSerial* serial);
static uint8 isReceiveDataAvailable(tSerial* serial);
static uint8 isSendReady(tSerial* serial);

/* private macros */
#define FCY             (39982250UL)            /* instruction cycle frequency */
#define BAUDRATE        115200                  /* baudrate for serial interface */
#define BRGVAL          (((FCY/BAUDRATE)/16)-1) /* for BRGH = 0 */

// FICD
#pragma config ICS = PGD3               // ICD Communication Channel Select bits (Communicate on PGEC3 and PGED3)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer always enabled)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)

#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSECMD           // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Source Selection (Fast RC Oscillator with divide-by-N with PLL module (FRCPLL))
#pragma config PWMLOCK = ON             // PWM Lock Enable bit (Certain PWM registers may only be written after key sequence)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)


/** 
 * @brief Hardware initialization.
 */
void initHardware(void)
{
    /*------------------------------------------------------------------------*/
    /** - Configuration of oscillator
    *    - Internal oscillator (fast RC oscillator with PLL)
    *    - fCY = 40MHz (39.98MHz)
    *    .
    */
    /*------------------------------------------------------------------------*/   
    /* Configure PLL prescaler, PLL postscaler, PLL divisor
     * FRC frequency: 7.37MHz
     * NOTE: FRC frequency is not accurate -> frequency may vary!
     * fCY = 7.37MHz * 217/(4*5) / 2 = 39.98225MHz
     */
    PLLFBDbits.PLLDIV = 215;    /* M = 215 + 2 = 217 */
    CLKDIVbits.PLLPOST = 1;     /* N2 = 2*(1+1) = 4 */
    CLKDIVbits.PLLPRE = 3;      /* N1 = 3 + 2 = 5 */

    /* Switch to FRC with PLL */
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    /* Wait for Clock switch to occur */
    while (OSCCONbits.COSC != 0x01);
    /* Wait for PLL to lock */
    while(OSCCONbits.LOCK != 1) {};

    /* Enable watchdog */
    RCONbits.SWDTEN = 1;


    /*------------------------------------------------------------------------*/
    /** - Configuration of IO ports */
    /*------------------------------------------------------------------------*/
    /* LED1 */
    TRISBbits.TRISB6 = 0; /* digital output */
    LATBbits.LATB6 = 0; /* LED off */
    /* LED2 */
    TRISBbits.TRISB7 = 0; /* digital output */
    LATBbits.LATB7 = 0; /* LED off */
    /* LED3 */
    TRISBbits.TRISB8 = 0; /* digital output */
    LATBbits.LATB8 = 0; /* LED off */
    /* LED4 */
    TRISBbits.TRISB9 = 0; /* digital output */
    LATBbits.LATB9 = 0; /* LED off */

    /* PB1 */
    ANSELAbits.ANSA4 = 0;
    TRISAbits.TRISA4 = 1;   /* digital input */
    /* PB2 */
    TRISBbits.TRISB5 = 1;   /* digital input */

    /* UART1 Rx */
    ANSELBbits.ANSB2 = 0;
    TRISBbits.TRISB2 = 1;
    RPINR18bits.U1RXR = 34;     /* map UART1 Rx to RP34 */
    /* UART1 Tx */
    ANSELBbits.ANSB3 = 0;
    TRISBbits.TRISB3 = 0;
    RPOR0bits.RP35R = 1;        /* map UART1 Tx to RP35 */

    /* VPot */
    ANSELAbits.ANSA1 = 1; /* AN1: analog input */
    /* VTouch */
    ANSELAbits.ANSA0 = 1; /* AN0: analog input */
    
    
    /*------------------------------------------------------------------------*/
    /** - Configuration of serial port
     *    - Baudrate: 115.2kB/s
     *    - Data bits: 8
     *    - Parity: none
     *    - Stop bits: 1
     *    .
     */ 
    /*------------------------------------------------------------------------*/
    U1BRG = BRGVAL;             /* set baudrate */
    U1MODEbits.ABAUD = 0;       /* disable automatic baud rate measurement */
    U1MODEbits.PDSEL = 0b00;    /* 8-bit data, no parity */
    U1MODEbits.STSEL = 0;       /* 1 stop bit */
    U1MODEbits.UARTEN = 1;      /* enable UART 1 */
    U1STAbits.UTXEN = 1;        /* enable transmitter */
    

    /*------------------------------------------------------------------------*/
    /** - Configuration of ADC
     *    - 10 bit mode
     *    - internal RC clock source
     *    - continuous sampling and auto conversion
     *    - channel scan AN0, AN1
     *    .
     */
    /*------------------------------------------------------------------------*/
    AD1CON1bits.AD12B = 0;      /* 10bit mode */
    AD1CON2bits.VCFG = 0b000;   /* AVdd and AVss as voltage reference */
    AD1CON3bits.ADRC = 1;       /* ADC uses internal RC clock */
    AD1CON2bits.CHPS = 0b00;    /* converts CH0 */
    AD1CON2bits.CSCNA = 1;      /* scan channel 0 */
    AD1CON2bits.SMPI = 1;       /* scan 2 channels */
    AD1CHS0bits.CH0NA = 0;      /* channel 0 negative input is Vrefl */
    AD1CHS0bits.CH0SA = 0b0000; /* channel 0 positive input is AN0 */
    AD1CSSLbits.CSS0 = 1;       /* select AN0 for input scan */
    AD1CSSLbits.CSS1 = 1;       /* select AN1 for input scan */
    AD1CON1bits.SIMSAM = 1;     /* simultaneously sampling */
    AD1CON1bits.ASAM = 1;       /* sampling begins after last conversion */
    AD1CON1bits.SSRCG = 0;      /* sample trigger group 0 */
    AD1CON1bits.SSRC = 0b111;   /* internal counter ends sampling and starts conversion (auto conversion) */
    AD1CON3bits.SAMC = 0b00000; /* not used for SSRC = 0b111 */
    AD1CON1bits.FORM = 0b00;    /* integer output (right aligned) */
    AD1CON1bits.ADON = 1;       /* enable ADC */


    /*------------------------------------------------------------------------*/
    /** - Configuration of Timer 1 unit for sampling time (100us) */
    /*------------------------------------------------------------------------*/
    T1CONbits.TCS = 0;      /* internal clock (fCY) */
    T1CONbits.TGATE = 0;    /* timer in counter mode */
    T1CONbits.TCKPS = 0b00; /* 1:1 prescaler */
    PR1 = 4000;             /* @ fCY = 40MHz -> 100us timebase */
    TMR1 = 0x0000;          /* clear timer 1 value */
    IFS0bits.T1IF = 0;      /* clear interrupt flag */
    IEC0bits.T1IE = 1;      /* set interrupt enable bit */
    T1CONbits.TON = 1;      /* start timer 1 */

}


/*============================================================================*/
/* Initialization of serial interface (overriding methods) */
/*============================================================================*/
/**
 * @brief Initialization of serial interface.
 * 
 * @param serial Serial interface object.
 */
void initSerial(tSerial* serial)
{
  serial->send = (void (*)(tInterface*, uint8))sendSerial;
  serial->receive = (uint8(*)(tInterface*))receiveSerial;
  serial->isReceiveDataAvailable = (uint8(*)(tInterface*))isReceiveDataAvailable;
  serial->isSendReady = (uint8(*)(tInterface*))isSendReady;
}


/**
 * @brief Routine to send data over serial interface.
 * 
 * @param serial Serial interface object.
 * @param data Data byte to send.
 */
static void sendSerial(tSerial* serial, uint8 data)
{
  U1TXREG = data;
}


/**
 * @brief Routine to fetch data from the serial interface.
 * 
 * @param serial Serial interface object.
 * @return Received data byte.
 */
static uint8 receiveSerial(tSerial* serial)
{
  if (U1STA & 0x0E)
  {
    U1STAbits.OERR = 0; /* reset error */
    return ((uint8) 0);
  }
  return (U1RXREG);
}


/**
 * @brief Routine to check if data from the serial interface is available.
 * 
 * @param serial Serial interface object.
 * @return 1 when data is available, 0 otherwise.
 */
static uint8 isReceiveDataAvailable(tSerial* serial)
{
  return (U1STAbits.URXDA);
}


/**
 * @brief Routine to check if data can be send over the serial interface.
 *  
 * @param serial Serial interface object.
 * @return 1 when data can be send, 0 otherwise.
 */
static uint8 isSendReady(tSerial* serial)
{
  return (!U1STAbits.UTXBF);
}


/**
 * @brief Interrupt service routine for Timer 1.
 * 
 * This routine will be called every 100us (= sample time) and calls the main
 * application task.
 */
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
  IFS0bits.T1IF = 0; /* clear interrupt flag */
  mainTask();
}
