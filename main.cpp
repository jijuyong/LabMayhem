#include "Game.h"

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE); 
    Game etheriumGame;
    etheriumGame.play(); 
    return 0;
}