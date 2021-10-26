/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   npuzzle.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 19:31:50 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/26 19:32:14 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"

npuzzle::npuzzle()
{
    _mFirstNote->array = NULL;
    _mFirstNote->h = 0;
    _mFirstNote->g = 0;
}

void    npuzzle::setFirstNote(std::ifstream & file)
{
    int pos;
    std::string line;
    for (int j=0; getline(file, line);)
    {
        pos = line.find('#');
        line = line.substr(0, pos);
        pos = line.find_last_not_of(" \n\r\t\f\v");
        line = line.substr(0, pos+1);
        if ((!line.empty()) && line.find_last_not_of(" \n\r\t\f\v") == '\0')
        {
            _mFirstNote->array = new int*[atoi(line.c_str()) + 1];
            _mFirstNote->array[atoi(line.c_str())] = NULL;
            for (int i = 0; i < atoi(line.c_str()); i++)
                _mFirstNote->array[i] = new int[atoi(line.c_str())];
        }
        else if (!line.empty())
        {
            std::stringstream stream(line);
            for (int i = 0; stream >>_mFirstNote->array[j][i]; i++); 
            j++; 
        }
    }
}

const note & npuzzle::getFirstNote() const{
    return(*_mFirstNote);
}

void    npuzzle::setNote(note & n)
{
    _mNote.push(n);
}

const note &  npuzzle::getNote() const
{
    return (_mNote.top());
}