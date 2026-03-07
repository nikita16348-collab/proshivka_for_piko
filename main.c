#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "shared.h"
#include "pilot.h"
#include "navigator.h"

volatile MouseState mouse={0};//глобальное состояние


int main()
{
    //функции-инициализаторы.обьявляют какие пины за что отвечают.
    pilot_init();
    navigator_init();

    stdio_init_all();

    multicore_launch_core1(core1_entry);//запуск 2го ядра


    while(1)
    {

        //анализ данных с ядра 1:
        // if(mouse.dist_l>30.0f)
        // {
        //     printf("ok\n");
            
        // }
        // else if(mouse.dist_l<30.0f)
        // {
        //     printf( "pizdec! now vrezemsia!\n");
        // }

        core0_entry();

        sleep_ms(1);//быстрый цикл 1кгц.задаем ритм для процессора
    }

    
}
