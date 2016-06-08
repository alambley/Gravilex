/* 
 * File:   grid.cpp
 * Author: Alex
 * 
 * Created on April 28, 2014, 4:00 PM
 */

#include "grid.h"
#include <vector>




grid::grid() {
    lastmove = -1;
    for(int a = 0; a < 6; a++){
        for(int b = 0; b < 7; b++){
            gamegrid[(a*7)+b] = '.';
        }
    }
}

grid::grid(vector<std::string> a){
    for(int c1 = 0; c1 < 7; c1++){
        gamegrid[35+c1] = a[0].at(c1);
        gamegrid[28+c1] = a[1].at(c1);
        gamegrid[21+c1] = a[2].at(c1);
        gamegrid[14+c1] = a[3].at(c1);
        gamegrid[7+c1] = a[4].at(c1);
        gamegrid[c1] = a[5].at(c1);
    }
    
}

int grid::getlastmove(){
    return lastmove;
}

void grid::printgrid(){
    cout << '\n';
    for(int a = 5; a > -1; a--){
        for(int b = 0; b < 7; b++){
            cout << gamegrid[(a*7)+b];
        }
        cout << '\n';
    }
    for(int b = 1; b < 8; b++){
        cout << b;
    }
    cout << '\n';
}

bool grid::columnfull(int a){
    if ((a > 0) && (a < 8)){
         if(gamegrid[a+34] == "."){
             return false;
         }
    }
    return true;
}

bool grid::gameover(){
    bool isgameover = true;
    for(int a = 35; a < 42; a++){
        if(gamegrid[a] == "."){
            isgameover = false;
        }
    }
    return isgameover;
}

void grid::placechar(int a, char b){
    bool found = false;
    for(int c = 0; (c < 6) && (found == false); c++){
        if(gamegrid[(7*c)+(a-1)] == "."){
            gamegrid[(7*c)+(a-1)] = b;
            lastmove = (7*c)+(a-1);
            found = true;
        }
    }
}

std::string grid::getxxaxis(int x){
   std::string a,b,c;
   b = gamegrid[x]; 
   for(int ac = 1; ((x - ac)>-1) && (((x-ac)+1) % 7 != 0) && (gamegrid[x-ac] != "."); ac++){
       a = a + gamegrid[x-ac];
   }
   a = string (a.rbegin(), a. rend());    
   for(int cc = 1; ((x+cc)<42) && ((x+cc) % 7 != 0) && (gamegrid[x+cc] != "."); cc++){
       c = c + gamegrid[x+cc];
   }
   return a+b+c;   
}

std::string grid::getyyaxis(int x){
    std::string a,b,c;
    b = gamegrid[x];
    for(int ac = 1; (x+(ac*7) < 42) && (gamegrid[x+(ac*7)] != "."); ac++){
        a = a + gamegrid[x+(ac*7)];
    }
    a = string (a.rbegin(), a. rend());
    for(int cc = 1; (x-(cc*7) > -1) && (gamegrid[x-(cc*7)] != "."); cc++){
        c = c + gamegrid[x-(cc*7)];
    }
    return a+b+c;
}

std::string grid::getxyaxis(int x){
    std::string a,b,c;
    b = gamegrid[x];
    for(int ac = 1; (x-(ac*8)> -1) && (((x-(ac*8))+1) % 7 != 0) && (gamegrid[x-(ac*8)] != ".") ; ac++){
        a = a + gamegrid[x-(ac*8)];
    }
    a = string (a.rbegin(), a. rend());
    for(int cc = 1; (x+(cc*8)< 42) && ((x+(cc*8)) % 7 != 0) && (gamegrid[x+(cc*8)] != ".") ; cc++){
        c = c + gamegrid[x+(cc*8)];
    }
    return a+b+c;
}

std::string grid::getyxaxis(int x){
    std::string a,b,c;
    b = gamegrid[x];
    for(int ac = 1; ((x+(ac*6)) < 42) && (((x+(ac*6))+1) % 7 != 0) && (gamegrid[x+(ac*6)] != ".") ; ac++){
        a = a + gamegrid[x+(ac*6)];
    }
    a = string (a.rbegin(), a. rend());
    for(int cc = 1; ((x-(cc*6)) > -1) && ((x-(cc*6)) % 7 != 0) && (gamegrid[x-(cc*6)] != "."); cc++){
        c = c + gamegrid[x-(cc*6)];
    }
    return a+b+c;
}

void grid::resetpoint(int a){
    gamegrid[a] = ".";
}

void grid::setlastmove(int a){
    lastmove = a;
}




