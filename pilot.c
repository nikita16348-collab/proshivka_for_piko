#include "pilot.h"
#include "shared.h"
#include "pico\stdlib.h"


void pilot_init(void)
{
    //настройка шим для моторов,прерывания на энкодерах
}

void core0_entry(void)
{
    // пид регулятор ,правило левой руки, отправка ШИМа на двигатели
}