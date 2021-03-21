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

class IGame {
    public:
        virtual ~IGame() = default;

        virtual std::vector<std::string> GetMap() = 0;
        virtual int GetScore() = 0;
        virtual void Update(evtKey key) = 0;

    protected:
    private:

};

#endif /* !IGAME_HPP_ */
