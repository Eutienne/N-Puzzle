/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   npuzzle.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 18:24:35 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/03 21:38:24 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <string>
// # include <ncurses.h>
# include <iostream>
# include <fstream>
# include <sstream>
# include <memory>
# include <queue>
# include <set>

// enum colors {
//   number_color = 1,
//   zero_color, 
//   blank_color,
//   b_and_w
// };

// struct  screen
// {
//     int mY , mX, mHeight, mWidth, mBegY, mBegX, mStartY, mStartX;
// };

struct  node
{
    
    node const &   operator=(node & n)
    {
        int i = 0;
        this->g = n.g;
        this->h = n.h;
        this->x = n.x;
        this->y = n.y;

        for (; this->array[i] != NULL; i++);
        std::copy(&n.array[0][0], &n.array[0][0]+(i+1)*(i+1), &this->array[0][0]);
        return *this;
    }
    int  **array;
    int             g, h, x, y;
    std::shared_ptr<struct node>    prev;
};

struct  F
{
    bool    operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b)
    {
        return (a->h + a->g  > b->h + b->g);
    }
};

struct  Puzzle{
    bool operator()(std::shared_ptr<node>& a, std::shared_ptr<node>& b)
    {
        for (int y = 0; a->array[y] || b->array[y]; y++)
        {
            for (int x = 0; a->array[y][x] || b->array[y][x]; x++)
            {
                if (!(a->array[y][x] || b->array[y][x]) || (a->array[y][x] == b->array[y][x]))
                    return (false);
            }
        }
        return (true);
    }
};

// class   display{
//     public:
//         display();
//         ~display();
        

//         void    setup();
//         void    draw(node const & N);
//         void    pallet();

//     private:
//         screen                                              _mScreen;
//         int                                                 _mGridsize;        
// };

class   npuzzle{
    public:
        npuzzle();
        ~npuzzle();
        
        const node &  getFirstNode() const;
        std::shared_ptr<node> copyNode(std::shared_ptr<node> const & n);
        void    setFirstNode(std::ifstream & file);
        void    setNode(std::shared_ptr<node> const & n);
        const std::shared_ptr<node> &  getNode() const;
        int  getNodeSize() const;
        void    setGoal();
        const node &    getGoal() const;
        void    print(node const & n);
        void    setH(std::shared_ptr<node> & n);
        void    move_up(node & n);
        void    move_down(node & n);
        void    move_left(node & n);
        void    move_right(node & n);
        void    puzzle();
        void    movements(std::shared_ptr<node> const & n, std::string s);
        bool    getGameover();
        void    setGameover(bool b);

    private:
        bool                                                _mGameover;
        int                                                 _mGridsize;
        std::shared_ptr<node>                               _mFirstNode;
        std::shared_ptr<node>                               _mGoal;
        std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, F>     _mNode;
        std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, F>     _mNode2;
        // std::set<std::shared_ptr<node>, Puzzle>                                                _mClosed;
};

#endif
