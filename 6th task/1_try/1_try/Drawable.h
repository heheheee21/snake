#pragma once
#include <curses.h>

/*Ёта часть определ€ет базовый класс Drawable дл€ объектов,
которые можно отрисовывать на экране*/

class Drawable {
public:
	Drawable()//создаем пустой объект в координатах (0, 0)
	{
		y = x = 0;
		icon = ' ';
	}
	Drawable(int y, int x, chtype ch)//создаем объект с заданными координатами (y,x) и символом ch
	{
		this->y = y;
		this->x = x;
		this->icon = ch;
	}

	int getX()//узнаем X
	{
		return x;
	}

	int getY()//узнаем Y
	{
		return y;
	}

	int getIcon()//узнаем символ дл€ отображени€ объекта
	{
		return icon;
	}

protected://ѕеременные y, x и icon €вл€ютс€ защищенными и доступны только дл€ наследников класса Drawable.
	int y, x;
	chtype icon;
};