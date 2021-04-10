/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Core
*/

#include "Core.hpp"

Core::Core()
{

}

Core::~Core()
{

}

void Core::PrintUsage()
{
    std::cout << "Usage: ./arcade [lib_name.so]" << std::endl;
    std::cout << "\nCommands:"<< std::endl;
    std::cout << "\t[directional arrows] for the up/down/left/right directions" << std::endl;
    std::cout << "\t[r] Reset the game" << std::endl;
    std::cout << "\t[o] Load the first game" << std::endl;
    std::cout << "\t[p] Load the second game" << std::endl;
    std::cout << "\t[b] Load the previous graphical library" << std::endl;
    std::cout << "\t[n] Load the next graphical library" << std::endl;
    std::cout << "\t[del] Go back to the main menu" << std::endl;
    std::cout << "\t[Enter] Confirm your name in the game over screen"<< std::endl;
    std::cout << "\t[Escape] Quit the program" << std::endl;
    std::cout << "\nDisclaimer:" << std::endl;
    std::cout << "\tYou might want to resize your terminal to a bigger size before you load the NCurses library for the borders to be shown properly." << std::endl;
}

void Core::CheckIfLibIsGraphical(std::string libName)
{
    for (auto const &lm : GetDLLoader().GetGraphicLibsMap()) {
        if (libName.find(lm.first) != std::string::npos) {
            return;
        }
    }
    throw AError(std::cerr, "./arcade: file \"" + libName + "\" is not a proper graphical library file.");
}

void Core::CheckIfLibExists(std::string libName)
{
    std::ifstream file = std::ifstream(libName.c_str());
    if (!file.good())
        throw AError(std::cerr, "./arcade: file \"" + libName + "\" doesn't exist.");
}

void Core::CheckArgs(int argc, char *argv[])
{
    if (argc == 1){
        throw AError(std::cerr, "./arcade: missing graphic library name\nTry '-h' for more information.");
    }
    if (argc == 2) {
        std::string f_arg = std::string(argv[1]);
        if (f_arg.compare("-h") == 0) {
            PrintUsage();
            std::exit(0);
        }
        else {
            CheckIfLibExists(f_arg);
            CheckIfLibIsGraphical(f_arg);
        }
    }
    else {
        throw AError(std::cerr, "./arcade: too many arguments.\nTry '-h' for more information.");
    }
}

void Core::Run()
{
    while (IsRunning()) {
        GetGraphic()->Clear();
        if (GetCurrentGame() == NO_GAME) {
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
            RefreshHighScores(PACMAN);
            RefreshHighScores(NIBBLER);
            GetGraphic()->DrawHighScores(_pacman_highscores_list, _nibbler_highscores_list);
            GetGraphic()->DisplayMenu();
        }
        else if (GetCurrentGame() == GAME_OVER) {
            evtKey key = GetGraphic()->InputGameOverName();
            ReadCoreEvent(key);
            GetGraphic()->DisplayGameOver();
        }
        else {
            evtKey key = GetGraphic()->GetEventKey();
            ReadCoreEvent(key);
            GetGame()->Update(key);
            CheckIfGameOver(GetGame()->IsGameOver());
            GetGraphic()->DrawMap(GetGame()->GetMap());
            GetGraphic()->DrawScore(GetGame()->GetScore());
            GetGraphic()->Display(GetGame()->GetDeltaTime());
        }
    }

    GetDLLoader().CloseHandles();
}

void Core::CheckIfScoreFilesExist()
{
    std::ifstream i_file_n;
    i_file_n.open("./lib/games/score/nibbler_score");
    if (!i_file_n.good()) {
        std::ofstream o_file_n { "./lib/games/score/nibbler_score" };
        o_file_n.close();
    }
    std::ifstream i_file_p;
    i_file_p.open("./lib/games/score/pacman_score");
    if (!i_file_p.good()) {
        std::ofstream o_file_p { "./lib/games/score/pacman_score" };
        o_file_p.close();
    }
}

bool Core::isOrdered(std::vector<std::pair<std::string, std::string>> list) const
{
    for (size_t i = 0; i < list.size() - 1; i++) {
        if (!(std::atoi(list[i].first.c_str()) >= std::atoi(list[i + 1].first.c_str()))) {
            return (false);
        }
    }
    return (true);
}

void Core::SetHighScore(std::string path, std::vector<std::pair<std::string, std::string>> list)
{
    std::ofstream file("./lib/games/score/" + path, std::ios::out);
    if (!file.good())
        throw AError(std::cerr, "./arcade: file : ./lib/games/score/" + path + " doesn't exist");

    for (size_t i = 0; i < list.size() && i < 5; i++) {
        file << list[i].first << " " << list[i].second << std::endl;
    }

    file.close();
}

void Core::RegisterHighScoresByGameName(std::string path)
{
    std::vector<std::pair<std::string, std::string>> tmp = GetHighScoresByGameName(path);
    tmp.push_back(std::make_pair(std::to_string(GetGame()->GetScore()), GetGraphic()->GetUsername()));

    while (!isOrdered(tmp)) {
        for (size_t i = 0; i < tmp.size() - 1; i++) {
            if (std::atoi(tmp[i].first.c_str()) < std::atoi(tmp[i + 1].first.c_str())) {
                std::swap(tmp[i], tmp[i + 1]);
            }
        }
    }

    SetHighScore(path, tmp);
}

void Core::RegisterHighScores(game_e curr_game)
{
    if (curr_game == game_e::PACMAN)
        RegisterHighScoresByGameName("pacman_score");
    if (curr_game == game_e::NIBBLER)
        RegisterHighScoresByGameName("nibbler_score");
}

std::vector<std::pair<std::string, std::string>> Core::GetHighScoresByGameName(std::string path)
{
    if (path.compare("pacman_score") == 0)
        _pacman_highscores_list.clear();
    if (path.compare("nibbler_score") == 0)
        _nibbler_highscores_list.clear();
    std::ifstream file("./lib/games/score/" + path);
    if (!file.good())
        throw AError(std::cerr, "./arcade: file : ./lib/games/score/" + path + " doesn't exist");

    std::vector<std::pair<std::string, std::string>> tmp;
    std::string line, score, name;
    size_t space;

    while (getline(file, line)) {
        space = line.find(' ');
        score = line.substr(0, space);
        name = line.substr(space + 1, std::string::npos);

        if (path.compare("pacman_score") == 0)
            _pacman_highscores_list.push_back(std::make_pair(score, name));
        if (path.compare("nibbler_score") == 0)
            _nibbler_highscores_list.push_back(std::make_pair(score, name));

        tmp.push_back(std::make_pair(score, name));
    }

    file.close();
    return (tmp);
}

void Core::RefreshHighScores(game_e curr_game)
{
    if (curr_game == game_e::PACMAN)
        GetHighScoresByGameName("pacman_score");
    else
        GetHighScoresByGameName("nibbler_score");
}

void Core::CheckIfGameOver(bool state)
{
    if (state) {
        _current_game = GAME_OVER;
    }
}

void Core::ChangeCurrentGraphic(evtKey evt)
{
    int tmp = (int)_current_graphic;
    if (evt == evtKey::PREV_GRAPH) {
        tmp -= 1;
        if (tmp < 0)
            _current_graphic = (graph_e)2;
        else
            _current_graphic = (graph_e)tmp;
    }
    if (evt == evtKey::NEXT_GRAPH) {
        tmp += 1;
        if (tmp > 2)
            _current_graphic = (graph_e)0;
        else
            _current_graphic = (graph_e)tmp;
    }
}

void Core::ChangeCurrentGame(evtKey evt)
{
    if (_current_game == NO_GAME) {
        if (evt == evtKey::GO_MENU)
            return;
        if (evt == evtKey::PREV_GAME) {
            _game_before_pause = _current_game;
            _current_game = game_e::NIBBLER;
        }
        if (evt == evtKey::NEXT_GAME) {
            _game_before_pause = _current_game;
            _current_game = game_e::PACMAN;
        }
    }
    if (evt == evtKey::PREV_GAME) {
        _current_game = game_e::NIBBLER;
    }
    if (evt == evtKey::NEXT_GAME) {
        _current_game = game_e::PACMAN;
    }
    if (evt == evtKey::GO_MENU) {
        _game_before_pause = _current_game;
        _current_game = game_e::NO_GAME;
    }
    if (evt == evtKey::CONFIRM_NAME && _current_game == game_e::GAME_OVER) {
        _game_before_pause = _current_game;
        _current_game = game_e::NO_GAME;
    }
}

void Core::ReadCoreEvent(evtKey evt)
{
    if (_current_game != game_e::GAME_OVER) {
        if (evt == evtKey::GO_MENU) {
            ChangeCurrentGame(evt);
        }
        if (evt == evtKey::RESET_GAME && _current_game != game_e::NO_GAME) {
            SetGame(GetDLLoader().SwitchGame(evt, _current_game));
        }
        if (evt == evtKey::NEXT_GAME) {
            if (_game_before_pause == game_e::PACMAN) {
                ChangeCurrentGame(evt);
            }
            else {
                ChangeCurrentGame(evt);
                SetGame(GetDLLoader().SwitchGame(evt, _current_game));
            }
        }
        if (evt == evtKey::PREV_GAME) {
            if (_game_before_pause == game_e::NIBBLER) {
                ChangeCurrentGame(evt);
            }
            else {
                ChangeCurrentGame(evt);
                SetGame(GetDLLoader().SwitchGame(evt, _current_game));
            }
        }
        if (evt == evtKey::PREV_GRAPH) {
            ChangeCurrentGraphic(evt);
            GetGraphic()->Close();
            SetGraphic(GetDLLoader().SwitchGraphic(evt, _current_graphic));
        }
        if (evt == evtKey::NEXT_GRAPH) {
            ChangeCurrentGraphic(evt);
            GetGraphic()->Close();
            SetGraphic(GetDLLoader().SwitchGraphic(evt, _current_graphic));
        }
    }
    if (evt == evtKey::CONFIRM_NAME) {
        if (_current_game == game_e::GAME_OVER) {
            RegisterHighScores(GetGame()->GetGameName());
            ChangeCurrentGame(evt);
        }
    }
    if (evt == evtKey::QUIT_GAME) {
        GetGraphic()->Close();
        _running = false;
    }
}

game_e Core::GetCurrentGame() const
{
    return (_current_game);
}

bool Core::IsRunning() const
{
    return (_running);
}

IGame *Core::GetGame() const
{
    return (_game);
}

IGraphic *Core::GetGraphic() const
{
    return (_graphlib);
}

DLLoader Core::GetDLLoader() const
{
    return (_dlloader);
}

void Core::SetGame(IGame *game)
{
    _game = game;
}

void Core::SetGraphic(IGraphic *graphlib)
{
    _graphlib = graphlib;
}