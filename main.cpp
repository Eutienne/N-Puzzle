/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/02 17:48:58 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"
#include <functional>

int main(int argc, char **argv)
{
    std::ifstream   file(argv[1]);
    npuzzle         P;
    
    if (file.is_open())
    {
        P.setFirstNode(file);
        file.close();
        P.setGoal();
        P.puzzle();
    }
    // P.print(*std::make_shared<node>(P.getFirstNode()));
    // P.setNode(P.getFirstNode());
    // for (node n; P.getNodeSize() != 0; n = P.getNode())
    // {
    //     if (n.x > 0)
    //         std::thread th1([(&npuzzle::movements), n, P](){P.movements(n, "LEFT")});
    //     if (n.x < _mGridsize -1)
    //         std::thread th2(std::mem_fn(&npuzzle::movements), n, "RIGHT");
    //     if (n.y > 0)
    //         std::thread th3(std::mem_fn(&npuzzle::movements), n, "UP");
    //     if (n.y < _mGridsize -1)
    //         std::thread th4(std::mem_fn(&npuzzle::movements), n, "DOWN");
    //     th1.join();
    // }
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.setNode(P.copyNode(P.getFirstNode()));
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getNode());
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.move_up(const_cast<node&>(P.getNode()));
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getNode());
    // P.move_left(const_cast<node&>(P.getNode()));
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getNode());
    // P.move_down(const_cast<node&>(P.getNode()));
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getNode());
    // P.move_right(const_cast<node&>(P.getNode()));
    // std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getNode());

  
    // P.setGoal();
    // P.setH(P.getFirstNode());
    // P.print(P.getGoal());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(P.getFirstNode());
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    // P.print(*test);
    // while(1);
}