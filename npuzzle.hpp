/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   npuzzle.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eutrodri <eutrodri@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 18:24:35 by eutrodri      #+#    #+#                 */
/*   Updated: 2021/10/26 20:47:19 by eutrodri      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <memory>
# include <queue>


struct  note
{
    int  **array;
    int             g, h;
};

struct  F
{
    bool    operator()(const note& a, const note& b)
    {
        return (a.h + a.g  > b.h + b.g);
    }
};

class   npuzzle{
    public:
        npuzzle();
        
        const note &  getFirstNote() const;
        void    setFirstNote(std::ifstream & file);
        void    setNote(note & n);
        const note &  getNote() const;



    private:
        std::shared_ptr<note>    _mFirstNote = std::make_shared<note>();
        std::priority_queue<note, std::vector<note>, F>   _mNote;
};











#endif