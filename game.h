#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <memory>
#include <fstream>

enum class Stav_Hra {
    Hlavni_menu,       
    Ukazat_rules,      
    InputName,         
    Ukazat_lvl,        
    AskQuestion,
    Ukazat_mk_inx, 
    WrongAnswer,       
    hadat_heslo,       
    OpenChest,         
    GameOver           
};

struct Player {
    std::string name;
};

struct Otazka {
    int poradi;
    int typy;  // 0 = text, 1 = cislo
    std::string question;
    std::vector<std::string> spravny_text;
    int spravny_cislo;
};

struct Level {
    std::string jmeno_level;
    std::string link_p; 
    std::vector<Otazka> seznam;
    std::string link_v;
};

class Game {
private:
    bool level_bezchyb = true;
    sf::RenderWindow okno;
    sf::Font font;
    static sf::Music bg_song;

    // Bộ quản lý hệ thống Texture đồ họa theo kịch bản mới
    sf::Texture tex_bgMenu;
    sf::Texture tex_gameBg;
    sf::Texture tex_rules;
    sf::Texture tex_zadaiCharakteru;
    sf::Texture tex_zadejOdpoved;
    sf::Texture tex_chyba;
    sf::Texture tex_gameOverBg;
    sf::Texture tex_zadejteHeslo;
    sf::Texture tex_tvojePokladJe;
    sf::Texture tex_btnPlay;
    sf::Texture tex_vynoril_cislo;
    sf::Texture tex_box;

    sf::Sprite sprite_bg;

    // Quản lý Animation GIF cho dòng chữ stiskni_enter_pro_hra
    std::vector<sf::Texture> gif_frames;
    size_t current_gif_frame;
    sf::Clock gif_clock;

    // Biến điều khiển trạng thái và logic nội bộ
    Stav_Hra stav;
    Player Hrac;
    std::vector<Level> seznam;
    std::vector<int> heslo; 
    int pocet_chyb;       
    
    size_t current_level_idx;
    size_t current_question_idx;
    std::string player_input; 

    // Hệ thống biến cho vòng đoán mật mã phức hợp
    int zbylo_pokusu; 
    std::vector<std::string> feedback_lines; 
    std::string trung_khớp_thong_bao;

    // Quản lý thời gian chuyển cảnh tự động
    sf::Clock timer;
    bool timer_started;

    void tvorit_heslo();
    void tvorit_level();
    void load_assets();
    void pocet_pokusu_podle_chyb();
    void draw_animated_gif_text(float x, float y);
    
    std::string naMale(std::string text);
    bool kontrolovatOdpoved(const std::string& answer, const std::vector<std::string>& correct_answers);
    std::string hledat_prvni_cislo(const std::string& input);

public:
    Game();
    void play();
    void zpracovat_udalosti();
    void zpracovat_textovy_vstup(char znak);
    void zpracovat_stisk_enteru();
    void vykreslit();
};

