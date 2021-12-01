/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/12/01 15:16:26 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/npuzzle.hpp"
#include "../header/nsolver.hpp"
#include <chrono>

class Usage : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return ("Usage : ./[executeble] [file] [--A_STAR*] [--GREEDY*] [--UNIFORM*]\n\
        [--MANHATTAN / --m**] [--EUCLIDEAN / --e**] [--HAMMING / --h**] [--VERBOSE***]  \n\n\
    positional arguments:\n\n\tfile                  input file\n\n\
    Optional choice of heuristic and search\n\n\
    -h, --help\t            show this help message and exit\n\n\
    * :\t --A_STAR\t\t use A_star search\n\t --GREEDY\t\t use greedy search\n\t --UNIFORM\t\t use uniform search\n\n\
    **:\t --MANHATTAN, --m\t use manhattan heuristic\n\t --EUCLIDEAN, --e \t use euclidean heuristic\n\t --HAMMING, --h\t\t use manhattan heuristic\n\n\
    ***: --VERBOSE\t\t gui visualizer\n\n");
        }

};

int main(int argc, char **argv)
{
    auto start = std::chrono::steady_clock::now();
    npuzzle         P;
    int             i;

    try
    {
        if (argc > 5)
            throw Usage();
        if (argc == 1 || argv[1][0] == '-')
        {
            if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
                throw Usage();
            std::cout << "Give the size of your grid between 3 and 20" << std::endl;
            std::cin >> i;
            if (i > 2 && i < 21)
                P.make_npuzzle(i);
            else
                throw std::runtime_error("Wrong number");
            i = 1;
        }
        else if (argv[1] )
        {
            std::ifstream   file(argv[1]);
            if (file.is_open())
            {
                P.setNode(file);
                file.close();
                if (P.getGridsize() < 3)
                    throw std::runtime_error("File is wrong");            
                i = 2;
            }
        }
        else
            throw Usage();
        for (; argv[i]; i++)
            P.setHmethod(argv[i]);
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