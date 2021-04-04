/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Ghost
*/

#include "Ghost.hpp"

Ghost::Ghost(Ghost::ghost_name name, int x, int y)
{
    _name = name;
    _x = x;
    _y = y;
    _x_spawn = x;
    _y_spawn = y;
    _can_move_clock = clock();
    _scared_clock = clock();
}

Ghost::~Ghost()
{

}

int Ghost::GetX()
{
    return (_x);
}

int Ghost::GetY()
{
    return (_y);
}

int Ghost::GetGotoX()
{
    return (_goto_x);
}

int Ghost::GetGotoY()
{
    return (_goto_y);
}

bool Ghost::IsScared()
{
    return (_is_scared);
}

bool Ghost::CanMove()
{
    return (_can_move);
}

Ghost::ghost_name Ghost::GetName()
{
    return (_name);
}

std::vector<std::pair<int, int>> Ghost::GetMvtStack()
{
    return (_mvt_stack);
}

clock_t Ghost::GetMoveClock()
{
    return (_can_move_clock);
}

clock_t Ghost::GetScaredClock()
{
    return (_scared_clock);
}

void Ghost::UpdateScaredClock()
{
    if (!IsScared()) {
        _scared_clock = clock();
    }
    if (IsScared()) {
        clock_t end = clock();
        if ((double)(end - _scared_clock) / CLOCKS_PER_SEC * 100 >= 10.0) {
            _scared_clock = clock();
            SetScared(false);
        }
    }
}

void Ghost::UpdateMoveClock()
{
    if (CanMove()) {
        _can_move_clock = clock();
    }
    if (!CanMove()) {
        clock_t end = clock();
        if ((double)(end - _can_move_clock) / CLOCKS_PER_SEC * 100 >= 10.0) {
            _can_move_clock = clock();
            SetMove(true);
        }
    }
}

void Ghost::UpdateClocks()
{
    UpdateScaredClock();
    UpdateMoveClock();
}

void Ghost::ResetPosition()
{
    _mvt_stack.clear();
    _x = _x_spawn;
    _y = _y_spawn;
}

void Ghost::SetX(int x)
{
    _x = x;
}

void Ghost::SetY(int y)
{
    _y = y;
}

void Ghost::SetGotoX(int x)
{
    _goto_x = x;
}

void Ghost::SetGotoY(int y)
{
    _goto_y = y;
}

void Ghost::SetScared(bool state)
{
    _is_scared = state;
}

void Ghost::SetMove(bool state)
{
    _can_move = state;
}

void Ghost::SetName(ghost_name name)
{
    _name = name;
}

void Ghost::AddMvt(int x, int y)
{
    _mvt_stack.emplace_back(std::make_pair(x, y));
}

void Ghost::RemoveMvt()
{
    _mvt_stack.erase(_mvt_stack.begin());
}