/* 
 * File:   gamestate.cpp
 * Author: Alex
 * 
 * Created on April 29, 2014, 4:14 PM
 */
#include <iostream>
#include "gamestate.h"

const char standardtile[31] = {'a','a','b','c','d','e','e','f','g','h','i',
        'i','j','k','l','m','n','o','o','p','q','r','s','t','u','u','v','w','x','y','z'};

gamestate::gamestate() {
    playerpoints = 0;
    computerpoints = 0;
    for(int counter = 0; counter < 31; counter++){
        playertiles.push_back(standardtile[counter]);
    }
    for(int counter2 = 0; counter2 < 31; counter2++){
        computertiles.push_back(standardtile[counter2]);
    }    
}

gamestate::gamestate(vector<std::string> a, int b, int c){
    playerpoints = b;
    computerpoints = c;
    for(int c1 = 0; (c1 < a[0].size() - 1); c1++){
        playertiles.push_back(a[0].at(c1));
    }
    for(int c2 = 0; (c2 < a[1].size() - 1); c2++){
        computertiles.push_back(a[1].at(c2));
    }
}


int gamestate::getplayerscore(){
    return playerpoints;
}

int gamestate::getcomputerscore(){
    return computerpoints;
}

bool gamestate::checkplayertile(char a){
    int loc = 0;
    while (loc < playertiles.size() && playertiles[loc] < a) {
        ++loc;
    }
    if (loc < playertiles.size() && playertiles[loc] == a){
        return true;
    }
    else{
        return false;
    }
}

bool gamestate::checkcomputertile(char a){
    int loc = 0;
    while (loc < computertiles.size() && computertiles[loc] < a) {
        ++loc;
    }
    if (loc < computertiles.size() && computertiles[loc] == a){
        return true;
    }
    else{
        return false;
    }
}

void gamestate::removeplayertile(char a){
    int loc = 0;
    while (loc < playertiles.size() && playertiles[loc] < a) {
        ++loc;
    }
    if (loc < playertiles.size() && playertiles[loc] == a){
        playertiles[loc] = '.';
    }
}

void  gamestate::removecomputertile(char a){
        int loc = 0;
    while (loc < computertiles.size() && computertiles[loc] < a) {
        ++loc;
    }
    if (loc < computertiles.size() && computertiles[loc] == a){
        computertiles[loc] = '.';
    }
}

 void gamestate::printplayertile(){
     cout << "Letters remaining to you:" << endl;
     for(int counter = 0; counter < playertiles.size(); counter++){
         if(playertiles[counter] != '.'){
             cout << playertiles[counter] << " ";
         }
     }
     cout << '\n';
 }
void gamestate::printcomputertile(){
     cout << "Letters remaining to me:" << endl;
     for(int counter = 0; counter < computertiles.size(); counter++){
         if(computertiles[counter] != '.'){
             cout << computertiles[counter] << " ";
         }
     }
     cout << '\n';
}

void gamestate::addplayerpoint(int a){
    playerpoints += a;
}
void gamestate::addcomputerpoint(int a){
    computerpoints += a;
}

vector<char> gamestate::getcomputertiles(){
    return computertiles;
}






