/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   npuzzle.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 18:24:35 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/29 21:43:56 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <string>
# include <ncurses.h>
# include <iostream>
# include <fstream>
# include <sstream>
# include <memory>
# include <queue>

enum colors {
  number_color = 1,
  zero_color, 
  blank_color,
  b_and_w
};

struct  screen
{
    int mY , mX, mHeight, mWidth, mBegY, mBegX, mStartY, mStartX;
};

struct  note
{
    note &   operator=(note const & n)
    {
        *this = n;
        return *this;
    }
    int  **array;
    int             g, h, x, y;
};

struct  F
{
    bool    operator()(const note& a, const note& b)
    {
        return (a.h + a.g  > b.h + b.g);
    }
};

class   npuzzle{
    public:
        npuzzle();
        ~npuzzle();
        
        const note &  getFirstNote() const;
        void    setFirstNote(std::ifstream & file);
        void    setNote(note & n);
        const note &  getNote() const;
        void    setGoal();
        const note &    getGoal() const;
        void    print(note const & n);
        void    setH(note const & n);
        void    move_up();
        void    move_down();
        void    move_left();
        void    move_right();
        bool    getGameover();
        void    setGameover(bool b);
        void    setup();
        void    draw();
        void    pallet();



    private:
        bool                                                _mGameover;
        int                                                 _mGridsize;
        std::shared_ptr<note>                               _mFirstNote;
        std::shared_ptr<note>                               _mGoal;
        std::priority_queue<note, std::vector<note>, F>     _mNote;
        screen                                              _mScreen;
};











#endif