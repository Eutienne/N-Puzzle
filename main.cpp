/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/27 22:24:22 by eutrodri      ########   odam.nl         */
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
    
    P.setGoal();
    P.setH(P.getFirstNote());
    P.print(P.getGoal());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.print(P.getFirstNote());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.move_up();
    P.print(P.getFirstNote());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.move_right();
    P.print(P.getFirstNote());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.move_down();
    P.print(P.getFirstNote());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.move_left();
    P.print(P.getFirstNote());
}