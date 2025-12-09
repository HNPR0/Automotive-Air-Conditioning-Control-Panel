#include "motor.h"
#include "gpio.h"
#include "pwm.h"

/*
 * Initialize the motor control pins as outputs.
 */
void motor_init(void)
{
    gpio_setup_pin_direction(MOTOR_PORT_ID, MOTOR_PIN_IN1, PIN_OUTPUT);
    gpio_setup_pin_direction(MOTOR_PORT_ID, MOTOR_PIN_IN2, PIN_OUTPUT);
}

/*
 * Rotate DC motor in the required direction with the required speed (0–100%).
 */
void dc_motor_rotate(DcMotor_State motorState, uint8 speed)
{
    /* make sure pins are outputs */
    gpio_setup_pin_direction(MOTOR_PORT_ID, MOTOR_PIN_IN1, PIN_OUTPUT);
    gpio_setup_pin_direction(MOTOR_PORT_ID, MOTOR_PIN_IN2, PIN_OUTPUT);

    if (speed > 100)
        speed = 100;

    /* 0–100% → 0–255 duty */
    uint8 duty = (uint8)((speed * 255U) / 100U);

    switch (motorState)
    {
    case CW:
        gpio_write_pin(MOTOR_PORT_ID, MOTOR_PIN_IN1, LOGIC_HIGH);
        gpio_write_pin(MOTOR_PORT_ID, MOTOR_PIN_IN2, LOGIC_LOW);
        break;

    case A_CW:
        gpio_write_pin(MOTOR_PORT_ID, MOTOR_PIN_IN1, LOGIC_LOW);
        gpio_write_pin(MOTOR_PORT_ID, MOTOR_PIN_IN2, LOGIC_HIGH);
        break;

    case STOP:
    default:
        gpio_write_pin(MOTOR_PORT_ID, MOTOR_PIN_IN1, LOGIC_LOW);
        gpio_write_pin(MOTOR_PORT_ID, MOTOR_PIN_IN2, LOGIC_LOW);
        duty = 0; /* stop PWM */
        break;
    }

    /* Timer0 PWM – you must wire OC0 (D6) to the L298 EN pin */
    PWM_Timer0_Init(duty);
}