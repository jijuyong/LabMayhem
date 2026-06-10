#include "game.h"
#include <filesystem>

sf::Music Game::bg_song;


Game::Game() : okno(sf::VideoMode({1600, 1000}), "The Etherium - SFML 3.0 Edition"), sprite_bg(tex_bgMenu)
{
    system("chcp 65001");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    okno.setFramerateLimit(60);
    srand(static_cast<unsigned int>(time(0)));

    stav = Stav_Hra::Hlavni_menu;
    current_level_idx = 0;
    current_question_idx = 0;
    pocet_chyb = 0;
    player_input = "";
    current_gif_frame = 0;

    if (!font.openFromFile("C:/Windows/Fonts/Consola.ttf"))
    {
        std::cerr << "Chyba: Nepodarilo se nacist font Consola.ttf" << std::endl;
    }

    tvorit_heslo();
    tvorit_level();
    load_assets();
    sprite_bg.setTexture(tex_bgMenu);

    if (bg_song.getStatus() == sf::SoundStream::Status::Stopped)
    {
        if (!bg_song.openFromFile("background_song.mp3"))
        {
            std::cout << "Loi: Khong the tai file nhac background_song.mp3!" << std::endl;
            return;
        }
        bg_song.setLooping(true); // Lặp lại vô hạn
        bg_song.setVolume(40.f);  // Âm lượng 40%
        bg_song.play();           // Phát nhạc
    }
}

void Game::tvorit_heslo(){
    heslo.clear();

    while (heslo.size() < 5)
    {
        int x = rand() % 10;

        bool existuje = false;
        for (int cislo : heslo)
        {
            if (cislo == x)
            {
                existuje = true;
                break;
            }
        }

        if (!existuje)
        {
            heslo.push_back(x);
        }
    }
}

void Game::tvorit_level(){
    //level1
    Level lvl1;
    lvl1.jmeno_level = "Level 1 - Foam Apocalypse";
    lvl1.link_p = "Obrazky/level/lvl1.png";
    lvl1.link_v = "video_reakce\\elephant.mp4";

    Otazka o1_1;
    o1_1.poradi =1;
    o1_1.typy = 0;
    o1_1.question  = {"Zadejte nazev H2O2"};
    o1_1. spravny_text = {"peroxid vodiku", "peroxid vodíku", "peroxidvodiku"};
    Otazka o1_2;
    o1_2.poradi =2;
    o1_2.typy = 1;
    o1_2.question  = {"Kolik gramu drozdi (katalyzatoru) pouzijes(gram)?"};
    o1_2.spravny_cislo = 15;

    lvl1.seznam.push_back(o1_1);
    lvl1.seznam.push_back(o1_2);
    seznam.push_back(lvl1);
    //level2
    Level lvl2;
    lvl2.jmeno_level = "Level 2 - Midnight Neon";
    lvl2.link_p = "Obrazky/level/lvl2.png";
    lvl2.link_v = "video_reakce\\luminol.mp4";

    Otazka o2_1;
    o2_1.poradi =1;
    o2_1.typy = 1;
    o2_1.question  = {"kolik ml chloranu sodného"};
    o2_1. spravny_cislo =  2;
    Otazka o2_2;
    o2_2.poradi =2;
    o2_2.typy = 0;
    o2_2.question  = {"0,8 g čeho máme smíchat s 0,1 g luminolu"};
    o2_2.spravny_text = {"hydroxid sodny", "hydroxid sodný", "hydroxidsodny"};

    lvl2.seznam.push_back(o2_1);
    lvl2.seznam.push_back(o2_2);
    seznam.push_back(lvl2);
    //level3
    Level lvl3;
    lvl3.jmeno_level = "Level 3 - Howl of the Hellhound";
    lvl3.link_p = "Obrazky/level/lvl3.png";
    lvl3.link_v = "video_reakce\\barking_dog.mp4";

    Otazka o3_1;
    o3_1.poradi =1;
    o3_1.typy = 0;
    o3_1.question  = {"Jaký plyn se v experimentu používá kromě NO nebo N₂O(napiš název plynu)"};
    o3_1. spravny_text = {"sirouhlik","sirouhlík"};
    Otazka o3_2;
    o3_2.poradi =2;
    o3_2.typy = 1;
    o3_2.question  = {"Kolik sirouhlíku se přidává na 1 litr plynu(v ml)"};
    o3_2.spravny_cislo = 2;

    lvl3.seznam.push_back(o3_1);
    lvl3.seznam.push_back(o3_2);
    seznam.push_back(lvl3);

    //level4
    Level lvl4;
    lvl4.jmeno_level = "Level 4 - Iron Rain";
    lvl4.link_p = "Obrazky/level/lvl4.png";
    lvl4.link_v = "video_reakce\\thermit.mp4";

    Otazka o4_1;
    o4_1.poradi =1;
    o4_1.typy = 0;
    o4_1.question  = {"Jak se jinak říká hliníku"};
    o4_1. spravny_text = {"aluminium"};
    Otazka o4_2;
    o4_2.poradi =2;
    o4_2.typy = 0;
    o4_2.question  = {"V jakém minerálu se oxid železitý (Fe₂O₃) vyskytuje nejčastěji"};
    o4_2. spravny_text = {"hematit"};

    lvl4.seznam.push_back(o4_1);
    lvl4.seznam.push_back(o4_2);
    seznam.push_back(lvl4);
    //level5
    Level lvl5;
    lvl5.jmeno_level = "Level 5 - Abyssal Detonation";
    lvl5.link_p = "Obrazky/level/lvl5.png";
    lvl5.link_v = "video_reakce\\bubble.mp4";

    Otazka o5_1;
    o5_1.poradi =1;
    o5_1.typy = 0;
    o5_1.question  = {"Jak se nazývá látka vznikající reakcí vodíku a kyslíku?"};
    o5_1. spravny_text = {"voda"};
    Otazka o5_2;
    o5_2.poradi =2;
    o5_2.typy = 0;
    o5_2.question  = {"Jak se obecně označuje prudká reakce doprovázená uvolněním velkého množství energie?"};
    o5_2. spravny_text = {"ezploxe","výbuch","exotermní","vybuch","exotermni"};

    lvl5.seznam.push_back(o5_1);
    lvl5.seznam.push_back(o5_2);
    seznam.push_back(lvl5);
}

void Game::load_assets(){
    if (!tex_bgMenu.loadFromFile("Obrazky/background.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_gameBg.loadFromFile("Obrazky/Game_bg.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_rules.loadFromFile("Obrazky/rules.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_zadaiCharakteru.loadFromFile("Obrazky/Nadpis/zadai_charakteru.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_zadejOdpoved.loadFromFile("Obrazky/Nadpis/zadej_answer.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_chyba.loadFromFile("Obrazky/Nadpis/chyba.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_gameOverBg.loadFromFile("Obrazky/GameOver_bg.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_zadejteHeslo.loadFromFile("Obrazky/Nadpis/zadejte_heslo.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_tvojePokladJe.loadFromFile("Obrazky/Nadpis/tvoje_poklad_je.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }
    if (!tex_btnPlay.loadFromFile("Obrazky/Button/button_play.png"))
    {
        std::cerr << "khong mo duoc" << std::endl;
    }

    // Tự động tải chuỗi ảnh Gif phân rã từ thư mục frame/
    
    for (int i = 0; i <= 4; i++)
    {
        sf::Texture f;
        if (f.loadFromFile("Obrazky/frame/frame_" + std::to_string(i) + ".png"))
        {   
            gif_frames.push_back(f);
        }
    }
}

void Game::pocet_pokusu_podle_chyb()
{
    if (pocet_chyb == 0)
        zbylo_pokusu = 1;
    else if (pocet_chyb <= 3)
        zbylo_pokusu = 3;
    else
        zbylo_pokusu = 5;
}

std::string Game::naMale(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

bool Game::kontrolovatOdpoved(const std::string &answer, const std::vector<std::string> &correct_answers)
{
    std::string low_ans = naMale(answer);
    for (const auto &correct : correct_answers)
    {
        if (low_ans == naMale(correct))
            return true;
    }
    return false;
}

// Chống hack/gian lận: Tìm chữ số hợp lệ đầu tiên xuất hiện trong chuỗi người chơi nhập
std::string Game::filter_first_number_string(const std::string &input)
{
    std::string result = "";
    for (char c : input)
    {
        if (std::isdigit(c))
        {
            result += c;
            if (result.length() == 5)
                break; // Lấy đủ chiều dài chuỗi mã
        }
    }
    return result;
}

void Game::play(){
    while (okno.isOpen())
    {
        zpracovat_udalosti();

        // Xử lý đếm giờ tự động cho quy trình nạp cảnh nền chơi game
        if (stav == Stav_Hra::Ukazat_rules && !timer_started)
        {
            timer.restart();
            timer_started = true;
        }

        if (stav == Stav_Hra::Ukazat_lvl)
        {
            if (timer.getElapsedTime().asSeconds() >= 15.f)
            {
                stav = Stav_Hra::AskQuestion;
                player_input = "";
            }
        }

        vykreslit();
    }
}

void Game::zpracovat_udalosti(){
    while (const std::optional<sf::Event> event = okno.pollEvent()){
        if (event->is<sf::Event::Closed>()){
            okno.close();
        }
        if (const auto *mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()){
            if (stav == Stav_Hra::Hlavni_menu &&
                mouseEvent->button == sf::Mouse::Button::Left){
                sf::Vector2f mousePos(static_cast<float>(mouseEvent->position.x), static_cast<float>(mouseEvent->position.y));
                if (mousePos.x >= 680.f && mousePos.x <= 950.f && mousePos.y >= 850.f && mousePos.y <= 930.f){
                    stav = Stav_Hra::Ukazat_rules;
                    sprite_bg.setTexture(tex_gameBg);
                }
                if (mousePos.x >= 650.f && mousePos.x <= 950.f && mousePos.y >= 550.f && mousePos.y <= 630.f){
                    okno.close();
                }
            }
        }

        if (const auto *textEvent = event->getIf<sf::Event::TextEntered>()){
            zpracovat_textovy_vstup(textEvent->unicode);
        }

        if (const auto *keyEvent = event->getIf<sf::Event::KeyPressed>()){

            if (keyEvent->code == sf::Keyboard::Key::Enter){
                zpracovat_stisk_enteru();
            }
        }
    }
}

void Game::zpracovat_textovy_vstup(char znak)
{
    if (stav == Stav_Hra::InputName || stav == Stav_Hra::AskQuestion ||
        stav == Stav_Hra::WrongAnswer || stav == Stav_Hra::hadat_heslo)
    {
        if (znak == 8)
        {
            if (!player_input.empty())
                player_input.pop_back();
        }
        else if (znak >= 32 && znak != 127 && player_input.length() < 30)
        {
            player_input += static_cast<char>(znak);
        }
    }
}

void Game::zpracovat_stisk_enteru()
{
    if (stav == Stav_Hra::Ukazat_rules)
    {
        if (timer.getElapsedTime().asSeconds() >= 2.f)
        {
            stav = Stav_Hra::InputName;
            player_input = "";
        }
    }
    else if (stav == Stav_Hra::InputName)
    {
        if (!player_input.empty())
        {
            Hrac.name = player_input;
            stav = Stav_Hra::Ukazat_lvl;
            timer.restart();
            player_input = "";
        }
    }
    else if (stav == Stav_Hra::Ukazat_lvl)
    {
        stav = Stav_Hra::AskQuestion;
        player_input = "";
    }
    else if (stav == Stav_Hra::AskQuestion)
    {
        Level &lvl = seznam[current_level_idx];
        Otazka &q = lvl.seznam[current_question_idx];
        bool dung = false;

        if (q.typy == 0)
            dung = kontrolovatOdpoved(player_input, q.spravny_text);
        else
        {
            try
            {
                dung = (std::stoi(player_input) == q.spravny_cislo);
            }
            catch (...)
            {
                dung = false;
            }
        }

        if (dung)
        {
            current_question_idx++;
            player_input = "";
            if (current_question_idx >= lvl.seznam.size())
            {
                // Gọi video phản ứng tương ứng trên hệ thống
                system(("start " + lvl.link_v).c_str());

                // Hiển thị số mật mã tương ứng thu thập được
                std::cout << "Kycislo urovne " << current_level_idx + 1 << " je: " << heslo[current_level_idx] << std::endl;

                current_level_idx++;
                current_question_idx = 0;
                if (current_level_idx >= 5)
                {
                    stav = Stav_Hra::hadat_heslo;
                    pocet_pokusu_podle_chyb();
                }
                else
                {
                    stav = Stav_Hra::Ukazat_lvl;
                    timer.restart();
                }
            }
        }
        else
        {
            pocet_chyb++;
            stav = Stav_Hra::WrongAnswer;
            player_input = "";
        }
    }
    else if (stav == Stav_Hra::WrongAnswer)
    {
        std::string s = naMale(player_input);
        if (s == "ano")
        {
            stav = Stav_Hra::Ukazat_lvl;
            timer.restart();
            current_question_idx = 0;
        }
        else if (s == "ne")
        {
            stav = Stav_Hra::GameOver;
        }
        player_input = "";
    }
    else if (stav == Stav_Hra::hadat_heslo)
    {
        std::string filtered = filter_first_number_string(player_input);
        if (filtered.length() < 5)
        {
            player_input = "";
            return;
        }

        // Kiểm tra logic chuỗi mật mã tổ hợp
        bool khop_hoan_toan = true;
        feedback_lines.clear();

        for (size_t i = 0; i < 5; i++)
        {
            int digit_nhap = filtered[i] - '0';
            if (digit_nhap == heslo[i])
            {
                feedback_lines.push_back("Cislo " + std::to_string(digit_nhap) + " je SPRAVNE a na SPRAVNEM miste.");
            }
            else
            {
                khop_hoan_toan = false;
                if (std::find(heslo.begin(), heslo.end(), digit_nhap) != heslo.end())
                {
                    feedback_lines.push_back("Cislo " + std::to_string(digit_nhap) + " je spravne, ale na ŠPATNÉM miste.");
                }
                else
                {
                    feedback_lines.push_back("Cislo " + std::to_string(digit_nhap) + " v hesle VUBEC NEEXISTUJE.");
                }
            }
        }

        if (khop_hoan_toan)
        {
            stav = Stav_Hra::OpenChest;
        }
        else
        {
            zbylo_pokusu--;
            if (zbylo_pokusu <= 0)
            {
                stav = Stav_Hra::GameOver;
            }
        }
        player_input = "";
    }
}

void Game::draw_animated_gif_text(float x, float y)
{
    if (!gif_frames.empty())
    {
        if (gif_clock.getElapsedTime().asMilliseconds() > 150)
        {
            current_gif_frame = (current_gif_frame + 1) % gif_frames.size();
            gif_clock.restart();
        }
        sf::Sprite gif_sprite(gif_frames[current_gif_frame]);
        gif_sprite.setPosition({x, y});
        gif_sprite.setScale({0.5f,0.5f});
        okno.draw(gif_sprite);
    }
}

void Game::vykreslit()
{
    okno.clear();

    // Chọn hình nền phù hợp với trạng thái trò chơi
    sf::Sprite bg(tex_gameBg);
    if (stav == Stav_Hra::Hlavni_menu)
        bg.setTexture(tex_bgMenu);
    else if (stav == Stav_Hra::WrongAnswer)
        bg.setTexture(tex_gameBg);
    else if (stav == Stav_Hra::GameOver)
        bg.setTexture(tex_gameOverBg);
    else
        bg.setTexture(tex_gameBg);
    okno.draw(bg);

    sf::Text txt(font);
    txt.setCharacterSize(28);
    txt.setFillColor(sf::Color(0, 255, 100)); // Màu xanh Neon đặc trưng phòng thí nghiệm quân sự

    if (stav == Stav_Hra::Hlavni_menu)
    {
        sf::Sprite btn(tex_btnPlay);
        btn.setPosition({680.f, 850.f}); // Canh nút bấm chính diện tâm màn hình
        okno.draw(btn);
    }
    else if (stav == Stav_Hra::Ukazat_rules){
        sf::Sprite sp(tex_rules);
        sp.setScale({0.8f,0.8f});
        sp.setPosition({400.f, 150.f}); // Căn chính giữa nền
        okno.draw(sp);
        draw_animated_gif_text(650.f, 850.f);
    
    }
    else if (stav == Stav_Hra::InputName)
    {
        sf::Sprite sp(tex_zadaiCharakteru);
        sp.setPosition({500.f, 200.f});
        okno.draw(sp);

        txt.setString(player_input);
        txt.setPosition({650.f, 438.f}); // Vị trí đè khớp lên khung nhập liệu ô trống của PNG
        okno.draw(txt);
        draw_animated_gif_text(650.f, 850.f);
    }
    else if (stav == Stav_Hra::Ukazat_lvl)
    {
        sf::Texture lvl_tex;
        if (lvl_tex.loadFromFile(seznam[current_level_idx].link_p))
        {
            sf::Sprite sp(lvl_tex);
            sp.setScale({0.8f,0.8f});
            sp.setPosition({200.f, 80.0f}); // Vừa khít tâm nền màn hình vẽ
            okno.draw(sp);
        }
        int sec = 15 - static_cast<int>(timer.getElapsedTime().asSeconds());
        txt.setString("Zbyva casu: " + std::to_string(sec > 0 ? sec : 0) + "s");
        txt.setPosition({680.f, 850.f});
        okno.draw(txt);
    }
    else if (stav == Stav_Hra::AskQuestion)
    {
        txt.setString(seznam[current_level_idx].seznam[current_question_idx].question);
        txt.setPosition({650.f, 550.f});
        okno.draw(txt);

        sf::Sprite box(tex_zadejOdpoved);
        box.setPosition({450.f, 200.f});
        okno.draw(box);

        sf::Text input_disp(font);
        input_disp.setString(player_input);
        input_disp.setCharacterSize(26);
        input_disp.setFillColor(sf::Color::Yellow);
        input_disp.setPosition({650.f, 438.f}); // Căn lề lọt thỏm trong ảnh zadej_question.png
        okno.draw(input_disp);
    }
    else if (stav == Stav_Hra::WrongAnswer)
    {
        sf::Sprite sb(tex_chyba);
        sb.setPosition({480.f,200.f});
        okno.draw(sb);
        txt.setString(player_input);
        txt.setFillColor(sf::Color::White);
        txt.setPosition({650.f, 470.f});
        okno.draw(txt);
    }
    else if (stav == Stav_Hra::hadat_heslo)
    {
        sf::Sprite sp(tex_zadejteHeslo);
        sp.setPosition({400.f, 100.f});
        okno.draw(sp);

        txt.setString("Pocet zbyvajicich pokusu: " + std::to_string(zbylo_pokusu));
        txt.setFillColor(sf::Color::Red);
        txt.setPosition({520.f, 320.f});
        okno.draw(txt);

        sf::Text inp(font);
        inp.setString(player_input);
        inp.setCharacterSize(35);
        inp.setFillColor(sf::Color::Cyan);
        inp.setPosition({680.f, 420.f});
        okno.draw(inp);

        // Hiển thị từng dòng manh mối gợi ý giải mã mật mã
        float start_y = 540.f;
        for (const auto &line : feedback_lines)
        {
            sf::Text f_txt(font);
            f_txt.setString(line);
            f_txt.setCharacterSize(22);
            f_txt.setFillColor(sf::Color::Yellow);
            f_txt.setPosition({420.f, start_y});
            okno.draw(f_txt);
            start_y += 40.f;
        }
    }
    else if (stav == Stav_Hra::OpenChest)
    {
        sf::Sprite sp(tex_tvojePokladJe);
        sp.setPosition({400.f, 150.f});
        okno.draw(sp);

        // Đọc ngẫu nhiên một phần thưởng từ file poklad.txt theo Index định sẵn
        std::ifstream file("poklad.txt");
        std::vector<std::string> poklady;
        std::string line;
        while (std::getline(file, line))
        {
            if (!line.empty())
                poklady.push_back(line);
        }
        file.close();

        if (!poklady.empty())
        {
            int rand_idx = rand() % poklady.size();
            txt.setString("POKLAD [" + std::to_string(rand_idx + 1) + "]: " + poklady[rand_idx]);
            txt.setCharacterSize(35);
            txt.setFillColor(sf::Color::Yellow);
            txt.setPosition({450.f, 500.f});
            okno.draw(txt);

            // Tự động mở video tương ứng hệ thống index bắt đầu từ 1
            static bool video_opened = false;
            if (!video_opened)
            {
                system(("start video_reakce\\treasure_" + std::to_string(rand_idx + 1) + ".mp4").c_str());
                video_opened = true;
            }
        }
    }

    okno.display();
}
