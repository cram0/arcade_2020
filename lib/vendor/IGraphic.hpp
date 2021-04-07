/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include <vector>
#include <string>

#include "evtVar.hpp"
#include "AClock.hpp"

typedef enum {
    SFML,
    SDL2,
    NCURSES
} graph_e;

class IGraphic {
    public:
        virtual ~IGraphic() = default;

        virtual void Initialize() = 0;
        virtual void DrawMap(std::vector<std::string> map) = 0;
        virtual void DrawScore(int score) = 0;
        virtual void DrawHighScores(std::vector<std::pair<std::string, std::string>> list) = 0;
        virtual void Display(AClock &delta) = 0;
        virtual void DisplayMenu() = 0;
        virtual void DisplayGameOver() = 0;
        virtual void Destroy() = 0;
        virtual void Clear() = 0;
        virtual void Close() = 0;
        virtual evtKey GetEventKey() = 0;
        virtual std::string GetUsername() = 0;
        virtual evtKey InputGameOverName() = 0;

    protected:
    private:
};

#endif /* !IGRAPHIC_HPP_ */
