/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/26 17:35:09 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"
#include "nsolver.hpp"

class Usage : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return ("Usage : \n \t./[executeble] [file] --[method search*/heuristics**] --[method search*/heuristics**]\n\
        Optional choice of heuristic and search\n\n\
    * :\t 1: A_STAR\t\t use A_star search\n\t 2: GREEDY\t\t use greedy search\n\t 3: UNIFORM\t\t use uniform search\n\
    **:\t 1: MANHATTAN / m\t use manhattan heuristic\n\t 2: EUCLEADEAN / e \t use eucleadean heuristic\n\t 3: HAMMING / h\t\t use manhattan heuristic");
        }

};

int main(int argc, char **argv)
{
    npuzzle         P;

    try
    {
        if (argc > 4 || argc < 2)
            throw Usage();
        std::ifstream   file(argv[1]);
        if (file.is_open())
        {
            P.setNode(file);
            file.close();
            for (int i = 2; argv[i]; i++)
                P.setHmethod(argv[i]);
        }
        else
            throw Usage();
    nsolver         S(P.getNode());
    S.puzzle();
    S.printS();
    }
    catch(const std::exception& e)
    {
        std::cerr << BOLDBLUE << e.what() << RESET << '\n';
        exit(1);
    }
}