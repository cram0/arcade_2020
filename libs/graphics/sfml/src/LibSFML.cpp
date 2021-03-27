/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibSFML
*/

#include "LibSFML.hpp"

LibSFML::LibSFML()
{
    Initialize();

}

LibSFML::~LibSFML()
{

}

void LibSFML::Initialize()
{
    _window.create((sf::VideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, 32}, "Title", sf::Style::Close);
    _window.setFramerateLimit(60);
    _clock.restart();
    InitScoreText();
    InitMenuPrompt();
}

void LibSFML::InitScoreText()
{
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

void LibSFML::InitMenuPrompt()
{
    _menu_prompt.setFont(_score_font);
    _menu_prompt.setPosition((sf::Vector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4});
    _menu_prompt.setString("\t\tArcade :");
    _menu_prompt.setCharacterSize(40);
    _menu_prompt.setFillColor(sf::Color::White);
    _menu_prompt_choice_one.setFont(_score_font);
    _menu_prompt_choice_one.setPosition((sf::Vector2f){_menu_prompt.getPosition().x, _menu_prompt.getPosition().y + 100});
    _menu_prompt_choice_one.setString("Nibbler\n\tO");
    _menu_prompt_choice_one.setCharacterSize(30);
    _menu_prompt_choice_one.setFillColor(sf::Color::White);
    _menu_prompt_choice_two.setFont(_score_font);
    _menu_prompt_choice_two.setPosition((sf::Vector2f){_menu_prompt_choice_one.getPosition().x + 170, _menu_prompt_choice_one.getPosition().y});
    _menu_prompt_choice_two.setString("Pacman\n\tP");
    _menu_prompt_choice_two.setCharacterSize(30);
    _menu_prompt_choice_two.setFillColor(sf::Color::White);
}

void LibSFML::DrawRectangle(char id, sf::Vector2f r_pos)
{
    sf::RectangleShape rect;
    rect.setSize((sf::Vector2f){CELL_SIZE, CELL_SIZE});
    rect.setPosition(r_pos);
    if (id == '0')
        rect.setFillColor(sf::Color::Black);
    if (id == '1')
        rect.setFillColor(sf::Color::Red);
    if (id == '2')
        rect.setFillColor(sf::Color::White);
    if (id == '3')
        rect.setFillColor(sf::Color::Green);
    if (id == '4')
        rect.setFillColor((sf::Color){0, 100, 255});
    if (id == '5') {
        float offset = (CELL_SIZE / 6.0) / 2.0;
        float gum_pos = CELL_SIZE / 2.0 - offset;
        rect.setSize((sf::Vector2f){CELL_SIZE / 6, CELL_SIZE / 6});
        rect.setFillColor(sf::Color::White);
        rect.move((sf::Vector2f){gum_pos, gum_pos});
    }
    if (id == '-') {
        rect.setSize((sf::Vector2f){CELL_SIZE, CELL_SIZE / 2});
        rect.move((sf::Vector2f){0, (CELL_SIZE / 2) - ((CELL_SIZE / 2) / 2)});
    }
    _window.draw(rect);
}

void LibSFML::DrawCircle(char id, sf::Vector2f r_pos)
{
    sf::CircleShape circ;
    circ.setRadius(CELL_SIZE / 2);
    circ.setPosition(r_pos);
    if (id == 'a')
        circ.setFillColor(sf::Color::Yellow);
    if (id == 'u') {
        float offset = (CELL_SIZE / 3.0) / 2.0;
        circ.setFillColor(sf::Color::White);
        circ.setRadius(CELL_SIZE / 3);
        circ.move((sf::Vector2f){offset, offset});
    }
    if (id == 'p')
        circ.setFillColor((sf::Color){255, 192, 203});
    if (id == 'b')
        circ.setFillColor(sf::Color::Red);
    if (id == 'i')
        circ.setFillColor(sf::Color::Cyan);
    if (id == 'c')
        circ.setFillColor((sf::Color){255,165,0});
    _window.draw(circ);
}

void LibSFML::DrawShapeFromID(char id, sf::Vector2f r_pos)
{
    sf::CircleShape circ;
    circ.setRadius(0.5);
    if ((id >= '0' && id <= '9') || id == '-')
        DrawRectangle(id, r_pos);
    else
        DrawCircle(id, r_pos);
}

void LibSFML::DrawMap(std::vector<std::string> map)
{
    sf::Vector2f r_pos = {1, 1};
    sf::RectangleShape bg_rect;
    bg_rect.setPosition(r_pos);
    bg_rect.setSize((sf::Vector2f){CELL_SIZE * GRID_SIZE_X, CELL_SIZE * GRID_SIZE_Y});
    bg_rect.setOutlineThickness(1.0);
    bg_rect.setFillColor(sf::Color::Black);
    _window.draw(bg_rect);

    for (int y = 0; y < GRID_SIZE_Y; y++) {
        for (int x = 0; x < GRID_SIZE_X; x++) {
            DrawShapeFromID(map[y][x], r_pos);
            r_pos.x += CELL_SIZE;
        }
        r_pos.y += CELL_SIZE;
        r_pos.x = 1;
    }
}

void LibSFML::DrawScore(int score)
{
    _score_value.setString(std::to_string(score));
    _window.draw(_score_value);
    _window.draw(_score_label);
}

void LibSFML::DisplayMenu()
{
    _window.draw(_menu_prompt);
    _window.draw(_menu_prompt_choice_one);
    _window.draw(_menu_prompt_choice_two);
    _window.display();
}

void LibSFML::Display()
{
    while (_clock.getElapsedTime().asMilliseconds() <= 70.0) {
        _window.display();
    }
    _clock.restart();
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
                case sf::Keyboard::O:
                    return (evtKey::PREV_GAME);
                case sf::Keyboard::P:
                    return (evtKey::NEXT_GAME);
                case sf::Keyboard::R:
                    return (evtKey::RESET_GAME);
                case sf::Keyboard::Enter:
                    return (evtKey::GO_MENU);
                default:
                    return (evtKey::NONE);
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