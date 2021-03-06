/*
 * Hardware initialization.
 *
 * $LastChangedRevision: 609 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "Target.h"
#include "Main.h"
#include "Hardware.h"

/* private prototypes */
static void initWatchdog(void);
static void initGpio(void);
static void initTimer(void);
static void initAdc(void);
static void initInterrupts(void);
static void sendSerial(tSerial* serialSTM32F0, uint8 data);
static uint8 receiveSerial(tSerial* serialSTM32F0);
static uint8 isReceiveDataAvailable(tSerial* serialSTM32F0);
static uint8 isSendReady(tSerial* serialSTM32F0);

#define PWM_FREQUENCY_10KHZ ((uint16)2400)
#define PWM_FREQUENCY_20KHZ ((uint16)1200)
#define PWM_FREQUENCY_30KHZ ((uint16)800)
#define PWM_FREQUENCY_40KHZ ((uint16)600)
#define PWM_FREQUENCY_50KHZ ((uint16)480)

#define PWM_FREQUENCY PWM_FREQUENCY_10KHZ

void initHardware(void)
{
  initWatchdog();
	initInterrupts();
	initGpio();
	initTimer();
	initAdc();
}

/* Clock configuration */
void initClock(void)
{	
	/* enable flash prefetch buffer */
	FLASH_PrefetchBufferCmd(ENABLE);
	/* set flash waitstates to 1 @ 48 MHz */
	FLASH_SetLatency(FLASH_Latency_1);
	
	/* enable HSI and wait until it's ready */
	RCC_HSICmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	
	/* PLL multiplicator */
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
	
	/* divider for SYSCLK & HCLK */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);
	
	/* enable PLL */
	RCC_PLLCmd(ENABLE);
	/* wait until PLL is locked */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	
	/* select PLL as clock source */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	/* wait until PLL is used as clock source */
	while (RCC_GetSYSCLKSource() != 0x08);
}

/* IWDG init function */
static void initWatchdog(void)
{
	/* enable APB2 DBGMCU clock to access debug options */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_DBGMCU, ENABLE);
	/* stops IWDG during debug access */
	DBGMCU_APB1PeriphConfig(DBGMCU_IWDG_STOP, ENABLE);
	
	/* enable write access to IWDG config registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	/* set IWDG prescaler to 4 (lowest possible) */
	IWDG_SetPrescaler(IWDG_Prescaler_4);
	/* set reload value to 82 */
	/* -> 32.768 kHz * 1 (PS) * 33 = ~ 10 ms */
 	IWDG_SetReload(82);
	/* reloads new counter value with reload value */
	/* (reset watchdog counter) */
	IWDG_ReloadCounter();
	/* enable IWDG */
	IWDG_Enable();
}

static void initTimer(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef        TIM_OCInitStructure;
  
  /* ADC1 and TIM1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  
  /* TIM1 DeInit */
  TIM_DeInit(TIM1);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_OCStructInit(&TIM_OCInitStructure); 
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_FREQUENCY;
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  /* Output Compare PWM Mode configuration */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           
  TIM_OCInitStructure.TIM_Pulse = 0x01;
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	/* PWM output */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_FREQUENCY / 2;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  
  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
  
  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

static void initInterrupts(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	
	NVIC_Init(&NVIC_InitStructure);
}

static void initAdc(void)
{
	ADC_InitTypeDef          ADC_InitStructure;
  GPIO_InitTypeDef         GPIO_InitStructure;

  /* GPIOA Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* ADC1 and TIM1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* set analog inputs */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;    
  ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConv_T1_CC4;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
	
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
  
  /* Convert the ADC1 Channel #0 with 1.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_1_5Cycles);
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}

static void initGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* enable GPIO C clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	/* configure C8 (blue LED) and C9 (green LED) as outputs */
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}


void initSerial(tSerial* serialSTM32F0)
{
	USART_InitTypeDef initUSART;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	USART_StructInit(&initUSART);
	initUSART.USART_BaudRate = 115200;
	initUSART.USART_WordLength = USART_WordLength_8b;
	initUSART.USART_StopBits = USART_StopBits_1;
	initUSART.USART_Parity = USART_Parity_No;
	initUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	initUSART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &initUSART);
	USART_Cmd(USART1, ENABLE);
	serialSTM32F0->send = (void (*)(tInterface*, uint8))sendSerial;
	serialSTM32F0->receive = (uint8 (*)(tInterface*))receiveSerial;
	serialSTM32F0->isReceiveDataAvailable = (uint8 (*)(tInterface*))isReceiveDataAvailable;
	serialSTM32F0->isSendReady = (uint8 (*)(tInterface*))isSendReady;

	/* enable port A clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		
	/* setup pins A9 & A10 as USART1 pins */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
		
	/* setup USART Rx- & Tx pins */
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* send byte */
static void sendSerial(tSerial* serialSTM32F0, uint8 data)
{
	USART_SendData(USART1, data);
}

/* receive byte */
static uint8 receiveSerial(tSerial* serialSTM32F0)
{
	uint8 data;
	data = USART_ReceiveData(USART1);
	return (data);
}

/* receive data check function */
static uint8 isReceiveDataAvailable(tSerial* serialSTM32F0)
{
	return (USART_GetFlagStatus(USART1, USART_FLAG_RXNE));	
}

static uint8 isSendReady(tSerial* serialSTM32F0)
{
	return (USART_GetFlagStatus(USART1, USART_FLAG_TXE));
}

void ADC1_COMP_IRQHandler(void)
{
	mainTask();
	ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}
