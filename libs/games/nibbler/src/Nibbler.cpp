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
}

Nibbler::~Nibbler()
{

}

void Nibbler::InitNibbler()
{
    _nibbler.emplace_back((nibbler_t){true, 25, 25});
    _nibbler.emplace_back((nibbler_t){false, 24, 25});
    _nibbler.emplace_back((nibbler_t){false, 23, 25});
    _nibbler.emplace_back((nibbler_t){false, 22, 25});
}

void Nibbler::InitMap()
{
    std::string row;
    for (int i = 0; i < GRID_SIZE; i++) {
        row.append("0");
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        _game_map.emplace_back(row);
    }

    for (auto const &s : _game_map) {
        std::cout << s << std::endl;
    }
}

void Nibbler::UpdateNibblerDirection(evtKey key)
{
    if (key == evtKey::NONE)
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
        _nibbler[0].y -= 1;
    }
    if (_direction == direction::DOWN) {
        _nibbler[0].y += 1;
    }
    if (_direction == direction::LEFT) {
        _nibbler[0].x -= 1;
    }
    if (_direction == direction::RIGHT) {
        _nibbler[0].x += 1;
    }
}

void Nibbler::UpdateNibblerBodyPos(std::vector<nibbler_t> old_nibbler)
{

    for (size_t i = 0; i < _nibbler.size(); i++) {
        if (!_nibbler[i].is_head) {
            _nibbler[i].x = old_nibbler[i - 1].x;
            _nibbler[i].y = old_nibbler[i - 1].y;
        }
    }
}

void Nibbler::UpdateNibblerPos(evtKey key)
{
    std::vector<nibbler_t> old_nibbler = _nibbler;
    UpdateNibblerHeadPos(key);
    UpdateNibblerBodyPos(old_nibbler);
}

void Nibbler::ClearMap()
{
    for (size_t y = 0; y < GRID_SIZE; y++) {
        for (size_t x = 0; x < GRID_SIZE; x++) {
            _game_map[y][x] = '0';
        }
    }
}

void Nibbler::UpdateMap()
{
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

std::string Nibbler::GetScore()
{
    return (_score);
}