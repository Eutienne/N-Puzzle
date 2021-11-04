/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   npuzzle.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 18:24:35 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/04 21:46:20 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include "node.hpp"

# include <string>
# include <iostream>
# include <fstream>
# include <memory>
// # include <queue>
// # include <set>


struct  node;

// struct  F
// {
//     bool    operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b);
// };

// struct  Puzzle{
//     bool operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b)
//     {
//         for (int y = 0; a->array[y] || b->array[y]; y++)
//         {
//             for (int x = 0; a->array[y][x] || b->array[y][x]; x++)
//             {
//                 if (!(a->array[y][x] || b->array[y][x]) || (a->array[y][x] == b->array[y][x]))
//                     return (false);
//             }
//         }
//         return (true);
//     }
// };

class   npuzzle{
    public:
        npuzzle();
        ~npuzzle();
        
        const node &  getNode() const;
        void    setNode(std::ifstream & file);
        void    print(node const & n);
        // std::shared_ptr<node> copyNode(std::shared_ptr<node> const & n);
        // void    setNode(std::shared_ptr<node> const & n);
        // const std::shared_ptr<node> &  getNode() const;
        // void    setGoal();
        // const node &    getGoal() const;
        // void    setH(std::shared_ptr<node> & n);
        // void    move_up(node & n);
        // void    move_down(node & n);
        // void    move_left(node & n);
        // void    move_right(node & n);
        // void    puzzle();
        // void    movements(std::shared_ptr<node> const & n, std::string s);
        // bool    getGameover();
        // void    setGameover(bool b);

    private:
        int                                                 _mGridsize;
        std::shared_ptr<node>                               _mNode;
        // bool                                                _mGameover;
        // std::shared_ptr<node>                               _mFirstNode;
        // std::shared_ptr<node>                               _mGoal;
        // std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, F>     _mNode;
        // std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, F>     _mNode2;
        // std::set<std::shared_ptr<node>, Puzzle>                                                _mClosed;
};

#endif
