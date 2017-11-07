/*
 * $LastChangedRevision: 833 $
 * $LastChangedDate:: 2015-12-15 18:11:05 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include <asf.h>
#include "SerialGeneric.h"
#include "Hardware.h"

extern void mainTask(void);

/* private prototypes */
static void sendSerial(tSerial* serial, uint8 data);
static uint8 receiveSerial(tSerial* serial);
static uint8 isReceiveDataAvailable(tSerial* serial);
static uint8 isSendReady(tSerial* serial);

#define UART_INTERFACE (CONSOLE_UART)

#define CURRENT_PWM_CHANNEL (PWM_CHANNEL_0)
#define CURRENT_PWM_COMPARE_UNIT (PWM_CMP_UNIT_0)

#define ADC_CLOCK (6400000)
#define CURRENT_ADC_CHANNEL (ADC_CHANNEL_0)

static pwm_channel_t channel_instance;
static pwm_cmp_t cmp_config;

void initHardware(void)
{
	/* UART */
	usart_serial_options_t usart_opts = {
		.baudrate = 115200,
		.charlength = US_MR_CHRL_8_BIT,
		.paritytype = US_MR_PAR_NO,
		.stopbits = US_MR_NBSTOP_1_BIT
	};
	stdio_serial_init(UART_INTERFACE, &usart_opts);
	
	/* LED */
	gpio_configure_pin(PIO_PB27_IDX, (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT));
	
	/* PWM */
	{
		pwm_clock_t clock_setting = {
			.ul_clka = 1000 * 200, /* 200 kHz */
			.ul_clkb = 0, /* disabled */
			.ul_mck = sysclk_get_cpu_hz()
		};
		
		pmc_enable_periph_clk(ID_PWM);
		
		pwm_channel_disable(PWM, CURRENT_PWM_CHANNEL);
		
		pwm_init(PWM, &clock_setting);
		
		channel_instance.alignment = PWM_ALIGN_CENTER;
		channel_instance.polarity = PWM_LOW;
		channel_instance.ul_prescaler = PWM_CMR_CPRE_CLKA;
		channel_instance.ul_period = 10;
		channel_instance.ul_duty = 10/2;
		channel_instance.channel = CURRENT_PWM_CHANNEL;
		
		pwm_channel_init(PWM, &channel_instance);

		cmp_config.unit = CURRENT_PWM_COMPARE_UNIT;
		cmp_config.b_enable = true;
		cmp_config.b_pulse_on_line_0 = true;
		cmp_config.ul_value = 10;
		cmp_config.b_is_decrementing = false;
		pwm_cmp_init(PWM, &cmp_config);
		
		pwm_channel_enable(PWM, CURRENT_PWM_CHANNEL);
	}
	
	/* ADC */
	{
		pmc_enable_periph_clk(ID_ADC);
		
		adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, ADC_STARTUP_TIME_4);
		adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
		adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
		adc_enable_channel(ADC, CURRENT_ADC_CHANNEL);
		
		adc_enable_interrupt(ADC, ADC_IER_DRDY);
		NVIC_EnableIRQ(ADC_IRQn);
		
		adc_configure_trigger(ADC, ADC_TRIG_PWM_EVENT_LINE_0, 0);
	}
	
}


static void sendSerial(tSerial* serial, uint8 data)
{
	uart_write(UART_INTERFACE, data);
}

static uint8 receiveSerial(tSerial* serial)
{
	uint8 data;
	
	uart_read(UART_INTERFACE, &data);
	return (data);
}

static uint8 isReceiveDataAvailable(tSerial* serial)
{
	uint32 isReady = uart_is_rx_ready(UART_INTERFACE);
	return ((uint8)isReady);
}


static uint8 isSendReady(tSerial* serial)
{
	uint32 isReady = uart_is_tx_ready(UART_INTERFACE);
	return ((uint8)isReady);
}

/* Initializes serial interface functions */
void initSerial(tSerial* serial)
{
    serial->send = (void (*)(tInterface*, uint8))sendSerial;
    serial->receive = (uint8 (*)(tInterface*))receiveSerial;
    serial->isReceiveDataAvailable = (uint8 (*)(tInterface*))isReceiveDataAvailable;
    serial->isSendReady = (uint8 (*)(tInterface*))isSendReady;
}

/* ADC interrupt handler */
void ADC_Handler(void)
{
	mainTask();
	/* read last ADC value to clear EOC flag */
	adc_get_latest_value(ADC);
}
