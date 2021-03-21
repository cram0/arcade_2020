/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGame.hpp"

#include "evtVar.hpp"

#include <vector>
#include <string>

#define GRID_SIZE_X 28
#define GRID_SIZE_Y 31

class Pacman : public IGame {
    public:
        Pacman();
        ~Pacman();

        void InitMap();

        std::vector<std::string> GetMap();
        int GetScore();
        void Update(evtKey key);

    protected:
    private:
        std::vector<std::string> _game_map;
        int _score = 0;
};

#endif /* !PACMAN_HPP_ */
