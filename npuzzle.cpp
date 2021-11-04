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

// bool    F::operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b)
// {
//         return (a->h + a->g  > b->h + b->g);
// }


// void    npuzzle::setGoal()
// {
//     for (int i = 0; i < _mGridsize; i++)
//     {
//         for (int j = 0; j < _mGridsize; j++)
//             _mGoal->array[i][j] = 0;
//     }
//     for (int i = 0, j = 0, n = 1; _mGoal->array[i] && _mGoal->array[i][j] == 0 && n < _mGridsize * _mGridsize;)
//     {
//         for (; j < _mGridsize && _mGoal->array[i][j] == 0; j++, n++)
//             _mGoal->array[i][j] = n; 
//         j--; i++;
//         for (; i < _mGridsize && _mGoal->array[i][j] == 0; i++, n++)
//             _mGoal->array[i][j] = n;
//         i--; j--;
//         for (; j > -1 && _mGoal->array[i][j] == 0; j--, n++)
//             _mGoal->array[i][j] = n;
//         j++; i--;
//         for (; i > -1 && _mGoal->array[i][j] == 0; i--, n++)
//             _mGoal->array[i][j] = n;
//         i++; j++;
//     }
//     _mGoal->y = _mGridsize/2;
//     _mGridsize % 2 == 0 ? _mGoal->array[_mGridsize / 2][(_mGridsize / 2) -1] = 0 : _mGoal->array[_mGridsize / 2][(_mGridsize / 2)] = 0;
//     _mGridsize % 2 == 0 ? _mGoal->x = (_mGridsize / 2) -1 : _mGoal->x = _mGridsize / 2;
// }

npuzzle::npuzzle()
{
    // _mGameover = false;
}

npuzzle::~npuzzle()
{
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

// void    npuzzle::setNode(std::shared_ptr<node> const & n)
// {
//     _mNode.push(n);
// }

// std::shared_ptr<node>  npuzzle::copyNode(std::shared_ptr<node> const & n){
//     std::shared_ptr<node> copy = make_node(_mGridsize);

//     node tmp = *n;
//     copy->g = tmp.g;
//     copy->h = tmp.h;
//     copy->x = tmp.x;
//     copy->y = tmp.y;
//     copy->prev = n;

//     for (int y = 0; y < _mGridsize; y++)
//     {
//         for (int x = 0; x < _mGridsize; x++)
//             copy->array[y][x] = tmp.array[y][x];
//     }
//     return copy;
// }


// const node & npuzzle::getGoal() const
// {
//     return (*_mGoal);
// }

// const std::shared_ptr<node> &  npuzzle::getNode() const
// {
//     return (_mNode.top());
// }

void    npuzzle::print(node const & n)
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            std::cout << std::left << std::setw(5) << n.array[i][j];
        std::cout << std::endl;
    }
}

// void    npuzzle::setH(std::shared_ptr<node> & n)
// {
//     int h = 0;
//     for (int i=0; i < _mGridsize; i++)
//     {
//         for (int j = 0; j < _mGridsize; j++)
//         {
//             for (int y=0; j < _mGridsize && y < _mGridsize && n->array[i][j] != 0; y++)
//             {
//                 for (int x=0; x < _mGridsize; x++)
//                 {
//                     if (n->array[i][j] == _mGoal->array[y][x])
//                     {
//                         y > i ? h += y - i : h += i - y;
//                         x > j ? h += x - j : h += j - x;
//                         break;
//                     }
//                 }
//             }
//         }
//     }
//     n->h = h;
// }

// void    npuzzle::move_up(node & n)
// {
//     if (n.y > 0)
//     {
//         std::swap(n.array[n.y][n.x], n.array[n.y - 1][n.x]);
//         n.y--;
//     }
// }

// void    npuzzle::move_down(node & n)
// {
//     if (n.y < _mGridsize -1)
//     {
//         std::swap(n.array[n.y][n.x], n.array[n.y + 1][n.x]);
//         n.y++;
//     }
// }

// void    npuzzle::move_left(node & n)
// {
//     if (n.x > 0)
//     {
//         std::swap(n.array[n.y][n.x], n.array[n.y][n.x - 1]);
//         n.x--;
//     }
// }

// void    npuzzle::move_right(node & n)
// {
//     if (n.x < _mGridsize -1)
//     {
//         std::swap(n.array[n.y][n.x], n.array[n.y][n.x + 1]);
//         n.x++;
//     }
// }

// bool    npuzzle::getGameover()
// {
//     return (_mGameover);
// }

// void    npuzzle::setGameover(bool b)
// {
//     _mGameover = b;
// }


// void npuzzle::movements(std::shared_ptr<node> const & n, std::string s)
// {
//     std::string moves[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
//     void    (npuzzle::*p2f[])(node &n) = {&npuzzle::move_up, &npuzzle::move_down, &npuzzle::move_left, &npuzzle::move_right};

//     std::shared_ptr<node>    tmp = copyNode(n);

//     for (int i = 0; i < 4; i++)
//     {
//         if (moves[i] == s)
//         {
//             tmp->g++;
//             (this->*p2f[i])(*tmp);
//             setH(tmp);
//             setNode(tmp);
//             break;
//         }
//     }
// }

// void npuzzle::puzzle()
// {
//     std::shared_ptr<node>    n;

//     n = std::make_shared<node>(getFirstNode());
//     setH(n);
//     setNode(n);
//     for (;n->h != 0; n = getNode())
//     {
//         _mNode.pop();
//         if (n->h == 0)
//             break;
//         if (n->prev == NULL || (n->x < _mGridsize -1 && n->h != 0 && n->prev->x != n->x +1))
//             movements(n, "RIGHT");
//         if (n->prev == NULL || (n->y > 0 && n->h != 0 && n->prev->y != n->y -1))
//             movements(n, "UP");
//         if (n->prev == NULL || (n->y < _mGridsize -1 && n->h != 0 && n->prev->y != n->y +1))
//             movements(n, "DOWN");
//         if (n->prev == NULL || (n->x > 0 && n->h != 0 && n->prev->x != n->x -1))
//             movements(n, "LEFT");
//         _mNode2.push(n);
//     }
//     for (; n; n = n->prev)
//     {
//         std::cout << "________________\n";
//         print(*n);
//     }
// }