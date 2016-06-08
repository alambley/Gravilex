/* 
 * File:   gravilex.cpp
 * Author: Alex
 *
 * Created on April 28, 2014, 4:22 PM
 */

#include <cstdlib>
#include "grid.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "library.h"
#include "gamestate.h"




using namespace std;

struct aicompmove {
    int column;
    char letter;
    bool nextto;
};

void processlibrary(ifstream&, vector<std::string>&);
void processpossiblewords(grid, vector<std::string>&);
bool searchvector(vector<std::string>&, std::string);
int wordlengthtopoints(int);
bool testforallwhitespace(string a);
string delspaces(string &str);
aicompmove aibestmove(grid, library, gamestate);
void processgame(ifstream&, vector<std::string>&, vector<std::string>&, int&, int&);

int main(int argc, char** argv) {
    ifstream libraryinfile, gameinfile;
    vector<std::string> libraryvect, gridvect, tilevect;
    int inplayerpoints, incomppoints;
    libraryinfile.open(argv[1]);
    processlibrary(libraryinfile, libraryvect);
    libraryinfile.close();

    gameinfile.open(argv[2]);
    processgame(gameinfile, gridvect, tilevect, inplayerpoints, incomppoints);
    gameinfile.close();
    
    //freopen(argv[3], "r",stdin);

    grid gamegrid(gridvect);
    library gamelibrary(libraryvect);
    gamestate referee(tilevect, inplayerpoints, incomppoints);

    while (gamegrid.gameover() == false) {
        aicompmove mymove;
        string line;
        char charchoice, spelledcorrectlychoice;       
        int columnchoice, playerpointsscored = 0, computerpointsscored = 0;
        vector<std::string> possiblewords, claimedwords, compclaimedwords;
        gamegrid.printgrid();
        do {
            referee.printplayertile();
            cout << "What letter would you like to drop? ";
            cin >> charchoice;
            if(cin.eof()){
                cout << '\n' <<"End of file detected.";
                return 1;
            }
            charchoice = tolower(charchoice);
        } while ((!referee.checkplayertile(charchoice)) || (charchoice == '.'));
        do {
            cout << "What column would you like to drop that in? (1-7) ";
            cin >> columnchoice;
            std::cin.ignore();
            if(cin.eof()){
                cout << '\n' <<"End of file detected.";
                return 1;
            }
        } while (gamegrid.columnfull(columnchoice));
        gamegrid.placechar(columnchoice, charchoice);
        referee.removeplayertile(charchoice);
        gamegrid.printgrid();
        processpossiblewords(gamegrid, possiblewords);
        do {
            cout << "Enter a word that you would like to claim (empty line to end) ";
            getline(cin, line);
            if(cin.eof()){
                cout << '\n' <<"End of file detected.";
                return 1;
            }
            if (!testforallwhitespace(line)) {
                delspaces(line);
                for(int c3 = line.size(); c3 > 0; c3-- ){
                    if(isspace(line.at(c3-1))){
                        line.resize((c3-1));
                        if(!isspace(line.at(c3-2))){
                            cout << endl;
                        }
                    }
                }
                for (int linecounter = 0; linecounter < line.size(); linecounter++) {
                    line[linecounter] = tolower(line[linecounter]);
                }
                if ((searchvector(possiblewords, line)) && (gamelibrary.isinlibrary(line))) {
                    if (!(searchvector(claimedwords, line))) {
                        referee.addplayerpoint(gamelibrary.checkword(line));
                        playerpointsscored += gamelibrary.checkword(line);
                        claimedwords.push_back(line);
                    } else {
                        cout << "Sorry, you've already claimed that word!" << endl;
                    }
                } else if ((searchvector(possiblewords, line)) && (!gamelibrary.isinlibrary(line))) {
                    do {
                        cout << "I don't know that word. Are you sure you spelled it correctly? (y/n) ";
                        cin >> spelledcorrectlychoice;
                        if(cin.eof()){
                                cout << '\n' <<"End of file detected.";
                                return 1;
                        }
                        spelledcorrectlychoice = tolower(spelledcorrectlychoice);
                        std::cin.ignore();
                    } while (!((spelledcorrectlychoice != 'y') || (spelledcorrectlychoice != 'n')));
                    if (spelledcorrectlychoice == 'y') {
                        if (!(searchvector(claimedwords, line))) {
                            referee.addplayerpoint(wordlengthtopoints(line.size()));
                            playerpointsscored += wordlengthtopoints(line.size());
                            claimedwords.push_back(line);
                        } else {
                            cout << "Sorry, you've already claimed that word!" << endl;
                        }
                    }
                } else {
                    cout << "Sorry, you cannot claim that word." << endl;
                }
            }
        } while (!testforallwhitespace(line));
        cout << '\n' << "Points scored on this turn: " << playerpointsscored << endl;
        gamegrid.printgrid();
        referee.printcomputertile();
        mymove = aibestmove(gamegrid, gamelibrary, referee);
        cout << "I will drop the letter " << mymove.letter << " in column " << mymove.column << endl;
        gamegrid.placechar(mymove.column, mymove.letter);
        referee.removecomputertile(mymove.letter);
        gamegrid.printgrid();
        processpossiblewords(gamegrid, compclaimedwords);
        for(int c1 = 0; c1 < compclaimedwords.size(); c1++){
            if(gamelibrary.isinlibrary(compclaimedwords[c1]) &&(compclaimedwords[c1].size() > 2)){
                cout << "I claim the word: " << compclaimedwords[c1] << endl;
                computerpointsscored += gamelibrary.checkword(compclaimedwords[c1]);
                referee.addcomputerpoint(gamelibrary.checkword(compclaimedwords[c1])); 
            }
        }
        cout << "Points scored on this turn: " << computerpointsscored << endl;
        cout << "Score so far: You=" << referee.getplayerscore() << " Me=" << referee.getcomputerscore() << endl;        
    }
    cout << "The game is over!" << endl;
    if(referee.getplayerscore() > referee.getcomputerscore()){
        cout << "You beat me with " << referee.getplayerscore() << " points over my " << referee.getcomputerscore() << endl;
    }
    else if(referee.getplayerscore() < referee.getcomputerscore()){
        cout << "I beat you with " << referee.getcomputerscore() << " points over your " << referee.getplayerscore() << endl;
    }
    else{
        cout << "We tied with " << referee.getplayerscore() << " points each." << endl;
    }
    cout << "Thanks for playing!";
    return 0;
}

void processlibrary(ifstream& herp, vector<std::string> &libvect) {
    string in;
    while (herp >> in) {
        libvect.push_back(in);
    }
}

void processpossiblewords(grid a, vector<std::string>& b) {
    b.push_back(a.getxxaxis(a.getlastmove()));
    b.push_back(string(b[0].rbegin(), b[0]. rend()));
    b.push_back(a.getyyaxis(a.getlastmove()));
    b.push_back(string(b[2].rbegin(), b[2]. rend()));
    b.push_back(a.getxyaxis(a.getlastmove()));
    b.push_back(string(b[4].rbegin(), b[4]. rend()));
    b.push_back(a.getyxaxis(a.getlastmove()));
    b.push_back(string(b[6].rbegin(), b[6]. rend()));
}

bool searchvector(vector<std::string>& a, std::string b) {

    int loc = 0;
    while (loc < a.size() && a[loc] != b) {
        ++loc;
    }
    if (loc < a.size() && a[loc] == b) {
        return true;
    } else {
        return false;
    }
}

int wordlengthtopoints(int a) {
    switch (a) {
        case 3:
            return 1;
            break;
        case 4:
            return 2;
            break;
        case 5:
            return 4;
            break;
        case 6:
            return 8;
            break;
        case 7:
            return 16;
            break;
        default:
            return 0;
    }
}

bool testforallwhitespace(string a) {
    for (int counter = 0; counter < a.size(); counter++) {
        if (isspace(a[counter]) == 0) {
            return false;
        }
    }
    return true;
}

string delspaces(string &str) {
    int size = str.length();
    for (int a = 0; a <= size; a++) {
        if (str[a] == ' ') {
            str.erase(str.begin() + a);
            a--;
        }
    }
    return str;
}

aicompmove aibestmove(grid a, library b, gamestate c) {
    int maxscore, lastmovecopy = 0;
    vector<aicompmove> movepool;
    vector<char> availabletiles = c.getcomputertiles();
    vector<std::string> possiblewords;
    lastmovecopy = a.getlastmove();
    for (int columncounter = 1; columncounter < 8; columncounter++) {
        if (!a.columnfull(columncounter)) {
            for (int tilecounter = 0; tilecounter < availabletiles.size(); tilecounter++) {
                if (availabletiles[tilecounter] != '.') {
                    if (movepool.size() == 0) {
                        int emptylistscore = 0;
                        aicompmove aicompmovea;
                        aicompmovea.column = columncounter;
                        aicompmovea.letter = availabletiles[tilecounter];
                        a.placechar(columncounter, availabletiles[tilecounter]);
                        processpossiblewords(a, possiblewords);
                        if (possiblewords[0].size() > 1) {
                            aicompmovea.nextto = true;
                        }
                        if (possiblewords[2].size() > 1) {
                            aicompmovea.nextto = true;
                        }
                        for (int emptylistcounter = 0; emptylistcounter < possiblewords.size(); emptylistcounter++) {
                            if (b.isinlibrary(possiblewords[emptylistcounter])) {
                                emptylistscore += b.checkword(possiblewords[emptylistcounter]);
                            }
                        }
                        maxscore = emptylistscore;
                        movepool.push_back(aicompmovea);
                        a.resetpoint(a.getlastmove());
                        possiblewords.clear();
                    } else {
                        int nextlistscore = 0;
                        aicompmove aicompmoveb;
                        aicompmoveb.column = columncounter;
                        aicompmoveb.letter = availabletiles[tilecounter];
                        a.placechar(columncounter, availabletiles[tilecounter]);
                        processpossiblewords(a, possiblewords);
                        if (possiblewords[0].size() > 1) {
                            aicompmoveb.nextto = true;
                        }
                        for (int nextlistcounter = 0; nextlistcounter < possiblewords.size(); nextlistcounter++) {
                            if (b.isinlibrary(possiblewords[nextlistcounter])) {
                                nextlistscore += b.checkword(possiblewords[nextlistcounter]);
                            }
                        }
                        a.resetpoint(a.getlastmove());
                        possiblewords.clear();
                        if (nextlistscore > maxscore) {
                            movepool.clear();
                            movepool.push_back(aicompmoveb);
                            maxscore = nextlistscore;
                        } else if (nextlistscore == maxscore) {
                            movepool.push_back(aicompmoveb);
                        }
                    }
                }
            }
        }
    }
    a.setlastmove(lastmovecopy);
    vector<aicompmove> consonantmoves;
    for (int consonantcounter = 0; consonantcounter < movepool.size(); consonantcounter++) {
        if ((movepool[consonantcounter].letter != 'a') && (movepool[consonantcounter].letter != 'e') &&
                (movepool[consonantcounter].letter != 'i') && (movepool[consonantcounter].letter != 'o') &&
                (movepool[consonantcounter].letter != 'u')) {
            consonantmoves.push_back(movepool[consonantcounter]);
        }
    }
    if (consonantmoves.size() != 0) {
        movepool = consonantmoves;
    }

    vector<aicompmove> nexttotile;
    for (int nexttotilecounter = 0; nexttotilecounter < movepool.size(); nexttotilecounter++) {
        if (movepool[nexttotilecounter].nextto) {
            nexttotile.push_back(movepool[nexttotilecounter]);
        }
    }
    if (nexttotile.size() != 0) {
        movepool = nexttotile;
    }
    vector<aicompmove> higheralphabet;
    char highestchar;
    for (int higheralphabetcounter = 0; higheralphabetcounter < movepool.size(); higheralphabetcounter++) {
        if (higheralphabetcounter == 0) {
            higheralphabet.push_back(movepool[higheralphabetcounter]);
            highestchar = movepool[higheralphabetcounter].letter;
        } else {
            if (movepool[higheralphabetcounter].letter < highestchar) {
                higheralphabet.clear();
                higheralphabet.push_back(movepool[higheralphabetcounter]);
                highestchar = movepool[higheralphabetcounter].letter;
            } else if (movepool[higheralphabetcounter].letter == highestchar) {
                higheralphabet.push_back(movepool[higheralphabetcounter]);
            }
        }
    }
    if (higheralphabet.size() != 0) {
        movepool = higheralphabet;
    }
    vector<aicompmove> leftmostmove;
    int leftmostpos;
    for (int leftcounter = 0; leftcounter < movepool.size(); leftcounter++) {
        if (leftcounter == 0) {
            leftmostpos = movepool[leftcounter].column;
            leftmostmove.push_back(movepool[leftcounter]);
        } else {
            if (movepool[leftcounter].column < leftmostpos) {
                leftmostpos = movepool[leftcounter].column;
                leftmostmove.clear();
                leftmostmove.push_back(movepool[leftcounter]);
            } else if (movepool[leftcounter].column == leftmostpos) {
                leftmostmove.push_back(movepool[leftcounter]);
            }
        }
    }
    if (leftmostmove.size() != 0) {
        movepool = leftmostmove;
    }
    return movepool[0];
}

void processgame(ifstream& a, vector<std::string>& b, vector<std::string>& c, int& d, int& e) {
    std::string in;
    while (std::getline(a, in)) {
        b.push_back(in);
    };
    c.push_back(delspaces(b[6]));
    c.push_back(delspaces(b[7]));
    b.resize(6);
    std::stringstream ss(b[8]);
    ss << b[8];
    ss >> d >> e;


}
