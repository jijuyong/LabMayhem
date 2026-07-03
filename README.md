
# The Etherium - SFML 3.0 Edition 🧪

**The Etherium** je interaktivní vzdělávací a logická hra vytvořená v C++ za použití multimediální knihovny SFML 3.0. Hráč se ocitá v prostředí vojenské chemické laboratoře, kde musí správně odpovídat na chemické a laboratorní otázky, aby získal indicie k tajnému heslu a odemkl ukrytý poklad.

---

## 🎮 Přehled hry & Herní mechaniky

1. **Zadání jména a pravidla:** Hráč se seznámí s pravidly laboratoře a zadá své jméno.
2. **Chemické laboratoře (Levely):** Hra obsahuje 5 odlišných úrovní zaměřených na reálné chemické experimenty (např. Elephant's Toothpaste, Luminol, Barking Dog, Termit). Každý level ukazuje vizuální zadání a hráč má 15 sekund na přípravu před otázkami.
3. **Získávání indicií:** * Pokud hráč projde celý level **bez jediné chyby**, odhalí se mu jedno číslo z 5místného tajného hesla.
   * Pokud hráč udělá chybu, možnost odhalit dané číslo v tomto levelu ztrácí.
4. **Hádání hesla:** Na konci hry musí hráč zadat správnou kombinaci 5místného hesla. Hra poskytuje zpětnou vazbu ve stylu hry *Logik* (zda je číslo správné a na správném místě, správné ale na špatném místě, nebo v hesle vůbec není).
5. **Počet pokusů:** Odvíjí se od celkového počtu chyb během hry. Čím méně chyb, tím méně pokusů (ale s vědomím více čísel).
6. **Odměna:** Po úspěšném prolomení hesla hra náhodně vybere odměnu ze souboru `poklad.txt` a spustí vítězné video.

---

## 🛠️ Použité technologie a knihovny

* **Jazyk:** C++17
* **Grafika & Zvuk:** [SFML 3.0](https://www.sfml-dev.org/) (Graphics, Window, System, Audio)
* **Sestavení projektu:** CMake (minimální verze 3.15)
* **Vývojové prostředí / Kompilátor:** MSYS2 (UCRT64 / GCC), VS Code
* **OS Specifické funkce:** Windows API (`windows.h`) pro skrytí konzolového okna a spouštění videí.

---

## 📂 Struktura projektu

* `main.cpp` - Vstupní bod programu, skrývá konzoli a spouští herní smyčku.
* `game.h` / `game.cpp` - Hlavní logika hry, správa stavů (`enum class Stav_Hra`), načítání textur, zpracování vstupu (klávesnice/myš) a vykreslování scén.
* `CMakeLists.txt` - Konfigurační soubor pro CMake nastavený pro linkování SFML 3.0.
* `Obrazky/` - Adresář obsahující herní grafiku, pozadí, tlačítka a snímky animovaného GIFu.
* `video_reakce/` & `video_poklad/` - Složky obsahující videozáznamy chemických reakcí a bonusových videí.
* `poklad.txt` - Textový soubor se seznamem odměn.

---

## 🚀 Jak projekt zprovoznit a spustit

### Požadavky
* Nainstalovaný **MSYS2** s prostředím **UCRT64**.
* Nainstalovaná knihovna **SFML 3.0** (standardní cesta v projektu je nastavena na `C:/msys64/ucrt64/lib/cmake/SFML`).
* **CMake** a kompilátor podporující C++17.
