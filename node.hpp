/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:51:10 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/26 16:52:29 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP
# include <memory>
# include <sstream>
# include <vector>
# include <memory>
# include <algorithm>

# define MA (1 << 0)
# define EU (1 << 1)
# define HA (1 << 2)
# define A_STAR (1 << 3)
# define GR (1 << 4)
# define UN (1 << 5)
# define VB (1 << 6)


struct   node{

    node();
    ~node();
    node &   operator=(const node & n);
    bool     operator<(const node & a) const;
    bool     operator==(const node & a) const;

    void    move_up();
    void    move_down();
    void    move_left();
    void    move_right();

    std::vector<std::vector<int> >  array;
    int             gen, distance, x, y, gridsize;
    char            FLAGS;
    char            move;
    struct node*    prev;
};

std::unique_ptr<node> make_node(int grid);



#endif