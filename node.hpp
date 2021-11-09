/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:51:10 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/09 16:28:35 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP
# include <memory>
# include <sstream>

enum heuristics {
  MANHATTAN = 0,
  EUCLIDEAN, 
  HAMMING
};

struct   node{

// AL: operator= should return 'node&' not 'const node&'
    node const &   operator=(node & n);

// AL: use 'std::vector<std::vector<int>>' and you'll get 'operator =' for free
    int  **array;
    // AL: use valuable names for the members, I don't get what 'g' and 'h' mean
    int             g, h, x, y, gridsize;
    heuristics      heuristic;
    std::shared_ptr<struct node>    prev;
};

std::shared_ptr<node>  make_node(int grid);



#endif