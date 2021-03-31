/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibSDL2
*/

#ifndef LIBSDL2_HPP_
#define LIBSDL2_HPP_

#include <iostream>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <map>

#include "IGraphic.hpp"
#include "evtVar.hpp"

#define CELL_SIZE 22.0
#define GRID_SIZE_X 28
#define GRID_SIZE_Y 31
#define WINDOW_WIDTH 646
#define WINDOW_HEIGHT 800

class LibSDL2 : public IGraphic {
    public:
        LibSDL2();
        ~LibSDL2();

        void Initialize();
        void InitEverything();
        void InitRenderer();
        void InitFont();
        void InitGameText();
        void InitMenuText();
        void InitGameOverText();

        void SDL_RenderFillCircle(int x, int y, int radius);
        void DrawRectangle(char id, SDL_Point r_pos);
        void DrawCircleFromPos(int x0, int y0, int radiusX, int radiusY);
        void DrawCircle(char id, SDL_Point r_pos);
        void DrawShapeFromID(char id, SDL_Point r_pos);

        void DrawMapBackground();
        void DrawMap(std::vector<std::string> map);

        void InputGameOverName();
        void UpdateScoreValue(int score);
        void DrawText(const char *text, SDL_Rect rect);
        void DrawScore(int score);
        void Display();
        void DisplayMenu();
        void DisplayGameOver();
        void Destroy();
        void Clear();
        void Close();

        evtKey GetEventKey();
        std::string GetUsername();

    protected:
    private:
        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;
        SDL_Event _event;

        TTF_Font *_font = nullptr;
        std::vector<std::pair<std::string, SDL_Rect>> _score_text_list;
        std::vector<std::pair<std::string, SDL_Rect>> _menu_text_list;
        std::vector<std::pair<std::string, SDL_Rect>> _game_over_text_list;
        std::string _game_over_name_input;

        clock_t _start_clock;

};

extern "C" LibSDL2 *getLibSDL2() {
    return (new LibSDL2());
}

#endif /* !LIBSDL2_HPP_ */
