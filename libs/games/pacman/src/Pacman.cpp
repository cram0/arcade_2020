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
    srand((unsigned int)time(NULL));
}

Pacman::~Pacman()
{

}

void Pacman::InitGhosts()
{
    _ghost_vector.emplace_back((ghost_t){11, 14, ghost_name::PINKY});
    // _ghost_vector.emplace_back((ghost_t){12, 14, ghost_name::CLYDE});
    // _ghost_vector.emplace_back((ghost_t){16, 14, ghost_name::INKY});
    // _ghost_vector.emplace_back((ghost_t){15, 17, ghost_name::BLINKY});
}

void Pacman::InitMap()
{
    std::ifstream file("libs/games/pacman/map");
    std::string row;
    if (file.is_open()) {
        while (getline(file, row)) {
            _game_map.emplace_back(row);
        }
        file.close();
    }
}

std::vector<std::string> Pacman::GetMap()
{
    std::vector<std::string> _temp_map = _game_map;
    _temp_map[_pacman.y][_pacman.x] = 'a';
    for (auto g : _ghost_vector) {
        if (g.name == ghost_name::PINKY)
            _temp_map[g.y][g.x] = 'p';
    }
    return (_temp_map);
}

void Pacman::UpdatePacmanPos()
{
    if (_pacman.dir == direction::DOWN)
        _pacman.y = (_game_map[_pacman.y + 1][_pacman.x] != '4') ? _pacman.y + 1 : _pacman.y;
    if (_pacman.dir == direction::UP)
        _pacman.y = (_game_map[_pacman.y - 1][_pacman.x] != '4') ? _pacman.y - 1 : _pacman.y;
    if (_pacman.dir == direction::LEFT) {
        if (_pacman.x - 1 >= 0) {
            _pacman.x = (_game_map[_pacman.y][_pacman.x - 1] != '4') ? _pacman.x - 1 : _pacman.x;
        }
    }
    if (_pacman.dir == direction::RIGHT) {
        if (_pacman.x + 1 <= GRID_SIZE_X) {
            _pacman.x = (_game_map[_pacman.y][_pacman.x + 1] != '4') ? _pacman.x + 1 : _pacman.x;
        }
    }
}

void Pacman::UpdatePacmanDirection(evtKey key)
{
    if (key == evtKey::NONE)
        return;
    _pacman.dir = (direction)key;
}

void Pacman::SetGhostsToScared()
{
    for (auto g : _ghost_vector) {
        g.is_scared = true;
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
        _score += 100;
        SetGhostsToScared();
    }
}

void Pacman::UpdateBlinkyPath()
{

}

void Pacman::UpdateInkyPath()
{

}

void Pacman::UpdatePinkyPath()
{
    int new_x = rand() % GRID_SIZE_X;
    int new_y = rand() % GRID_SIZE_Y;

    while (_game_map[new_y][new_x] != '0' && _game_map[new_y][new_x] != '5') {
        new_x = rand() % GRID_SIZE_X;
        new_y = rand() % GRID_SIZE_Y;
    }

    _ghost.goto_x = new_x;
    _ghost.goto_y = new_y;
}

void Pacman::UpdateClydePath()
{

}


void Pacman::UpdateGhostPath()
{
    switch (_ghost.name) {
        case ghost_name::PINKY:
            std::cout << "bite2" << std::endl;
            UpdatePinkyPath(_ghost);
            break;
        default:
            break;
    }
}

void Pacman::CheckGhostPath()
{
    for (auto g : _ghost_vector) {
        if (g.goto_x == -1 && g.goto_y == -1) {
            std::cout << "bite1" << std::endl;
            UpdateGhostPath();
        }
        if (g.goto_x == g.x && g.goto_y == g.y) {
            UpdateGhostPath();
        }
    }
}

bool Pacman::IsValid(int pos_x, int pos_y)
{
    if (pos_x < 0 || pos_y < 0 || pos_x > GRID_SIZE_X - 1 || pos_y > GRID_SIZE_Y)
        return (false);
    if (_game_map[pos_y][pos_x] == '0')
        return (false);
    if (_visited_map[pos_y][pos_x] == true)
        return (false);
    return (true);
}

void Pacman::DepthFirstSearch(int pos_x, int pos_y, int goto_x, int goto_y, ghost_t &g)
{
    // Top
    // Right
    // Down
    // Left

    _visited_map[pos_y][pos_x] = true;
    _mvt_stack.push_back(std::make_pair(pos_x, pos_y));

    if (pos_x == goto_x && pos_y == goto_y) {
        g.x = _mvt_stack.back().first;
        g.y = _mvt_stack.back().second;
    }

    if (IsValid(pos_x, pos_y - 1))
        DepthFirstSearch(pos_x, pos_y - 1, goto_x, goto_y, g);
    if (IsValid(pos_x + 1, pos_y))
        DepthFirstSearch(pos_x + 1, pos_y, goto_x, goto_y, g);
    if (IsValid(pos_x, pos_y + 1))
        DepthFirstSearch(pos_x, pos_y + 1, goto_x, goto_y, g);
    if (IsValid(pos_x - 1, pos_y))
        DepthFirstSearch(pos_x - 1, pos_y, goto_x, goto_y, g);

    _mvt_stack.pop_back();
}

void Pacman::UpdateGhostPos()
{
    for (auto g : _ghost_vector) {
        std::cout << "PINKY dans update ghost pos goto_x : " << g.goto_x << " goto_y : " << g.goto_y << std::endl;
        DepthFirstSearch(g.x, g.y, g.goto_x, g.goto_y, g);
    }
}

void Pacman::Update(evtKey key)
{
    // TODO : IMPLEMENTER CLASSES POUR LES FANTOMES;
    UpdatePacmanDirection(key);
    CheckPacmanCollision();
    UpdatePacmanPos();
    CheckGhostPath();
    UpdateGhostPos();
}

int Pacman::GetScore()
{
    return (_score);
}