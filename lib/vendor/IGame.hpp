/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <string>
#include <vector>

#include "evtVar.hpp"
#include "AClock.hpp"

typedef enum {
    NO_GAME,
    NIBBLER,
    PACMAN,
    GAME_OVER,
} game_e;

class IGame {
    public:
        virtual ~IGame() = default;

        virtual std::vector<std::string> GetMap() = 0;
        virtual int GetScore() = 0;
        virtual bool IsGameOver() = 0;
        virtual void Update(evtKey key) = 0;
        virtual game_e GetGameName() = 0;
        virtual AClock &GetDeltaTime() = 0;

    protected:
    private:

};

#endif /* !IGAME_HPP_ */
