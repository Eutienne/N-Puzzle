/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/29 21:27:41 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"

int main(int argc, char **argv)
{
    std::ifstream   file(argv[1]);
    npuzzle         P;
    

    if (file.is_open())
    {
        P.setFirstNote(file);
        file.close();
    }
    P.setup();
    P.draw();
    while (P.getGameover() == false)
    {
        switch (getch())
        {
            case 'w':
            // std::cout << "w" << std::endl;
                P.move_up();
                P.draw();
                break;
            case 'a':
                P.move_left();
                P.draw();
                break;
            case 's':
                P.move_down();
                P.draw();
                break;
            case 'd':
                P.move_right();
                P.draw();
                break;
            case 'q':
                P.setGameover(true);
                P.draw();
                break;
            refresh();
        }
    }
    // char c = getch();
    
    // clear();
    // endwin();
    // P.setGoal();
    // P.setH(P.getFirstNote());
    // P.print(P.getGoal());
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getFirstNote());
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.move_up();
    // P.print(P.getFirstNote());
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.move_right();
    // P.print(P.getFirstNote());
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.move_down();
    // P.print(P.getFirstNote());
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.move_left();
    // P.print(P.getFirstNote());
    // while(1);
}