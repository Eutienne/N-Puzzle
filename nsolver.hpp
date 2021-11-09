/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:51:58 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/09 17:45:00 by eutrodri      ########   odam.nl         */
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

struct  F
{
    bool    operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b);
};

struct  Puzzle{
    bool operator()(const std::shared_ptr<node>& a, const std::shared_ptr<node>& b);
};


class nsolver
{
public:
    nsolver(node const & n);
    ~nsolver();

    std::shared_ptr<node> copyNode(std::shared_ptr<node> const & n);
    
    void    print(node const & n);
    void    manhattan(std::shared_ptr<node> & n);
    void    euclidean(std::shared_ptr<node> & n);
    void    hamming(std::shared_ptr<node> & n);
    void    move_up(node & n);
    void    move_down(node & n);
    void    move_left(node & n);
    void    move_right(node & n);
    void    movements(std::shared_ptr<node> const & n, moves m);
    void    puzzle();


    void    setOpen(std::shared_ptr<node> const & n);
    void    setH(std::shared_ptr<node> & n);
    void    setGoal();
    void    setmGoal();
    
    const std::shared_ptr<node> &   getOpen() const;
    const node &                    getGoal() const;
    const node &                    getFirstNode() const;


private:
    nsolver();
    int                                                                                     _mGridsize;
    std::shared_ptr<node>                                                                   _mFirstNode;
    std::shared_ptr<node>                                                                   _mGoal;
    std::pair<int,int>*                                                                     _mmGoal;
    std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, F>      _mOpen;
    std::set<std::shared_ptr<node>, Puzzle>                                                 _mClosed;
};


#endif
