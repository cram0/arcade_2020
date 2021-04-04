/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include <vector>
#include <ctime>

class Ghost {
    public:
        typedef enum {
            INKY,
            BLINKY,
            PINKY,
            CLYDE
        } ghost_name;

        typedef enum {
            UP = 1,
            DOWN,
            LEFT,
            RIGHT
        } direction;

        Ghost(Ghost::ghost_name name, int x, int y);
        ~Ghost();

        int GetX();
        int GetY();
        int GetGotoX();
        int GetGotoY();
        bool IsScared();
        bool CanMove();
        ghost_name GetName();
        std::vector<std::pair<int, int>> GetMvtStack();
        clock_t GetMoveClock();
        clock_t GetScaredClock();

        void SetX(int x);
        void SetY(int y);
        void SetGotoX(int x);
        void SetGotoY(int y);
        void SetScared(bool state);
        void SetMove(bool state);
        void SetName(ghost_name name);

        void ResetPosition();

        void AddMvt(int x, int y);
        void RemoveMvt();
        void UpdateClocks();
        void UpdateScaredClock();
        void UpdateMoveClock();


    protected:
    private:
        int _x;
        int _y;
        int _x_spawn;
        int _y_spawn;
        ghost_name _name;
        int _goto_x = -1;
        int _goto_y = -1;
        bool _can_move = false;
        bool _is_scared = false;
        std::vector<std::pair<int, int>> _mvt_stack;
        clock_t _can_move_clock;
        clock_t _scared_clock;
};

#endif /* !GHOST_HPP_ */
