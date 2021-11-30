/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unsolvable.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 18:03:44 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/30 18:05:25 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../header/npuzzle.hpp"
#include "../header/nsolver.hpp"
#include "../header/node.hpp"

TEST(unsolvable, 1)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/unsolvable/UNpuzzle1.txt");
    file.is_open();
    P.setNode(file);
    ASSERT_THROW(nsolver         S(P.getNode()), std::runtime_error);
}

TEST(unsolvable, 2)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/unsolvable/UNpuzzle2.txt");
    file.is_open();
    P.setNode(file);
    ASSERT_THROW(nsolver         S(P.getNode()), std::runtime_error);
}

TEST(unsolvable, 3)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/unsolvable/UNpuzzle3.txt");
    file.is_open();
    P.setNode(file);
    ASSERT_THROW(nsolver         S(P.getNode()), std::runtime_error);
}

TEST(unsolvable, 4)
{
    npuzzle         P;
    
    std::ifstream   file("../maps/unsolvable/UNpuzzle4.txt");
    file.is_open();
    P.setNode(file);
    ASSERT_THROW(nsolver         S(P.getNode()), std::runtime_error);
}