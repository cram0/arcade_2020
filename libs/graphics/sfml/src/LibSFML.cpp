/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibSFML
*/

#include "LibSFML.hpp"

LibSFML::LibSFML()
{
    _window.create((sf::VideoMode){800, 800, 32}, "Title", sf::Style::Close);
    _window.setFramerateLimit(60);
    _clock.restart();
}

LibSFML::~LibSFML()
{

}

void LibSFML::Initialize()
{

}

void LibSFML::DrawMap(std::vector<std::string> map)
{
    sf::Vector2f r_pos = {6, 6};
    sf::RectangleShape bg_rect;
    bg_rect.setPosition(r_pos);
    bg_rect.setSize((sf::Vector2f){CELL_SIZE * GRID_SIZE, CELL_SIZE * GRID_SIZE});
    // bg_rect.setFillColor(sf::Color::White);
    bg_rect.setOutlineThickness(1.0);
    _window.draw(bg_rect);

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            sf::RectangleShape rect;
            rect.setSize((sf::Vector2f){CELL_SIZE, CELL_SIZE});
            if (map[y][x] == '0')
                rect.setFillColor(sf::Color::Black);
            if (map[y][x] == '1')
                rect.setFillColor(sf::Color::Red);
            if (map[y][x] == '2')
                rect.setFillColor(sf::Color::White);
            if (map[y][x] == '3')
                rect.setFillColor(sf::Color::Green);
            rect.setPosition(r_pos);
            _window.draw(rect);
            r_pos.x += CELL_SIZE;
        }
        r_pos.y += CELL_SIZE;
        r_pos.x = 6;
    }
}

void LibSFML::DrawScore(std::string const &score)
{

}

void LibSFML::Display()
{
    _window.display();
}

evtKey LibSFML::GetEventKey()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Up:
                    return (evtKey::UP);
                case sf::Keyboard::Down:
                    return (evtKey::DOWN);
                case sf::Keyboard::Left:
                    return (evtKey::LEFT);
                case sf::Keyboard::Right:
                    return (evtKey::RIGHT);
                default:
                    break;
            }
        }
    }
    return (evtKey::NONE);
}

void LibSFML::Destroy()
{

}

void LibSFML::Close()
{
    _window.close();
}

void LibSFML::Clear()
{
    _window.clear(sf::Color::Black);
}