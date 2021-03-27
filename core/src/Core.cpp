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
    SetGraphic(graph);

    while (IsRunning()) {
        GetGraphic()->Clear();
        if (GetCurrentGame() == NO_GAME) {
            GetGraphic()->DisplayMenu();
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
        }
        else {
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
            GetGame()->Update(key);
            GetGraphic()->DrawMap(GetGame()->GetMap());
            GetGraphic()->DrawScore(GetGame()->GetScore());
            GetGraphic()->Display();
        }
    }
}

void Core::ChangeCurrentGame(evtKey evt)
{
    if (_current_game == NO_GAME) {
        if (evt == evtKey::GO_MENU)
            return;
        if (evt == evtKey::NEXT_GAME)
            _current_game = game_e::NIBBLER;
        if (evt == evtKey::PREV_GAME)
            _current_game = game_e::PACMAN;
    }
    if (evt == evtKey::PREV_GAME)
        _current_game = game_e::NIBBLER;
    if (evt == evtKey::NEXT_GAME)
        _current_game = game_e::PACMAN;
    if (evt == evtKey::GO_MENU) {
        _is_pause = true;
        _current_game = game_e::NO_GAME;
    }
}

void Core::ReadCoreEvent(evtKey evt)
{
    if (evt == evtKey::GO_MENU) {
        ChangeCurrentGame(evt);
    }
    if (evt == evtKey::RESET_GAME) {
        SetGame(GetDLLoader().SwitchGame(evt, _current_game));
    }
    if (evt == evtKey::NEXT_GAME) {
        if (_is_pause == true) {
            ChangeCurrentGame(evt);
            _is_pause = false;
        }
        else {
            ChangeCurrentGame(evt);
            SetGame(GetDLLoader().SwitchGame(evt, _current_game));
        }
    }
    if (evt == evtKey::PREV_GAME) {
        if (_is_pause == true) {
            ChangeCurrentGame(evt);
            _is_pause = false;
        }
        else {
            ChangeCurrentGame(evt);
            SetGame(GetDLLoader().SwitchGame(evt, _current_game));
        }
    }
}

game_e Core::GetCurrentGame()
{
    return (_current_game);
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