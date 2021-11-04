/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:56:34 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/04 22:32:35 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nsolver.hpp"

bool    F::operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b)
{
        return (a->h + a->g  > b->h + b->g);
}

bool Puzzle::operator()(const std::shared_ptr<node>& a, const std::shared_ptr<node>& b)
{
        return (a->array != b->array);
}

nsolver::nsolver()
{
}

nsolver::nsolver(node const & n)
    : _mGridsize(n.gridsize)
{
    _mGoal = make_node(_mGridsize);
    this->setGoal();
    _mFirstNode = std::make_shared<node>(n);

}

nsolver::~nsolver()
{
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

void    nsolver::setGoal()
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            _mGoal->array[i][j] = 0;
    }
    for (int i = 0, j = 0, n = 1; _mGoal->array[i] && _mGoal->array[i][j] == 0 && n < _mGridsize * _mGridsize;)
    {
        for (; j < _mGridsize && _mGoal->array[i][j] == 0; j++, n++)
            _mGoal->array[i][j] = n; 
        j--; i++;
        for (; i < _mGridsize && _mGoal->array[i][j] == 0; i++, n++)
            _mGoal->array[i][j] = n;
        i--; j--;
        for (; j > -1 && _mGoal->array[i][j] == 0; j--, n++)
            _mGoal->array[i][j] = n;
        j++; i--;
        for (; i > -1 && _mGoal->array[i][j] == 0; i--, n++)
            _mGoal->array[i][j] = n;
        i++; j++;
    }
    _mGoal->y = _mGridsize/2;
    _mGridsize % 2 == 0 ? _mGoal->array[_mGridsize / 2][(_mGridsize / 2) -1] = 0 : _mGoal->array[_mGridsize / 2][(_mGridsize / 2)] = 0;
    _mGridsize % 2 == 0 ? _mGoal->x = (_mGridsize / 2) -1 : _mGoal->x = _mGridsize / 2;
}

void    nsolver::setOpen(std::shared_ptr<node> const & n)
{
    _mOpen.push(n);
}

void    nsolver::setH(std::shared_ptr<node> & n)
{
    int h = 0;
    for (int i=0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
        {
            for (int y=0; j < _mGridsize && y < _mGridsize && n->array[i][j] != 0; y++)
            {
                for (int x=0; x < _mGridsize; x++)
                {
                    if (n->array[i][j] == _mGoal->array[y][x])
                    {
                        y > i ? h += y - i : h += i - y;
                        x > j ? h += x - j : h += j - x;
                        break;
                    }
                }
            }
        }
    }
    n->h = h;
}

std::shared_ptr<node>  nsolver::copyNode(std::shared_ptr<node> const & n){
    std::shared_ptr<node> copy = make_node(_mGridsize);

    node tmp = *n;
    copy->g = tmp.g;
    copy->h = tmp.h;
    copy->x = tmp.x;
    copy->y = tmp.y;
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

void nsolver::movements(std::shared_ptr<node> const & n, std::string s)
{
    std::string moves[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
    void    (nsolver::*p2f[])(node &n) = {&nsolver::move_up, &nsolver::move_down, &nsolver::move_left, &nsolver::move_right};

    std::shared_ptr<node>    tmp = copyNode(n);

    for (int i = 0; i < 4; i++)
    {
        if (moves[i] == s)
        {
            tmp->g++;
            (this->*p2f[i])(*tmp);
            setH(tmp);
            if (_mClosed.find(tmp) == _mClosed.end()) {
                setOpen(tmp);
                _mClosed.insert(tmp);
            }
            break;
        }
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
        if (n->h == 0)
            break;
        if ((!(n->prev)) || (n->x < _mGridsize -1 && n->h != 0 && n->prev->x != n->x +1))
            movements(n, "RIGHT");
        if ((!(n->prev)) || (n->y > 0 && n->h != 0 && n->prev->y != n->y -1))
            movements(n, "UP");
        if ((!(n->prev)) || (n->y < _mGridsize -1 && n->h != 0 && n->prev->y != n->y +1))
            movements(n, "DOWN");
        if ((!(n->prev)) || (n->x > 0 && n->h != 0 && n->prev->x != n->x -1))
            movements(n, "LEFT");
        _mClosed.insert(n);
    }
    for (; n; n = n->prev)
    {
        std::cout << "________________\n";
        print(*n);
    }
}