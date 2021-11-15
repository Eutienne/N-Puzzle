/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:51:58 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/15 21:49:00 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSOLVER_HPP
# define NSOLVER_HPP

# include "node.hpp"

# include <queue>
# include <unordered_map>
# include <iostream>
# include <iomanip>
# include <math.h>
# include<functional>

enum moves {
  UP = 0,
  DOWN, 
  LEFT,
  RIGHT
};

struct hash_X{
  size_t operator()(const std::vector<std::vector<int> > &x) const {
    size_t hash = 3131313131;

    for (auto i : x) {
      for (auto j : i) {
        hash ^= std::hash<int>()(j);
      }
    }

    return hash;
  }
};

struct  F
{
    bool    operator()(node * a, node * b) const;
};

class nsolver
{
public:
    nsolver(const node & n);
    ~nsolver();

    node &  copyNode(const node& n);
    
    void    print(node const & n) const;
    void    manhattan(node & n) const;
    void    euclidean(node & n) const;
    void    hamming(node & n) const;
    void    move_up(node & n) const;
    void    move_down(node & n) const;
    void    move_left(node & n) const;
    void    move_right(node & n) const;
    void    movements(const node & n, moves m);
    void    puzzle();


    void    setOpen(node * n);
    void    setH(node & n) const;
    void    setGoal();
    
    node &    getOpen() const;
    // const node &                    getGoal() const;
    const node &                    getFirstNode() const;


private:
    nsolver();
    int                                                                                     _mGridsize;
    node*                                                                                   _mFirstNode;
    std::pair<int,int>*                                                                     _mGoal;
    std::queue<node*>                                                                       _mViseted;
    std::priority_queue<node*, std::vector<node*>, F >                       _mOpen;
    std::unordered_map<std::vector<std::vector<int> >, int, hash_X>                         _mClosed;
    // std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, F>      _mOpen;
};


#endif
