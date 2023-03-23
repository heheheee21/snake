#pragma once
#include <curses.h>

/*��� ����� ���������� ������� ����� Drawable ��� ��������,
������� ����� ������������ �� ������*/

class Drawable {
public:
	Drawable()//������� ������ ������ � ����������� (0, 0)
	{
		y = x = 0;
		icon = ' ';
	}
	Drawable(int y, int x, chtype ch)//������� ������ � ��������� ������������ (y,x) � �������� ch
	{
		this->y = y;
		this->x = x;
		this->icon = ch;
	}

	int getX()//������ X
	{
		return x;
	}

	int getY()//������ Y
	{
		return y;
	}

	int getIcon()//������ ������ ��� ����������� �������
	{
		return icon;
	}

protected://���������� y, x � icon �������� ����������� � �������� ������ ��� ����������� ������ Drawable.
	int y, x;
	chtype icon;
};