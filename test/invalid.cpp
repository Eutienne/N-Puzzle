/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:33:11 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/30 18:14:47 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../header/npuzzle.hpp"
#include "../header/nsolver.hpp"
#include "../header/node.hpp"

TEST(invalid, 1)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/invalid/3npuzzle1.txt");
    file.is_open();

    ASSERT_THROW(P.setNode(file), std::runtime_error);
}

TEST(invalid, 2)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/invalid/4puzzle1.txt");
    file.is_open();
    
    ASSERT_THROW(P.setNode(file), std::runtime_error);
}

TEST(invalid, 3)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/invalid/4puzzle2.txt");
    file.is_open();
    
    ASSERT_THROW(P.setNode(file), std::runtime_error);
}

TEST(invalid, 4)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/invalid/4puzzle3.txt");
    file.is_open();
    
    ASSERT_THROW(P.setNode(file), std::runtime_error);
}

TEST(invalid, 5)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/invalid/4puzzle4.txt");
    file.is_open();
    
    ASSERT_THROW(P.setNode(file), std::runtime_error);
}

TEST(invalid, 6)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/invalid/4puzzle5.txt");
    file.is_open();
    
    ASSERT_THROW(P.setNode(file), std::runtime_error);
}