#pragma once
#include <fstream>
#include <curses.h>

using namespace std;

class BestScore
{
public:
    BestScore() : m_score(0)//������ ��������� ����� 0 ���� ���
    {
        load();//��������� �� ����� ������ � ����������
        createWindow();//������� ����
    }

    ~BestScore()//�������������
    {
        delwin(m_window);
    }

    int get()//������� ������ ���������
    {
        return m_score;
    }

    bool set(int score)/*��������� ����� �������� ������� ����������
        � ��������� ���, ���� ���������� �������� ������ ��������*/
    {
        if (score > m_score)
        {
            m_score = score;
            return save();
        }
        return false;
    }

    void updateWindow()//��������� ���������� ����
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
    int m_score;//������� ������ ��������� � ����
    WINDOW* m_window;//�����

    bool save()//��������� � ����
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

    bool load()//��������� �� �����
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

    void createWindow()//������� ����
    {
        m_window = newwin(3, 30, 5, 45); 
        box(m_window, 0, 0);
        updateWindow();
    }
};
