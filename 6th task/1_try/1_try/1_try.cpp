#include <curses.h>
#include <iostream>
#include <fstream>
#include "Board.h"
#include "SnakeGame.h"
#include "Drawable.h"
#include "Scoreboard_thebest.h"
#include "SnakeGameApp.h"


using namespace std;

int main() 
{
    SnakeGameApp app;
    app.run();
    return 0;
}
