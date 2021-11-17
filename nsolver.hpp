/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:51:58 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/17 17:02:12 by eutrodri      ########   odam.nl         */
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
# include <deque>

enum moves {
  UP = 0,
  DOWN, 
  LEFT,
  RIGHT
};

struct hash_X{
  uint64_t operator()(const std::vector<std::vector<int> > &x) const {
    // size_t hash = 4;
    uint64_t hash = 3131313131;

    for (auto i : x) {
      for (auto j : i) {
         hash ^= j + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        // hash ^= std::hash<int>()(j);
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

    std::unique_ptr<node>  copyNode(const node& n);
    
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
    std::deque<std::unique_ptr<node> >                                                     _mViseted;
    std::priority_queue<node*, std::vector<node*>, F >                                      _mOpen;
    std::unordered_map<uint64_t, int>                                                       _mClosed;
};


#endif
