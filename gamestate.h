/* 
 * File:   gamestate.h
 * Author: Alex
 *
 * Created on April 29, 2014, 4:14 PM
 */

#ifndef GAMESTATE_H
#define	GAMESTATE_H
#include <vector>

using namespace std;

class gamestate {
public:
    gamestate();
    gamestate(vector<std::string>, int, int);
    int getplayerscore();
    int getcomputerscore();
    bool checkplayertile(char);
    bool checkcomputertile(char);
    void removeplayertile(char);
    void removecomputertile(char);
    void printplayertile();
    void printcomputertile();
    void addplayerpoint(int);
    void addcomputerpoint(int);
    int getcomputerremaining();
    vector<char> getcomputertiles();
    

private:
    int playerpoints;
    int computerpoints;
    vector<char> playertiles;
    vector<char> computertiles;
};

#endif	/* GAMESTATE_H */

