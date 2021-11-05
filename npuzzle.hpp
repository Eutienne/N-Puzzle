/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   npuzzle.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 18:24:35 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/11/05 19:55:01 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include "node.hpp"

# include <string>
# include <iostream>
# include <fstream>
# include <memory>
// # include <queue>
// # include <set>


struct  node;

class   npuzzle{
    public:
        npuzzle();
        ~npuzzle();
        
        const node &  getNode() const;
        void    setNode(std::ifstream & file);
        void    print(node const & n);
        void    setHmethod(std::string s);


    private:
        int                                                 _mGridsize;
        std::shared_ptr<node>                               _mNode;
};

#endif
