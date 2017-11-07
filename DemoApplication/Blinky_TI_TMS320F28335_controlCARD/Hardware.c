/*
 * Hardware configuration.
 *
 * $LastChangedRevision: 541 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "Target.h"
#include "Hardware.h"

#define TX_FIFO_SIZE ((uint16)4)

/* private prototypes */
static void sendSerial(tSerial* serial, uint8 data);
static uint8 receiveSerial(tSerial* serial);
static uint8 isReceiveDataAvailable(tSerial* serial);
static uint8 isSendReady(tSerial* serial);
static void delayMicroseconds(uint16 time);
void mainTask(void);

interrupt void UnusedIsr(void);
interrupt void ADCIsr(void);

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

	/* set PLL multiplier = 10 */
	SysCtrlRegs.PLLCR.bit.DIV = (uint16)0x000A;

	/* wait for PLL to lock */
	while (SysCtrlRegs.PLLSTS.bit.PLLLOCKS == (uint16)0x0001);

	/* enable failed oscillator detect logic */
	SysCtrlRegs.PLLSTS.bit.MCLKOFF = (uint16)0x0000;
	/* set DIVSEL to 2 -> clock divider = 2 */
	SysCtrlRegs.PLLSTS.bit.DIVSEL = (uint16)0x0002;

	/* SYSCLK = OSCCLK * PLLMULT / CLKDIV */
	/* -> 30 MHz * 10 / 2 = 150 MHz */

	/* enable watchdog with prescaler 1 */
	/* (watchdog timeout = 512 * PS / OSCCLK * 2^8 */
	/* -> 512 * 4 / 30e6 * 2^8 = ~ 17 ms) */
	SysCtrlRegs.WDCR = (uint16)0x00AB;

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
	/* LED LD2 */
	GpioCtrlRegs.GPADIR.bit.GPIO31 = (uint16)1;
	/* LED LD3 */
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = (uint16)1;


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
	/* select reference source */
	AdcRegs.ADCREFSEL.bit.REF_SEL = (uint16)0x00;

	AdcRegs.ADCTRL3.bit.ADCBGRFDN = (uint16)0x03;
	AdcRegs.ADCTRL3.bit.ADCPWDN = (uint16)1;
	AdcRegs.ADCTRL3.bit.ADCCLKPS = (uint16)0x03;
	AdcRegs.ADCTRL3.bit.SMODE_SEL = (uint16)1;

	/* ADCREFSEL + ADCOFFTRIM
	  -----------------------------
	  The ADC_cal() routine is programmed into TI reserved OTP memory
	  by the factory. The boot ROM automatically calls the ADC_cal() routine
	  to initialize the ADCREFSEL and ADCOFFTRIM registers with device specific
	  calibration data. During normal operation, this process occurs
	  automatically and no action is required by the user.
	*/

	/* delay before powering up rest of ADC */
	delayMicroseconds(5000);

    AdcRegs.ADCTRL1.bit.CPS = (uint16)1;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = (uint16)1;

    AdcRegs.ADCTRL2.bit.RST_SEQ1 = (uint16)1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = (uint16)1;
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = (uint16)1;

    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = (uint16)0x07;

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = (uint16)0x00;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = (uint16)0x01;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = (uint16)0x02;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = (uint16)0x03;

    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = (uint16)0x04;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = (uint16)0x05;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = (uint16)0x06;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = (uint16)0x07;

    AdcRegs.ADCCHSELSEQ3.all = (uint16)0x0000;

    AdcRegs.ADCCHSELSEQ4.all = (uint16)0x0000;

	/************************************************/
	/* PWM Time-Base Module                         */
	/************************************************/
    EPwm1Regs.TBPRD = 7500;

    EPwm1Regs.TBCTL.bit.PHSDIR = (uint16)1;
    EPwm1Regs.TBCTL.bit.CLKDIV = (uint16)0x00;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = (uint16)0x00;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = (uint16)0x01;
    EPwm1Regs.TBCTL.bit.CTRMODE = (uint16)0x02;

	/************************************************/
	/* PWM Event-trigger Module                     */
	/************************************************/
    EPwm1Regs.ETSEL.bit.SOCAEN = (uint16)1;
    EPwm1Regs.ETSEL.bit.SOCASEL = (uint16)0x01;

    /* start ADC every PWM period */
    EPwm1Regs.ETPS.bit.SOCAPRD = (uint16)0x01;

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

	/* Baud rate = 115200 @ SYSCLK = 150MHz */
	SciaRegs.SCIHBAUD = 0x00;
	SciaRegs.SCILBAUD = 0xA2;


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
		/* wait for watchdog to reboot target */
	}
}

/*
 * Interrupt service routine for ADC end of conversion.
 */
interrupt void ADCIsr(void)
{
	/* control task */
	mainTask();

	PieCtrlRegs.PIEACK.bit.ACK1 = (uint16)1;
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = (uint16)1;
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = (uint16)1;
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

	PieVectTable.XINT13 = &UnusedIsr;
	PieVectTable.TINT2 = &UnusedIsr;
	PieVectTable.DATALOG = &UnusedIsr;
	PieVectTable.RTOSINT = &UnusedIsr;
	PieVectTable.EMUINT = &UnusedIsr;
	PieVectTable.XNMI = &UnusedIsr;
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

	PieVectTable.SEQ1INT = &UnusedIsr;
	PieVectTable.SEQ2INT = &UnusedIsr;
	PieVectTable.rsvd1_3 = &UnusedIsr;
	PieVectTable.XINT1 = &UnusedIsr;
	PieVectTable.XINT2 = &UnusedIsr;
	PieVectTable.ADCINT = &UnusedIsr;
	PieVectTable.TINT0 = &UnusedIsr;
	PieVectTable.WAKEINT = &UnusedIsr;

	PieVectTable.EPWM1_TZINT = &UnusedIsr;
	PieVectTable.EPWM2_TZINT = &UnusedIsr;
	PieVectTable.EPWM3_TZINT = &UnusedIsr;
	PieVectTable.EPWM4_TZINT = &UnusedIsr;
	PieVectTable.EPWM5_TZINT = &UnusedIsr;
	PieVectTable.EPWM6_TZINT = &UnusedIsr;
	PieVectTable.rsvd2_7 = &UnusedIsr;
	PieVectTable.rsvd2_8 = &UnusedIsr;

	PieVectTable.EPWM1_INT = &UnusedIsr;
	PieVectTable.EPWM2_INT = &UnusedIsr;
	PieVectTable.EPWM3_INT = &UnusedIsr;
	PieVectTable.EPWM4_INT = &UnusedIsr;
	PieVectTable.EPWM5_INT = &UnusedIsr;
	PieVectTable.EPWM6_INT = &UnusedIsr;
	PieVectTable.rsvd3_7 = &UnusedIsr;
	PieVectTable.rsvd3_8 = &UnusedIsr;

	PieVectTable.ECAP1_INT = &UnusedIsr;
	PieVectTable.ECAP2_INT = &UnusedIsr;
	PieVectTable.ECAP3_INT = &UnusedIsr;
	PieVectTable.ECAP4_INT = &UnusedIsr;
	PieVectTable.ECAP5_INT = &UnusedIsr;
	PieVectTable.ECAP6_INT = &UnusedIsr;
	PieVectTable.rsvd4_7 = &UnusedIsr;
	PieVectTable.rsvd4_8 = &UnusedIsr;

	PieVectTable.EQEP1_INT = &UnusedIsr;
	PieVectTable.EQEP2_INT = &UnusedIsr;
	PieVectTable.rsvd5_3 = &UnusedIsr;
	PieVectTable.rsvd5_4 = &UnusedIsr;
	PieVectTable.rsvd5_5 = &UnusedIsr;
	PieVectTable.rsvd5_6 = &UnusedIsr;
	PieVectTable.rsvd5_7 = &UnusedIsr;
	PieVectTable.rsvd5_8 = &UnusedIsr;

	PieVectTable.SPIRXINTA = &UnusedIsr;
	PieVectTable.SPITXINTA = &UnusedIsr;
	PieVectTable.MRINTB = &UnusedIsr;
	PieVectTable.MXINTB = &UnusedIsr;
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
	PieVectTable.SCIRXINTC = &UnusedIsr;
	PieVectTable.SCITXINTC = &UnusedIsr;
	PieVectTable.rsvd8_7 = &UnusedIsr;
	PieVectTable.rsvd8_8 = &UnusedIsr;

	PieVectTable.SCIRXINTA = &UnusedIsr;
	PieVectTable.SCITXINTA = &UnusedIsr;
	PieVectTable.SCIRXINTB = &UnusedIsr;
	PieVectTable.SCITXINTB = &UnusedIsr;
	PieVectTable.ECAN0INTA = &UnusedIsr;
	PieVectTable.ECAN1INTA = &UnusedIsr;
	PieVectTable.ECAN0INTB = &UnusedIsr;
	PieVectTable.ECAN1INTB = &UnusedIsr;

	PieVectTable.rsvd10_1 = &UnusedIsr;
	PieVectTable.rsvd10_2 = &UnusedIsr;
	PieVectTable.rsvd10_3 = &UnusedIsr;
	PieVectTable.rsvd10_4 = &UnusedIsr;
	PieVectTable.rsvd10_5 = &UnusedIsr;
	PieVectTable.rsvd10_6 = &UnusedIsr;
	PieVectTable.rsvd10_7 = &UnusedIsr;
	PieVectTable.rsvd10_8 = &UnusedIsr;

	PieVectTable.rsvd11_1 = &UnusedIsr;
	PieVectTable.rsvd11_2 = &UnusedIsr;
	PieVectTable.rsvd11_3 = &UnusedIsr;
	PieVectTable.rsvd11_4 = &UnusedIsr;
	PieVectTable.rsvd11_5 = &UnusedIsr;
	PieVectTable.rsvd11_6 = &UnusedIsr;
	PieVectTable.rsvd11_7 = &UnusedIsr;
	PieVectTable.rsvd11_8 = &UnusedIsr;

	PieVectTable.XINT3 = &UnusedIsr;
	PieVectTable.XINT4 = &UnusedIsr;
	PieVectTable.XINT5 = &UnusedIsr;
	PieVectTable.XINT6 = &UnusedIsr;
	PieVectTable.XINT7 = &UnusedIsr;
	PieVectTable.rsvd12_6 = &UnusedIsr;
	PieVectTable.LVF = &UnusedIsr;
	PieVectTable.LUF = &UnusedIsr;

	/* used interrupts */
	PieVectTable.SEQ1INT = &ADCIsr;

	EDIS;
}

/*
 * Delay function.
 */
static void delayMicroseconds(uint16 time)
{
   	uint16 i;

   	for (i=0;i<time;i++)
   	{
		asm(" RPT #150 || NOP");
	}
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
    /* (see TMS320F28335, table 6-70) */
    /* 5 / 5 / 8 */
    FlashRegs.FBANKWAIT.bit.RANDWAIT = (uint16)0x05;
    FlashRegs.FBANKWAIT.bit.PAGEWAIT = (uint16)0x05;
    FlashRegs.FOTPWAIT.bit.OTPWAIT = (uint16)0x0008;

    /* enable flash pipeline mode */
    FlashRegs.FOPT.bit.ENPIPE = (uint16)0x01;

    EDIS;

    /* wait 8 cycles to ensure complete pipeline flush */
    asm(" RPT #8 || NOP");
}
