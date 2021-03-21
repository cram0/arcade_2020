/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman()
{
    InitMap();
}

Pacman::~Pacman()
{

}

void Pacman::InitMap()
{
    std::string row;
    for (int i = 0; i < GRID_SIZE_X; i++) {
        row.append("0");
    }

    for (int i = 0; i < GRID_SIZE_Y; i++) {
        _game_map.emplace_back(row);
    }
}

std::vector<std::string> Pacman::GetMap()
{

}

void Pacman::Update(evtKey key)
{

}

int Pacman::GetScore()
{
    return (_score);
}