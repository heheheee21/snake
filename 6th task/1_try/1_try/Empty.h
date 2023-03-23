#pragma once

#include <curses.h>
#include "Drawable.h"

class Empty : public Drawable//��������� ������ drawable
	/*��� ��������� ������������ ������ drawable ��� ������������� �������������� �� � ������ Empty.
	���� ����� ������������ ���������� ���������� y, x � icon, ������� ���������� � ������ Drawable*/
{
public:
	Empty(int y, int x)//���������� ������ ������ � �����������
	{
		this->y = y;
		this->x = x;
		this->icon = ' ';
	}
};