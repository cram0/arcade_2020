/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "evtVar.hpp"
#include "IGame.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <stack>

#define GRID_SIZE_X 28
#define GRID_SIZE_Y 31

class Pacman : public IGame {

    typedef enum {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT
    } direction;

    typedef enum {
        INKY,
        BLINKY,
        PINKY,
        CLYDE
    } ghost_name;

    typedef struct {
        int x = 15;
        int y = 17;
        direction dir = direction::RIGHT;
    } pacman_t;

    typedef struct {
        int x;
        int y;
        ghost_name name;
        int goto_x = -1;
        int goto_y = -1;
        bool is_scared = false;
        bool can_move = false;
        direction dir = direction::RIGHT;
    } ghost_t;

    public:
        Pacman();
        ~Pacman();

        void InitMap();
        void InitGhosts();

        std::vector<std::string> GetMap();
        int GetScore();

        void SetGhostsToScared();

        bool IsValid(int pos_x, int pos_y);
        void DepthFirstSearch(int pos_x, int pos_y, int goto_x, int goto_y, ghost_t &g);

        void UpdateBlinkyPath();
        void UpdateInkyPath();
        void UpdatePinkyPath();
        void UpdateClydePath();
        void UpdateGhostPath();
        void UpdateGhostPos();
        void CheckGhostPath();
        void CheckPacmanCollision();
        void UpdatePacmanPos();
        void UpdatePacmanDirection(evtKey key);
        void Update(evtKey key);

    protected:
    private:
        std::vector<std::string> _game_map;
        std::vector<ghost_t> _ghost_vector;
        std::vector<std::pair<int, int>> _mvt_stack;
        bool _visited_map[GRID_SIZE_Y][GRID_SIZE_X];
        int _score = 0;

        pacman_t _pacman;
};

extern "C" Pacman *getLibPacman() {
    return (new Pacman());
}

#endif /* !PACMAN_HPP_ */
