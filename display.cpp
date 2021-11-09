/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 12:12:02 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/05 13:22:05 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// AL: it seems this class is not used at all, delete it then
#include "display.hpp"

// AL: init _mScreen and _mGridsize here as well, all the members should be initialized in the constructor
display::display()
{
    _mGameover = false;
}

display::~display(){
    clear();
	endwin();
}

// AL: is this function used?
bool    display::getGameover()
{
    return (_mGameover);
}

// AL: is this function used?
void    display::setGameover(bool b)
{
    _mGameover = b;
}

void    display::setup()
{
    // initscr();
	// cbreak(); 
	// noecho(); // suppress automatic echo of typed input
    // // raw();
	// curs_set(0); // make cursor invisible
    // refresh();pallet();
    box(stdscr, 0 , 0);
	refresh();
    getyx(stdscr, _mScreen.mY, _mScreen.mX);
    getbegyx(stdscr, _mScreen.mBegY, _mScreen.mBegX);
	getmaxyx(stdscr, _mScreen.mHeight, _mScreen.mWidth);
    _mScreen.mStartY = _mScreen.mHeight / 2 - ((3 * _mGridsize) / 2);
    _mScreen.mStartX = _mScreen.mWidth / 2 - ((3 * _mGridsize) / 2);
    // _mBoard = newwin(_mGridsize *3 +1, _mGridsize *3 +1, _mScreen.mStartY, _mScreen.mStartX);
    
    refresh();
}

void    display::pallet()
{
    start_color(); 
	init_pair(number_color, COLOR_YELLOW, COLOR_BLACK);
	init_pair(zero_color, COLOR_RED, COLOR_BLACK);
	init_pair(blank_color, COLOR_BLACK, COLOR_BLACK);
	init_pair(b_and_w, COLOR_WHITE, COLOR_BLACK);
}

void    display::draw(node const & N)
{
    clear();
    box(stdscr, 0, 0);
	attron(COLOR_PAIR(number_color));
	for (int y = 0, j = 0; y < _mGridsize; y++, j+=3)
	{
        for (int x = 0, i = 0; x < _mGridsize; x++, i+=3)
        {
            if (N.array[y][x] == 0)
            {
            	attron(COLOR_PAIR(zero_color));
    		    mvprintw(j + _mScreen.mStartY, i + _mScreen.mStartX, "%d", N.array[y][x]);
            	attron(COLOR_PAIR(number_color));
            }    
            else
                mvprintw(j + _mScreen.mStartY, i + _mScreen.mStartX, "%d", N.array[y][x]);
        }
    }
	attron(COLOR_PAIR(b_and_w));
	refresh();
}