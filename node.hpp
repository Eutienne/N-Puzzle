/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:51:10 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/10 19:05:03 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP
# include <memory>
# include <sstream>
# include <vector>

enum heuristics {
  MANHATTAN = 0,
  EUCLIDEAN, 
  HAMMING
};

struct   node{

    node &   operator=(node & n);
    bool     operator<(const node & a) const;

    std::vector<std::vector<int> >  array;
    int             gen, distance, x, y, gridsize;
    heuristics      heuristic;
    std::shared_ptr<struct node>    prev;
};

std::shared_ptr<node>  make_node(int grid);



#endif