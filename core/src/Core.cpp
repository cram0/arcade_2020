/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Core
*/

#include "Core.hpp"

Core::Core()
{

}

Core::~Core()
{

}

void Core::Run()
{
    IGraphic *graph = GetDLLoader().GetGraphicLibrary("libs/graphics/sfml/arcade_sfml.so");
    IGame *game = GetDLLoader().GetGameLibrary("libs/games/nibbler/arcade_nibbler.so");
    SetGraphic(graph);
    SetGame(game);

    while (IsRunning()) {
        GetGraphic()->Clear();
        evtKey key = GetGraphic()->GetEventKey();
        GetGame()->Update(key);
        GetGraphic()->DrawMap(GetGame()->GetMap());
        GetGraphic()->DrawScore(GetGame()->GetScore());
        GetGraphic()->Display();
    }
}

bool Core::IsRunning()
{
    return (_running);
}

IGame *Core::GetGame()
{
    return (_game);
}

IGraphic *Core::GetGraphic()
{
    return (_graphlib);
}

DLLoader Core::GetDLLoader()
{
    return (_dlloader);
}

void Core::SetGame(IGame *game)
{
    _game = game;
}

void Core::SetGraphic(IGraphic *graphlib)
{
    _graphlib = graphlib;
}