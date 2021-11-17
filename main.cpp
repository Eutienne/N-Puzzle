/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/17 22:43:36 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"
#include "nsolver.hpp"

int main(int argc, char **argv)
{
    {
    npuzzle         P;
    int             i;

    if (argc > 3 || argc < 2)
    {
        std::cout << "wrong arguments" << std::endl;
        exit(-1);
    }
    argc == 3 ? i = 2 : i = 1;
    std::ifstream   file(argv[i]);
    if (file.is_open())
    {
        P.setNode(file);
        file.close();
        if (i == 2)
            P.setHmethod(argv[1]);
    }
    else
    {
        std::cout << "can't read last argument" << std::endl;
        exit(1);
    }
    nsolver         S(P.getNode());
    S.puzzle();
    S.printS();
    }
}