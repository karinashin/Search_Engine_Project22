#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "include/rapidjson/document.h"
#include "DocParser.h"
#include "DSAVLTree.h"
#include "Word.h"
#include "QueryProcessor.h"
#include "UserInterface.h"

using namespace std;
int main(int argc, char** argv) {
    //mnt/c/users/18476/c++/searchData 2648 files
    //TODO LIST: Fix ranking articles, make persistence file (figure out how to erase contents of file)

    UserInterface parse;
    parse.run(argv[1]);
}
