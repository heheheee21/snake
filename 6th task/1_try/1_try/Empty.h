#pragma once

#include <curses.h>
#include "Drawable.h"

class Empty : public Drawable//наследник класса drawable
	/*Это позволяет использовать методы drawable без необходимости переопределять их в классе Empty.
	Плюс можно использовать защищенные переменные y, x и icon, которые определены в классе Drawable*/
{
public:
	Empty(int y, int x)//отображаем пустой символ в координатах
	{
		this->y = y;
		this->x = x;
		this->icon = ' ';
	}
};