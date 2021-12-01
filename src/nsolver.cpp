/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:56:34 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/12/01 14:00:44 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/nsolver.hpp"

bool    F::operator()(node * a, node * b) const
{
    if (a->distance + a->gen == b->gen + b->distance || a->FLAGS & GR)
        return (!(a->distance < b->distance));
    else if (a->FLAGS & UN)
        return (!(a->gen < b->gen));
    return (!(a->distance + a->gen < b->gen + b->distance));
}

nsolver::nsolver() = default;


nsolver::nsolver(const node & n)
    : _mGridsize(n.gridsize), _mFirstNode(const_cast<node*>(&n)), _mHeuristic(MANHATTAN)
{
    if (n.FLAGS & EU) 
        _mHeuristic = EUCLIDEAN;
    else if (n.FLAGS & HA)
        _mHeuristic  = HAMMING;
    setGoal();
    isSolveble();

}

nsolver::~nsolver()
{
}

void    nsolver::isSolveble()
{
    std::vector<int>    init;
    std::vector<int>    goal;
    int                 inversions=0;
    int                 tmp;

    goal.resize(_mGridsize*_mGridsize);

    for (int i = 0; i < _mGridsize * _mGridsize; i++)
        goal[i] = _mGoal[i].first * _mGridsize + _mGoal[i].second +1;
    
    for (int y = 0; y < _mGridsize; y++)
    {
        for (int x = 0; x < _mGridsize; x++){
            init.push_back(goal[_mFirstNode->array[y][x]]);
        }
    }

    for (int i = 0, x =init.size() ; i < x; i++){
        for (int j = i+1; j < x; j++){
            if (init[j] < init[i])
                inversions++;
        }
    }
    tmp = abs(_mFirstNode->y - _mGoal[0].first);
    tmp += abs(_mFirstNode->x - _mGoal[0].second);
    if (inversions % 2 != tmp %2)
        throw std::runtime_error("unsolveble puzzle");
}


void    nsolver::printS() const
{
    for (int i = _mSolution._mStaps.size() -1; i >= 0; i--){
        std::cout << BOLDGREEN << "Step: " << _mSolution._mStaps[i]->gen << "     Move: " << _mSolution._mStaps[i]->move << std::endl;
        print(*_mSolution._mStaps[i]);}
    std::cout << BOLDYELLOW << "complexity in time: " << _mSolution._mCtime << std::endl;
    std::cout << "complexity in size: " << _mSolution._mCsize << std::endl;
    std::cout << "number of moves: " << _mSolution._mCmoves << RESET << std::endl;
}

void    nsolver::print(node const & n) const
{
    for (int y = 0; y < _mGridsize; y++)
    {
        std::cout << BOLDCYAN << std::left << std::setw(3) << " (";
        for (int x = 0; x < _mGridsize; x++)
            std::cout << std::left << std::setw(4) << n.array[y][x];
        std::cout << ")" << std::endl;
    }
    std::cout << RESET << std::endl;
}

node &   nsolver::getOpen() const
{
    return (*_mOpen.top());
}

const node & nsolver::getFirstNode() const{
    return(*_mFirstNode);
}

void    nsolver::setGoal()
{
    _mGoal.resize(_mGridsize*_mGridsize, std::pair<int, int>());
    if (_mGridsize % 2 == 0)
        _mGoal[0] =  std::make_pair(_mGridsize / 2, (_mGridsize / 2) -1);
    else
        _mGoal[0] = std::make_pair(_mGridsize / 2, (_mGridsize / 2));
    for (int counter = _mGridsize, n = 1, y = 0, x = 0, min = -1; n < _mGridsize * _mGridsize;)
    {
        for(; x < counter && n < _mGridsize * _mGridsize; x++, n++)
            _mGoal[n] = std::make_pair(y, x);
        x--; y++;
        for(;y < counter && n < _mGridsize * _mGridsize; y++, n++)
            _mGoal[n] = std::make_pair(y, x);
        x--; y--; counter--;
        for (;x > min && n < _mGridsize * _mGridsize; x--, n++)
            _mGoal[n] = std::make_pair(y, x);
        x++; y--; min++;
        for (;y > min && n < _mGridsize * _mGridsize; y--, n++)
            _mGoal[n] = std::make_pair(y, x);
        x++; y++;
    }
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
            _mGoal[n.array[y][x]].first == y && _mGoal[n.array[y][x]].second == x ? h = h : h++;
    }
    n.distance = h;
}

void    nsolver::setH(node & n) const
{
    switch (_mHeuristic)
    {
    case 0:
        manhattan(n);
        break;
    case 1:
        euclidean(n);
        break;
    default:
        hamming(n);
        break;
    }
}

void    nsolver::setSolution(node * n, int size)
{
    node *tmp = n;
    _mSolution._mCmoves = n->gen;
    _mSolution._mCsize = size;
    for (int i = 0; i < tmp->gen; tmp = tmp->prev)
        _mSolution._mStaps.push_back(tmp);
    _mSolution._mStaps.push_back(tmp);
}


std::unique_ptr<node>  nsolver::copyNode(const node & n){
    std::unique_ptr<node> copy(make_node(_mGridsize));

    *copy = n;
    copy->prev = const_cast<node*>(&n);
    return std::move(copy);
}

void nsolver::movements(const node & n, moves m)
{
    std::unique_ptr<node>    tmp = copyNode(n);
    hash_X  X;
    uint64_t s;
    
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
    
    n = _mFirstNode;
    n->prev = NULL;
    setH(*n);
    setOpen(n);
    _mClosed.insert(std::make_pair(X.operator()(n->array), n->gen));
    for (;n->distance != 0; n = &getOpen())
    {
        _mSolution._mCtime++;
        if (n->FLAGS & VB)
            print(*n);
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
    setSolution(n, _mClosed.size());
}