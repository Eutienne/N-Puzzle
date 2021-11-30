/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:22:36 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/30 14:22:57 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return (RUN_ALL_TESTS());
}
