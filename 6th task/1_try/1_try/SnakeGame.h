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


	// ��������� ����� �������� ������� ������
	void createApple()
	{
		int y, x;
		board.getEmptyCoorinates(y, x); // �������� ���������� ������ ������
		apple = new Apple(y, x); // ������� ������ ������ �� ���������� �����������
		board.add(*apple); // ��������� ������ �� ������� �����
	}

	// ��������� ����� ��������� ���������� ������� ����
	void handleNextPiece(SnakePiece next)
	{
		if (apple != NULL) // ���� ���� ������ �� ������� �����
		{
			switch (board.getCharAt(next.getY(), next.getX())) // ��������� ������ �� ��������� �������
			{
			case 'A': // ���� ������ 'A', �� ���� ����� ������
				eatApple();
				break;
			case' ': // ���� ������ ' ', �� ���� �������� �� ������ ������
			{
				int emptyRow = snake.tail().getY(); // �������� ���������� ������ ����
				int emptyCol = snake.tail().getX();
				board.add(Empty(emptyRow, emptyCol)); // ��������� ������ ������ �� ������� ����� �� ����� ������ ����
				snake.removePiece(); // ������� ������� ������ ����
				break;
			}
			default: // ����� ���� ����������� � ������������ ��� ����� �����
				game_over = true; // ������������� ���� ��������� ����
				break;

			}
		}

		board.add(next); // ��������� ��������� ������� ���� �� ������� �����
		snake.addPiece(next); // ��������� ��������� ������� ���� � ������ ����
	}

	// ��������� ����� ��������� ���������� ������
	void eatApple()
	{
		delete apple; // ����������� ������ ���������� ��� ������
		apple = NULL; // ������������� ��������� �� ���
		scoreboard.increaseScore(); // ����������� ���� �� �������
		int current_score = scoreboard.getScore();//������ ������� ���������
		if (best_score.set(current_score))
		{
			best_score.updateWindow();//��������� ������ ���������, ���� ������������ ��� �����
		}
	}

public:
	// ����������� ������
	SnakeGame(int height, int width, int speed) : scoreboard(45, 23, 30, 3), best_score()
	{
		board = Board(height, width, speed); // �������� ������� �����
		int sb_row = board.getStartCol() + height,
			sb_col = board.getStartCol();
		initialize(); // ����� ������ ������������� ����
		best_score.updateWindow(); // ���������� ���� ������� ����������
	}

	// ���������� ������
	~SnakeGame()
	{
		delete apple; // �������� ������� ������
	}

	// ����� ������������� ����
	void initialize()
	{
		apple = NULL; // ������������� ��������� �� ������ � ����
		board.initialize(); // �������������� ������� �����

		game_over = false; // ������������� ���� ��������� ���� � ����
		srand(time(NULL)); // �������������� ��������� ��������� �����
		snake.setDirection(down); // ������������� ����������� �������� ���� ����
		handleNextPiece(SnakePiece(1, 1)); // ��������� ���������� ������� ����
		handleNextPiece(snake.nextHead()); // ��������� ���������� ������� ����
		handleNextPiece(snake.nextHead()); // ��������� ���������� ������� ����

		snake.setDirection(righht); // ������������� ����������� �������� ���� ������

		handleNextPiece(snake.nextHead()); // ��������� ���������� ������� ����

		if (apple == NULL) // ���� ��������� �� ������ ������ �� ����������, �� ������� ������
			createApple();
	}

	// ����� ��������� ����������������� �����
	void processInput()
	{
		chtype input = board.getInput(); // ��������� ������� ����� �� ������������
		int old_timeout = board.getTimeout(); // ���������� �������� ��������
		switch (input)
		{
		case KEY_UP:
		case 'w':
			snake.setDirection(up); // ������������� ����������� �������� ���� �����
			break;
		case KEY_DOWN:
		case 's':
			snake.setDirection(down); // ������������� ����������� �������� ���� ����
			break;
		case KEY_RIGHT:
		case 'd':
			snake.setDirection(righht); // ������������� ����������� �������� ������
			break;
		case KEY_LEFT:
		case 'a':
			snake.setDirection(lefft);// ������������� ����������� �������� �����
			break;
		case 'p': // ���� ������ ������� 'p'
			board.setTimeout(-1); // ������������� ������� � -1, ��� ����� ���� ������������������
			while (board.getInput() != 'p') // �������, ���� �� ����� ������ ������� 'p' ��� ���
				;
			board.setTimeout(old_timeout); // ��������������� �������
			break;
		default:
			break;
		}
	}

	void updateState()//��������� ��������� ����
	{
		handleNextPiece(snake.nextHead()); //�������� ��������� ������ ������(������ �� �������)

		if (apple == NULL)//��������� ������
			createApple();
	}
	void redraw()//��������� ����
	{
		board.refresh();
		scoreboard.refresh();
		best_score.updateWindow();
	}

	bool isOver()//�������� �� ����� ����
	{
		return game_over;
	}
	int getScore()//������ ����
	{
		return scoreboard.getScore();
	}

};