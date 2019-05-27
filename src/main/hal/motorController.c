#include "driver/mcpwm.h"

#define GPIO_PWM0A_OUT 19  // Set GPIO 19 as PWM0A
#define GPIO_PWM0B_OUT 18  // Set GPIO 18 as PWM0B
#define GPIO_PWM1A_OUT 22  // Set GPIO 22 as PWM1A
#define GPIO_PWM1B_OUT 21  // Set GPIO 21 as PWM1B

/**
 * @brief Configure whole MCPWM module
 */
static void mcpwm_frequency_initialize() {
  mcpwm_config_t pwm_config;
  pwm_config.frequency = 100;  // frequency = 100Hz
  pwm_config.cmpr_a = 0.0;     // duty cycle of PWMxA = 0.0%
  pwm_config.cmpr_b = 0.0;     // duty cycle of PWMxb = 0.0%
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(
      MCPWM_UNIT_0, MCPWM_TIMER_0,
      &pwm_config);  // Configure PWM0A(19) & PWM0B(18) with above settings
  // connect 19 and 18 to a single motors
  pwm_config.frequency = 100;  // frequency = 100Hz
  pwm_config.cmpr_a = 0.0;     // duty cycle of PWMxA = 0.0%
  pwm_config.cmpr_b = 0.0;     // duty cycle of PWMxb = 0.0%
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(
      MCPWM_UNIT_0, MCPWM_TIMER_1,
      &pwm_config);  // Configure PWM1A(21) & PWM1B(22) with above settings
}

/*
 * Call this initialize before starting to set speed of the both motors
 */
void mcpwm_initialize() {
  printf("initializing mcpwm gpio...\n");
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, GPIO_PWM1A_OUT);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, GPIO_PWM1B_OUT);
  mcpwm_frequency_initialize();
}

// speed is positive to go forward, negative to go backward. -100 to 100.
void setLeftSpeed(double speed) {
  if (speed > 0) {
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, speed);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A,
                        MCPWM_DUTY_MODE_0);
  } else {
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, -speed);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B,
                        MCPWM_DUTY_MODE_0);
  }
}

// speed is positive to go forward, negative to go backward. -100 to 100.
void setRightSpeed(double speed) {
  if (speed > 0) {
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, speed);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A,
                        MCPWM_DUTY_MODE_0);
  } else {
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, -speed);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B,
                        MCPWM_DUTY_MODE_0);
  }
}

void setMotors(float left, float right) {
  setLeftSpeed(left);
  setRightSpeed(right);
}

void stopMotors(void) { setMotors(0.0, 0.0); }
