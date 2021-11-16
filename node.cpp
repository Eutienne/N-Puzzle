/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:57:46 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/16 21:28:26 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.hpp"
#include <iostream>

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