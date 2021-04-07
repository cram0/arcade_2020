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
    InitGhosts();
}

Pacman::~Pacman()
{

}

void Pacman::InitGhosts()
{
    srand((unsigned int)time(NULL));
    _ghost_vector.clear();
    _ghost_vector.emplace_back(Ghost(Ghost::ghost_name::PINKY, 11, 13));
    _ghost_vector.emplace_back(Ghost(Ghost::ghost_name::INKY, 11, 15));
    _ghost_vector.emplace_back(Ghost(Ghost::ghost_name::CLYDE, 16, 13));
    _ghost_vector.emplace_back(Ghost(Ghost::ghost_name::BLINKY, 16, 15));
}

game_e Pacman::GetGameName()
{
    return (game_e::PACMAN);
}

void Pacman::InitMap()
{
    _game_map.clear();
    std::ifstream file("lib/games/pacman/map");
    std::string row;
    if (file.is_open()) {
        while (getline(file, row)) {
            _game_map.emplace_back(row);
        }
        file.close();
    }
}

bool Pacman::IsGameOver()
{
    return (_is_game_over);
}

AClock &Pacman::GetDeltaTime()
{
    return (_game_clock);
}

std::vector<std::string> Pacman::GetMap()
{
    std::vector<std::string> _temp_map = _game_map;
    for (auto &g : _ghost_vector) {
        // for (auto mvt : g.GetMvtStack()) {
        //     _temp_map[mvt.second][mvt.first] = '2';
        // }
        // _temp_map[g.GetGotoY()][g.GetGotoX()] = '3';
        if (g.GetName() == Ghost::ghost_name::PINKY) {
            if (g.IsScared())
                _temp_map[g.GetY()][g.GetX()] = 's';
            else
                _temp_map[g.GetY()][g.GetX()] = 'p';
        }
        if (g.GetName() == Ghost::ghost_name::INKY) {
            if (g.IsScared())
                _temp_map[g.GetY()][g.GetX()] = 's';
            else
                _temp_map[g.GetY()][g.GetX()] = 'i';
        }
        if (g.GetName() == Ghost::ghost_name::BLINKY) {
            if (g.IsScared())
                _temp_map[g.GetY()][g.GetX()] = 's';
            else
                _temp_map[g.GetY()][g.GetX()] = 'b';
        }
        if (g.GetName() == Ghost::ghost_name::CLYDE) {
            if (g.IsScared())
                _temp_map[g.GetY()][g.GetX()] = 's';
            else
                _temp_map[g.GetY()][g.GetX()] = 'c';
        }
    }
    _temp_map[_pacman.y][_pacman.x] = 'a';
    return (_temp_map);
}

void Pacman::UpdatePacmanPos()
{
    if (_pacman.dir == direction::DOWN)
        _pacman.y = (_game_map[_pacman.y + 1][_pacman.x] != '4' && _game_map[_pacman.y + 1][_pacman.x] != '-') ? _pacman.y + 1 : _pacman.y;
    if (_pacman.dir == direction::UP)
        _pacman.y = (_game_map[_pacman.y - 1][_pacman.x] != '4' && _game_map[_pacman.y - 1][_pacman.x] != '-') ? _pacman.y - 1 : _pacman.y;
    if (_pacman.dir == direction::LEFT) {
        if (_pacman.x - 1 >= 0) {
            _pacman.x = (_game_map[_pacman.y][_pacman.x - 1] != '4' && _game_map[_pacman.y][_pacman.x - 1] != '-') ? _pacman.x - 1 : _pacman.x;
        }
    }
    if (_pacman.dir == direction::RIGHT) {
        if (_pacman.x + 1 <= GRID_SIZE_X) {
            _pacman.x = (_game_map[_pacman.y][_pacman.x + 1] != '4' && _game_map[_pacman.y][_pacman.x + 1] != '-') ? _pacman.x + 1 : _pacman.x;
        }
    }
}

void Pacman::UpdatePacmanDirection(evtKey key)
{
    if (key == evtKey::NONE || key > 4)
        return;
    _pacman.dir = (direction)key;
}

void Pacman::SetGhostsToScared()
{
    for (auto &g : _ghost_vector) {
        g.SetScared(true);
    }
}

void Pacman::CheckPacmanCollision()
{
    if (_pacman.x == 0) {
        _pacman.x = 27;
    }
    if (_pacman.x == 28) {
        _pacman.x = 0;
    }
    if (_game_map[_pacman.y][_pacman.x] == '5') {
        _game_map[_pacman.y][_pacman.x] = '0';
        _score += 10;
    }
    if (_game_map[_pacman.y][_pacman.x] == 'u') {
        _game_map[_pacman.y][_pacman.x] = '0';
        _score += 50;
        SetGhostsToScared();
    }
    for (auto &g : _ghost_vector) {
        if (_pacman.x == g.GetX() && _pacman.y == g.GetY() && !g.IsScared()) {
            _is_game_over = true;
        }
        if (_pacman.x == g.GetX() && _pacman.y == g.GetY() && g.IsScared()) {
            _score += 200;
            g.ResetPosition();
            g.SetScared(false);
            g.SetMove(false);
        }
    }
}

void Pacman::UpdateChasePath(Ghost &g)
{
    g.SetGotoX(_pacman.x);
    g.SetGotoY(_pacman.y);
}

void Pacman::UpdateRandomPath(Ghost &g)
{
    int new_x = rand() % GRID_SIZE_X;
    int new_y = rand() % GRID_SIZE_Y;

    while (_game_map[new_y][new_x] != '0' && _game_map[new_y][new_x] != '5') {
        new_x = rand() % GRID_SIZE_X;
        new_y = rand() % GRID_SIZE_Y;
    }

    g.SetGotoX(new_x);
    g.SetGotoY(new_y);
}

void Pacman::ResetVisitedMap()
{
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        for (int x = 0; x < GRID_SIZE_X; x++) {
            _visited_map[y][x] = false;
        }
    }
}

void Pacman::UpdateGhostPath(Ghost &g)
{
    ResetVisitedMap();
    std::vector<std::pair<int, int>> temp;
    DepthFirstSearch(g.GetX(), g.GetY(), g, temp);
}

void Pacman::CheckGhostPath()
{
    for (auto &g : _ghost_vector) {
        if (g.GetMvtStack().empty()) {
            if (g.GetName() == Ghost::ghost_name::BLINKY)
                UpdateChasePath(g);
            if (g.GetName() == Ghost::ghost_name::INKY)
                UpdateChasePath(g);
            else
                UpdateRandomPath(g);
            UpdateGhostPath(g);
        }
    }
}

bool Pacman::IsValid(int pos_x, int pos_y)
{
    if (pos_x < 0 || pos_y < 0 || pos_x > GRID_SIZE_X - 1 || pos_y > GRID_SIZE_Y)
        return (false);
    if (_game_map[pos_y][pos_x] == '4')
        return (false);
    if (_visited_map[pos_y][pos_x] == true)
        return (false);
    return (true);
}

bool Pacman::DepthFirstSearch(int pos_x, int pos_y, Ghost &g, std::vector<std::pair<int, int>> &temp)
{
    _visited_map[pos_y][pos_x] = true;
    temp.emplace_back(std::make_pair(pos_x, pos_y));

    if (g.GetGotoX() == pos_x && g.GetGotoY() == pos_y) {
        return (true);
    }

    if (IsValid(pos_x, pos_y - 1))
        if (DepthFirstSearch(pos_x, pos_y - 1, g, temp)) {
            for (auto st : temp)
                g.AddMvt(st.first, st.second);
            temp.clear();
            return (true);
        }
    if (IsValid(pos_x + 1, pos_y))
        if (DepthFirstSearch(pos_x + 1, pos_y, g, temp)) {
            for (auto st : temp)
                g.AddMvt(st.first, st.second);
            temp.clear();
            return (true);
        }
    if (IsValid(pos_x, pos_y + 1))
        if (DepthFirstSearch(pos_x, pos_y + 1, g, temp)) {
            for (auto st : temp)
                g.AddMvt(st.first, st.second);
            temp.clear();
            return (true);
        }
    if (IsValid(pos_x - 1, pos_y))
        if (DepthFirstSearch(pos_x - 1, pos_y, g, temp)) {
            for (auto st : temp)
                g.AddMvt(st.first, st.second);
            temp.clear();
            return (true);
        }
    temp.pop_back();
    return (false);
}

void Pacman::UpdateGhostPos()
{
    for (auto &g : _ghost_vector) {
        if (g.CanMove()) {
            if (g.GetMvtStack().size() != 0) {
                g.SetX(g.GetMvtStack().front().first);
                g.SetY(g.GetMvtStack().front().second);
                g.RemoveMvt();
            }
        }
    }
}

void Pacman::UpdateGhostState()
{
    for (auto &g : _ghost_vector) {
        g.UpdateClocks();
    }
}

void Pacman::CheckIfWin()
{
    for (size_t y = 0; y < GRID_SIZE_Y; y++) {
        for (size_t x = 0; x < GRID_SIZE_X; x++) {
            if (_game_map[y][x] == '5') {
                return;
            }
        }
    }
    InitMap();
    InitGhosts();
}

void Pacman::Update(evtKey key)
{
    UpdatePacmanDirection(key);
    CheckPacmanCollision();
    UpdatePacmanPos();
    CheckGhostPath();
    UpdateGhostPos();
    UpdateGhostState();
    CheckIfWin();
}

int Pacman::GetScore()
{
    return (_score);
}