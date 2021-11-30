/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_m.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 20:06:33 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/30 22:32:32 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/npuzzle.hpp"
#include "../header/display.hpp"


int main(int argc, char **argv)
{
    npuzzle         P;
    std::ifstream   file(argv[1]);
    display         G;
    node*           N;
    
    if (argc != 2)
        return 0;

    G.setup();
    if (file.is_open())
    {
        P.setNode(file);
        file.close();
    }
    else
        return 0;
    N = const_cast<node*>(&P.getNode());
    G.draw(*N);
 
    while (G.getGameover() == false)
    {
        switch (getch())
        {
            case 'w':
                N->move_up();
                G.draw(*N);
                break;
            case 'a':
                N->move_left();
                G.draw(*N);
                break;
            case 's':
                N->move_down();
                G.draw(*N);
                break;
            case 'd':
                N->move_right();
                G.draw(*N);
                break;
            case 'q':
                G.setGameover(true);
                G.draw(*N);
                break;
            refresh();
        }
    }
    return 0;
}
