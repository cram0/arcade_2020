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

#include "IGraphic.hpp"

#include "evtVar.hpp"


class LibNcurses : public IGraphic {
    public:
        LibNcurses();
        ~LibNcurses();

        void Initialize();
        void DrawMap(std::vector<std::string> map);
        void DrawScore(int score);
        void Display();
        void DisplayMenu();
        void DisplayGameOver();
        void Destroy();
        void Clear();
        void Close();
        evtKey GetEventKey();

    protected:
    private:
};

extern "C" LibNcurses *getLibNcurses() {
    return (new LibNcurses());
}

#endif /* !LIBNCURSES_HPP_ */
