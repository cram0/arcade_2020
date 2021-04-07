/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibNcurses
*/

#ifndef LIBNCURSES_HPP_
#define LIBNCURSES_HPP_

#include <ncurses.h>
#include <iostream>
#include <ctime>
#include <string>

#include "IGraphic.hpp"

#include "evtVar.hpp"

#define GRID_SIZE_X 28
#define GRID_SIZE_Y 31

#define GREEN_RECT 1
#define WHITE_RECT 2
#define RED_RECT 3
#define BLACK_RECT 4
#define PACMAN 5
#define BLUE_RECT 6
#define INKY 7
#define BLINKY 8
#define CLYDE 9
#define PINKY 10
#define BARRIER 11
#define PACGUM 12
#define SCARED 13

class LibNcurses : public IGraphic {

    typedef enum {
        MENU,
        GAME_OVER,
        GAME
    } scene_e;

    public:
        LibNcurses();
        ~LibNcurses();

        void Initialize();
        void InitColors();
        void InitMenu();
        void InitGameOver();

        void DrawBox();
        void DrawId(char const id,  int y, int x);
        void DrawMap(std::vector<std::string> map);
        void DrawScore(int score);
        void DrawHighScores(std::vector<std::pair<std::string, std::string>> list);

        void Display(AClock &delta);
        void DisplayMenu();
        void DisplayGameOver();
        void Destroy();
        void Clear();
        void Close();
        evtKey InputGameOverName();

        evtKey GetEventKey();
        std::string GetUsername();

    protected:
    private:
        WINDOW *_game_window;
        scene_e _current_scene = MENU;

        std::string _menu_prompt;
        std::string _menu_prompt_games;
        std::string _menu_prompt_keys;

        std::string _game_over_prompt;
        std::string _game_over_score_label;
        std::string _game_over_score_value;

        std::string _player_name;


};

extern "C" LibNcurses *getLibNcurses() {
    return (new LibNcurses());
}

#endif /* !LIBNCURSES_HPP_ */
