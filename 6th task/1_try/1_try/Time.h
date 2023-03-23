#pragma once

#include <chrono>
#include <ctime>

class Time
{
    /*Используем стандартную библиотеку C++ chrono для 
    получения текущего времени в миллисекундах с точностью до эпохи Unix.*/
public:
    static time_t milliseconds()
    {
        auto now = std::chrono::system_clock::now();//получаем текущее время
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);//округляем до ближайшей миллисекнуды
        auto epoch = now_ms.time_since_epoch();//вычисляем количество миллисекунд, прошедших с эпохи Unix
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        return value.count();//возвращаем значение нашего времени в милисекундах
    }
};