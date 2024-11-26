#include "main.h"
#include <stdio.h>

// ADC and UART handles (ensure they're declared in CubeMX)
ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;

// Redirect printf to UART
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

// Function to calculate FSR resistance
float calculateResistance(uint32_t adcValue, float vRef, float rFixed) {
    float vOut = (adcValue / 4095.0) * vRef; // Convert ADC value to voltage
    if (vOut == 0) return 1e6;              // Handle edge case for 0V
    return rFixed * ((vRef / vOut) - 1);    // Voltage divider formula
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_USART2_UART_Init(); // Add UART initialization

    HAL_ADC_Start(&hadc1); // Start ADC in continuous mode

    while (1) {
        // Fetch the latest ADC value
        uint32_t adcValue = HAL_ADC_GetValue(&hadc1);

        // Calculate FSR resistance
        float fsrResistance = calculateResistance(adcValue, 3.3, 1000.0);

        // Print or log the result
        printf("ADC Value: %lu, FSR Resistance: %.2f Ohms\n", adcValue, fsrResistance);

        HAL_Delay(33); // Wait ~1/30 seconds (30 Hz update rate)
    }
}
