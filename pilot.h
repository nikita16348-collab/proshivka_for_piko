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
void set_motor_speed(int left,int right);

//высокоуровневые функции движения
void move_forward(int speed);
void move_backward(int speed);
void turn_left(float angle,int speed);
void turn_right(float angle,int speed);//короче надо подумать 1 функция с абсолютным углом или 2 с относительным
void stop(void);

