/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:56:34 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/09 20:35:08 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nsolver.hpp"

// AL: you definitely don't need to use std::shared_ptr here, use 'const node&' parameters
bool    F::operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b)
{
        return (a->h + a->g  > b->h + b->g);
}

bool Puzzle::operator()(const std::shared_ptr<node>& a, const std::shared_ptr<node>& b)
{
        return (a->array != b->array);
}

// AL: all the member variables should be initialized in the constructor, init _mmGoal and _mGridsize here, otherwise, don't create this constructor, use '= default` instead
nsolver::nsolver()
{
}

nsolver::nsolver(node const & n)
    : _mGridsize(n.gridsize)
{
    // _mGoal = make_node(_mGridsize);
    // this->setGoal();
    // AL: put _mFirstNode initialization in initialization list
    _mFirstNode = std::make_shared<node>(n);
    setmGoal();
}

nsolver::~nsolver()
{
    delete[] _mmGoal;
}

void    nsolver::print(node const & n)
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            std::cout << std::left << std::setw(5) << n.array[i][j];
        std::cout << std::endl;
    }
}

// AL: is this function used?
const node & nsolver::getGoal() const
{
    return (*_mGoal);
}

const std::shared_ptr<node> &  nsolver::getOpen() const
{
    return (_mOpen.top());
}

const node & nsolver::getFirstNode() const{
    return(*_mFirstNode);
}

void    nsolver::setmGoal()
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
    _mmGoal = grid ;
}

void    nsolver::setOpen(std::shared_ptr<node> const & n)
{
    _mOpen.push(n);
}

void    nsolver::manhattan(std::shared_ptr<node> & n)
{
    int h = n->prev? n->h : 0;
    if (!n->prev)
    {
        for (int y=0; y < _mGridsize; y++)
        {
            for (int x = 0; x < _mGridsize; x++)
            {
                if (n->array[y][x] != 0)
                {
                    h += abs(y - _mmGoal[n->array[y][x]].first);
                    h += abs(x - _mmGoal[n->array[y][x]].second);
                }
            }
        }
    }
    else 
    {
        int tmp, tmp2;
        if (n->prev->x == n->x)
        {
            tmp = abs(n->y - _mmGoal[n->prev->array[n->y][n->x]].first);
            tmp2 = abs(n->prev->y - _mmGoal[n->prev->array[n->y][n->x]].first);
        }
        else
        {
            tmp = abs(n->x - _mmGoal[n->prev->array[n->y][n->x]].second);
            tmp2 = abs(n->prev->x - _mmGoal[n->prev->array[n->y][n->x]].second);
        }
        if (tmp != tmp2)
            tmp < tmp2 ? h++ : h--;
    }
    n->h = h;
}

void    nsolver::euclidean(std::shared_ptr<node> & n)
{
    float h = 0;
    for (int y=0; y < _mGridsize; y++)
    {
        for (int x=0, tmp1 =0, tmp2 = 0; x < _mGridsize; x++)
        {
            if (n->array[y][x] != 0)
            {
                tmp1 = abs(_mmGoal[n->array[y][x]].first - y);
                tmp2 = abs(_mmGoal[n->array[y][x]].second - x);
                h += sqrt((tmp1 * tmp1) + (tmp2 * tmp2));
            }        
        }
    }
    n->h = h;  
}

// AL: no need to us shared_ptr here as well, use 'node&'
void    nsolver::hamming(std::shared_ptr<node> & n)
{
    int h = 0;
    // AL: if you used std::vector<> instead of int**, you could use std::accumulate
    for (int y = 0; y < _mGridsize; y++)
    {
        for (int x = 0; x < _mGridsize; x++)
            n->array[y][x] != _mGoal->array[y][x] ? h++ : h = h;
    }

}

void    nsolver::setH(std::shared_ptr<node> & n)
{
    void    (nsolver::*p2f[])(std::shared_ptr<node> & n) = {&nsolver::manhattan, &nsolver::euclidean, &nsolver::hamming};
    (this->*p2f[n->heuristic])(n);
}

std::shared_ptr<node>  nsolver::copyNode(std::shared_ptr<node> const & n){
    std::shared_ptr<node> copy = make_node(_mGridsize);

    node tmp = *n;
    copy->g = tmp.g;
    copy->h = tmp.h;
    copy->x = tmp.x;
    copy->y = tmp.y;
    copy->heuristic = tmp.heuristic;
    copy->prev = n;

    for (int y = 0; y < _mGridsize; y++)
    {
        for (int x = 0; x < _mGridsize; x++)
            copy->array[y][x] = tmp.array[y][x];
    }
    return copy;
}

void    nsolver::move_up(node & n)
{
    if (n.y > 0)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y - 1][n.x]);
        n.y--;
    }
}

void    nsolver::move_down(node & n)
{
    if (n.y < _mGridsize -1)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y + 1][n.x]);
        n.y++;
    }
}

void    nsolver::move_left(node & n)
{
    if (n.x > 0)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y][n.x - 1]);
        n.x--;
    }
}

void    nsolver::move_right(node & n)
{
    if (n.x < _mGridsize -1)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y][n.x + 1]);
        n.x++;
    }
}

void nsolver::movements(std::shared_ptr<node> const & n, moves m)
{
    void    (nsolver::*p2f[])(node &n) = {&nsolver::move_up, &nsolver::move_down, &nsolver::move_left, &nsolver::move_right};

    std::shared_ptr<node>    tmp = copyNode(n);

    tmp->g++;
    (this->*p2f[m])(*tmp);
    setH(tmp);
    if (_mClosed.find(tmp) == _mClosed.end()) {
        setOpen(tmp);
        _mClosed.insert(tmp);
    }
}

void nsolver::puzzle()
{
    std::shared_ptr<node>    n;

    n = _mFirstNode;
    setH(n);
    setOpen(n);
    for (;n->h != 0; n = getOpen())
    {
        _mOpen.pop();
        // AL: this condition is redundant, as you already have 'n->h != 0' in the 'for' loop
        if (n->h == 0)
            break;
        if ((!(n->prev)) || (n->x < _mGridsize -1 && n->h != 0 && n->prev->x != n->x +1))
            movements(n, RIGHT);
        if ((!(n->prev)) || (n->y > 0 && n->h != 0 && n->prev->y != n->y -1))
            movements(n, UP);
        if ((!(n->prev)) || (n->y < _mGridsize -1 && n->h != 0 && n->prev->y != n->y +1))
            movements(n, DOWN);
        if ((!(n->prev)) || (n->x > 0 && n->h != 0 && n->prev->x != n->x -1))
            movements(n, LEFT);
        _mClosed.insert(n);
    }
    for (; n; n = n->prev)
    {
        std::cout << "________________\n";
        print(*n);
    }
}