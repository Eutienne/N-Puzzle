/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:57:46 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/18 14:35:20 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.hpp"

node * make_node(int grid)
{
    node *n = new node();
    n->array.resize(grid, std::vector<int>(grid,0));
    n->prev = nullptr;
    return (n);
}

node::node()
    : prev(NULL), gen(0), distance(0), x(0), y(0), gridsize(0), heuristic(MANHATTAN)
{
}

node::~node()
{
}

bool     node::operator<(const node & a) const
{
    return (this->distance < a.distance);
}

node &   node::operator=(const node & n)
{
    this->gen = n.gen;
    this->distance = n.distance;
    this->x = n.x;
    this->gridsize = n.gridsize;
    this->y = n.y;
    this->heuristic = n.heuristic;
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
    }
}

void    node::move_down()
{
    if (this->array[this->y + 1][this->x])
    {
        std::swap(this->array[this->y][this->x], this->array[this->y + 1][this->x]);
        this->y++;
        this->gen++;
    }
}

void    node::move_left()
{
    if (this->x > 0)
    {
        std::swap(this->array[this->y][this->x], this->array[this->y][this->x - 1]);
        this->x--;
        this->gen++;
    }
}

void    node::move_right()
{
    if (this->array[this->y][this->x + 1])
    {
        std::swap(this->array[this->y][this->x], this->array[this->y][this->x + 1]);
        this->x++;
        this->gen++;
    }
}