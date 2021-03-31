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

void Core::PrintUsage()
{
    std::cout << "Usage: ./arcade [lib_name.so]" << std::endl;
}

void Core::CheckIfLibIsGraphical(std::string libName)
{
    for (auto const &lm : GetDLLoader().GetGraphicLibsMap()) {
        if (libName.find(lm.first) != std::string::npos) {
            return;
        }
    }
    throw AError(std::cerr, "./arcade: file \"" + libName + "\" is not a proper graphical library file.");
}

void Core::CheckIfLibExists(std::string libName)
{
    std::ifstream file = std::ifstream(libName.c_str());
    if (!file.good())
        throw AError(std::cerr, "./arcade: file \"" + libName + "\" doesn't exist.");
}

int Core::CheckArgs(int argc, char *argv[])
{
    if (argc == 1){
        throw AError(std::cerr, "./arcade: missing graphic library name\nTry '-h' for more information.");
    }
    if (argc == 2) {
        std::string f_arg = std::string(argv[1]);
        if (f_arg.compare("-h") == 0) {
            PrintUsage();
            std::exit(0);
        }
        else {
            CheckIfLibExists(f_arg);
            CheckIfLibIsGraphical(f_arg);
        }
    }
    else {
        throw AError(std::cerr, "./arcade: too many arguments.\nTry '-h' for more information.");
    }
}

void Core::Run()
{
    while (IsRunning()) {
        GetGraphic()->Clear();
        if (GetCurrentGame() == NO_GAME) {
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
            GetGraphic()->DisplayMenu();
        }
        else if (GetCurrentGame() == GAME_OVER) {
            std::string name = GetGraphic()->GetUsername();
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

    GetDLLoader().CloseHandles();
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
    if (evt == evtKey::QUIT_GAME) {
        GetGraphic()->Close();
        _running = false;
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