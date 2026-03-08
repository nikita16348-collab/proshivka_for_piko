#include "pilot.h"
#include "shared.h"
#include "pico\stdlib.h"


void pilot_init(void)
{
    //настройка шим для моторов,прерывания на энкодерах


    //инициализация пинов для моторов
    gpio_init(L_MOTOR_PWM);
    gpio_set_dir(L_MOTOR_PWM,GPIO_OUT);

    gpio_init(R_MOTOR_PWM);
    gpio_set_dir(R_MOTOR_PWM,GPIO_OUT);
    
    //дальше там страшная хуйня от ии.потом разберу
}

void core0_entry(void)
{
    // пид регулятор ,правило левой руки, отправка ШИМа на двигатели
}