/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibSFML
*/

#include "LibSFML.hpp"

LibSFML::LibSFML()
{
    _window.create((sf::VideoMode){712, 800, 32}, "Title", sf::Style::Close);
    _window.setFramerateLimit(60);
    _clock.restart();
    _score_font.loadFromFile("libs/graphics/font/OpenSans-Regular.ttf");
    _score_value.setFont(_score_font);
    _score_value.setString("0");
    _score_value.setPosition((sf::Vector2f){190.0, 710.0});
    _score_value.setFillColor(sf::Color::White);
    _score_value.setCharacterSize(50);
    _score_label.setFont(_score_font);
    _score_label.setString("SCORE: ");
    _score_label.setPosition((sf::Vector2f){10.0, 710.0});
    _score_label.setFillColor(sf::Color::White);
    _score_label.setCharacterSize(50);
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

void LibSFML::DrawScore(int score)
{
    _score_value.setString(std::to_string(score));
    _window.draw(_score_value);
    _window.draw(_score_label);
}

void LibSFML::Display()
{
    while (_clock.getElapsedTime().asMilliseconds() <= 50.0) {
        _window.display();
    }
    _clock.restart();
}

evtKey LibSFML::GetEventKey()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                return(evtKey::UP);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                return(evtKey::DOWN);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                return(evtKey::LEFT);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                return(evtKey::RIGHT);
            // switch (_event.key.code) {
            //     case sf::Keyboard::Up:
            //         return (evtKey::UP);
            //     case sf::Keyboard::Down:
            //         return (evtKey::DOWN);
            //     case sf::Keyboard::Left:
            //         return (evtKey::LEFT);
            //     case sf::Keyboard::Right:
            //         return (evtKey::RIGHT);
            //     default:
            //         break;
            // }
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