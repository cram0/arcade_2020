/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include <map>

#include "IGraphic.hpp"
#include "IGame.hpp"

class DLLoader {
    public:
        DLLoader();
        ~DLLoader();

        IGraphic *GetGraphicLibrary(std::string const &path);
        IGame *GetGameLibrary(std::string const &path);

        IGame *SwitchGame(game_e current_game);

    protected:
    private:
        std::map<std::string, std::string> _graphic_libs_map;
        std::map<std::string, std::string> _game_libs_map;
        void *_handle_game;
        void *_handle_graphic;
};

#endif /* !DLLOADER_HPP_ */
