/* 
 * File:   library.h
 * Author: Alex
 *
 * Created on April 28, 2014, 10:37 PM
 */

#ifndef LIBRARY_H
#define	LIBRARY_H
#include <vector>
#include <iostream>

using namespace std;

class library {
public:
    library(vector<std::string>);
    int checkword(std::string);
    bool isinlibrary(std::string);
 

private:
vector<std::string> words;
};

#endif	/* LIBRARY_H */

