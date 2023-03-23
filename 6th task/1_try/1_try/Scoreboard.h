#pragma once
#include <curses.h>

class Scoreboard 
{
private:
	int score;
	WINDOW* window;

public:
    Scoreboard(int x, int y, int width, int height) : score(0), window(newwin(height, width, y, x))
    {
        // ����� ��� ����
        box(window, 0, 0);
        // ����������� ���������� �����
        mvwprintw(window, 1, 1, "Score: %d", score);
        // ���������� ����
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        wbkgd(window, COLOR_PAIR(1));
        wrefresh(window);
    }

    ~Scoreboard() 
    {
        // �������� ����
        delwin(window);
    }

    // ����� ��� ���������� �����
    void increaseScore() 
    {
        score++;
        updateScore();
    }

    void refresh()//���������� ����
    {
        wrefresh(window);
    }

    // ����� ��� ���������� ����������� �����
    void updateScore() 
    {
        wclear(window);
        box(window, 0, 0);
        mvwprintw(window, 1, 1, "Score: %d", score);
        wrefresh(window);
    }

    // ����� ��� ��������� �������� �����
    int getScore() 
    {
        return score;
    }
};