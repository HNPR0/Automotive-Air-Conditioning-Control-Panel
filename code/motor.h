#ifndef std_types
#define std_types
#include "std_types.h"
#endif

#ifndef macros
#define macros
#include "common_macros.h"
#endif

#ifndef avr
#define avr
#include "avr/io.h"
#endif // avr

#ifndef MOTOR_H_
#define MOTOR_H_

/* Port indexing: 0=PORTA,1=PORTB,2=PORTC,3=PORTD */
#define MOTOR_PORT_ID   1   /* PORTB */
/* PB2 = D10, PB3 = D11 */
#define MOTOR_PIN_IN1   2
#define MOTOR_PIN_IN2   3

/* DC motor states */
typedef enum
{
    STOP = 0,
    CW,
    A_CW
} DcMotor_State;

/* Global motor state defined in demo.ino */
extern DcMotor_State motorState;

/* Functions Prototypes */
void motor_init(void);
void dc_motor_rotate(DcMotor_State motorState, uint8 speed);

#endif /* MOTOR_H_ */