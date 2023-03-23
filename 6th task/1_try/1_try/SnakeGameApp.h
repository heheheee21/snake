#pragma once
#include <curses.h>
#include <iostream>
#include <fstream>
#include "Board.h"
#include "SnakeGame.h"
#include "Drawable.h"
#include "Scoreboard_thebest.h"

using namespace std;

#define BOARD_DIM 15
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2

class SnakeGameApp 
{
public:
    SnakeGameApp() 
    {
        initscr();
        noecho();
        curs_set(0);
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
    }

    ~SnakeGameApp() 
    {
        endwin();
    }

    void run() 
    {
        while (true) 
        {
            SnakeGame game(BOARD_ROWS, BOARD_COLS, 300);

            while (!game.isOver()) {
                game.processInput();
                game.updateState();
                game.redraw();
            }

            showGameOverScreen(game.getScore());
            if (!playAgain()) {
                break;
            }
        }
    }

private:
    void showGameOverScreen(int score) 
    {
        clear();
        refresh();
        WINDOW* textwin = newwin(4, 30, 10, 20);
        wbkgd(textwin, COLOR_PAIR(2));
        mvwprintw(textwin, 1, 1, "Game Over! Your score: % d", score);
        mvwprintw(textwin, 2, 1, "Would u like to play again?");
        wrefresh(textwin);
    }

    bool playAgain() 
    {
        WINDOW* menuwin = newwin(4, 5, 13, 25);
        box(menuwin, 0, 0);
        wbkgd(menuwin, COLOR_PAIR(1));
        wrefresh(menuwin);
        keypad(menuwin, true);
        string choices[2] = { "Yes", "No" };
        int choice;
        int highlight = 0;
        while (1) {
            for (int i = 0; i < 2; i++) {
                if (i == highlight)
                    wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin, i + 1, 1, choices[i].c_str());
                wattroff(menuwin, A_REVERSE);
            }
            choice = wgetch(menuwin);
            switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 2)
                    highlight = 1;
                break;
            default:
                break;
            }
            if (choice == 10) // выбор пункта меню
                break;
        }
        wrefresh(menuwin);
        clear();
        refresh();

        return highlight == 0;
    }
};


