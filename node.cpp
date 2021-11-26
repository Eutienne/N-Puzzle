/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:57:46 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/26 17:03:01 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.hpp"

std::unique_ptr<node> make_node(int grid)
{
    std::unique_ptr<node> n = std::make_unique<node>();
    n->array.resize(grid, std::vector<int>(grid,0));
    n->prev = nullptr;
    return (std::move(n));
}

node::node()
    : prev(NULL), gen(0), distance(0), x(0), y(0), gridsize(0), FLAGS(0), move('0')
{
}

node::~node()
{
}

bool     node::operator<(const node & a) const
{
    return (this->array < a.array);
}

node &   node::operator=(const node & n)
{
    this->FLAGS = n.FLAGS;
    this->gen = n.gen;
    this->distance = n.distance;
    this->x = n.x;
    this->gridsize = n.gridsize;
    this->y = n.y;
    this->move = n.move;
    this->array = n.array;
    this->prev = n.prev;

    return *this;
}

void    node::move_up()
{
    if (this->y > 0)
    {
        std::swap(this->array[this->y][this->x], this->array[this->y - 1][this->x]);
        this->y--;
        this->gen++;
        this->move = 'U';
    }
}

void    node::move_down()
{
    if (this->array[this->y + 1][this->x])
    {
        std::swap(this->array[this->y][this->x], this->array[this->y + 1][this->x]);
        this->y++;
        this->gen++;
        this->move = 'D';
    }
}

void    node::move_left()
{
    if (this->x > 0)
    {
        std::swap(this->array[this->y][this->x], this->array[this->y][this->x - 1]);
        this->x--;
        this->gen++;
        this->move = 'L';
    }
}

void    node::move_right()
{
    if (this->array[this->y][this->x + 1])
    {
        std::swap(this->array[this->y][this->x], this->array[this->y][this->x + 1]);
        this->x++;
        this->gen++;
        this->move = 'R';
    }
}