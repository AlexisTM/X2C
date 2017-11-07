/* $LastChangedRevision: 851 $
 * $LastChangedDate:: 2015-11-05 15:25:38 +0100 $
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

/* ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1) */
#pragma config ICS = PGD1

/* Select internal FRC without PLL at POR */
_FOSCSEL(FNOSC_FRC);
/* Enable Clock Switching, disable primary oscillator and disable clock out function */
_FOSC(FCKSM_CSECMD & POSCMD_NONE & OSCIOFNC_OFF);


/** 
 * @brief Hardware initialization.
 */
void initHardware(void)
{
    /*------------------------------------------------------------------------*/
    /** - Configuration of oscillator
     *    - Internal oscillator (fast RC oscillator with PLL)
     *    - fCY = 40MHz
     *    .
     */
    /*------------------------------------------------------------------------*/
    /* Configure PLL prescaler, PLL postscaler, PLL divisor
     * FRC frequency: 7.37MHz -> tuning to 8MHz
     * NOTE: FRC frequency is not accurate -> frequency may vary!
     * fCY = 8MHz * 40/(2*2) / 2 = 40MHz
     */
    OSCTUNbits.TUN = 23;        /* 7.37MHz + 23*0.00375*7.37MHz = 8MHz */
    PLLFBDbits.PLLDIV = 38;     /* M = 38 + 2 = 40 */
    CLKDIVbits.PLLPOST = 0;     /* N2 = 2*(0+1) = 2 */
    CLKDIVbits.PLLPRE = 0;      /* N1 = 0 + 2 = 2 */

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
    /** - Configuration of serial port
     *    - Baudrate: 115.2kB/s
     *    - Data bits: 8
     *    - Parity: none
     *    - Stop bits: 1
     *    .
     */ 
    /*------------------------------------------------------------------------*/
    RPINR18bits.U1RXR = 11;     /* map UART #1 rx to RP11 */
    RPOR5bits.RP10R = 3;        /* map UART #1 tx to RP43 */

    U1BRG = 21;                 /* set baudrate to 115200bps (21 = (fCY/baudrate/16)-1)*/
    U1MODEbits.ABAUD = 0;       /* disable automatic baud rate measurement */
    U1MODEbits.PDSEL = 0b00;    /* 8-bit data, no parity */
    U1MODEbits.STSEL = 0;       /* 1 stop bit */
    U1MODEbits.UARTEN = 01;     /* enable UART 1 */
    U1STAbits.UTXEN = 1;        /* enable transmitter */


    /*------------------------------------------------------------------------*/
    /** - Configuration of IO ports */
    /*------------------------------------------------------------------------*/
    /* LED1 */
    TRISBbits.TRISB12 = 0;  /* digital output */
    LATBbits.LATB12 = 0;    /* LED off */
    /* LED2 */
    TRISBbits.TRISB13 = 0;  /* digital output */
    LATBbits.LATB13 = 0;    /* LED off */
    /* LED3 */
    TRISBbits.TRISB14 = 0;  /* digital output */
    LATBbits.LATB14 = 0;    /* LED off */
    /* LED4 */
    TRISBbits.TRISB15 = 0;  /* digital output */
    LATBbits.LATB15 = 0;    /* LED off */

    /* UART1 Rx */
    TRISBbits.TRISB11 = 1;  /* RB11: digital input (UART Rx configuration is done in serialInit()) */
    CNPU1bits.CN11PUE = 1;  /* activate weak pull up */
    
    /* VPOT */
    AD1PCFGLbits.PCFG0 = 0; /* AN0: analog input */
    /* VTEMP */
    AD1PCFGLbits.PCFG1 = 0; /* AN1: analog input */

    /* PIEZO */
    TRISBbits.TRISB5 = 0;       /* digital ouput */
    RPOR2bits.RP5R = 0b10010;   /* map OC1 to RP5 */

    /* Encoder */
    RPINR14bits.QEA1R = 6;     /* map QEA1 to RP6 */
    RPINR14bits.QEB1R = 7;     /* map QEB1 to RP7 */


    /*------------------------------------------------------------------------*/
    /** - Configuration of ADC
     *    - 10 bit mode
     *    - internal RC clock source
     *    - continuous sampling and auto conversion
     *    .
     */
    /*------------------------------------------------------------------------*/
    AD1CON1bits.AD12B = 0;      /* 10bit mode */
    AD1CON2bits.VCFG = 0b000;   /* AVdd and AVss as voltage reference */
    AD1CON3bits.ADRC = 1;       /* ADC uses internal RC clock */
    AD1CON2bits.CHPS = 0b00;    /* converts CH0 */
    AD1CHS0bits.CH0SA = 0b0000; /* channel 0 positive input is AN0 */
    AD1CON1bits.SIMSAM = 1;     /* simultaneously sampling */
    AD1CON1bits.ASAM = 1;       /* sampling begins after last conversion */
    AD1CON1bits.SSRC = 0b111;   /* internal counter ends sampling and starts conversion (auto conversion) */
    AD1CON3bits.SAMC = 0b00000; /* not used for SSRC = 0b111 */
    AD1CON1bits.FORM = 0b00;    /* integer output (right aligned) */
    AD1CON1bits.ADON = 1;       /* enable ADC */

    /*------------------------------------------------------------------------*/
    /** - Configuration of QEP unit */
    /*------------------------------------------------------------------------*/
    QEI1CONbits.QEIM = 0b111;   /* QEI enabled (x4 mode) with counter reset by match */
    MAX1CNT = 0x7FFF;           /* only positive numbers [Q15] */

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


    /*------------------------------------------------------------------------*/
    /** - Configuration of Timer 2 unit for compare unit (PWM) */
    /*------------------------------------------------------------------------*/
    T2CONbits.TCS = 0;      /* internal clock (fCY) */
    T2CONbits.TGATE = 0;    /* timer in counter mode */
    T2CONbits.TCKPS = 0b00; /* 1:1 prescaler */
    PR2 = PWM_FREQUENCY;    /* @ fCY = 40MHz -> 4kHz PWM frquency */
    TMR2 = 0x0000;          /* clear timer 2 value */
    T2CONbits.TON = 1;      /* start timer 2 */

    /*------------------------------------------------------------------------*/
    /** - Configuration of compare unit for PWM */
    /*------------------------------------------------------------------------*/
    OC1CONbits.OCTSEL = 0;      /* timer 2 as clock source */
    OC1R = 0x0000;              /* clear compare value */
    OC1RS = 0x0000;             /* clear secondary compare value */
    OC1CONbits.OCM = 0b110;     /* PWM mode, fault pin disabled */
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
    serial->receive = (uint8 (*)(tInterface*))receiveSerial;
    serial->isReceiveDataAvailable = (uint8 (*)(tInterface*))isReceiveDataAvailable;
    serial->isSendReady = (uint8 (*)(tInterface*))isSendReady;
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
        return ((uint8)0);
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
