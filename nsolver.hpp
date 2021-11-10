/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:51:58 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/10 19:33:54 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSOLVER_HPP
# define NSOLVER_HPP

# include "node.hpp"

# include <queue>
# include <set>
# include <iostream>
# include <iomanip>
# include <math.h>

enum moves {
  UP = 0,
  DOWN, 
  LEFT,
  RIGHT
};

// struct  F
// {
//     bool    operator()(const std::shared_ptr<node>& a, const std::shared_ptr<node>& b) const;
// };

struct  Puzzle{
    bool operator()(const std::shared_ptr<node>& a, const std::shared_ptr<node>& b) const;
};


class nsolver
{
public:
    nsolver(node const & n);
    ~nsolver();

    std::shared_ptr<node> copyNode(std::shared_ptr<node> const & n);
    
    void    print(node const & n) const;
    void    manhattan(node & n) const;
    void    euclidean(node & n) const;
    void    hamming(node & n) const;
    void    move_up(node & n) const;
    void    move_down(node & n) const;
    void    move_left(node & n) const;
    void    move_right(node & n) const;
    void    movements(std::shared_ptr<node> const & n, moves m);
    void    puzzle();


    void    setOpen(std::shared_ptr<node> const & n);
    void    setH(std::shared_ptr<node> & n) const;
    void    setGoal();
    
    const std::shared_ptr<node> &   getOpen() const;
    // const node &                    getGoal() const;
    const node &                    getFirstNode() const;


private:
    nsolver();
    int                                                                                     _mGridsize;
    std::shared_ptr<node>                                                                   _mFirstNode;
    std::pair<int,int>*                                                                     _mGoal;
    std::priority_queue<std::reference_wrapper<std::shared_ptr<node> > >   _mOpen;
    // std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, F>      _mOpen;
    std::set<std::shared_ptr<node>, Puzzle>                                                 _mClosed;
};


#endif
