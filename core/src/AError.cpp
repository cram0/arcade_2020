/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** AError
*/

#include "AError.hpp"

AError::AError(std::ostream &stream, std::string const& message)
: _stream(stream), _message(message)
{

}

AError::~AError() throw()
{

}

char const* AError::what() const throw()
{
    return (_message.c_str());
}
