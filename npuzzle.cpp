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


display::display()
{
}

display::~display(){
    clear();
	endwin();
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

node const &  make_node(int grid)
{
    std::unique_ptr<node> n(new node);

    n->array = new int*[grid];
    n->array[grid] = NULL;
    for (int i = 0; i < grid; i++)
        n->array[i] = new int[grid];
    return (std::move(*n));
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
    _mGameover = false;
}

npuzzle::~npuzzle()
{
}

void    npuzzle::setFirstNode(std::ifstream & file)
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
           _mFirstNode = std::make_shared<node>(make_node(_mGridsize));
           _mGoal = std::make_shared<node>(make_node(_mGridsize));
        }
        else if (!line.empty())
        {
            std::stringstream stream(line);
            for (int i = 0; stream >>_mFirstNode->array[j][i]; i++)
            {
                if (_mFirstNode->array[j][i] == 0)
                {
                    _mFirstNode->y = j;
                    _mFirstNode->x = i;
                }
            }
            j++; 
        }
    }
}

const node & npuzzle::getFirstNode() const{
    return(*_mFirstNode);
}

void    npuzzle::setNode(node const & n)
{
    _mNode.push(n);
}

const node &  npuzzle::copyNode(node const & n){
    node const &copy = make_node(_mGridsize);
    const_cast<node&>(copy) = n;
    return copy;
}


const node & npuzzle::getGoal() const
{
    return (*_mGoal);
}

const node &  npuzzle::getNode() const
{
    return (_mNode.top());
}

void    npuzzle::print(node const & n)
{
    for (int i = 0; i < _mGridsize; i++)
    {
        for (int j = 0; j < _mGridsize; j++)
            std::cout << std::left << std::setw(5) << n.array[i][j];
        std::cout << std::endl;
    }
}

void    npuzzle::setH(node const & n)
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

void    npuzzle::move_up(node & n)
{
    if (n.y > 0)
    {
        std::swap(n.array[n.y][n.x], n.array[_mFirstNode->y - 1][n.x]);
        n.y--;
    }
}

void    npuzzle::move_down(node & n)
{
    if (n.y < _mGridsize -1)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y + 1][n.x]);
        n.y++;
    }
}

void    npuzzle::move_left(node & n)
{
    if (n.x > 0)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y][n.x - 1]);
        n.x--;
    }
}

void    npuzzle::move_right(node & n)
{
    if (n.x < _mGridsize -1)
    {
        std::swap(n.array[n.y][n.x], n.array[n.y][n.x + 1]);
        n.x++;
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


void npuzzle::movements(node const & n, std::string s)
{
    std::string moves[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
    void    (npuzzle::*p2f[])(node &n) = {&npuzzle::move_up, &npuzzle::move_down, &npuzzle::move_left, &npuzzle::move_right};

    node    tmp = copyNode(n);

    for (int i = 0; i < 4; i++)
    {
        if (moves[i] == s)
        {
            tmp.g++;
            (this->*p2f[i])(tmp);
            setH(tmp);
            m1.lock();
            setNode(tmp);
            m1.unlock();
        }
    }
}

void npuzzle::puzzle()
{
    node    n;

    n = _mNode.size() == 0? getFirstNode() : getNode();
    if (n.x > 0)
        std::thread move1(npuzzle::movements, n, "LEFT");
    if (n.x < _mGridsize -1)
        std::thread move2(this->movements, n, "RIGHT");
        // movements(n, "RIGHT");
    if (n.y > 0)
        std::thread move3(this->movements(), n, "UP");
        // movements(n, "UP");
    if (n.y < _mGridsize -1)
        std::thread move4(movements(n, "DOWN"));
        // movements(n, "DOWN");
    
    move1.join();
    
}