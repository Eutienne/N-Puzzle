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
    : _mGridsize(0)
{
}

npuzzle::~npuzzle()
{
}


void    npuzzle::setHmethod(const std::string s)
{
    if ((s == "--m" || s == "--MANHATTAN") && (!(_mNode->FLAGS & EU) && (!(_mNode->FLAGS & HA))))
        _mNode->FLAGS |= MA;
    else if ((s == "--e" || s == "--EUCLIDEAN") && (!(_mNode->FLAGS & HA) && (!(_mNode->FLAGS & HA))))
        _mNode->FLAGS |= EU;
    else if ((s == "--h" || s == "--HAMMING") && (!(_mNode->FLAGS & EU) && (!(_mNode->FLAGS & MA)))) 
        _mNode->FLAGS |= HA;
    else if (s == "--A_STAR" && (!(_mNode->FLAGS & GR) && (!(_mNode->FLAGS & UN))))
        _mNode->FLAGS |= A_STAR;
    else if (s == "--GREEDY" && (!(_mNode->FLAGS & A_STAR) && (!(_mNode->FLAGS & UN))))
        _mNode->FLAGS |= GR;
    else if (s == "--UNIFORM" && (!(_mNode->FLAGS & GR) && (!(_mNode->FLAGS & A_STAR))))
        _mNode->FLAGS |= UN;
    else if (s == "--VERBOSE")
        _mNode->FLAGS |= VB;
    else
        throw std::runtime_error("Wrong argument");
}

void    remove_comment(std::string & line)
{
    int pos;

    pos = line.find('#');
    line = line.substr(0, pos);
    pos = line.find_last_not_of(" \n\r\t\f\v");
    line = line.substr(0, pos+1);
    for (int i = 0, c;line[i]; i++)
    {
        c=line[i];
        if (!(isspace(c) || isdigit(c)))
            throw std::runtime_error("Wrong argument");            
    }
}

void    npuzzle::setNode(std::ifstream & file)
{
    std::unordered_set<int> check;
    int pos = 0;
    std::string line;
    for (int j=0; getline(file, line);)
    {
        remove_comment(line);
        if ((!line.empty()) && pos == 0)
        {
            pos++;
            _mGridsize = atoi(line.c_str());
            _mNode = make_node(_mGridsize);
            _mNode->gen = 0;
            _mNode->gridsize = _mGridsize;
        }
        else if (!line.empty())
        {
            std::stringstream stream(line);
            for (int i = 0; stream >>_mNode->array[j][i]; i++)
            {
                if (_mNode->array[j][i] >= _mGridsize * _mGridsize)
                    throw std::runtime_error("The number is to big");
                check.insert(_mNode->array[j][i]);
                if (_mNode->array[j][i] == 0)
                {
                    _mNode->y = j;
                    _mNode->x = i;
                }
            }
            j++; 
        }
    }
    if (check.size() != _mGridsize * _mGridsize)
        throw std::runtime_error("Wrong Input");
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
