/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
{
    InitMap();
    InitNibbler();
    InitApple();
}

Nibbler::~Nibbler()
{

}

void Nibbler::InitNibbler()
{
    _nibbler.emplace_back((nibbler_t){true, 10, 15});
    _nibbler.emplace_back((nibbler_t){false, 9, 15});
    _nibbler.emplace_back((nibbler_t){false, 8, 15});
    _nibbler.emplace_back((nibbler_t){false, 7, 15});
}

void Nibbler::InitMap()
{
    std::string row;
    for (int i = 0; i < GRID_SIZE_X; i++) {
        row.append("0");
    }

    for (int i = 0; i < GRID_SIZE_Y; i++) {
        _game_map.emplace_back(row);
    }
}

void Nibbler::InitApple()
{
    srand((unsigned int)time(NULL));
    int pos_x, pos_y;

    do {
        pos_x = rand() % GRID_SIZE_X;
    } while (pos_x >= 7 && pos_x <= 10);

    do {
        pos_y = rand() % GRID_SIZE_Y;
    } while (pos_y == 15);

    _apple.x = pos_x;
    _apple.y = pos_y;
}

bool Nibbler::IsGameOver()
{
    return (_is_game_over);
}

void Nibbler::RandomizeApplePos()
{
    _apple.x = rand() % GRID_SIZE_X;
    _apple.y = rand() % GRID_SIZE_Y;

    for (size_t i = 0; i < _nibbler.size(); i++) {
        if (_apple.x == _nibbler[i].x && _apple.y == _nibbler[i].y) {
            _apple.x = rand() % GRID_SIZE_X;
            _apple.y = rand() % GRID_SIZE_Y;
            i = 0;
        }
    }
}

void Nibbler::UpdateNibblerDirection(evtKey key)
{
    if (key == evtKey::NONE || key > 4)
        return;
    if (_direction == direction::RIGHT && key != evtKey::LEFT)
        _direction = (direction)key;
    if (_direction == direction::UP && key != evtKey::DOWN)
        _direction = (direction)key;
    if (_direction == direction::DOWN && key != evtKey::UP)
        _direction = (direction)key;
    if (_direction == direction::LEFT && key != evtKey::RIGHT)
        _direction = (direction)key;
}

void Nibbler::UpdateNibblerHeadPos(evtKey key)
{
    if (_direction == direction::UP){
        if (_nibbler[0].y > 0)
            _nibbler[0].y -= 1;
        else
            _is_game_over = true;
    }
    if (_direction == direction::DOWN) {
        if (_nibbler[0].y < GRID_SIZE_Y - 1)
            _nibbler[0].y += 1;
        else
            _is_game_over = true;
    }
    if (_direction == direction::LEFT) {
        if (_nibbler[0].x > 0)
            _nibbler[0].x -= 1;
        else
            _is_game_over = true;
    }
    if (_direction == direction::RIGHT) {
        if (_nibbler[0].x < GRID_SIZE_X - 1)
            _nibbler[0].x += 1;
        else
            _is_game_over = true;
    }
}

void Nibbler::UpdateNibblerBodyPos(std::vector<nibbler_t> old_nibbler)
{
    if (_is_apple_eaten) {
        _nibbler.emplace_back((nibbler_t){false, 0, 0});
        _is_apple_eaten = false;
    }
    for (size_t i = 0; i < _nibbler.size(); i++) {
        if (!_nibbler[i].is_head) {
            _nibbler[i].x = old_nibbler[i - 1].x;
            _nibbler[i].y = old_nibbler[i - 1].y;
        }
    }

}

void Nibbler::CheckHeadCollision(std::vector<nibbler_t> old_nibbler)
{
    for (auto n : old_nibbler) {
        if (_nibbler[0].x == n.x && _nibbler[0].y == n.y) {
            _is_game_over = true;
        }
    }
}

void Nibbler::CheckAppleCollision()
{
    if (_nibbler[0].x == _apple.x && _nibbler[0].y == _apple.y) {
        _is_apple_eaten = true;
        _score += 10;
        RandomizeApplePos();
    }
}

void Nibbler::UpdateNibblerPos(evtKey key)
{
    CheckAppleCollision();
    std::vector<nibbler_t> old_nibbler = _nibbler;
    UpdateNibblerHeadPos(key);
    CheckHeadCollision(old_nibbler);
    UpdateNibblerBodyPos(old_nibbler);
}

void Nibbler::ClearMap()
{
    for (size_t y = 0; y < GRID_SIZE_Y; y++) {
        for (size_t x = 0; x < GRID_SIZE_X; x++) {
            _game_map[y][x] = '0';
        }
    }
}

void Nibbler::UpdateMap()
{
    _game_map[_apple.y][_apple.x] = '1';

    for (auto n : _nibbler) {
        if (n.is_head)
            _game_map[n.y][n.x] = '3';
        else
            _game_map[n.y][n.x] = '2';
    }
}

void Nibbler::Update(evtKey key)
{
    ClearMap();
    UpdateNibblerDirection(key);
    UpdateNibblerPos(key);
    UpdateMap();
}

std::vector<std::string> Nibbler::GetMap()
{
    return (_game_map);
}

int Nibbler::GetScore()
{
    return (_score);
}

game_e Nibbler::GetGameName()
{
    return (game_e::NIBBLER);
}