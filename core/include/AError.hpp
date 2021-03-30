/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** AError
*/

#ifndef AERROR_HPP_
#define AERROR_HPP_

#include <exception>
#include <string>

class AError : public std::exception
{
    public:
        AError(std::ostream &stream, std::string const& message);
        ~AError() throw();

        const char *what() const throw();
    private:
        std::ostream &_stream;
        std::string _message;
};

#endif /* !AERROR_HPP_ */
