/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:57:46 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/04 18:37:43 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.hpp"

std::shared_ptr<node>  make_node(int grid)
{
    std::shared_ptr<node> n = std::make_shared<node>();
    n->array = new int*[grid+1];
    n->array[grid] = NULL;
    for (int i = 0; i < grid; i++)
        n->array[i] = new int[grid];
    return (n);
}

node const &   node::operator=(node & n)
{
    int i = 0;
    this->g = n.g;
    this->h = n.h;
    this->x = n.x;
    this->gridsize = n.gridsize;
    this->y = n.y;

    for (; this->array[i] != NULL; i++);
    std::copy(&n.array[0][0], &n.array[0][0]+(i+1)*(i+1), &this->array[0][0]);
    return *this;
}