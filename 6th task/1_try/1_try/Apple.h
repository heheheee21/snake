#pragma once

#include <curses.h>
#include "Drawable.h"

class Apple : public Drawable
{
public:
	Apple(int y, int x)//������� ������
	{
		this->x = x;
		this->y = y;
		this->icon = 'A';
	}
};