/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibSFML
*/

#ifndef LIBSFML_HPP_
#define LIBSFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "IGraphic.hpp"

#include "evtVar.hpp"

#define CELL_SIZE 22.0
#define GRID_SIZE_X 28
#define GRID_SIZE_Y 31
#define WINDOW_WIDTH 646
#define WINDOW_HEIGHT 800

class LibSFML : public IGraphic {
    public:
        LibSFML();
        ~LibSFML();

        void Initialize();
        void InitFont();
        void InitMenuPrompt();
        void InitScoreText();
        void InitGameOverPrompt();

        void UpdateGameOverScoreValue();

        void DrawRectangle(char id, sf::Vector2f r_pos);
        void DrawCircle(char id, sf::Vector2f r_pos);
        void DrawShapeFromID(char id, sf::Vector2f r_pos);
        void DrawMap(std::vector<std::string> map);
        void DrawScore(int score);
        void DrawHighScores(std::vector<std::pair<std::string, std::string>> &pacman_list, std::vector<std::pair<std::string, std::string>> &nibbler_list);

        void Display(AClock &delta);
        void DisplayMenu();
        void DisplayGameOver();

        void Destroy();
        void Clear();
        void Close();

        evtKey GetEventKey();
        std::string GetUsername() const;

        evtKey InputGameOverName();

    protected:
    private:
        sf::RenderWindow _window;
        sf::Event _event;

        sf::Text _score_value;
        sf::Text _score_label;
        sf::Font _font;

        sf::Text _menu_prompt;
        sf::Text _menu_prompt_choice_one;
        sf::Text _menu_prompt_choice_two;

        sf::Text _game_over_prompt;
        sf::Text _game_over_enter_name;
        sf::Text _game_over_score_prompt;
        sf::Text _game_over_score_value;
        sf::String _player_name_input;
        sf::Text _player_name;

};

extern "C" LibSFML *getLibSFML() {
    return (new LibSFML());
}

#endif /* !LIBSFML_HPP_ */
