#include "pilot.h"
#include "shared.h"
#include "pico\stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

//Обработчик прерываний для энкодеров
void encoder_callback(uint gpio, uint32_t events)
{
    if (gpio == ENCODER_L)
    {
        mouse.ticks_l++;
    }
    if(gpio == ENCODER_R)
    {
        mouse.ticks_r++;
    }
}

void pilot_init(void)
{//Настройка пинов направления как выходов
    gpio_init(L_MOTOR_IN1);
    gpio_init(L_MOTOR_IN2);
    gpio_init(R_MOTOR_IN1);
    gpio_init(R_MOTOR_IN2);
    gpio_set_dir(L_MOTOR_IN1,GPIO_OUT);
    gpio_set_dir(L_MOTOR_IN2,GPIO_OUT);
    gpio_set_dir(R_MOTOR_IN1,GPIO_OUT);
    gpio_set_dir(R_MOTOR_IN2,GPIO_OUT);
//Настройка пинов ШИМ
    gpio_set_function(L_MOTOR_PWM,GPIO_FUNC_PWM);
    gpio_set_function(R_MOTOR_PWM,GPIO_FUNC_PWM);
//влючение шим генераторов
    uint slice_num_l=pwm_gpio_to_slice_num(L_MOTOR_PWM);
    uint slice_num_r=pwm_gpio_to_slice_num(R_MOTOR_PWM);
    pwm_set_enabled(slice_num_l,true);
    pwm_set_enabled(slice_num_r,true);
//настройка энкодеров как выходов с прерываниями
    gpio_init(ENCODER_L);
    gpio_init(ENCODER_R);
    gpio_set_dir(ENCODER_L,GPIO_IN);
    gpio_set_dir(ENCODER_R,GPIO_IN);
    gpio_pull_up(ENCODER_L);
    gpio_pull_up(ENCODER_R);
//прерывания
    gpio_set_irq_enabled_with_callback(ENCODER_L,GPIO_IRQ_EDGE_RISE,true,&encoder_callback);
    gpio_set_irq_enabled(ENCODER_R,GPIO_IRQ_EDGE_RISE,true);
//сразу ставим моторы в стоп
    gpio_put(L_MOTOR_IN1,0);
    gpio_put(L_MOTOR_IN2,0);
    gpio_put(R_MOTOR_IN1,0);
    gpio_put(R_MOTOR_IN2,0);
    pwm_set_gpio_level(L_MOTOR_PWM,0);//нулевая скорость
    pwm_set_gpio_level(R_MOTOR_PWM,0);

    printf("Pilot: Init OK \n");

   
}

void set_motor_speed(int left, int right)
{
    // Защита от долбаеба
    if (left > 255) left = 255;
    if (left < -255) left = -255;
    if (right > 255) right = 255;
    if (right < -255) right = -255;


    //левый мотор
    if(left>0)
    {
        gpio_put(L_MOTOR_IN1,1);
        gpio_put(L_MOTOR_IN2,0);
    }
    else if(left<0)
    {
        gpio_put(L_MOTOR_IN1,0);
        gpio_put(L_MOTOR_IN2,1);
    }
    else
    {
        //активный тормоз
        gpio_put(L_MOTOR_IN1,1);
        gpio_put(L_MOTOR_IN2,1);
    }
    pwm_set_gpio_level(L_MOTOR_PWM,abs(left)*257);


    //правый мотор
    if(right>0)
    {
        gpio_put(R_MOTOR_IN1,1);
        gpio_put(R_MOTOR_IN2,0);
    }
    else if(right<0)
    {
        gpio_put(R_MOTOR_IN1,0);
        gpio_put(R_MOTOR_IN2,1);
    }
    else
    {
        //активный тормоз
        gpio_put(R_MOTOR_IN1,1);
        gpio_put(R_MOTOR_IN2,1);
    }
    pwm_set_gpio_level(R_MOTOR_PWM,abs(left)*257);
}

void move_forward(int speed)
{
    set_motor_speed(speed,speed);
}
void move_backward(int speed)
{
    set_motor_speed(-speed,-speed);
}
void turn_left(float target_angle,int speed)
{
    float start_angle = mouse.angle;
    float current_angle= mouse.angle;

    // Если уже повернули куда надо - не делаем ничего
    if (target_angle <= 0) return;

    // Крутимся, пока не достигнем цели
    while (fabs(current_angle - start_angle) < target_angle) {
        set_motor_speed(-speed, speed);  // Разворот
        current_angle = mouse.angle;      // Гироскоп говорит правду!
        sleep_us(1000);                    // Маленькая задержка
    }
    
    set_motor_speed(0, 0);
}
void turn_right(float target_angle,int speed)
{
    float start_angle = mouse.angle;
    float current_angle = mouse.angle;
    
    // Если уже повернули куда надо - не делаем ничего
    if (target_angle <= 0) return;
    
    // Крутимся, пока не достигнем цели
    while (fabs(current_angle - start_angle) < target_angle) {
        set_motor_speed(speed, -speed);  // Разворот
        current_angle = mouse.angle;      // Гироскоп говорит правду!
        sleep_us(1000);                    // Маленькая задержка
    }
    
    set_motor_speed(0, 0);
}
void stop(void)
{

}
void core0_entry(void)
{
    // пид регулятор ,правило левой руки, отправка ШИМа на двигатели
}