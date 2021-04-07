/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** AClock
*/

#ifndef ACLOCK_HPP_
#define ACLOCK_HPP_

#include <ctime>

class AClock {
    public:
        AClock();
        ~AClock();
        double GetElapsedTime();
        void Restart();

    protected:
    private:
        clock_t _clock;

};

#endif /* !ACLOCK_HPP_ */
