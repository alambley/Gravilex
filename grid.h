/* 
 * File:   grid.h
 * Author: Alex
 *
 * Created on April 28, 2014, 4:00 PM
 */
#include <iostream>
#include <sstream>
#include <vector>
#ifndef GRID_H
#define	GRID_H

using namespace std;

class grid {
public:
    grid();
    grid(vector<std::string>);
    int getlastmove();
    void printgrid();
    bool columnfull(int);
    bool gameover();
    void placechar(int, char);
    std::string getxxaxis(int);
    std::string getyyaxis(int);
    std::string getxyaxis(int);
    std::string getyxaxis(int);
    void resetpoint(int);
    void setlastmove(int);

private:
    std::string gamegrid[42];
    int lastmove;
};

#endif	/* GRID_H */

