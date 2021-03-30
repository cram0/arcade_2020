/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** main
*/

#include "Core.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    try {
        Core core;
        core.CheckArgs(argc, argv);
        core.SetGraphic(core.GetDLLoader().GetGraphicLibrary(std::string(argv[1])));
        core.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::exit(84);
    }

    return (0);
}