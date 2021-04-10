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
#include <random>
#include <time.h>

#define GRID_SIZE_X 28
#define GRID_SIZE_Y 31

class Nibbler : public IGame {

    typedef struct {
        bool is_head = false;
        int x = 0;
        int y = 0;
    } nibbler_t;

    typedef struct {
        int x;
        int y;
    } apple_t;

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
        void InitApple();

        std::vector<std::string> GetMap() const;
        int GetScore() const;
        game_e GetGameName() const;
        AClock &GetDeltaTime();

        bool IsGameOver() const;

        void Update(evtKey key);

        void ClearMap();
        void UpdateMap();

        void RandomizeApplePos();

        void CheckAppleCollision();
        void CheckHeadCollision(std::vector<nibbler_t> old_nibbler);
        void UpdateNibblerHeadPos(evtKey key);
        void UpdateNibblerBodyPos(std::vector<nibbler_t> old_nibbler);
        void UpdateNibblerDirection(evtKey key);
        void UpdateNibblerPos(evtKey key);

    protected:
    private:
        std::vector<std::string> _game_map;
        std::vector<nibbler_t> _nibbler;
        bool _is_apple_eaten = false;
        apple_t _apple;
        direction _direction = direction::RIGHT;
        int _score = 0;
        bool _is_game_over = false;

        AClock _game_clock;

};

extern "C" Nibbler *getLibNibbler() {
    return (new Nibbler());
}

#endif /* !NIBBLER_HPP_ */
