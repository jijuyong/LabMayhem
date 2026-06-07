#include "game.h"
#include <fstream>

Game::Game()
: okno(sf::VideoMode({1600,1000}), "The Etherium - Awakening")
, sprite_bg(tex_bgGame){

    okno.setFramerateLimit(60);
    srand(static_cast<unsigned int>(time(0)));

    stav = Stav_Hra :: Hlavni_menu;
    current_level_idx = 0;
    current_question_idx = 0;
    pocet_chyb = 0;
    player_input = "";

    index_hadani = 0;
    zbylo_pokusu = 0;

    if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf")) { // Chú ý chữ F viết hoa!
        std::cerr << "Chyba: Nepodarilo se nacist font Arial.ttf" << std::endl;
    }

    tvorit_heslo();
    tvorit_level();
    load_bg();

    if (bg_song.openFromFile("background_song")){
        bg_song.setLooping(true);
        bg_song.setVolume(40.f);
        bg_song.play();
    }
    
}
void SetColor(int mau)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
}

std::string Game::naMale(std::string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        text[i] = tolower(text[i]);
    }
    return text;
}

void Game::tvorit_heslo()
{
    for (int i = 0; i < 5; i++)
    {
        int x = rand() % 10;
        heslo.push_back(x);
    }
}

bool Game::kontrolovatOdpoved(const std::string &odpovedOdHrace, const std::vector<std::string> &spravny_odpoved)
{
    std::string answer = naMale(odpovedOdHrace);
    for (const auto &spravnej : spravny_odpoved)
    {
        if (answer == naMale(spravnej))
            return true;
    }
    return false;
}


void Game:: tvorit_level(){
    Level lvl1 ("Foam Apocalypse","Obrazky/level/lvl1.png","video_reakce\\elephant.mp4");
    Otazka o1_1 (1,0,"Zadejte nazev H₂O₂: ");
    o1_1.settext_odpoved({"peroxid vodiku", "peroxid vodíku", "peroxidvodiku"});
    Otazka o1_2 (2,1,"Kolik gramů droždí (katalyzátoru) použiješ(gram)?: ");
    o1_2.setSpravne_Cislo(15);
    lvl1.prijat_otazky(o1_1);
    lvl1.prijat_otazky(o1_2);
    seznam.push_back(lvl1);

    Level lvl2 ("Level 2 - Midnight Neon","Obrazky/level/lvl2.png","video_reakce\\luminol.mp4");
    Otazka o2_1(1,1,"kolik ml chloranu sodného: ");
    o2_1.setSpravne_Cislo (2);
    Otazka o2_2(2, 0, "0,8 g čeho máme smíchat s 0,1 g luminolu: ");
    o2_2.settext_odpoved({"hydroxid sodny", "hydroxid sodný", "hydroxidsodny"});
    lvl2.prijat_otazky(o2_1);
    lvl2.prijat_otazky(o2_2);
    seznam.push_back(lvl2);

    Level lvl3 ("Level 3 - Howl of the Hellhound","Obrazky/level/lvl3.png","video_reakce\\barking_dog.mp4");
    Otazka o3_1 (1,0,"Jaký plyn se v experimentu používá kromě NO nebo N₂O(napiš název plynu): ");
    o3_1.settext_odpoved ({"sirouhlik","sirouhlík"});
    Otazka o3_2 (2,1,"Kolik sirouhlíku se přidává na 1 litr plynu(v ml): ");
    o3_2.setSpravne_Cislo(2);
    lvl3.prijat_otazky(o3_1);
    lvl3.prijat_otazky(o3_2);
    seznam.push_back(lvl3);

    Level lvl4 ("Level 4 - Iron Rain","Obrazky/level/lvl4.png","video_reakce\\thermit.mp4");
    Otazka o4_1 (1,0,"Jak se jinak říká hliníku: ");
    o4_1.settext_odpoved ({"aluminium"});
    Otazka o4_2 (2,0,"V jakém minerálu se oxid železitý (Fe₂O₃) vyskytuje nejčastěji: ");
    o4_2.settext_odpoved({"hematit"});
    lvl4.prijat_otazky(o4_1);
    lvl4.prijat_otazky(o4_2);
    seznam.push_back(lvl4);

    Level lvl5 ("Level 5 - Abyssal Detonation","Obrazky/level/lvl5.png","video_reakce\\bubble.mp4");
    Otazka o5_1 (1,0,"Jak se nazývá látka vznikající reakcí vodíku a kyslíku?: ");
    o5_1.settext_odpoved ({"voda"});
    Otazka o5_2 (2,0,"Jak se obecně označuje prudká reakce doprovázená uvolněním velkého množství energie?: ");
    o5_2.settext_odpoved({"exploze"});
    lvl5.prijat_otazky(o5_1);
    lvl5.prijat_otazky(o5_2);
    seznam.push_back(lvl5);

}

void Game:: load_bg(){
    tex_bgMenu.loadFromFile("Obrazky/background_menu.png");
    tex_bgGame.loadFromFile("Obrazky/background_game.png"); 
    tex_bgGameOver.loadFromFile("Obrazky/background_gameover.png");
    sprite_bg.setTexture(tex_bgMenu);
}

void Game :: pocet_pokusu_podle_chyb(){
    if(pocet_chyb == 0){
        zbylo_pokusu = 1;
    }else if(pocet_chyb >1 && pocet_chyb<=3){
        zbylo_pokusu = 3;
    }else zbylo_pokusu = 5;
}

void Game :: opokovat_current_lvl (){
    current_question_idx = 0;
    player_input ="";
}

void Game :: play(){
    while (okno.isOpen()){
        zpracovat_udalosti();
        vykreslit();
    }
    
}

void Game::zpracovat_udalosti()
{
    while (const std::optional<sf::Event> event = okno.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            okno.close();
        }

        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (stav == Stav_Hra::Hlavni_menu &&
                mouseEvent->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePos(
                    static_cast<float>(mouseEvent->position.x),
                    static_cast<float>(mouseEvent->position.y)
                );

                if (mousePos.x >= 650.f && mousePos.x <= 950.f &&
                    mousePos.y >= 400.f && mousePos.y <= 480.f)
                {
                    stav = Stav_Hra::InputName;
                    sprite_bg.setTexture(tex_bgGame);
                }

                if (mousePos.x >= 650.f && mousePos.x <= 950.f &&
                    mousePos.y >= 550.f && mousePos.y <= 630.f)
                {
                    okno.close();
                }
            }
        }

        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>())
        {
            zpracovat_text_vstup(textEvent->unicode);
        }

        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyEvent->code == sf::Keyboard::Key::Enter)
            {
                zpracovat_tisk_emteru();
            }
        }
    }
}

void Game  :: zpracovat_text_vstup (char znak){
    if (stav == Stav_Hra::InputName || stav == Stav_Hra::AskQuestion || 
        stav == Stav_Hra::WrongAnswer || stav == Stav_Hra::hadat_heslo) {
        
        if (znak == 8) { 
            if (!player_input.empty()) player_input.pop_back();
        } 
        else if (znak >= 32 && znak < 128 && player_input.length() < 30) {
            player_input += znak; 
        }
    }
}

void Game :: zpracovat_tisk_emteru(){
    if (stav == Stav_Hra::InputName){
        if (!player_input.empty()) {
            Hrac.Zadat_jmeno(player_input); 
            stav = Stav_Hra::Ukazat_rules;  
            player_input = "";
        }
    }
    else if (stav == Stav_Hra::Ukazat_rules) {
        stav = Stav_Hra::Ukazat_lvl; 
        player_input = "";
    } 
    else if (stav == Stav_Hra::Ukazat_lvl) {
        stav = Stav_Hra::AskQuestion;    
        player_input = "";
    } 
    else if (stav == Stav_Hra::AskQuestion) {
        const Level& current_lvl = seznam[current_level_idx];
        const Otazka& current_q = current_lvl.getSeznam_otazka()[current_question_idx];
        bool is_correct = false;

        if (current_q.getTyp() == 0) { 
            is_correct = kontrolovatOdpoved(player_input, current_q.getspravny_text());
        } else { 
            try {
                int num = std::stoi(player_input);
                if (num == current_q.getspravne_Cislo()) is_correct = true;
            } catch (...) { is_correct = false; }
        }

        if (is_correct) {
            current_question_idx++;
            player_input = "";
            
            if (current_question_idx >= current_lvl.getSeznam_otazka().size()) {
                system(("start " + current_lvl.getLink_V()).c_str());
                
                current_level_idx++;
                if (current_level_idx < 5) {
                    stav = Stav_Hra::Ukazat_lvl; 
                    current_question_idx = 0;
                } else {
                    stav = Stav_Hra::hadat_heslo;
                    index_hadani = 0;
                    pocet_pokusu_podle_chyb(); 
                }
            }
        } else {
            pocet_chyb++;
            system("start video_reakce\\explosion.mp4");
            stav = Stav_Hra::WrongAnswer; 
            player_input = "";
        }
    } 
    else if (stav == Stav_Hra::WrongAnswer) {
        std::string choice = naMale(player_input);
        if (choice == "ano") {
            opokovat_current_lvl();
            stav = Stav_Hra::Ukazat_lvl; 
        } else if (choice == "ne") {
            stav = Stav_Hra::GameOver;
            sprite_bg.setTexture(tex_bgGameOver); 
        }
        player_input = "";
    }
    else if (stav == Stav_Hra::hadat_heslo) {
        try {
            int guessed_num = std::stoi(player_input);
            if (guessed_num == heslo[index_hadani]) {
                index_hadani++; 
                player_input = "";
                if (index_hadani >= 5) {
                    stav = Stav_Hra::OpenChest; 
                } else {
                    pocet_pokusu_podle_chyb(); 
                }
            } else {
                zbylo_pokusu--; 
                player_input = "";
                if (zbylo_pokusu <= 0) {
                    stav = Stav_Hra::GameOver;
                    sprite_bg.setTexture(tex_bgGameOver); 
                }
            }
        } catch (...) { player_input = ""; }
    }
}

void Game :: vykreslit (){
    okno.clear();
    okno.draw(sprite_bg);

    sf::Text text_title(font);
    text_title.setCharacterSize(45);
    text_title.setFillColor(sf::Color::Yellow);

    sf::Text text_sub(font);
    text_sub.setCharacterSize(30);
    text_sub.setFillColor(sf::Color::White);

    if (stav == Stav_Hra::Hlavni_menu) {
        text_title.setString("THE ETHERIUM LABORATORY");
        text_title.setPosition({480.f, 200.f});
        okno.draw(text_title);

        sf::RectangleShape btnPlay(sf::Vector2f(300.f, 80.f));
        btnPlay.setFillColor(sf::Color(50, 150, 50));
        btnPlay.setPosition({650.f, 400.f});
        okno.draw(btnPlay);

        text_sub.setString("PLAY GAME");
        text_sub.setPosition({720.f, 420.f});
        okno.draw(text_sub);

        sf::RectangleShape btnExit(sf::Vector2f(300.f, 80.f));
        btnExit.setFillColor(sf::Color(150, 50, 50));
        btnExit.setPosition({650.f, 550.f});
        okno.draw(btnExit);

        text_sub.setString("EXIT GAME");
        text_sub.setPosition({725.f, 570.f});
        okno.draw(text_sub);
    }
    else if (stav == Stav_Hra::InputName) {
        text_title.setString("ZADANI CHARAKTERU");
        text_title.setPosition({580.f, 200.f});
        okno.draw(text_title);

        text_sub.setString("Zadej jmeno sveho charakteru:\n\n > " + player_input);
        text_sub.setPosition({450.f, 400.f});
        okno.draw(text_sub);

        text_sub.setString("Stiskni [ENTER] pro potvrzeni.");
        text_sub.setFillColor(sf::Color(150, 150, 150));
        text_sub.setPosition({580.f, 650.f});
        okno.draw(text_sub);
    }
    else if (stav == Stav_Hra::Ukazat_rules) {
        sf::Texture tex_rules;
        if (tex_rules.loadFromFile("Obrazky/rules.png")) {
            sf::Sprite sp_rules(tex_rules);
            sp_rules.setPosition({300.f, 100.f});
            okno.draw(sp_rules);
        }
        text_sub.setString("Stiskni ENTER pro hru...");
        text_sub.setFillColor(sf::Color::Cyan);
        text_sub.setPosition({630.f, 850.f});
        okno.draw(text_sub);
    }
    else if (stav == Stav_Hra::Ukazat_lvl) {
        sf::Texture tex_lvl;
        if (tex_lvl.loadFromFile(seznam[current_level_idx].getLink_P())) {
            sf::Sprite sp_lvl(tex_lvl);
            sp_lvl.setPosition({250.f, 100.f});
            okno.draw(sp_lvl);
        }
        text_sub.setString("Prostuduj navod a stiskni ENTER pro zobrazeni otazky...");
        text_sub.setFillColor(sf::Color::Green);
        text_sub.setPosition({450.f, 880.f});
        okno.draw(text_sub);
    }
    else if (stav == Stav_Hra::AskQuestion) {
        text_title.setString(seznam[current_level_idx].getJmenoLevel());
        text_title.setPosition({200.f, 80.f});
        okno.draw(text_title);

        const Otazka& q = seznam[current_level_idx].getSeznam_otazka()[current_question_idx];
        text_sub.setString("Otazka " + std::to_string(q.getporadi()) + ": " + q.getOdpoveved());
        text_sub.setPosition({200.f, 300.f});
        okno.draw(text_sub);

        sf::RectangleShape box(sf::Vector2f(800.f, 60.f));
        box.setFillColor(sf::Color(30, 30, 30));
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color::White);
        box.setPosition({200.f, 450.f});
        okno.draw(box);

        sf::Text text_input(font);
        text_input.setString(" > " + player_input);
        text_input.setCharacterSize(30);
        text_input.setFillColor(sf::Color::Yellow);
        text_input.setPosition({210.f, 460.f});
        okno.draw(text_input);

        text_sub.setString("Napis odpoved a stiskni [ENTER] pro odeslani.");
        text_sub.setFillColor(sf::Color(180, 180, 180));
        text_sub.setPosition({200.f, 550.f});
        okno.draw(text_sub);
    }
    else if (stav == Stav_Hra::WrongAnswer) {
        text_title.setString("CHYBA! TVE RESENI BYLO NESPAVNE!");
        text_title.setFillColor(sf::Color::Red);
        text_title.setPosition({350.f, 300.f});
        okno.draw(text_title);

        text_sub.setString("Chces znovu zkusit tento level? (napis: ano / ne): \n\n Vasi volba: " + player_input);
        text_sub.setPosition({420.f, 450.f});
        okno.draw(text_sub);
    }
    else if (stav == Stav_Hra::hadat_heslo) {
        text_title.setString("DEKODOVANI FINALNIHO ZAMKU KUFRU");
        text_title.setPosition({350.f, 100.f});
        okno.draw(text_title);

        std::string info_errors = "Celkovy pocet chyb v laborkach: " + std::to_string(pocet_chyb) + "\n";
        info_errors += "Mate k dispozici celkem " + std::to_string(zbylo_pokusu) + " pokusu na toto cislo.";
        text_sub.setString(info_errors);
        text_sub.setPosition({400.f, 220.f});
        okno.draw(text_sub);

        std::string secret_progress = "Zadejte " + std::to_string(index_hadani + 1) + ". tajne cislo (0-9):\n\n > " + player_input;
        sf::Text text_g(font);
        text_g.setString(secret_progress);
        text_g.setCharacterSize(35);
        text_g.setFillColor(sf::Color::Magenta);
        text_g.setPosition({400.f, 450.f});
        okno.draw(text_g);
    }
    else if (stav == Stav_Hra::OpenChest) {
        text_title.setString("GRATULUJEME! ODEMKL JSI TRUHLU S POKLADEM!");
        text_title.setFillColor(sf::Color::Green);
        text_title.setPosition({250.f, 300.f});
        okno.draw(text_title);

        sf::Texture tex_chest;
        if (tex_chest.loadFromFile("Obrazky/chest_open.png")) {
            sf::Sprite sp_chest(tex_chest);
            sp_chest.setPosition({600.f, 450.f});
            okno.draw(sp_chest);
        }
    }
    else if (stav == Stav_Hra::GameOver) {
        text_title.setString("GAME OVER - OPUSTIL JSI LABORKU");
        text_title.setFillColor(sf::Color::Red);
        text_title.setPosition({400.f, 400.f});
        okno.draw(text_title);
    }

    okno.display();
}




