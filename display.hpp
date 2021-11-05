/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 12:08:34 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/05 13:20:24 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HPP
# define DISPLAY_HPP

# include <ncurses.h>
# include "node.hpp"


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

class   display{
    public:
        display();
        ~display();
        

        void    setup();
        void    draw(node const & N);
        void    pallet();
        bool    getGameover();
        void    setGameover(bool b);
    
    private:
        screen                                              _mScreen;
        int                                                 _mGridsize;        
        bool                                                _mGameover;
};




#endif