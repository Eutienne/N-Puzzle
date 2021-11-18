/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:56:34 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/18 22:20:47 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nsolver.hpp"

bool    F::operator()(node * a, node * b) const
{
    // if (a->distance == b->distance)
    if (a->distance + a->gen == b->gen + b->distance)
        return (!(a->distance < b->distance));
        // return (!(a->gen < b->gen));
    return (!(a->distance + a->gen < b->gen + b->distance));
    // return (!(a->distance < b->distance));
}

nsolver::nsolver() = default;


nsolver::nsolver(const node & n)
    : _mGridsize(n.gridsize), _mFirstNode(const_cast<node*>(&n))
{
    setGoal();
}

nsolver::~nsolver()
{
    delete[] _mGoal;
}

void    nsolver::printS() const
{
    for (int i = _mSolution.size() -1; i >= 0; i--)
        print(*_mSolution[i]);
    std::cout << "complexity in time: " << _mCtime << std::endl;
    std::cout << "complexity in size: " << _mCsize << std::endl;
    std::cout << "number of moves: " << _mCmoves << std::endl;
    // std::cout << "solved in: " << _mTime << "ms" << std::endl;
}

void    nsolver::print(node const & n) const
{
    for (int y = 0; y < _mGridsize; y++)
    {
        std::cout << std::left << std::setw(3) << " (";
        for (int x = 0; x < _mGridsize; x++)
            std::cout << std::left << std::setw(3) << n.array[y][x];
        std::cout << ")" << std::endl;
    }
    std::cout << std::endl;
}

// std::pair<int, int> & nsolver::getGoal() const
// {
//     return (*_mGoal);
// }

node &   nsolver::getOpen() const
{
    return (*_mOpen.top());
}

const node & nsolver::getFirstNode() const{
    return(*_mFirstNode);
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

void    nsolver::setOpen(node * n)
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
    // switch (n.heuristic)
    // {
    // case 0:
    //     manhattan(n);
    //     break;
    // case 1:
    //     euclidean(n);
    //     break;
    // default:
    //     hamming(n);
    //     break;
    // }
}

std::unique_ptr<node>  nsolver::copyNode(const node & n){
    std::unique_ptr<node> copy(make_node(_mGridsize));

    *copy = n;
    copy->prev = const_cast<node*>(&n);
    return std::move(copy);
}

void nsolver::movements(const node & n, moves m)
{
    hash_X X;
    uint64_t s;
    std::unique_ptr<node>    tmp = copyNode(n);
    
    switch (m)
    {
    case 0:
        tmp->move_up();
        break;
    case 1:
        tmp->move_down();
        break;
    case 2:
        tmp->move_left();
        break;
    default:
        tmp->move_right();
        break;
    }
    setH(*tmp);
    s = X.operator()(tmp->array);
    auto it = _mClosed.find(s);
    if (it == _mClosed.end() || it->second > tmp->gen) {
        setOpen(&(*tmp));
        if (it == _mClosed.end())
            _mClosed.insert(std::make_pair(s, tmp->gen));
        else
            it->second = tmp->gen;        
        _mViseted.push_back(std::move(tmp));
    }
}

void nsolver::puzzle()
{
    node    *n;
    hash_X  X;
    int     i;

    n = _mFirstNode;
    n->prev = NULL;
    setH(*n);
    setOpen(n);
    _mClosed.insert(std::make_pair(X.operator()(n->array), n->gen));
    for (i = 0;n->distance != 0; n = &getOpen())
    {
        i++;
        _mOpen.pop();
        if (((!n->prev) || n->prev->x != n->x +1) && n->x < _mGridsize -1)
            movements(*n, RIGHT);
        if (((!n->prev) || n->prev->y != n->y -1) && n->y > 0)
            movements(*n, UP);
        if (((!n->prev) ||n->prev->y != n->y +1) && n->y < _mGridsize -1)
            movements(*n, DOWN);
        if (((!n->prev) || n->prev->x != n->x -1) && n->x > 0)
            movements(*n, LEFT);
    }
    _mCmoves = n->gen;
    _mCtime = _mViseted.size();
    _mCsize = i;

    for (int i = 0; i < n->gen; n = n->prev)
        _mSolution.push_back(n);
}