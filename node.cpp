/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:57:46 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/10 19:08:35 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.hpp"
#include <iostream>

std::shared_ptr<node>  make_node(int grid)
{
    std::shared_ptr<node> n = std::make_shared<node>();
    n->array.resize(grid, std::vector<int>(grid,0));
    return (n);
}

bool     node::operator<(const node & a) const
{
    std::cout << " A" << std::endl;
    return (this->distance < a.distance);
}


node &   node::operator=(node & n)
{
    this->gen = n.gen;
    this->distance = n.distance;
    this->x = n.x;
    this->gridsize = n.gridsize;
    this->y = n.y;
    this->array = n.array;

    return *this;
}