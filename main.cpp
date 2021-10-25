/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 20:47:13 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/25 17:55:31 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct  note
{
    int  **array;
    int             g, h;
};

void      setNote(std::ifstream & file, note & n)
{
    int pos;
    std::string line;
    while (getline(file, line))
    {
        pos = line.find('#');
        line = line.substr(0, pos);
        pos = line.find_last_not_of(" \n\r\t\f\v");
        line = line.substr(0, pos+1);
        if (!line.empty())
            std::cout << line << "$" << std::endl;
    }
    // return();
}


int main(int argc, char **argv)
{
    std::ifstream   file(argv[1]);
    // std::string     line;
    note            n;

    if (file.is_open())
    {
        setNote(file, n);
        file.close();
    }
    // std::cout << str << std::endl;
}