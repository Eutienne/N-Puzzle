/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:51:10 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/18 18:22:30 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP
# include <memory>
# include <sstream>
# include <vector>
# include <memory>
# include <algorithm>

enum heuristics {
  MANHATTAN = 0,
  EUCLIDEAN, 
  HAMMING
};

struct   node{

    node();
    ~node();
    node &   operator=(const node & n);
    bool     operator<(const node & a) const;

    void    move_up();
    void    move_down();
    void    move_left();
    void    move_right();

    std::vector<std::vector<int> >  array;
    int             gen, distance, x, y, gridsize;
    heuristics      heuristic;
    struct node*           prev;
};

node * make_node(int grid);
// std::shared_ptr<node>  make_node(int grid);



#endif