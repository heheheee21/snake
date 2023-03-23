#pragma once
#include <curses.h>
#include <queue>
#include "Drawable.h"

using namespace std;

enum Direction//������������ �������
{
	up = -1,
	down = 1,
	lefft = -2,
	righht = 2
};
class SnakePiece : public Drawable
{ 
public:
	SnakePiece()//������� ����� ����
	{
		this->x = this->y = 0;
		this->icon = '#';
	}

	SnakePiece(int y, int x)
	{
		this->x = x;
		this->y = y;
		this->icon = '#';
	}

};

class Snake
{
	queue <SnakePiece> prev_pieces;//��� �������� ���� � ������� �� ����������
	Direction cur_direction;//������� �����������
public:
	Snake()
	{
		cur_direction = down;
	}
	void addPiece(SnakePiece piece)//��������� ����� ������� � �������
	{
		prev_pieces.push(piece);
	}

	void removePiece()//������� ������� �� �������
	{
		prev_pieces.pop();
	}

	SnakePiece tail()//���������� ������ ������� �������(����� ����)
	{ 
		return prev_pieces.front();
	}

	SnakePiece head()//���������� ��������� ������� �������(������ ����)
	{
		return prev_pieces.back();
	}

	Direction getDirection()//������ ����� ������ �����������
	{
		return cur_direction;
	}

	void setDirection(Direction d)//������������� �����������
	{
		if(cur_direction + d != 0)//���� ����������� �� ��������������, �� ����� ������
			cur_direction = d;
	}
	
	SnakePiece nextHead()//��������� ���������� ���������� ��������
	{
		int row = head().getY();//������� ����������
		int col = head().getX();

		switch (cur_direction)//������ ���������� � ����������� �� ����
		{
		case down:
			row++;
			break;
		case up:
			row--;
			break;
		case lefft:
			col--;
			break;
		case righht:
			col++;
			break;
		}
		return SnakePiece(row, col);//����� ������ ������������ �� ������ � �������� ����������
	}
};

