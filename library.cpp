/* 
 * File:   library.cpp
 * Author: Alex
 * 
 * Created on April 28, 2014, 10:37 PM
 */

#include "library.h"

library::library(vector<std::string> a) {
    words = a;
}

int library::checkword(std::string a) {
    int forward, backward, loc = 0;
    while (loc < words.size() && words[loc] < a) {
        ++loc;
    }
    if (loc < words.size() && words[loc] == a) {
        switch (a.size()) {
            case 3:
                forward = 1;
                break;
            case 4:
                forward = 2;
                break;
            case 5:
                forward = 4;
                break;
            case 6:
                forward = 8;
                break;
            case 7:
                forward = 16;
                break;
            default:
                forward = 0;
        }
    }else{
        forward = 0;
    }
    return (forward);
}

bool library::isinlibrary(std::string a){
        int loc = 0;
    while (loc < words.size() && words[loc] < a) {
        ++loc;
    }
    if (loc < words.size() && words[loc] == a){
        return true;
    }
    else{
        return false;
    }
}





