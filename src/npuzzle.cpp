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

#include "../header/npuzzle.hpp"

npuzzle::npuzzle()
    : _mGridsize(0)
{
}

npuzzle::~npuzzle()
{
}

int     npuzzle::getGridsize()
{
    return (_mGridsize);
}



void    npuzzle::setHmethod(const std::string s)
{
    if ((s == "--m" || s == "--MANHATTAN") && (!(_mNode->FLAGS & EU) && (!(_mNode->FLAGS & HA))))
        _mNode->FLAGS |= MA;
    else if ((s == "--e" || s == "--EUCLIDEAN") && (!(_mNode->FLAGS & MA) && (!(_mNode->FLAGS & HA))))
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
        throw std::runtime_error("Wrong argument or flag");
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

void    check_mutiple_args(std::string line)
{
    for (int i = 0, c;line[i]; i++)
    {
        c=line[i];
        if (isspace(c))
            throw std::runtime_error("Wrong argument");            
    }
}


void    npuzzle::hustle_node()
{
    std::srand(std::time(nullptr));
    for (int i = 0; i < 80000; i++)
    {
        switch (std::rand() % 4)
        {
        case 0:
            _mNode->move_up();
            break;
        case 1:
            _mNode->move_down();
            break;
        case 2:
            _mNode->move_right();
            break;  
        default:
            _mNode->move_left();
            break;
        }
    }
}

void    npuzzle::fill_node()
{
    _mNode->y = _mGridsize /2;
    if (_mGridsize % 2 == 0)
        _mNode->x = (_mGridsize / 2) -1;
    else
        _mNode->x = _mGridsize / 2;
    for (int counter = _mGridsize, n = 1, y = 0, x = 0, min = -1; n < _mGridsize * _mGridsize;)
    {
        for(; x < counter && n < _mGridsize * _mGridsize; x++, n++)
            _mNode->array[y][x] = n;
        x--; y++;
        for(;y < counter && n < _mGridsize * _mGridsize; y++, n++)
            _mNode->array[y][x] = n;
        x--; y--; counter--;
        for (;x > min && n < _mGridsize * _mGridsize; x--, n++)
            _mNode->array[y][x] = n;
        x++; y--; min++;
        for (;y > min && n < _mGridsize * _mGridsize; y--, n++)
            _mNode->array[y][x] = n;
        x++; y++;
    }
}

void    npuzzle::make_npuzzle(int i)
{
    if (i < 3 || i > 20)
        throw std::runtime_error("Wrong size");            
    _mNode = make_node(i);
    _mGridsize = i;
    _mNode->gridsize = _mGridsize;
    fill_node();
    hustle_node();
    _mNode->gen = 0;
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
            check_mutiple_args(line);
            pos++;
            _mGridsize = atoi(line.c_str());
            if (_mGridsize < 3)
                throw std::runtime_error("The puzzle needs to be atleast 3 x 3");
            _mNode = make_node(_mGridsize);
            _mNode->gen = 0;
            _mNode->gridsize = _mGridsize;
        }
        else if ((!line.empty()) && j < _mGridsize)
        {
            std::stringstream stream(line);
            for (int i = 0; i < _mGridsize && stream >>_mNode->array[j][i]; i++)
            {
                if (_mNode->array[j][i] >= _mGridsize * _mGridsize)
                    throw std::runtime_error("The number is to big");
                check.insert(_mNode->array[j][i]);
                if (check.size() != j * _mGridsize + i + 1)
                    throw std::runtime_error("Wrong input");
                if (_mNode->array[j][i] == 0)
                {
                    _mNode->y = j;
                    _mNode->x = i;
                }
            }
            if (stream >> j)
                throw std::runtime_error("Wrong input");
            j++; 
        }
        else if (!line.empty())
            throw std::runtime_error("Wrong input");
    }
    if (check.size() != _mGridsize * _mGridsize)
        throw std::runtime_error("Wrong input");
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
