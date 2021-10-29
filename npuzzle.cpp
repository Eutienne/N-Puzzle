/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   npuzzle.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 19:31:50 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/26 19:32:14 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"

note const &  make_note(int grid)
{
    note *n = new note;

    n->array = new int*[grid];
    n->array[grid] = NULL;
    for (int i = 0; i < grid; i++)
        n->array[i] = new int[grid];
    return (*n);
}

void    npuzzle::setGoal()
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            _mGoal->array[i][j] = 0;
    }
    for (int i = 0, j = 0, n = 1; _mGoal->array[i] && _mGoal->array[i][j] == 0 && n < _mGridsize * _mGridsize;)
    {
        for (; j < _mGridsize && _mGoal->array[i][j] == 0; j++, n++)
            _mGoal->array[i][j] = n; 
        j--; i++;
        for (; i < _mGridsize && _mGoal->array[i][j] == 0; i++, n++)
            _mGoal->array[i][j] = n;
        i--; j--;
        for (; j > -1 && _mGoal->array[i][j] == 0; j--, n++)
            _mGoal->array[i][j] = n;
        j++; i--;
        for (; i > -1 && _mGoal->array[i][j] == 0; i--, n++)
            _mGoal->array[i][j] = n;
        i++; j++;
    }
    _mGoal->y = _mGridsize/2;
    _mGridsize % 2 == 0 ? _mGoal->array[_mGridsize / 2][(_mGridsize / 2) -1] = 0 : _mGoal->array[_mGridsize / 2][(_mGridsize / 2)] = 0;
    _mGridsize % 2 == 0 ? _mGoal->x = (_mGridsize / 2) -1 : _mGoal->x = _mGridsize / 2;
}

npuzzle::npuzzle()
{
    initscr();
	cbreak(); 
	noecho(); // suppress automatic echo of typed input
    // raw();
	curs_set(0); // make cursor invisible
    refresh();
    _mGameover = false;
}

npuzzle::~npuzzle()
{
    clear();
	endwin();
}

void    npuzzle::setFirstNote(std::ifstream & file)
{
    int pos;
    std::string line;
    for (int j=0; getline(file, line);)
    {
        pos = line.find('#');
        line = line.substr(0, pos);
        pos = line.find_last_not_of(" \n\r\t\f\v");
        line = line.substr(0, pos+1);
        if ((!line.empty()) && line.find_last_not_of(" \n\r\t\f\v") == '\0')
        {
            _mGridsize = atoi(line.c_str());
           _mFirstNote = std::make_shared<note>(make_note(_mGridsize));
           _mGoal = std::make_shared<note>(make_note(_mGridsize));
        }
        else if (!line.empty())
        {
            std::stringstream stream(line);
            for (int i = 0; stream >>_mFirstNote->array[j][i]; i++)
            {
                if (_mFirstNote->array[j][i] == 0)
                {
                    _mFirstNote->y = j;
                    _mFirstNote->x = i;
                }
            }
            j++; 
        }
    }
}

const note & npuzzle::getFirstNote() const{
    return(*_mFirstNote);
}

void    npuzzle::setNote(note & n)
{
    _mNote.push(n);
}

const note & npuzzle::getGoal() const
{
    return (*_mGoal);
}

const note &  npuzzle::getNote() const
{
    return (_mNote.top());
}

void    npuzzle::print(note const & n)
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            std::cout << std::left << std::setw(5) << n.array[i][j];
        std::cout << std::endl;
    }
}

void    npuzzle::setH(note const & n)
{
    int h = 0;
    for (int i=0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
        {
            for (int y=0; j < _mGridsize && y < _mGridsize && n.array[i][j] != 0; y++)
            {
                for (int x=0; x < _mGridsize; x++)
                {
                    if (n.array[i][j] == _mGoal->array[y][x])
                    {
                        y > i ? h += y - i : h += i - y;
                        x > j ? h += x - j : h += j - x;
                        break;
                    }
                }
            }
        }
    }
}

void    npuzzle::move_up()
{
    if (_mFirstNote->y > 0)
    {
        std::swap(_mFirstNote->array[_mFirstNote->y][_mFirstNote->x], _mFirstNote->array[_mFirstNote->y - 1][_mFirstNote->x]);
        _mFirstNote->y--;
    }
}

void    npuzzle::move_down()
{
    if (_mFirstNote->y < _mGridsize -1)
    {
        std::swap(_mFirstNote->array[_mFirstNote->y][_mFirstNote->x], _mFirstNote->array[_mFirstNote->y + 1][_mFirstNote->x]);
        _mFirstNote->y++;
    }
}

void    npuzzle::move_left()
{
    if (_mFirstNote->x > 0)
    {
        std::swap(_mFirstNote->array[_mFirstNote->y][_mFirstNote->x], _mFirstNote->array[_mFirstNote->y][_mFirstNote->x - 1]);
        _mFirstNote->x--;
    }
}

void    npuzzle::move_right()
{
    if (_mFirstNote->x < _mGridsize -1)
    {
        std::swap(_mFirstNote->array[_mFirstNote->y][_mFirstNote->x], _mFirstNote->array[_mFirstNote->y][_mFirstNote->x + 1]);
        _mFirstNote->x++;
    }
}

bool    npuzzle::getGameover()
{
    return (_mGameover);
}

void    npuzzle::setGameover(bool b)
{
    _mGameover = b;
}

void    npuzzle::setup()
{
    pallet();
    box(stdscr, 0 , 0);
	refresh();
    getyx(stdscr, _mScreen.mY, _mScreen.mX);
    getbegyx(stdscr, _mScreen.mBegY, _mScreen.mBegX);
	getmaxyx(stdscr, _mScreen.mHeight, _mScreen.mWidth);
    _mScreen.mStartY = _mScreen.mHeight / 2 - ((3 * _mGridsize) / 2);
    _mScreen.mStartX = _mScreen.mWidth / 2 - ((3 * _mGridsize) / 2);
    _mBoard = newwin(_mGridsize *3 +1, _mGridsize *3 +1, _mScreen.mStartY, _mScreen.mStartX);
    
    refresh();
}

void    npuzzle::pallet()
{
    start_color(); 
	init_pair(number_color, COLOR_YELLOW, COLOR_BLACK);
	init_pair(zero_color, COLOR_RED, COLOR_BLACK);
	init_pair(blank_color, COLOR_BLACK, COLOR_BLACK);
	init_pair(b_and_w, COLOR_WHITE, COLOR_BLACK);
}

void    npuzzle::draw()
{
    
    clear();
    box(stdscr, 0, 0);
	attron(COLOR_PAIR(number_color));
	for (int y = 0, j = 0; y < _mGridsize; y++, j+=3)
	{
        for (int x = 0, i = 0; x < _mGridsize; x++, i+=3)
        {
            if (_mFirstNote->array[y][x] == 0)
            {
            	attron(COLOR_PAIR(zero_color));
    		    mvprintw(j + _mScreen.mStartY, i + _mScreen.mStartX, "%d", _mFirstNote->array[y][x]);
            	attron(COLOR_PAIR(number_color));
            }    
            else
                mvprintw(j + _mScreen.mStartY, i + _mScreen.mStartX, "%d", _mFirstNote->array[y][x]);
        }
    }
	attron(COLOR_PAIR(b_and_w));
	refresh();
}
