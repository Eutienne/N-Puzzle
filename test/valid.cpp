/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 19:12:15 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/30 19:18:40 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../header/npuzzle.hpp"
#include "../header/nsolver.hpp"
#include "../header/node.hpp"

TEST(valid, 1)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/different_maps/3npuzzle1.txt");
    file.is_open();

    ASSERT_NO_THROW(P.setNode(file));
}

TEST(valid, 2)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/different_maps/4puzzle1.txt");
    file.is_open();
    
    ASSERT_NO_THROW(P.setNode(file));
}

TEST(valid, 3)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/different_maps/4puzzle2.txt");
    file.is_open();
    
    ASSERT_NO_THROW(P.setNode(file));
}

TEST(valid, 4)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/different_maps/4puzzle3.txt");
    file.is_open();
    
    ASSERT_NO_THROW(P.setNode(file));
}

TEST(valid, 5)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/different_maps/4puzzle4.txt");
    file.is_open();
    
    ASSERT_NO_THROW(P.setNode(file));
}

TEST(valid, 6)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/different_maps/4puzzle5.txt");
    file.is_open();
    
    ASSERT_NO_THROW(P.setNode(file));
}