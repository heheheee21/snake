#pragma once

#include <curses.h>
#include "Drawable.h"

class Apple : public Drawable
{
public:
	Apple(int y, int x)//создаем €блоко
	{
		this->x = x;
		this->y = y;
		this->icon = 'A';
	}
};