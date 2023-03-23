#pragma once
#include <curses.h>
#include <ctime>
#include <cstdlib>
#include "Board.h"
#include "Drawable.h"
#include "Apple.h"
#include "Empty.h"
#include "Snake.h"
#include "Scoreboard.h"
#include "Scoreboard_thebest.h"

class SnakeGame
{
	Board board;
	bool game_over;
	Apple* apple;
	Snake snake;
	Scoreboard scoreboard;
	BestScore best_score;


	// приватный метод создания объекта яблока
	void createApple()
	{
		int y, x;
		board.getEmptyCoorinates(y, x); // получаем координаты пустой клетки
		apple = new Apple(y, x); // создаем объект яблока на полученных координатах
		board.add(*apple); // добавляем яблоко на игровую доску
	}

	// приватный метод обработки следующего кусочка змеи
	void handleNextPiece(SnakePiece next)
	{
		if (apple != NULL) // если есть яблоко на игровой доске
		{
			switch (board.getCharAt(next.getY(), next.getX())) // проверяем символ на следующей позиции
			{
			case 'A': // если символ 'A', то змея съела яблоко
				eatApple();
				break;
			case' ': // если символ ' ', то змея движется по пустой клетке
			{
				int emptyRow = snake.tail().getY(); // получаем координаты хвоста змеи
				int emptyCol = snake.tail().getX();
				board.add(Empty(emptyRow, emptyCol)); // добавляем пустую клетку на игровую доску на место хвоста змеи
				snake.removePiece(); // удаляем кусочек хвоста змеи
				break;
			}
			default: // иначе змея столкнулась с препятствием или самой собой
				game_over = true; // устанавливаем флаг окончания игры
				break;

			}
		}

		board.add(next); // добавляем следующий кусочек змеи на игровую доску
		snake.addPiece(next); // добавляем следующий кусочек змеи в объект змеи
	}

	// приватный метод обработки съеденного яблока
	void eatApple()
	{
		delete apple; // освобождаем память выделенную под яблоко
		apple = NULL; // устанавливаем указатель на нул
		scoreboard.increaseScore(); // увеличиваем счет на единицу
		int current_score = scoreboard.getScore();//узнаем текущий результат
		if (best_score.set(current_score))
		{
			best_score.updateWindow();//обновляем лучший результат, если пользователь его побил
		}
	}

public:
	// конструктор класса
	SnakeGame(int height, int width, int speed) : scoreboard(45, 23, 30, 3), best_score()
	{
		board = Board(height, width, speed); // создание игровой доски
		int sb_row = board.getStartCol() + height,
			sb_col = board.getStartCol();
		initialize(); // вызов метода инициализации игры
		best_score.updateWindow(); // обновление окна лучшего результата
	}

	// деструктор класса
	~SnakeGame()
	{
		delete apple; // удаление объекта яблока
	}

	// метод инициализации игры
	void initialize()
	{
		apple = NULL; // устанавливаем указатель на яблоко в нуль
		board.initialize(); // инициализируем игровую доску

		game_over = false; // устанавливаем флаг окончания игры в ложь
		srand(time(NULL)); // инициализируем генератор случайных чисел
		snake.setDirection(down); // устанавливаем направление движения змеи вниз
		handleNextPiece(SnakePiece(1, 1)); // обработка следующего кусочка змеи
		handleNextPiece(snake.nextHead()); // обработка следующего кусочка змеи
		handleNextPiece(snake.nextHead()); // обработка следующего кусочка змеи

		snake.setDirection(righht); // устанавливаем направление движения змеи вправо

		handleNextPiece(snake.nextHead()); // обработка следующего кусочка змеи

		if (apple == NULL) // если указатель на объект яблока не установлен, то создаем яблоко
			createApple();
	}

	// метод обработки пользовательского ввода
	void processInput()
	{
		chtype input = board.getInput(); // получение символа ввода от пользователя
		int old_timeout = board.getTimeout(); // сохранение текущего таймаута
		switch (input)
		{
		case KEY_UP:
		case 'w':
			snake.setDirection(up); // устанавливаем направление движения змеи вверх
			break;
		case KEY_DOWN:
		case 's':
			snake.setDirection(down); // устанавливаем направление движения змеи вниз
			break;
		case KEY_RIGHT:
		case 'd':
			snake.setDirection(righht); // устанавливаем направление движения вправо
			break;
		case KEY_LEFT:
		case 'a':
			snake.setDirection(lefft);// устанавливаем направление движения влево
			break;
		case 'p': // если нажата клавиша 'p'
			board.setTimeout(-1); // устанавливаем таймаут в -1, тем самым игра приостанавливается
			while (board.getInput() != 'p') // ожидаем, пока не будет нажата клавиша 'p' еще раз
				;
			board.setTimeout(old_timeout); // восстанавливаем таймаут
			break;
		default:
			break;
		}
	}

	void updateState()//обновляем состояние игры
	{
		handleNextPiece(snake.nextHead()); //передаем следующую голову змейки(считая от текущей)

		if (apple == NULL)//добавляем яблоко
			createApple();
	}
	void redraw()//обновляем окна
	{
		board.refresh();
		scoreboard.refresh();
		best_score.updateWindow();
	}

	bool isOver()//проверка на конец игры
	{
		return game_over;
	}
	int getScore()//узнаем счет
	{
		return scoreboard.getScore();
	}

};