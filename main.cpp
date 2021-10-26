/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/26 20:48:22 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.hpp"

note &    make_note(note & n)
{
    note *b = new note;
    int c = 0;
    for (; n.array[c]; c++);
    b->array = new int*[c];
    b->array[c] = NULL;
    for (int i = 0; i < c; i++)
        b->array[i] = new int[c];

    for (int i = 0; n.array[i]; i++)
    {
        for (int j = 0; n.array[j]; j++)
            b->array[i][j] = n.array[i][j];
    }

    return (*b);
}

// void      setNote(std::ifstream & file, note & n)
// {
//     int pos;
//     std::string line;
//     for (int j=0; getline(file, line);)
//     {
//         pos = line.find('#');
//         line = line.substr(0, pos);
//         pos = line.find_last_not_of(" \n\r\t\f\v");
//         line = line.substr(0, pos+1);
//         if ((!line.empty()) && line.find_last_not_of(" \n\r\t\f\v") == '\0')
//         {
//             n.array = new int*[atoi(line.c_str()) + 1];
//             n.array[atoi(line.c_str())] = NULL;
//             for (int i = 0; i < atoi(line.c_str()); i++)
//                 n.array[i] = new int[atoi(line.c_str())];
//         }
//         else if (!line.empty())
//         {
//             std::stringstream stream(line);
//             for (int i = 0; stream >>n.array[j][i]; i++); 
//             j++; 
//         }
//     }
// }


int main(int argc, char **argv)
{
    std::ifstream   file(argv[1]);
    npuzzle         P;
    

    if (file.is_open())
    {
        P.setFirstNote(file);
        file.close();
    }

    // b = &make_note(n);

    // std::cout << P.getFirstNote().array << std::endl;

    for (int i = 0; P.getFirstNote().array[i]; i++)
    {
        for (int j = 0; P.getFirstNote().array[j]; j++)
            std::cout << P.getFirstNote().array[i][j] << " ";
        std::cout << std::endl;
    }
    std::swap(P.getFirstNote().array[2][2], P.getFirstNote().array[1][2]);
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    for (int i = 0; P.getFirstNote().array[i]; i++)
    {
        for (int j = 0; P.getFirstNote().array[j]; j++)
            std::cout << P.getFirstNote().array[i][j] << " ";
        std::cout << std::endl;
    }
}