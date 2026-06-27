#include "LightControl.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_tim.h"
#include "tim.h"
#include "usart.h"
#include "adc.h"
#include "OLED.h"
#include <stdio.h>

static uint8_t mode;
static uint16_t adc_value;
static uint16_t pwm_value;
static uint8_t rx_data;


void LightControl_Init(void)
{
    mode = 0;
    adc_value = 0;
    pwm_value = 0;
    rx_data = 0;

    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);

    OLED_Clear();
    OLED_ShowString(1, 1, "Light Control");
    OLED_ShowString(2, 1, "Mode:AUTO");
    OLED_ShowString(3, 1, "ADC:");
    OLED_ShowString(4, 1, "PWM:");

    printf("LightControl Init OK\r\n");
}

void LightControl_Upgrade(void)
{
    if(HAL_UART_Receive(&huart1,&rx_data,1,1) == HAL_OK)
		{
			
			if(rx_data == 'A')
			{
				mode = !mode;
			}
			else if(rx_data == '+' && mode == 1)
			{
				if(pwm_value <= 90) pwm_value += 10;
				else pwm_value = 100;
			}
			else if(rx_data == '-' && mode == 1)
			{
				if(pwm_value >= 10) pwm_value -= 10;
				else pwm_value = 0;
			}
			else if(rx_data == '0' && mode == 1)
			{
				pwm_value = 0;
			}
			else if (rx_data == 'S')
			{
				printf("STATUS: mode=%s, adc=%d, pwm=%d\r\n",
				mode == 0 ? "AUTO" : "MANUAL",
				adc_value,
				pwm_value);
			}	
			printf("RX=%c , mode=%d, PWM=%d\r\n",rx_data,mode,pwm_value);
		}
		
		if (mode == 0)
        {
             adc_value = ADC_ReadAverage();

             pwm_value = adc_value * 100 / 4095;
        }
		
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,pwm_value);

		OLED_ShowString(2,6,mode == 0? "AUTO" : "MANU");
		OLED_ShowNum(3, 5, adc_value, 4);
		OLED_ShowNum(4, 5, pwm_value, 3);
		
		HAL_Delay(500);

}
