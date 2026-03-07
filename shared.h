//здесь описывается структура данных,которую видят оба ядра
#pragma once
#include <stdint.h>
#include <stdbool.h>

//структура состояния мыши
typedef struct{

    float dist_l,dist_f,dist_r;  //дистанции в мм
    float angle; // отфильтрованный угол
    bool wall_l,wall_f,wall_r;//флаги стен
    int32_t ticks_l,ticks_r;//тики энкодеров
    int current_state;//текущее состояние мыши:едет,стоит,поворачивает...

} MouseState;

extern volatile MouseState mouse;//глобальная переменная состояния

