#pragma once
#include <curses.h>
#include "Drawable.h"
#include "Time.h"

class Board
{
public:
    Board()//конструктор 1: создаем поле с параметрами по дефолту
    {
        construct(0, 0, 300);
    }
	Board(int height, int width, int speed)//конструктор 2: создаем поле с заданными высотой шириной и скоростью
	{
        construct(height, width,  speed);
	}
    void initialize()//очищаем и обновляем поле(инициализируем его)
    {
        clear();
        refresh ();
    }
    void addBorder()//добавляем границы поля
    {
        box(board_win, 0, 0);
    }

    void add(Drawable drawable)//добавляем объект drawable используя его координаты и символ
    {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch)//добавляем символ на в заданных координатах
    {
        mvwaddch(board_win, y, x, ch);
    }

    chtype getInput()//получает ввод и возвращае его (решена проблема ускорения змейки посредством спама кнопок)
    {
        time_t time_last_input = Time::milliseconds(); //текущее время в миллисекундах
        chtype input = wgetch(board_win);//ввод пользователя
        chtype new_input = ERR;//объявлем ERR чтобы обозначить, что новый ввод не получен

        setTimeout(0);//блокируем программу 
        while (time_last_input + timeout >= Time::milliseconds()) //проверяем прошло ли время(по дефолту 300)
            //halfdelay(timeout - );
            new_input = wgetch(board_win);//если не прошло, то получаем новый ввод от пользователя
        setTimeout(timeout);//восстанавливаем таймаут

        if (new_input != ERR)
            input = new_input;//если получили новый ввод, то возвращаем его, если нет - возвращаем старый
        return input;//как только while закончился возвращаем новый или старый ввод 
    }

    void getEmptyCoorinates(int& y, int& x)//случайные пустые координаты
    {
        while ((mvwinch(board_win, y = rand() % height, x = rand() % width )) != ' ');
    }

    chtype getCharAt(int y, int x)//возвращет символ в заданных координатах
    {
        return mvwinch(board_win, y, x);
    }

    void clear()//очищает поле
    {
        wclear(board_win);
        addBorder();
    }

    void refresh()//обновляет его
    {
        wrefresh(board_win);
    }
    void setTimeout(int timeout)//устанавливает таймаут в миллисекундах
    {
        wtimeout(board_win, timeout);
    }

    int getTimeout()//возвращает текущее значение таймаута
    {
        return timeout;
    }

    int getStartRow()//возвращает координату Y верхнего левого угла игрового поля на экране.
    {
        return start_row;
    }

    int getStartCol()//возвращает координату X верхнего левого угла игрового поля на экране.
    {
        return start_col;
    }

private:
	WINDOW *board_win;

    int height, width, start_row, start_col, timeout;

    void construct(int height, int width, int speed)
        /* используется для инициализации объекта Board. 
        Она принимает высоту height, ширину width и скорость speed поля, создает окно board_win
        с заданными размерами и координатами, настраивает его, 
        устанавливает таймаут и включает режим keypad, который позволяет получать ввод от клавиатуры.*/
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

