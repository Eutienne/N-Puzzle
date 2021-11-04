/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 12:08:34 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/04 12:28:08 by eutrodri      ########   odam.nl         */
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

    private:
        screen                                              _mScreen;
        int                                                 _mGridsize;        
};




#endif