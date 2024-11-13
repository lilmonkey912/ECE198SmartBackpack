//Pressure Sensor Code
#include "delay.h"
#include "stdio.h"

extern void uart2_rxtx_init(void);

float get_voltage()
{
	while(!((ADC1->SR)&ADC_SR_EOC)){;}
	uint16_t adc_value= ADC1->DR;

	return (float)((adc_value)*3300/4095)/1000;

}


float pressure (float voltage)
{
return (float)(voltage - 0.33)/(2.475);

}



int main(void)
{
	uart2_rxtx_init();
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; //enable gpio a clock
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN; //enable adc clock
	GPIOA->MODER|=GPIO_MODER_MODER1;  //set the PA1 to analog mode
	ADC1->CR2=0; //disable the adc
	ADC1->CR2|=ADC_CR2_CONT;
	ADC1->SQR3|=1; //we are converting only one channel
	ADC1->CR2|=1; //enable the adc
	ADC1->CR2|=ADC_CR2_SWSTART; //start adc conversion

	while(1)
		{
			printf("pressure is = %f MPa\r\n",pressure(get_voltage()));
			delay(500);
		}

}


Pressure Sensor Schematics (HK1100C)
[9]


//The following code configures a GPIO pin on the STM32 to control the motor using Pulse Width Modulation (PWM)
#include "stm32f4xx_hal.h"

// Define GPIO pin and timer channel for the motor
#define MOTOR_PIN GPIO_PIN_9
#define MOTOR_PORT GPIOA
#define MOTOR_TIMER &htim2
#define MOTOR_CHANNEL TIM_CHANNEL_1

// PWM duty cycle for motor intensity
uint16_t dutyCycle = 50; // 0-100%

// Initialize GPIO and PWM
void Motor_Init(void)
{
    // GPIO Initialization
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = MOTOR_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(MOTOR_PORT, &GPIO_InitStruct);

    // Timer Initialization
    TIM_OC_InitTypeDef sConfigOC = {0};
    MOTOR_TIMER->Instance = TIM2;
    MOTOR_TIMER->Init.Prescaler = 84 - 1; // 1 MHz PWM frequency (assuming 84 MHz clock)
    MOTOR_TIMER->Init.CounterMode = TIM_COUNTERMODE_UP;
    MOTOR_TIMER->Init.Period = 100 - 1;   // 10 kHz PWM frequency
    MOTOR_TIMER->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(MOTOR_TIMER);

    // PWM Channel Configuration
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = dutyCycle; // Set duty cycle
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(MOTOR_TIMER, &sConfigOC, MOTOR_CHANNEL);

    // Start PWM
    HAL_TIM_PWM_Start(MOTOR_TIMER, MOTOR_CHANNEL);
}

// Function to Set Motor Intensity (Duty Cycle)
void Motor_SetIntensity(uint8_t intensity)
{
    __HAL_TIM_SET_COMPARE(MOTOR_TIMER, MOTOR_CHANNEL, intensity);
}

// Function to Stop Motor
void Motor_Stop(void)
{
    HAL_TIM_PWM_Stop(MOTOR_TIMER, MOTOR_CHANNEL);
}

// Function to Start Motor
void Motor_Start(void)
{
    HAL_TIM_PWM_Start(MOTOR_TIMER, MOTOR_CHANNEL);
}

// Example usage
int main(void)
{
    HAL_Init();
    Motor_Init();
    Motor_SetIntensity(70); // 70% intensity example

    // Motor runs for a certain time, then stops
    HAL_Delay(2000);
    Motor_Stop();

    while (1)
    {
        // Continuous loop
    }
}


