/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/01 18:48:53 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"

int main(int argc, char **argv)
{
    std::ifstream   file(argv[1]);
    npuzzle         P;
    
    if (file.is_open())
    {
        P.setFirstNode(file);
        file.close();
    }
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.setNode(P.copyNode(P.getFirstNode()));
    P.print(P.getNode());
    P.move_up(const_cast<node&>(P.getNode()));
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.print(P.getNode());
    P.move_left(const_cast<node&>(P.getNode()));
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.print(P.getNode());
    P.move_down(const_cast<node&>(P.getNode()));
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.print(P.getNode());
    P.move_right(const_cast<node&>(P.getNode()));
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    P.print(P.getNode());

  
    // P.setGoal();
    // P.setH(P.getFirstNode());
    // P.print(P.getGoal());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getFirstNode());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(*test);
    while(1);
}