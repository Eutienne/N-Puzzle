/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/29 12:33:42 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"
#include "nsolver.hpp"
#include <chrono>

class Usage : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return ("Usage : ./[executeble] [file] [--A_STAR*] [--GREEDY*] [--UNIFORM*]\n\
        [--MANHATTAN / --m**] [--EUCLIDEAN / -e**] [--HAMMING / --h**] [--VERBOSE***]  \n\n\
    positional arguments:\n\n\tfile                  input file\n\n\
    Optional choice of heuristic and search\n\n\
    * :\t --A_STAR\t\t use A_star search\n\t --GREEDY\t\t use greedy search\n\t --UNIFORM\t\t use uniform search\n\n\
    **:\t --MANHATTAN, --m\t use manhattan heuristic\n\t --EUCLIDEAN, --e \t use euclidean heuristic\n\t --HAMMING, --h\t\t use manhattan heuristic\n\n\
    ***: --VERBOSE\t\t gui visualizer\n\n");
        }

};

int main(int argc, char **argv)
{
    auto start = std::chrono::steady_clock::now();
    npuzzle         P;

    try
    {
        if (argc > 5 || argc < 2)
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
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << BOLDYELLOW << "time: " << diff.count() << "s" << RESET << std::endl;
}