/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibNcurses
*/

#include "LibNcurses.hpp"

LibNcurses::LibNcurses()
{
    Initialize();
}

LibNcurses::~LibNcurses()
{

}

void LibNcurses::Initialize()
{
    initscr();
}

void LibNcurses::DrawMap(std::vector<std::string> map)
{

}

void LibNcurses::DrawScore(int score)
{

}

void LibNcurses::Display()
{

}

void LibNcurses::DisplayMenu()
{

}

void LibNcurses::DisplayGameOver()
{

}

void LibNcurses::Destroy()
{

}

void LibNcurses::Clear()
{

}

void LibNcurses::Close()
{

}

evtKey GetEventKey()
{
    return evtKey::NONE;
}