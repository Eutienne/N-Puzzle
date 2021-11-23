/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nsolver.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 17:51:58 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/23 21:52:29 by eutrodri      ########   odam.nl         */
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
# include <deque>
# include <memory>

enum moves {
  UP = 0,
  DOWN, 
  LEFT,
  RIGHT
};

enum heuristics {
  MANHATTAN = 0,
  EUCLIDEAN, 
  HAMMING
};

struct Solution{
  Solution()
    : _mCtime(0), _mCsize(0), _mCmoves(0){}
  int _mCtime, _mCsize, _mCmoves;
  std::vector<node*>    _mStaps;
};

struct hash_X{
  uint64_t operator()(const std::vector<std::vector<int> > &x) const {
    uint64_t hash = 3131313131;

    for (auto i : x) {
      for (auto j : i) {
         hash ^= j + 0x9e3779b9 + (hash << 6) + (hash >> 2);
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
    
    void    manhattan(node & n) const;
    void    euclidean(node & n) const;
    void    hamming(node & n) const;
  
    void    movements(const node & n, moves m);
    void    puzzle();

    void    print(node const & n) const;
    void    printS() const;

    void    setOpen(node * n);
    void    setH(node & n) const;
    void    setGoal();
    void    setSolution(node * n, int size);
    void    isSolveble();
    
    node &    getOpen() const;
    const node &                    getFirstNode() const;
    // const node &                    getGoal() const;


private:
    nsolver();
    heuristics                                                                              _mHeuristic;
    int                                                                                     _mGridsize;
    node*                                                                                   _mFirstNode;
    std::vector<std::pair<int,int> >                                                        _mGoal;
    std::deque<std::unique_ptr<node> >                                                      _mViseted;
    std::priority_queue<node*, std::vector<node*>, F >                                      _mOpen;
    std::set<node>		                                                        			        _mClosed;
    Solution                                                                                _mSolution;
    
};


#endif
