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
}

npuzzle::~npuzzle()
{
}

void    npuzzle::setHmethod(std::string s)
{
    if (s == "-m")
        _mNode->s = "MANHATTAN";
    else if (s == "-e")
        _mNode->s = "EUCLIDEAN";
    else if (s == "-h")
        _mNode->s = "HAMMING";
    else
    {
        std::cout << "Wrong argument" << std::endl;
        exit(1);
    }
}


void    npuzzle::setNode(std::ifstream & file)
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
            _mGridsize = atoi(line.c_str());
            _mNode = make_node(_mGridsize);
            _mNode->g = 0;
            _mNode->gridsize = _mGridsize;
        }
        else if (!line.empty())
        {
            std::stringstream stream(line);
            for (int i = 0; stream >>_mNode->array[j][i]; i++)
            {
                if (_mNode->array[j][i] == 0)
                {
                    _mNode->y = j;
                    _mNode->x = i;
                }
            }
            j++; 
        }
    }
}

const node & npuzzle::getNode() const{
    return(*_mNode);
}

void    npuzzle::print(node const & n)
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            std::cout << std::left << std::setw(5) << n.array[i][j];
        std::cout << std::endl;
    }
}
