/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibNcurses
*/

#include "LibNcurses.hpp"

LibNcurses::LibNcurses()
{
    Initialize();
}

LibNcurses::~LibNcurses()
{

}

void LibNcurses::Initialize()
{
    initscr();
    _game_window = subwin(stdscr, GRID_SIZE_Y + 2, GRID_SIZE_X + 2, 1, 1);
    box(_game_window, ACS_VLINE, ACS_HLINE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);
    _start_clock = clock();
    InitColors();
    InitGameOver();
}

void LibNcurses::InitGameOver()
{
    _game_over_prompt = "GAME OVER";
    _game_over_score_label = "SCORE :";
}

void LibNcurses::InitColors()
{
    if (has_colors() == FALSE) {
        endwin();
        std::cout << "Your terminal does not support color" << std::endl;
        exit(1);
    } else {
        start_color();
        init_pair(GREEN_RECT, COLOR_GREEN, COLOR_GREEN);
        init_pair(WHITE_RECT, COLOR_WHITE, COLOR_WHITE);
        init_pair(RED_RECT, COLOR_RED, COLOR_RED);
        init_pair(BLACK_RECT, COLOR_BLACK, COLOR_BLACK);
        init_pair(BLUE_RECT, COLOR_BLUE, COLOR_BLUE);
        init_pair(PACMAN, COLOR_YELLOW, COLOR_BLACK);
        init_pair(INKY, COLOR_CYAN, COLOR_BLACK);
        init_pair(BLINKY, COLOR_RED, COLOR_BLACK);
        init_pair(CLYDE, COLOR_YELLOW, COLOR_BLACK);
        init_pair(PINKY, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(BARRIER, COLOR_WHITE, COLOR_BLACK);
        init_pair(PACGUM, COLOR_WHITE, COLOR_BLACK);
        init_pair(SCARED, COLOR_WHITE, COLOR_BLUE);
    }
}

void LibNcurses::DrawId(char const id, int y, int x)
{
    y += 1;
    x += 1;
    switch (id) {
        case '0':
            attron(COLOR_PAIR(BLACK_RECT));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(BLACK_RECT));
            break;
        case '1':
            attron(COLOR_PAIR(RED_RECT));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(RED_RECT));
            break;
        case '2':
            attron(COLOR_PAIR(WHITE_RECT));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(WHITE_RECT));
            break;
        case '3':
            attron(COLOR_PAIR(GREEN_RECT));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(GREEN_RECT));
            break;
        case '4':
            attron(COLOR_PAIR(BLUE_RECT));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(BLUE_RECT));
            break;
        case '5':
            attron(COLOR_PAIR(PACGUM));
            mvaddch(y, x, '.');
            attroff(COLOR_PAIR(PACGUM));
            break;
        case '-':
            attron(COLOR_PAIR(BARRIER));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(BARRIER));
            break;
        case 'p':
            attron(COLOR_PAIR(PINKY));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(PINKY));
            break;
        case 'b':
            attron(COLOR_PAIR(BLINKY));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(BLINKY));
            break;
        case 'i':
            attron(COLOR_PAIR(INKY));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(INKY));
            break;
        case 'c':
            attron(COLOR_PAIR(CLYDE));
            mvaddch(y, x, id);
            attroff(COLOR_PAIR(CLYDE));
            break;
        case 'a':
            attron(A_BOLD);
            attron(COLOR_PAIR(PACMAN));
            mvaddch(y, x, id);
            attroff(A_BOLD);
            attroff(COLOR_PAIR(PACMAN));
            break;
        case 'u':
            attron(COLOR_PAIR(PACGUM));
            mvaddch(y, x, 'o');
            attroff(COLOR_PAIR(PACGUM));
            break;
        case 's':
            attron(COLOR_PAIR(SCARED));
            mvaddch(y, x, 'X');
            attroff(COLOR_PAIR(SCARED));
            break;
    }
}

void LibNcurses::DrawMap(std::vector<std::string> map)
{
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        for (int x = 0; x < GRID_SIZE_X; x++) {
            DrawId(map[y][x], y, x);
        }
    }
}

void LibNcurses::DrawScore(int score)
{
    _game_over_score_value = std::to_string(score);
    mvprintw(1, GRID_SIZE_X + 5, "SCORE :");
    mvprintw(2, GRID_SIZE_X + 5, _game_over_score_value.c_str());
}

void LibNcurses::Display()
{
    if (_is_game_over)
        _is_game_over = false;
    clock_t _end_clock = clock();
    while ((double)(_end_clock - _start_clock) / CLOCKS_PER_SEC <= 0.1) {
        _end_clock = clock();
        refresh();
    }
    _start_clock = clock();
}

void LibNcurses::DisplayMenu()
{
    refresh();
}

void LibNcurses::DisplayGameOver()
{
    if (!_is_game_over)
        _is_game_over = true;

    mvprintw(1, GRID_SIZE_X / 2 - _game_over_prompt.length() / 2, _game_over_prompt.c_str());
    mvprintw(2, GRID_SIZE_X / 2 - _game_over_score_label.length() / 2, _game_over_score_label.c_str());
    mvprintw(2, GRID_SIZE_X / 2 - _game_over_score_label.length() / 2 + 8, _game_over_score_value.c_str());
    refresh();
}

void LibNcurses::Destroy()
{
    endwin();
}

void LibNcurses::Clear()
{
    if (!_is_game_over) {
        clear();
    }
}

void LibNcurses::Close()
{
    Destroy();
}

evtKey LibNcurses::GetEventKey()
{
    int key = getch();

    if (key == ERR) {
        return (evtKey::NONE);
    }

    switch (key) {
        case KEY_UP:
            return (evtKey::UP);
        case KEY_DOWN:
            return (evtKey::DOWN);
        case KEY_LEFT:
            return (evtKey::LEFT);
        case KEY_RIGHT:
            return (evtKey::RIGHT);
        case 'o':
            return (evtKey::PREV_GAME);
        case 'p':
            return (evtKey::NEXT_GAME);
        case 'r':
            return (evtKey::RESET_GAME);
        case 127:
            return (evtKey::GO_MENU);
        case KEY_ENTER:
            return (evtKey::CONFIRM_NAME);
        case 'b':
            return (evtKey::PREV_GRAPH);
        case 'n':
            return (evtKey::NEXT_GRAPH);
        default:
            return (evtKey::NONE);
    }

    return (evtKey::NONE);
}