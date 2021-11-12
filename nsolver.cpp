/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:56:34 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/12 21:51:18 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nsolver.hpp"

nsolver::nsolver() = default;


nsolver::nsolver(node const & n)
    : _mGridsize(n.gridsize), _mFirstNode(n)
{
    setGoal();
}

nsolver::~nsolver()
{
    delete[] _mGoal;
}

void    nsolver::print(node const & n) const
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            std::cout << std::left << std::setw(5) << n.array[i][j];
        std::cout << std::endl;
    }
}

// std::pair<int, int> & nsolver::getGoal() const
// {
//     return (*_mGoal);
// }

const node &  nsolver::getOpen() const
{
    return (_mOpen.top());
}

const node & nsolver::getFirstNode() const{
    return(_mFirstNode);
}

void    nsolver::setGoal()
{
    std::pair<int, int> *grid = new std::pair<int, int>[_mGridsize*_mGridsize];
    grid[0] = _mGridsize % 2 == 0 ? std::make_pair(_mGridsize / 2, (_mGridsize / 2) -1) : std::make_pair(_mGridsize / 2, (_mGridsize / 2));
    for (int counter = _mGridsize, n = 1, y = 0, x = 0, min = -1; n < _mGridsize * _mGridsize;)
    {
        for(; x < counter && n < _mGridsize * _mGridsize; x++, n++)
            grid[n] = std::make_pair(y, x);
        x--; y++;
        for(;y < counter && n < _mGridsize * _mGridsize; y++, n++)
            grid[n] = std::make_pair(y, x);
        x--; y--; counter--;
        for (;x > min && n < _mGridsize * _mGridsize; x--, n++)
            grid[n] = std::make_pair(y, x);
        x++; y--; min++;
        for (;y > min && n < _mGridsize * _mGridsize; y--, n++)
            grid[n] = std::make_pair(y, x);
        x++; y++;
    }
    _mGoal = grid ;
}

void    nsolver::setOpen(node const & n)
{
    _mOpen.push(n);
}

void    nsolver::manhattan(node & n)  const
{
    int distance = n.prev? n.distance : 0;
    if (!n.prev)
    {
        for (int y=0; y < _mGridsize; y++)
        {
            for (int x = 0; x < _mGridsize; x++)
            {
                if (n.array[y][x] != 0)
                {
                    distance += abs(y - _mGoal[n.array[y][x]].first);
                    distance += abs(x - _mGoal[n.array[y][x]].second);
                }
            }
        }
    }
    else 
    {
        int tmp, tmp2;
        if (n.prev->x == n.x)
        {
            tmp = abs(n.y - _mGoal[n.prev->array[n.y][n.x]].first);
            tmp2 = abs(n.prev->y - _mGoal[n.prev->array[n.y][n.x]].first);
        }
        else
        {
            tmp = abs(n.x - _mGoal[n.prev->array[n.y][n.x]].second);
            tmp2 = abs(n.prev->x - _mGoal[n.prev->array[n.y][n.x]].second);
        }
        if (tmp != tmp2)
            tmp < tmp2 ? distance++ : distance--;
    }
    n.distance = distance;
}

void    nsolver::euclidean(node & n) const
{
    float distance = 0;
    for (int y=0; y < _mGridsize; y++)
    {
        for (int x=0, tmp1 =0, tmp2 = 0; x < _mGridsize; x++)
        {
            if (n.array[y][x] != 0)
            {
                tmp1 = abs(_mGoal[n.array[y][x]].first - y);
                tmp2 = abs(_mGoal[n.array[y][x]].second - x);
                distance += sqrt((tmp1 * tmp1) + (tmp2 * tmp2));
            }        
        }
    }
    n.distance = distance;  
}


void    nsolver::hamming(node & n) const
{
    int h = 0;
    for (int y = 0; y < _mGridsize; y++)
    {
        for (int x = 0; x < _mGridsize; x++)
            _mGoal[n.array[y][x]].first == y && _mGoal[n.array[y][x]].second == x ? h++ : h = h;
    }

}

void    nsolver::setH(node & n) const
{
     void    (nsolver::*p2f[])(node & n)const = {&nsolver::manhattan, &nsolver::euclidean, &nsolver::hamming};
    (this->*p2f[n.heuristic])(n);
}

node  nsolver::copyNode(const node & n){
    node copy = make_node(_mGridsize);

    node tmp = n;
    copy.gen = tmp.gen;
    copy.distance = tmp.distance;
    copy.x = tmp.x;
    copy.y = tmp.y;
    copy.heuristic = tmp.heuristic;
    copy.prev = const_cast<node*>(&n);
    copy.array = tmp.array;

    return copy;
}

void    nsolver::move_up(node & n) const
{
    if (n.y > 0)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y - 1][n.x]);
        n.y--;
    }
}

void    nsolver::move_down(node & n) const
{
    if (n.y < _mGridsize -1)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y + 1][n.x]);
        n.y++;
    }
}

void    nsolver::move_left(node & n) const
{
    if (n.x > 0)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y][n.x - 1]);
        n.x--;
    }
}

void    nsolver::move_right(node & n) const
{
    if (n.x < _mGridsize -1)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y][n.x + 1]);
        n.x++;
    }
}

void nsolver::movements(const node & n, moves m)
{
    void    (nsolver::*p2f[])(node &n)const = {&nsolver::move_up, &nsolver::move_down, &nsolver::move_left, &nsolver::move_right};

    node    tmp = copyNode(n);

    tmp.gen++;
    tmp.prev = const_cast<node*>(&n);
    (this->*p2f[m])(tmp);
    setH(tmp);
    auto it = _mClosed.find(tmp.array);
    if (it != _mClosed.end()) {
        setOpen(tmp);
         _mClosed.insert(std::make_pair(tmp.array, tmp.gen));
    }

    // if (_mClosed.at(tmp->array)) {
    //     setOpen(*tmp);
    //     _mClosed.insert(std::make_pair(tmp->array, tmp->gen));
    // }
    // if (tmp->array != tmp->prev->array)
    //     setOpen(*tmp);
}

void nsolver::puzzle()
{
    node    n;

    n = _mFirstNode;
    n.prev = NULL;
    setH(n);
    setOpen(n);
    for (;n.distance != 0; n = getOpen())
    {
        _mOpen.pop();
        if ((!(n.prev)) || (n.x < _mGridsize -1 && n.prev->x != n.x +1))
            movements(n, RIGHT);
        if ((!(n.prev)) || (n.y > 0 && n.prev->y != n.y -1))
            movements(n, UP);
        if ((!(n.prev)) || (n.y < _mGridsize -1 && n.prev->y != n.y +1))
            movements(n, DOWN);
        if ((!(n.prev)) || (n.x > 0 && n.prev->x != n.x -1))
            movements(n, LEFT);
        _mClosed.insert(std::make_pair(n.array, n.gen));
        // _mClosed.insert(n);
    }
    // for (; n.prev; n = *n.prev)
    // {
    //     std::cout << "________________\n";
    //     print(n);
    // }
}