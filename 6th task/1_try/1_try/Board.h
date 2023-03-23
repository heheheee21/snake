#pragma once
#include <curses.h>
#include "Drawable.h"
#include "Time.h"

class Board
{
public:
    Board()//����������� 1: ������� ���� � ����������� �� �������
    {
        construct(0, 0, 300);
    }
	Board(int height, int width, int speed)//����������� 2: ������� ���� � ��������� ������� ������� � ���������
	{
        construct(height, width,  speed);
	}
    void initialize()//������� � ��������� ����(�������������� ���)
    {
        clear();
        refresh ();
    }
    void addBorder()//��������� ������� ����
    {
        box(board_win, 0, 0);
    }

    void add(Drawable drawable)//��������� ������ drawable ��������� ��� ���������� � ������
    {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch)//��������� ������ �� � �������� �����������
    {
        mvwaddch(board_win, y, x, ch);
    }

    chtype getInput()//�������� ���� � ��������� ��� (������ �������� ��������� ������ ����������� ����� ������)
    {
        time_t time_last_input = Time::milliseconds(); //������� ����� � �������������
        chtype input = wgetch(board_win);//���� ������������
        chtype new_input = ERR;//�������� ERR ����� ����������, ��� ����� ���� �� �������

        setTimeout(0);//��������� ��������� 
        while (time_last_input + timeout >= Time::milliseconds()) //��������� ������ �� �����(�� ������� 300)
            //halfdelay(timeout - );
            new_input = wgetch(board_win);//���� �� ������, �� �������� ����� ���� �� ������������
        setTimeout(timeout);//��������������� �������

        if (new_input != ERR)
            input = new_input;//���� �������� ����� ����, �� ���������� ���, ���� ��� - ���������� ������
        return input;//��� ������ while ���������� ���������� ����� ��� ������ ���� 
    }

    void getEmptyCoorinates(int& y, int& x)//��������� ������ ����������
    {
        while ((mvwinch(board_win, y = rand() % height, x = rand() % width )) != ' ');
    }

    chtype getCharAt(int y, int x)//��������� ������ � �������� �����������
    {
        return mvwinch(board_win, y, x);
    }

    void clear()//������� ����
    {
        wclear(board_win);
        addBorder();
    }

    void refresh()//��������� ���
    {
        wrefresh(board_win);
    }
    void setTimeout(int timeout)//������������� ������� � �������������
    {
        wtimeout(board_win, timeout);
    }

    int getTimeout()//���������� ������� �������� ��������
    {
        return timeout;
    }

    int getStartRow()//���������� ���������� Y �������� ������ ���� �������� ���� �� ������.
    {
        return start_row;
    }

    int getStartCol()//���������� ���������� X �������� ������ ���� �������� ���� �� ������.
    {
        return start_col;
    }

private:
	WINDOW *board_win;

    int height, width, start_row, start_col, timeout;

    void construct(int height, int width, int speed)
        /* ������������ ��� ������������� ������� Board. 
        ��� ��������� ������ height, ������ width � �������� speed ����, ������� ���� board_win
        � ��������� ��������� � ������������, ����������� ���, 
        ������������� ������� � �������� ����� keypad, ������� ��������� �������� ���� �� ����������.*/
    {
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);

        this->height = height;
        this->width = width;

        start_row = (yMax / 2) - (height / 2);
        start_col = (xMax / 2) - (width / 2);

        timeout = speed;

        board_win = newwin(height, width, start_row, start_col);
        setTimeout(speed);
        keypad(board_win, true);
    }
};

