/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <fstream>

#include "IGraphic.hpp"
#include "IGame.hpp"
#include "DLLoader.hpp"
#include "AError.hpp"

class Core {

    public:
        Core();
        ~Core();

        int CheckArgs(int argc, char *argv[]);
        void Run();
        bool IsRunning();
        void ReadCoreEvent(evtKey evt);
        
        void CheckIfLibIsGraphical(std::string libName);
        void CheckIfLibExists(std::string libName);
        void CheckIfGameOver(bool state);
        void PrintUsage();

        IGame *GetGame();
        IGraphic *GetGraphic();
        DLLoader GetDLLoader();
        game_e GetCurrentGame();

        void SetGame(IGame *game);
        void SetGraphic(IGraphic *graphlib);
        void ChangeCurrentGame(evtKey evt);
        void ChangeCurrentGraphic(evtKey evt);

    protected:
    private:
        bool _running = 1;
        game_e _current_game = NO_GAME;
        graph_e _current_graphic = SFML;
        game_e _game_before_pause = NO_GAME;

        IGame *_game;
        IGraphic *_graphlib;
        DLLoader _dlloader;
};

#endif /* !CORE_HPP_ */
