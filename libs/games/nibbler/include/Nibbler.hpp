/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "evtVar.hpp"
#include "IGame.hpp"

#include <iostream>
#include <vector>
#include <string>

#define CELL_SIZE 14.0
#define GRID_SIZE 50

class Nibbler : public IGame {

    typedef struct {
        bool is_head = false;
        int x;
        int y;
    } nibbler_t;

    typedef enum {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT
    } direction;

    public:
        Nibbler();
        ~Nibbler();

        void InitMap();
        void InitNibbler();

        std::vector<std::string> GetMap();
        std::string GetScore();

        void Update(evtKey key);

        void ClearMap();
        void UpdateMap();

        void UpdateNibblerHeadPos(evtKey key);
        void UpdateNibblerBodyPos(std::vector<nibbler_t> old_nibbler);
        void UpdateNibblerDirection(evtKey key);
        void UpdateNibblerPos(evtKey key);

    protected:
    private:
        std::vector<std::string> _game_map;
        std::vector<nibbler_t> _nibbler;
        direction _direction = direction::RIGHT;
        std::string _score;

};

extern "C" Nibbler *getLibNibbler() {
    return (new Nibbler());
}

#endif /* !NIBBLER_HPP_ */