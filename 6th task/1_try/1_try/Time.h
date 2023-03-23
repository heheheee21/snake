#pragma once

#include <chrono>
#include <ctime>

class Time
{
    /*���������� ����������� ���������� C++ chrono ��� 
    ��������� �������� ������� � ������������� � ��������� �� ����� Unix.*/
public:
    static time_t milliseconds()
    {
        auto now = std::chrono::system_clock::now();//�������� ������� �����
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);//��������� �� ��������� ������������
        auto epoch = now_ms.time_since_epoch();//��������� ���������� �����������, ��������� � ����� Unix
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        return value.count();//���������� �������� ������ ������� � ������������
    }
};