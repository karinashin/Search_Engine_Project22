//
// Created by Karina Shin on 4/23/2022.
//

#ifndef INC_22S_FINAL_PROJ_STOPWORD_H
#define INC_22S_FINAL_PROJ_STOPWORD_H

#include <iostream>
#include <fstream>
#include <string>
#include "DSAVLTree.h"

using namespace std;

class StopWord {
private:
    DSAVLTree<string> stops;
public:
    StopWord();
    bool isStopWord(string& str);
};


#endif //INC_22S_FINAL_PROJ_STOPWORD_H
