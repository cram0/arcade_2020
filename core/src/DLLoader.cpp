/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

#include <iostream>

DLLoader::DLLoader()
{
    _graphic_libs_map["arcade_sfml.so"] = "getLibSFML";
    _graphic_libs_map["arcade_sdl2.so"] = "getLibSDL";
    _graphic_libs_map["arcade_ncurses.so"] = "getLibNcurses";

    _game_libs_map["arcade_nibbler.so"] = "getLibNibbler";
    _game_libs_map["arcade_pacman.so"] = "getLibPacman";
}

DLLoader::~DLLoader()
{

}

IGame *DLLoader::SwitchGame(evtKey evt, game_e game_name)
{
    if (evt == evtKey::NEXT_GAME)
        return (GetGameLibrary("lib/arcade_pacman.so"));
    if (evt == evtKey::PREV_GAME)
        return (GetGameLibrary("lib/arcade_nibbler.so"));
    if (evt == evtKey::RESET_GAME) {
        if (game_name == game_e::NIBBLER)
            return (GetGameLibrary("lib/arcade_nibbler.so"));
        if (game_name == game_e::PACMAN)
            return (GetGameLibrary("lib/arcade_pacman.so"));
    }
}

IGame *DLLoader::GetGameLibrary(std::string const &path)
{
    char *error;
    IGame *(*tmp)();

    _handle_game = dlopen(path.c_str(), RTLD_LAZY);

    if (!_handle_game) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    for (const auto &p : _game_libs_map) {
        if (path.find(p.first) != std::string::npos) {
            *(void **)(&tmp) = dlsym(_handle_game, p.second.c_str());

            if ((error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", error);
                exit(EXIT_FAILURE);
            }
        }
    }
    return ((* tmp)());
}

IGraphic *DLLoader::GetGraphicLibrary(std::string const &path)
{
    char *error;
    IGraphic *(*tmp)();
    _handle_graphic = dlopen(path.c_str(), RTLD_LAZY);

    if (!_handle_graphic) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    for (const auto &p : _graphic_libs_map) {
        if (path.find(p.first) != std::string::npos) {
            *(void **)(&tmp) = dlsym(_handle_graphic, p.second.c_str());

            if ((error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", error);
                exit(EXIT_FAILURE);
            }
        }
    }
    return ((* tmp)());
}