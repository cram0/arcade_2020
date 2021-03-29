/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Core
*/

#include "Core.hpp"

// Je lègue ce projet à Eloise si je meurs entre temps d'un grain de poivre
// mal ingéré

Core::Core()
{

}

Core::~Core()
{

}

void Core::Run()
{
    IGraphic *graph = GetDLLoader().GetGraphicLibrary("lib/arcade_sdl2.so");
    SetGraphic(graph);

    while (IsRunning()) {
        GetGraphic()->Clear();
        if (GetCurrentGame() == NO_GAME) {
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
            GetGraphic()->DisplayMenu();
        }
        else if (GetCurrentGame() == GAME_OVER) {
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
            GetGraphic()->DisplayGameOver();
        }
        else {
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
            GetGame()->Update(key);
            CheckIfGameOver(GetGame()->IsGameOver());
            GetGraphic()->DrawMap(GetGame()->GetMap());
            GetGraphic()->DrawScore(GetGame()->GetScore());
            GetGraphic()->Display();
        }
    }
}

void Core::CheckIfGameOver(bool state)
{
    if (state)
        _current_game = GAME_OVER;
}

void Core::ChangeCurrentGraphic(evtKey evt)
{
    int tmp = (int)_current_graphic;
    if (evt == evtKey::PREV_GRAPH) {
        tmp -= 1;
        if (tmp < 0)
            _current_graphic = (graph_e)2;
        else
            _current_graphic = (graph_e)tmp;
    }
    if (evt == evtKey::NEXT_GRAPH) {
        tmp += 1;
        if (tmp > 2)
            _current_graphic = (graph_e)0;
        else
            _current_graphic = (graph_e)tmp;
    }
}

void Core::ChangeCurrentGame(evtKey evt)
{
    if (_current_game == NO_GAME) {
        if (evt == evtKey::GO_MENU)
            return;
        if (evt == evtKey::PREV_GAME) {
            _game_before_pause = _current_game;
            _current_game = game_e::NIBBLER;
        }
        if (evt == evtKey::NEXT_GAME) {
            _game_before_pause = _current_game;
            _current_game = game_e::PACMAN;
        }
    }
    if (evt == evtKey::PREV_GAME) {
        _current_game = game_e::NIBBLER;
    }
    if (evt == evtKey::NEXT_GAME) {
        _current_game = game_e::PACMAN;
    }
    if (evt == evtKey::GO_MENU) {
        _game_before_pause = _current_game;
        _current_game = game_e::NO_GAME;
    }
    if (evt == evtKey::CONFIRM_NAME && _current_game == game_e::GAME_OVER) {
        _game_before_pause = _current_game;
        _current_game = game_e::NO_GAME;
    }
}

void Core::ReadCoreEvent(evtKey evt)
{
    if (_current_game != game_e::GAME_OVER) {
        if (evt == evtKey::GO_MENU) {
            ChangeCurrentGame(evt);
        }
        if (evt == evtKey::RESET_GAME && _current_game != game_e::NO_GAME) {
            SetGame(GetDLLoader().SwitchGame(evt, _current_game));
        }
        if (evt == evtKey::NEXT_GAME) {
            if (_game_before_pause == game_e::PACMAN) {
                ChangeCurrentGame(evt);
            }
            else {
                ChangeCurrentGame(evt);
                SetGame(GetDLLoader().SwitchGame(evt, _current_game));
            }
        }
        if (evt == evtKey::PREV_GAME) {
            if (_game_before_pause == game_e::NIBBLER) {
                ChangeCurrentGame(evt);
            }
            else {
                ChangeCurrentGame(evt);
                SetGame(GetDLLoader().SwitchGame(evt, _current_game));
            }
        }
        if (evt == evtKey::PREV_GRAPH) {
            ChangeCurrentGraphic(evt);
            GetGraphic()->Close();
            SetGraphic(GetDLLoader().SwitchGraphic(evt, _current_graphic));
        }
        if (evt == evtKey::NEXT_GRAPH) {
            ChangeCurrentGraphic(evt);
            GetGraphic()->Close();
            SetGraphic(GetDLLoader().SwitchGraphic(evt, _current_graphic));
        }
    }
    if (evt == evtKey::CONFIRM_NAME) {
        if (_current_game == game_e::GAME_OVER) {
            ChangeCurrentGame(evt);
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