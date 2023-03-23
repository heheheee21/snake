#pragma once
#include <curses.h>
#include <queue>
#include "Drawable.h"

using namespace std;

enum Direction//устанавливем маршрут
{
	up = -1,
	down = 1,
	lefft = -2,
	righht = 2
};
class SnakePiece : public Drawable
{ 
public:
	SnakePiece()//создаем часть змеи
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
	queue <SnakePiece> prev_pieces;//все элементы змеи в пор€дке их следовани€
	Direction cur_direction;//текущее направление
public:
	Snake()
	{
		cur_direction = down;
	}
	void addPiece(SnakePiece piece)//добавл€ем новый элемент в очередь
	{
		prev_pieces.push(piece);
	}

	void removePiece()//удал€ет элемент из очереди
	{
		prev_pieces.pop();
	}

	SnakePiece tail()//возвращает первый элемент очереди(хвост змеи)
	{ 
		return prev_pieces.front();
	}

	SnakePiece head()//возвращает последний элемент очереди(голова змеи)
	{
		return prev_pieces.back();
	}

	Direction getDirection()//узнаем какое сейчас направление
	{
		return cur_direction;
	}

	void setDirection(Direction d)//устанавливаем направление
	{
		if(cur_direction + d != 0)//если направление не противоположно, то можем мен€ть
			cur_direction = d;
	}
	
	SnakePiece nextHead()//вычисл€ем координаты следующего элемента
	{
		int row = head().getY();//текущие координаты
		int col = head().getX();

		switch (cur_direction)//мен€ем координаты в зависимости от шага
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
		return SnakePiece(row, col);//нова€ голова возвращаетс€ из метода в качестве результата
	}
};

