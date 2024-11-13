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
    __HAL_RCC_GPIOA_CLK_ENABLE();  // Enable GPIOA clock
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = MOTOR_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Alternate function for PWM
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;  // Timer 2 PWM mode
    HAL_GPIO_Init(MOTOR_PORT, &GPIO_InitStruct);  // Initialize the pin

    // Timer Initialization for PWM
    TIM_OC_InitTypeDef sConfigOC = {0};
    MOTOR_TIMER->Instance = TIM2;  // Use Timer 2
    MOTOR_TIMER->Init.Prescaler = 84 - 1;  // Set prescaler for 1 MHz frequency (assuming 84 MHz clock)
    MOTOR_TIMER->Init.CounterMode = TIM_COUNTERMODE_UP;
    MOTOR_TIMER->Init.Period = 100 - 1;  // Set PWM frequency to 10 kHz
    MOTOR_TIMER->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(MOTOR_TIMER);  // Initialize PWM

    // PWM Channel Configuration
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = dutyCycle;  // Set duty cycle to 50%
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(MOTOR_TIMER, &sConfigOC, MOTOR_CHANNEL);

    // Start PWM
    HAL_TIM_PWM_Start(MOTOR_TIMER, MOTOR_CHANNEL);
}

// Function to Set Motor Intensity (Duty Cycle)
void Motor_SetIntensity(uint8_t intensity)
{
    // Update the PWM duty cycle to control motor intensity
    __HAL_TIM_SET_COMPARE(MOTOR_TIMER, MOTOR_CHANNEL, intensity);
}

// Function to Stop Motor
void Motor_Stop(void)
{
    // Stop PWM to turn off the motor
    HAL_TIM_PWM_Stop(MOTOR_TIMER, MOTOR_CHANNEL);
}

// Function to Start Motor
void Motor_Start(void)
{
    // Start PWM to turn on the motor
    HAL_TIM_PWM_Start(MOTOR_TIMER, MOTOR_CHANNEL);
}

// Main Function
int main(void)
{
    HAL_Init();  // Initialize HAL Library
    Motor_Init();  // Initialize motor control (PWM)

    // Set motor intensity to 70% (duty cycle)
    Motor_SetIntensity(70);  // Adjust the value to change the motor speed

    HAL_Delay(2000);  // Run motor for 2 seconds

    Motor_Stop();  // Stop motor after 2 seconds

    while (1)
    {
        // Continuous loop, motor is stopped.
    }
}
