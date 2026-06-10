#include "Game.h"

int main() {
    system("chcp 65001"); // UTF-8 podpora
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    // Ẩn cửa sổ dòng lệnh (Console) màu đen của Windows đi 
    // để người chơi chỉ tập trung nhìn vào cửa sổ đồ họa SFML duy nhất.
    ShowWindow(GetConsoleWindow(), SW_HIDE); 

    // Khởi tạo đối tượng Game
    Game etheriumGame;
    
    // Kích hoạt vòng lặp chính (Engine loop) để trò chơi bắt đầu chạy
    etheriumGame.play(); 
    
    return 0;
}