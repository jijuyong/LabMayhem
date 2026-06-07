#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <ctime>

//cac trang thai chay beham hra
enum class Stav_Hra {
    Hlavni_menu,       // Menu chính (Có nút Play và Exit)
    InputName,      // Màn hình nhập tên nhân vật bằng chữ đồ họa
    Ukazat_rules,      // Hiện rules.png + dòng chữ "Stiskni ENTER pro hru"
    Ukazat_lvl, // Hiện ảnh hướng dẫn của từng level (lvl1.png -> lvl5.png)
    AskQuestion,    // Màn hình câu hỏi + Ô nhập câu trả lời đồ họa
    WrongAnswer,    // Màn hình báo sai, hỏi chơi lại không (ano/ne)
    hadat_heslo,     // Vòng đoán 5 chữ số mật mã cuối game (Dựa trên file treti_verze.cpp)
    OpenChest,      // Màn hình mở rương kho báu thành công (Chiến thắng)
    GameOver        // Thua cuộc / Thoát game (Chuyển sang background gameover)
};

class Player {
private:
    std::string name;
public:
    void Zadat_jmeno(std::string jmeno) { name = jmeno; }
    std::string getName() const { return name; }
};

class Otazka {
private:
    int poradi;
    int typ; // 0 = chữ (văn bản), 1 = số
    std::string odpoved; // Nội dung câu hỏi hiển thị
    std::vector<std::string> spravne_text;
    int spravne_cislo;
public:
    Otazka(int stt, int typy, std::string cau_hoi)
        : poradi(stt), typ(typy), odpoved(cau_hoi), spravne_cislo(0) {}

    int getporadi() const { return poradi; }
    int getTyp() const { return typ; }
    std::string getOdpoveved() const { return odpoved; }
    
    std::vector<std::string> getspravny_text() const { return spravne_text; }
    void settext_odpoved(const std::vector<std::string>& odpoved_text) { spravne_text = odpoved_text; }

    int getspravne_Cislo() const { return spravne_cislo; }
    void setSpravne_Cislo(int odpoved_so) { spravne_cislo = odpoved_so; }
};

class Level {
private:
    std::string jmeno_level;
    std::string link_postup; // Đường dẫn ảnh hướng dẫn (lvl1.png, lvl2.png...)
    std::vector<Otazka> seznam_otazky;
    std::string link_video;  // Đường dẫn video phản ứng thành công
public:
    Level(std::string nameLevel, std::string link_p, std::string link_v)
        : jmeno_level(nameLevel), link_postup(link_p), link_video(link_v) {}

    void prijat_otazky(const Otazka &questions) { seznam_otazky.push_back(questions); }
    std::string getLink_P() const { return link_postup; }
    std::string getLink_V() const { return link_video; }
    std::vector<Otazka> getSeznam_otazka() const { return seznam_otazky; }
    std::string getJmenoLevel() const { return jmeno_level; }
};

class Game {
private:
    sf::RenderWindow okno;
    sf::Font font;
    sf::Music bg_song;

    // Các tài nguyên hình nền (Backgrounds)
    sf::Texture tex_bgMenu;
    sf::Texture tex_bgGame;
    sf::Texture tex_bgGameOver;
    sf::Sprite sprite_bg;

    // Biến quản lý logic trò chơi
    Stav_Hra stav;
    Player Hrac;
    std::vector<Level> seznam;
    std::vector<int> heslo; // Chuỗi mật mã bí mật gồm 5 chữ số
    int pocet_chyb;       // Tổng số lỗi tích lũy qua các level
    
    size_t current_level_idx;
    size_t current_question_idx;
    std::string player_input; 

    // Biến xử lý cho vòng đoán số cuối game 
    int index_hadani;    // Đang đoán đến chữ số thứ mấy (0 -> 4)
    int zbylo_pokusu; // Số lượt đoán còn lại cho chữ số hiện tại

    // Khởi tạo hệ thống dữ liệu nội bộ
    void tvorit_heslo();
    void tvorit_level();
    void load_bg();
    void pocet_pokusu_podle_chyb();
    
    // Hàm bổ trợ xử lý chuỗi
    std::string naMale(std::string text);
    bool kontrolovatOdpoved(const std::string& answer, const std::vector<std::string>& correct_answers);
    void opokovat_current_lvl();

    // Hệ thống bắt sự kiện và xử lý đồ họa SFML 3.0
    void zpracovat_udalosti();
    void zpracovat_text_vstup(char znak);
    void zpracovat_tisk_emteru();
    void vykreslit();

public:
    Game();
    void play();
};

#endif