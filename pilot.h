#pragma once

#define L_MOTOR_PWM 6
#define L_MOTOR_IN1 8
#define L_MOTOR_IN2 9

#define R_MOTOR_PWM 7
#define R_MOTOR_IN1 12
#define R_MOTOR_IN2 13

#define ENCODER_L 28
#define ENCODER_R 29


void pilot_init(void);
void core0_entry(void);
