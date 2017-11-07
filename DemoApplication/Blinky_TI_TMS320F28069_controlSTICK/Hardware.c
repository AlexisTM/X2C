/*
 * Hardware configuration.
 *
 * $LastChangedRevision: 541 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "Target.h"
#include "Main.h"
#include "Hardware.h"

#define TX_FIFO_SIZE ((uint16)4)

/* private prototypes */
static void delayMicroseconds(uint16 time);
static void sendSerial(tSerial* serialP, uint8 data);
static uint8 receiveSerial(tSerial* serialP);
static uint8 isReceiveDataAvailable(tSerial* serialP);
static uint8 isSendReady(tSerial* serialP);
interrupt void UnusedIsr(void);
interrupt void ADCIsr(void);

/*
 * Delay function.
 */
static void delayMicroseconds(uint16 time)
{
   	uint16 i;

   	for (i=0;i<time;i++)
   	{
		asm(" RPT #90 || NOP");
	}
}


/*
 * Hardware initialization.
 */
void initHardware(void)
{

	EALLOW;

	/************************************************/
	/*	Clock & Watchdog Setup                      */
	/************************************************/
	/* don't continue if device is in limp mode */
	while (SysCtrlRegs.PLLSTS.bit.MCLKSTS == (uint16)0x0001);
	/* disable watchdog during PLL init */
	SysCtrlRegs.WDCR = (uint16)0x0068;
	/* set DIVSEL to 0 */
	SysCtrlRegs.PLLSTS.bit.DIVSEL = (uint16)0x0000;
	/* disable failed oscillator detect logic */
	SysCtrlRegs.PLLSTS.bit.MCLKOFF = (uint16)0x0001;

	/* set PLL multiplier = 9 */
	SysCtrlRegs.PLLCR.bit.DIV = (uint16)0x0009;

	/* wait for PLL to lock */
	while (SysCtrlRegs.PLLSTS.bit.PLLLOCKS == (uint16)0x0001);

	/* enable failed oscillator detect logic */
	SysCtrlRegs.PLLSTS.bit.MCLKOFF = (uint16)0x0000;
	/* set DIVSEL to 3 -> clock divider = 1 */
	SysCtrlRegs.PLLSTS.bit.DIVSEL = (uint16)0x0003;

	/* SYSCLK = OSCCLK * PLLMULT / CLKDIV */
	/* -> 10 MHz * 9 / 1 = 90 MHz */

	/* enable watchdog with prescaler 1 */
	/* (watchdog timeout = 512 * PS / OSCCLK * 2^8 */
	/* -> 512 * 1 / 10e6 * 2^8 = ~ 13 ms) */
	SysCtrlRegs.WDCR = (uint16)0x00A8;

	/* LOSPCP = SYSCLK */
	SysCtrlRegs.LOSPCP.bit.LSPCLK = (uint16)0x0000;

	/************************************************/
	/*	Peripheral Clock Control Register           */
	/************************************************/
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = (uint16)1;
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = (uint16)1;

	/************************************************/
	/*	General Purpose Inputs and Outputs          */
	/************************************************/
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = (uint16)1;		/* direction = output */
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = (uint16)0;	/* function = GPIO */

	GpioCtrlRegs.GPBDIR.bit.GPIO33 = (uint16)0;		/* direction = input */
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = (uint16)0;	/* function = GPIO */


	/************************************************/
	/*	Interrupt initialization                    */
	/************************************************/
	/* disable & clear all CPU interrupts */
	DINT;

    /* enable PIE */
	PieCtrlRegs.PIECTRL.bit.ENPIE = (uint16)1;
	/* enable PI block to drive interrupts into the core (0 are ignored) */
	PieCtrlRegs.PIEACK.all = (uint16)0xFFFF;
	/* enable PIE (1.1 = SEQ1INT) */
	PieCtrlRegs.PIEIER1.bit.INTx1 = (uint16)1;
	/* enable IRQ 1 */
	IER |= (uint16)0x0001;
	/* enable global interrupt bit */
	EINT;

	/************************************************/
	/*	Init ADC                                    */
	/************************************************/
	/* reset ADC and wait 2 cycles for re-writing register */
	AdcRegs.ADCCTL1.bit.RESET = (uint16)1;
	asm(" RPT #2 || NOP");

	/* power up reference, bandgap & analog circuits */
	AdcRegs.ADCCTL1.bit.ADCPWDN = (uint16)1;
	AdcRegs.ADCCTL1.bit.ADCBGPWD = (uint16)1;
	AdcRegs.ADCCTL1.bit.ADCREFPWD = (uint16)1;

	/* wait at least 1 ms */
	delayMicroseconds(1000);

	/* set INT signal when value is written to result register */
	/* and enable ADC */
	AdcRegs.ADCCTL1.bit.INTPULSEPOS = (uint16)1;
	AdcRegs.ADCCTL1.bit.ADCENABLE = (uint16)1;

	/* enable ADCINT1, source = EOC0 */
	AdcRegs.INTSEL1N2.bit.INT1E = (uint16)1;

	/* simultaneous sample for all channels */
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = (uint16)1;
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN2 = (uint16)1;
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN4 = (uint16)1;
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN6 = (uint16)1;
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN8 = (uint16)1;
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN10 = (uint16)1;
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN12 = (uint16)1;
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN14 = (uint16)1;

	/* sample window is 7 cycles long */
	AdcRegs.ADCSOC0CTL.bit.ACQPS = (uint16)6;
	/* channel select = ADCINA0/ADCINB0 pair */
	AdcRegs.ADCSOC0CTL.bit.CHSEL = (uint16)0;
	/* trigger source = ADCTRIG5 � ePWM1, ADCSOCA */
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = (uint16)5;

	/************************************************/
	/*	Timer Initialization					 	*/
	/************************************************/
	EPwm1Regs.TBPRD = (uint16)4500;
	EPwm1Regs.TBCTL.bit.FREE_SOFT = (uint16)3;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = (uint16)0;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = (uint16)3;
	EPwm1Regs.TBCTL.bit.CTRMODE = (uint16)2;

	/* enable ADC SOC A on timer period */
	EPwm1Regs.ETSEL.bit.SOCASEL = (uint16)2;
	EPwm1Regs.ETSEL.bit.SOCAEN = (uint16)1;

	/* start SOC A event on the first event */
	EPwm1Regs.ETPS.bit.SOCAPRD = (uint16)1;

	/* enable timer base module clock after all ePWM have been configured */
	/* (required for exact synchronization if used) */
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = (uint16)1;

	EDIS;
}


/*
 * Serial interface initialization.
 */
void initSerial(tSerial* serial)
{
	EALLOW;

	/* enable SCI-A clock */
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = (uint16)1;

	/* Tx = GPIO29 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = (uint16)0x1;
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = (uint16)1;

	/* Rx = GPIO28 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = (uint16)0x1;
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = (uint16)1;


	SciaRegs.SCICCR.all = (uint16)0x0007;
	/* software reset */
	SciaRegs.SCICTL1.all = (uint16)0x0000;
	SciaRegs.SCICTL1.all = (uint16)0x0023;

	SciaRegs.SCICTL2.all = (uint16)0x0000;

	/* baudrate = 115200 @ SYSCLK = 90MHz */
	SciaRegs.SCIHBAUD = 0x00;
	SciaRegs.SCILBAUD = 0x61;


	SciaRegs.SCIFFTX.all = (uint16)0xE040;
	SciaRegs.SCIFFRX.all = (uint16)0x6040;
	SciaRegs.SCIFFCT.all = (uint16)0x0000;
	SciaRegs.SCIPRI.all = (uint16)0x0000;

	EDIS;

	serial->send = (void (*)(tInterface*, uint8))sendSerial;
	serial->receive = (uint8 (*)(tInterface*))receiveSerial;
	serial->isReceiveDataAvailable = (uint8 (*)(tInterface*))isReceiveDataAvailable;
	serial->isSendReady = (uint8 (*)(tInterface*))isSendReady;
}


/*
 * Serial send procedure.
 */
static void sendSerial(tSerial* serialP, uint8 data)
{
	SciaRegs.SCITXBUF = (uint16)data;
}

/*
 * Serial receive procedure.
 */
static uint8 receiveSerial(tSerial* serialP)
{
	/* reset if receive error occurred */
	if (SciaRegs.SCIRXST.bit.RXERROR == (uint16)1)
	{
		SciaRegs.SCICTL1.all = (uint16)0x0003;
		SciaRegs.SCICTL1.all = (uint16)0x0023;
	}
	return (SciaRegs.SCIRXBUF.bit.RXDT);
}

/*
 * Checks if serial data is available.
 */
static uint8 isReceiveDataAvailable(tSerial* serialP)
{
	return (SciaRegs.SCIFFRX.bit.RXFFST != 0);
}

/*
 * Checks if serial interface is ready to send.
 */
static uint8 isSendReady(tSerial* serialP)
{
	return ((uint8)(TX_FIFO_SIZE - SciaRegs.SCIFFTX.bit.TXFFST));
}


/*
 * Interrupt service routine for unused interrupt.
 */
interrupt void UnusedIsr(void)
{
	/* enable watchdog */
	EALLOW;
	SysCtrlRegs.WDCR = (uint16)0x00A8;
	EDIS;

	while (1)
	{
		/* wait for watchdog to reboot dsp */
	}
}

/*
 * Interrupt service routine for ADC end of conversion.
 */
interrupt void ADCIsr(void)
{
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = (uint16)1;
	PieCtrlRegs.PIEACK.all = (uint16)0x0001;

	/* control task */
	mainTask();
}


/*
 * Initialize interrupt vector table.
 */
void initInterruptVector(void)
{
	EALLOW;

	/* unused interrupts */
	/* TI recommends to not overwrite the first three entries because of */
	/* being used by bootloader functions */
/*	PieVectTable.PIE1_RESERVED = &UnusedIsr; */
/*	PieVectTable.PIE2_RESERVED = &UnusedIsr; */
/*	PieVectTable.PIE3_RESERVED = &UnusedIsr; */
	PieVectTable.PIE4_RESERVED = &UnusedIsr;
	PieVectTable.PIE5_RESERVED = &UnusedIsr;
	PieVectTable.PIE6_RESERVED = &UnusedIsr;
	PieVectTable.PIE7_RESERVED = &UnusedIsr;
	PieVectTable.PIE8_RESERVED = &UnusedIsr;
	PieVectTable.PIE9_RESERVED = &UnusedIsr;
	PieVectTable.PIE10_RESERVED = &UnusedIsr;
	PieVectTable.PIE11_RESERVED = &UnusedIsr;
	PieVectTable.PIE12_RESERVED = &UnusedIsr;
	PieVectTable.PIE13_RESERVED = &UnusedIsr;
	PieVectTable.TINT1 = &UnusedIsr;
	PieVectTable.TINT2 = &UnusedIsr;
	PieVectTable.DATALOG = &UnusedIsr;
	PieVectTable.RTOSINT = &UnusedIsr;
	PieVectTable.EMUINT = &UnusedIsr;
	PieVectTable.NMI = &UnusedIsr;
	PieVectTable.ILLEGAL = &UnusedIsr;
	PieVectTable.USER1 = &UnusedIsr;
	PieVectTable.USER2 = &UnusedIsr;
	PieVectTable.USER3 = &UnusedIsr;
	PieVectTable.USER4 = &UnusedIsr;
	PieVectTable.USER5 = &UnusedIsr;
	PieVectTable.USER6 = &UnusedIsr;
	PieVectTable.USER7 = &UnusedIsr;
	PieVectTable.USER8 = &UnusedIsr;
	PieVectTable.USER9 = &UnusedIsr;
	PieVectTable.USER10 = &UnusedIsr;
	PieVectTable.USER11 = &UnusedIsr;
	PieVectTable.USER12 = &UnusedIsr;
	PieVectTable.ADCINT1 = &UnusedIsr;
	PieVectTable.ADCINT2 = &UnusedIsr;
	PieVectTable.rsvd1_3 = &UnusedIsr;
	PieVectTable.XINT1 = &UnusedIsr;
	PieVectTable.XINT2 = &UnusedIsr;
	PieVectTable.ADCINT9 = &UnusedIsr;
	PieVectTable.TINT0 = &UnusedIsr;
	PieVectTable.WAKEINT = &UnusedIsr;
	PieVectTable.EPWM1_TZINT = &UnusedIsr;
	PieVectTable.EPWM2_TZINT = &UnusedIsr;
	PieVectTable.EPWM3_TZINT = &UnusedIsr;
	PieVectTable.EPWM4_TZINT = &UnusedIsr;
	PieVectTable.EPWM5_TZINT = &UnusedIsr;
	PieVectTable.EPWM6_TZINT = &UnusedIsr;
	PieVectTable.EPWM7_TZINT = &UnusedIsr;
	PieVectTable.EPWM8_TZINT = &UnusedIsr;
	PieVectTable.EPWM1_INT = &UnusedIsr;
	PieVectTable.EPWM2_INT = &UnusedIsr;
	PieVectTable.EPWM3_INT = &UnusedIsr;
	PieVectTable.EPWM4_INT = &UnusedIsr;
	PieVectTable.EPWM5_INT = &UnusedIsr;
	PieVectTable.EPWM6_INT = &UnusedIsr;
	PieVectTable.EPWM7_INT = &UnusedIsr;
	PieVectTable.EPWM8_INT = &UnusedIsr;
	PieVectTable.ECAP1_INT = &UnusedIsr;
	PieVectTable.ECAP2_INT = &UnusedIsr;
	PieVectTable.ECAP3_INT = &UnusedIsr;
	PieVectTable.rsvd4_4 = &UnusedIsr;
	PieVectTable.rsvd4_5 = &UnusedIsr;
	PieVectTable.rsvd4_6 = &UnusedIsr;
	PieVectTable.HRCAP1_INT = &UnusedIsr;
	PieVectTable.HRCAP2_INT = &UnusedIsr;
	PieVectTable.EQEP1_INT = &UnusedIsr;
	PieVectTable.EQEP2_INT = &UnusedIsr;
	PieVectTable.rsvd5_3 = &UnusedIsr;
	PieVectTable.HRCAP3_INT = &UnusedIsr;
	PieVectTable.HRCAP4_INT = &UnusedIsr;
	PieVectTable.rsvd5_6 = &UnusedIsr;
	PieVectTable.rsvd5_7 = &UnusedIsr;
	PieVectTable.USB0_INT = &UnusedIsr;
	PieVectTable.SPIRXINTA = &UnusedIsr;
	PieVectTable.SPITXINTA = &UnusedIsr;
	PieVectTable.SPIRXINTB = &UnusedIsr;
	PieVectTable.SPITXINTB = &UnusedIsr;
	PieVectTable.MRINTA = &UnusedIsr;
	PieVectTable.MXINTA = &UnusedIsr;
	PieVectTable.rsvd6_7 = &UnusedIsr;
	PieVectTable.rsvd6_8 = &UnusedIsr;
	PieVectTable.DINTCH1 = &UnusedIsr;
	PieVectTable.DINTCH2 = &UnusedIsr;
	PieVectTable.DINTCH3 = &UnusedIsr;
	PieVectTable.DINTCH4 = &UnusedIsr;
	PieVectTable.DINTCH5 = &UnusedIsr;
	PieVectTable.DINTCH6 = &UnusedIsr;
	PieVectTable.rsvd7_7 = &UnusedIsr;
	PieVectTable.rsvd7_8 = &UnusedIsr;
	PieVectTable.I2CINT1A = &UnusedIsr;
	PieVectTable.I2CINT2A = &UnusedIsr;
	PieVectTable.rsvd8_3 = &UnusedIsr;
	PieVectTable.rsvd8_4 = &UnusedIsr;
	PieVectTable.rsvd8_5 = &UnusedIsr;
	PieVectTable.rsvd8_6 = &UnusedIsr;
	PieVectTable.rsvd8_7 = &UnusedIsr;
	PieVectTable.rsvd8_8 = &UnusedIsr;
	PieVectTable.SCIRXINTA = &UnusedIsr;
	PieVectTable.SCITXINTA = &UnusedIsr;
	PieVectTable.SCIRXINTB = &UnusedIsr;
	PieVectTable.SCITXINTB = &UnusedIsr;
	PieVectTable.ECAN0INTA = &UnusedIsr;
	PieVectTable.ECAN1INTA = &UnusedIsr;
	PieVectTable.rsvd9_7 = &UnusedIsr;
	PieVectTable.rsvd9_8 = &UnusedIsr;
	PieVectTable.rsvd10_1 = &UnusedIsr;
	PieVectTable.rsvd10_2 = &UnusedIsr;
	PieVectTable.ADCINT3 = &UnusedIsr;
	PieVectTable.ADCINT4 = &UnusedIsr;
	PieVectTable.ADCINT5 = &UnusedIsr;
	PieVectTable.ADCINT6 = &UnusedIsr;
	PieVectTable.ADCINT7 = &UnusedIsr;
	PieVectTable.ADCINT8 = &UnusedIsr;
	PieVectTable.CLA1_INT1 = &UnusedIsr;
	PieVectTable.CLA1_INT2 = &UnusedIsr;
	PieVectTable.CLA1_INT3 = &UnusedIsr;
	PieVectTable.CLA1_INT4 = &UnusedIsr;
	PieVectTable.CLA1_INT5 = &UnusedIsr;
	PieVectTable.CLA1_INT6 = &UnusedIsr;
	PieVectTable.CLA1_INT7 = &UnusedIsr;
	PieVectTable.CLA1_INT8 = &UnusedIsr;
	PieVectTable.XINT3 = &UnusedIsr;
	PieVectTable.rsvd12_2 = &UnusedIsr;
	PieVectTable.rsvd12_3 = &UnusedIsr;
	PieVectTable.rsvd12_4 = &UnusedIsr;
	PieVectTable.rsvd12_5 = &UnusedIsr;
	PieVectTable.rsvd12_6 = &UnusedIsr;
	PieVectTable.LVF = &UnusedIsr;
	PieVectTable.LUF = &UnusedIsr;

	/* used interrupts */
	PieVectTable.ADCINT1 = &ADCIsr;

	EDIS;
}

/*
 * Configures flash for optimal operation.
 * Must be executed in RAM.
 */
#pragma CODE_SECTION(initFlash, "ramfuncs");
void initFlash(void)
{
	EALLOW;
	/* pump and bank active and in read mode */
	FlashRegs.FPWR.bit.PWR = (uint16)0x03;
	/* reset 3VSTAT bit by writing a 1 */
	FlashRegs.FSTATUS.bit.V3STAT = (uint16)1;

	/* wait-states page / random / OTP */
	/* (see TMS320F28069, table 5-83) */
	/* 3 / 3 / 5 */
	FlashRegs.FBANKWAIT.bit.RANDWAIT = (uint16)0x03;
	FlashRegs.FBANKWAIT.bit.PAGEWAIT = (uint16)0x03;
	FlashRegs.FOTPWAIT.bit.OTPWAIT = (uint16)0x0005;

	/* enable flash pipeline mode */
	FlashRegs.FOPT.bit.ENPIPE = (uint16)1;
	EDIS;

	/* wait 8 cycles to ensure complete pipeline flush */
	asm(" RPT #8 || NOP");
}
