#pragma once
#include <fstream>
#include <curses.h>

using namespace std;

class BestScore
{
public:
    BestScore() : m_score(0)//лучший результат равен 0 пока что
    {
        load();//загружаем из файла данные о результате
        createWindow();//создаем окно
    }

    ~BestScore()//деконструктор
    {
        delwin(m_window);
    }

    int get()//текущий лучший рещультат
    {
        return m_score;
    }

    bool set(int score)/*принимает новое значение лучшего результата
        и обновляет его, если переданное значение больше текущего*/
    {
        if (score > m_score)
        {
            m_score = score;
            return save();
        }
        return false;
    }

    void updateWindow()//обновляем содержимое окна
    {
        wclear(m_window);
        box(m_window, 0, 0);
        mvwprintw(m_window, 1, 1, "Best Score: %d", m_score);
        start_color();
        /*
        COLOR_BLACK
        COLOR_RED
        COLOR_GREEN
        COLOR_YELLOW
        COLOR_BLUE
        COLOR_MAGENTA
        COLOR_CYAN
        COLOR_WHITE
        */
        init_pair(1, COLOR_RED, COLOR_BLACK);
        wbkgd(m_window, COLOR_PAIR(1));
        wrefresh(m_window);
    }

private:
    int m_score;//текущий лучший результат в игре
    WINDOW* m_window;//экран

    bool save()//сохраняем в файл
    {
        ofstream file("best_score.txt");
        if (!file.is_open())
        {
            return false;
        }

        file << m_score;
        file.close();
        return true;
    }

    bool load()//загружаем из файла
    {
        ifstream file("best_score.txt");
        if (!file.is_open())
        {
            return false;
        }

        file >> m_score;
        file.close();
        return true;
    }

    void createWindow()//создаем окно
    {
        m_window = newwin(3, 30, 5, 45); 
        box(m_window, 0, 0);
        updateWindow();
    }
};
