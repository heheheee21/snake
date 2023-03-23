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
        // Рамка для окна
        box(window, 0, 0);
        // Отображение начального счета
        mvwprintw(window, 1, 1, "Score: %d", score);
        // Обновление окна
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        wbkgd(window, COLOR_PAIR(1));
        wrefresh(window);
    }

    ~Scoreboard() 
    {
        // Удаление окна
        delwin(window);
    }

    // Метод для увеличения счета
    void increaseScore() 
    {
        score++;
        updateScore();
    }

    void refresh()//обновление окна
    {
        wrefresh(window);
    }

    // Метод для обновления отображения счета
    void updateScore() 
    {
        wclear(window);
        box(window, 0, 0);
        mvwprintw(window, 1, 1, "Score: %d", score);
        wrefresh(window);
    }

    // Метод для получения текущего счета
    int getScore() 
    {
        return score;
    }
};