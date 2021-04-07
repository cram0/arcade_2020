/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** AClock
*/

#include "AClock.hpp"

AClock::AClock()
{
    _clock = clock();
}

AClock::~AClock()
{

}

double AClock::GetElapsedTime()
{
    return ((double)(clock() - _clock) / CLOCKS_PER_SEC);
}

void AClock::Restart()
{
    _clock = clock();
}
