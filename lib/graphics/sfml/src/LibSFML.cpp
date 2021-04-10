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
    Destroy();
}

void LibSFML::Initialize()
{
    _window.create((sf::VideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, 32}, "SFML", sf::Style::Close);
    _window.setFramerateLimit(0);
    InitFont();
    InitScoreText();
    InitMenuPrompt();
    InitGameOverPrompt();
}

void LibSFML::InitFont()
{
    _font.loadFromFile("lib/graphics/font/OpenSans-Regular.ttf");
}

void LibSFML::InitGameOverPrompt()
{
    _player_name_input = "";
    _player_name = sf::Text("", _font, 50);
    _player_name.setPosition((sf::Vector2f){10.0, 710.0});
    _player_name.setFillColor(sf::Color::White);

    _game_over_prompt = sf::Text("Game Over", _font, 80);
    _game_over_prompt.setPosition((sf::Vector2f){WINDOW_WIDTH / 2 - _game_over_prompt.getLocalBounds().width / 2, WINDOW_HEIGHT / 4 - _game_over_prompt.getLocalBounds().height / 2});
    _game_over_prompt.setFillColor(sf::Color::White);

    _game_over_enter_name = sf::Text("Enter your name :", _font, 40);
    _game_over_enter_name.setPosition((sf::Vector2f){10 , WINDOW_HEIGHT - 100 - _game_over_enter_name.getLocalBounds().height - 100});
    _game_over_enter_name.setFillColor(sf::Color::White);

    _game_over_score_prompt = sf::Text("Score : ", _font, 30);
    _game_over_score_prompt.setPosition(WINDOW_WIDTH / 2 - _game_over_score_prompt.getLocalBounds().width / 2, _game_over_prompt.getPosition().y + 100);

    _game_over_score_value = _score_value;
    _game_over_score_value.setPosition(_game_over_score_prompt.getPosition().x + 100, _game_over_score_prompt.getPosition().y);

}

void LibSFML::InitScoreText()
{
    _score_value = sf::Text("0", _font, 50);
    _score_value.setPosition((sf::Vector2f){190.0, 710.0});
    _score_value.setFillColor(sf::Color::White);

    _score_label = sf::Text("SCORE", _font, 50);
    _score_label.setPosition((sf::Vector2f){10.0, 710.0});
    _score_label.setFillColor(sf::Color::White);
}

void LibSFML::InitMenuPrompt()
{
    _menu_prompt = sf::Text("\t\tArcade :", _font, 40);
    _menu_prompt.setPosition((sf::Vector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4});
    _menu_prompt.setFillColor(sf::Color::White);

    _menu_prompt_choice_one = sf::Text("Nibbler\n\tO", _font, 30);
    _menu_prompt_choice_one.setPosition((sf::Vector2f){_menu_prompt.getPosition().x, _menu_prompt.getPosition().y + 100});
    _menu_prompt_choice_one.setFillColor(sf::Color::White);

    _menu_prompt_choice_two = sf::Text("Pacman\n\tP", _font, 30);
    _menu_prompt_choice_two.setPosition((sf::Vector2f){_menu_prompt_choice_one.getPosition().x + 170, _menu_prompt_choice_one.getPosition().y});
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
    if (id == 's')
        circ.setFillColor((sf::Color){0, 100, 255});
    _window.draw(circ);
}

void LibSFML::DrawShapeFromID(char id, sf::Vector2f r_pos)
{
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

void LibSFML::DrawHighScores(std::vector<std::pair<std::string, std::string>> &pacman_list, std::vector<std::pair<std::string, std::string>> &nibbler_list)
{
    sf::Vector2f pacman_pos = {WINDOW_WIDTH / 4 + 200, WINDOW_HEIGHT / 4 + 250};
    unsigned short place = 1;
    for (auto p : pacman_list) {
        sf::Text text = sf::Text(std::to_string(place++) + ". " + p.first + " " + p.second, _font, 19);
        text.setPosition(pacman_pos);
        text.setFillColor(sf::Color::White);
        _window.draw(text);
        pacman_pos.y += 20;
    }
    place = 1;
    sf::Vector2f nibbler_pos = {WINDOW_WIDTH / 6, WINDOW_HEIGHT / 4 + 250};
    for (auto n : nibbler_list) {
        sf::Text text = sf::Text(std::to_string(place++) + ". " + n.first + " " + n.second, _font, 19);
        text.setPosition(nibbler_pos);
        text.setFillColor(sf::Color::White);
        _window.draw(text);
        nibbler_pos.y += 20;
    }
}

evtKey LibSFML::InputGameOverName()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::TextEntered) {
            if (_event.text.unicode == '\b') {
                if (!_player_name_input.isEmpty())
                    _player_name_input.erase(_player_name_input.getSize() - 1, 1);
                _player_name.setString(_player_name_input);
            }
            else if (_event.text.unicode > 31 && _event.text.unicode < 127) {
                if (_player_name_input.getSize() < 20)
                    _player_name_input += _event.text.unicode;
                _player_name.setString(_player_name_input);
            }
        }
        if (_event.key.code == sf::Keyboard::Enter)
            return (evtKey::CONFIRM_NAME);
    }
    return (evtKey::NONE);
}

void LibSFML::UpdateGameOverScoreValue()
{
    _game_over_score_value = _score_value;
    _game_over_score_value.setPosition(_game_over_score_prompt.getPosition().x + 100, _game_over_score_prompt.getPosition().y);
    _game_over_score_value.setCharacterSize(30);
}

void LibSFML::DisplayGameOver()
{
    UpdateGameOverScoreValue();
    _window.draw(_game_over_score_prompt);
    _window.draw(_game_over_score_value);
    _window.draw(_game_over_prompt);
    _window.draw(_game_over_enter_name);
    _window.draw(_player_name);
    _window.display();
}

void LibSFML::DisplayMenu()
{
    _window.draw(_menu_prompt);
    _window.draw(_menu_prompt_choice_one);
    _window.draw(_menu_prompt_choice_two);
    _window.display();
}

void LibSFML::Display(AClock &delta)
{
    while (delta.GetElapsedTime() <= 0.1) {
        _window.display();
    }
    delta.Restart();
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
                case sf::Keyboard::Delete:
                    return (evtKey::GO_MENU);
                case sf::Keyboard::Enter:
                    return (evtKey::CONFIRM_NAME);
                case sf::Keyboard::B:
                    return (evtKey::PREV_GRAPH);
                case sf::Keyboard::N:
                    return (evtKey::NEXT_GRAPH);
                case sf::Keyboard::Escape:
                    return (evtKey::QUIT_GAME);
                default:
                    return (evtKey::NONE);
            }
        }
        if (_event.type == sf::Event::Closed) {
            return (evtKey::QUIT_GAME);
        }
    }
    return (evtKey::NONE);
}

std::string LibSFML::GetUsername() const
{
    return (_player_name_input.toAnsiString());
}

void LibSFML::Destroy()
{
    _window.close();
}

void LibSFML::Close()
{
    Destroy();
}

void LibSFML::Clear()
{
    _window.clear(sf::Color::Black);
}