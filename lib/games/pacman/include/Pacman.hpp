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
#include "Ghost.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
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

    typedef struct {
        int x = 15;
        int y = 17;
        direction dir = direction::RIGHT;
    } pacman_t;

    public:
        Pacman();
        ~Pacman();

        void InitMap();
        void InitGhosts();
        bool IsGameOver() const;
        void CheckIfWin();

        std::vector<std::string> GetMap() const;
        int GetScore() const;
        game_e GetGameName() const;
        AClock &GetDeltaTime();

        void SetGhostsToScared();

        bool IsValid(int pos_x, int pos_y);
        bool DepthFirstSearch(int pos_x, int pos_y, Ghost &g, std::vector<std::pair<int, int>> &temp);

        void ResetVisitedMap();

        void UpdateRandomPath(Ghost &g);
        void UpdateChasePath(Ghost &g);

        void UpdateGhostState();
        void UpdateGhostPath(Ghost &g);
        void UpdateGhostPos();
        void CheckGhostPath();
        void CheckPacmanCollision();
        void UpdatePacmanPos();
        void UpdatePacmanDirection(evtKey key);
        void Update(evtKey key);

    protected:
    private:
        std::vector<std::string> _game_map;
        std::vector<Ghost> _ghost_vector;
        bool _visited_map[GRID_SIZE_Y][GRID_SIZE_X];
        int _score = 0;
        bool _is_game_over = false;

        pacman_t _pacman;

        AClock _game_clock;

};

extern "C" Pacman *getLibPacman() {
    return (new Pacman());
}

#endif /* !PACMAN_HPP_ */
