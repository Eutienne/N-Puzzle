/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/23 21:57:54 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"
#include "nsolver.hpp"

class Usage : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return ("Usage : \n \t./[executeble] [file] --[method search*/heuistics**] --[method search*/heuistics**]\n\
        Optional choice of heuristic and search\n\n\
    * :\t 1: A*\n\t 2: GREEDY\n\t 3: UNIFORM\n\
    **:\t 1: MANHATTAN / m\n\t 2: EUCLEADEAN / e\n\t 3: HAMMING / h");
        }

};

int main(int argc, char **argv)
{
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
            // P.print(P.getNode());
            for (int i = 2; argv[i]; i++)
                P.setHmethod(argv[i]);
        }
        else
            throw Usage();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    nsolver         S(P.getNode());
    return 0;
    S.puzzle();
    S.printS();
    }
}