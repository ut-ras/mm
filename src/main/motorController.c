/* MCPWM basic config example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

/*
 * This example will show you how to use each submodule of MCPWM unit.
 * The example can't be used without modifying the code first.
 * Edit the macros at the top of mcpwm_example_basic_config.c to enable/disable the submodules which are used in the example.
 */

#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_attr.h"
#include "soc/rtc.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define MCPWM_EN_CARRIER 0   //Make this 1 to test carrier submodule of mcpwm, set high frequency carrier parameters
#define MCPWM_EN_DEADTIME 0  //Make this 1 to test deadtime submodule of mcpwm, set deadtime value and deadtime mode
#define MCPWM_EN_FAULT 0     //Make this 1 to test fault submodule of mcpwm, set action on MCPWM signal on fault occurence like overcurrent, overvoltage, etc
#define MCPWM_EN_SYNC 0      //Make this 1 to test sync submodule of mcpwm, sync timer signals
#define MCPWM_EN_CAPTURE 0   //Make this 1 to test capture submodule of mcpwm, measure time between rising/falling edge of captured signal
#define MCPWM_GPIO_INIT 1    //select which function to use to initialize gpio signals
#define CAP_SIG_NUM 3   //Three capture signals

#define CAP0_INT_EN BIT(27)  //Capture 0 interrupt bit
#define CAP1_INT_EN BIT(28)  //Capture 1 interrupt bit
#define CAP2_INT_EN BIT(29)  //Capture 2 interrupt bit


#define GPIO_PWM0A_OUT 19   //Set GPIO 19 as PWM0A
#define GPIO_PWM0B_OUT 18   //Set GPIO 18 as PWM0B
#define GPIO_PWM1A_OUT 21   //Set GPIO 17 as PWM1A
#define GPIO_PWM1B_OUT 22   //Set GPIO 16 as PWM1B
#define GPIO_PWM2A_OUT 15   //Set GPIO 15 as PWM2A
#define GPIO_PWM2B_OUT 14   //Set GPIO 14 as PWM2B
#define GPIO_CAP0_IN   23   //Set GPIO 23 as  CAP0
#define GPIO_CAP1_IN   25   //Set GPIO 25 as  CAP1
#define GPIO_CAP2_IN   26   //Set GPIO 26 as  CAP2
#define GPIO_SYNC0_IN   2   //Set GPIO 02 as SYNC0
#define GPIO_SYNC1_IN   4   //Set GPIO 04 as SYNC1
#define GPIO_SYNC2_IN   5   //Set GPIO 05 as SYNC2
#define GPIO_FAULT0_IN 32   //Set GPIO 32 as FAULT0
#define GPIO_FAULT1_IN 34   //Set GPIO 34 as FAULT1
#define GPIO_FAULT2_IN 34   //Set GPIO 34 as FAULT2

typedef struct {
    uint32_t capture_signal;
    mcpwm_capture_signal_t sel_cap_signal;
} capture;

xQueueHandle cap_queue;
#if MCPWM_EN_CAPTURE
static mcpwm_dev_t *MCPWM[2] = {&MCPWM0, &MCPWM1};
#endif

static void mcpwm_example_gpio_initialize()
{
    printf("initializing mcpwm gpio...\n");
#if MCPWM_GPIO_INIT
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, GPIO_PWM1A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, GPIO_PWM1B_OUT);
    
#else
    mcpwm_pin_config_t pin_config = {
        .mcpwm0a_out_num = GPIO_PWM0A_OUT,
        .mcpwm0b_out_num = GPIO_PWM0B_OUT,
        .mcpwm1a_out_num = GPIO_PWM1A_OUT,
        .mcpwm1b_out_num = GPIO_PWM1B_OUT,
    };
    mcpwm_set_pin(MCPWM_UNIT_0, &pin_config);
#endif
}



/**
 * @brief Configure whole MCPWM module
 */
static void mcpwm_initialize()
{
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 100;    //frequency = 100Hz
    pwm_config.cmpr_a = 0.0;       //duty cycle of PWMxA = 0.0%
    pwm_config.cmpr_b = 0.0;       //duty cycle of PWMxb = 0.0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);   //Configure PWM0A(19) & PWM0B(18) with above settings
    //connect 19 and 18 to a single motors
    pwm_config.frequency = 100;     //frequency = 100Hz
    pwm_config.cmpr_a = 0.0;       //duty cycle of PWMxA = 0.0%
    pwm_config.cmpr_b = 0.0;    //duty cycle of PWMxb = 0.0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);   //Configure PWM1A(21) & PWM1B(22) with above settings
}

//speed is positive to go forward, negative to go backward.
void setLeftSpeed(double speed){
    if(speed < 0){
        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, -speed);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
    } else {
        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, speed);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
    }
}

//speed is positive to go forward, negative to go backward.
void setRightSpeed(double speed){
    if(speed > 0){
        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, speed);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
    } else {
        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, -speed);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
    }
}

//sets one side go forward then backward. The other side go forward then backward.
static void motorController(void *arg){
    mcpwm_example_gpio_initialize();
    mcpwm_initialize();
    setRightSpeed(60.0);
    vTaskDelay(2000 / portTICK_RATE_MS);
    setRightSpeed(-60.0);
    vTaskDelay(2000 / portTICK_RATE_MS);
    setRightSpeed(0.0);
    vTaskDelay(2000 / portTICK_RATE_MS);
    setLeftSpeed(60.0);
    vTaskDelay(2000 / portTICK_RATE_MS);
    setLeftSpeed(-60.0);
    vTaskDelay(2000 / portTICK_RATE_MS);
    setLeftSpeed(0.0);
    vTaskDelay(2000 / portTICK_RATE_MS);
}

// void app_main()
// {
//     printf("Testing MCPWM...\n");
//     xTaskCreate(motorController, "motor_control", 4096, NULL, 5, NULL);
    
// }

