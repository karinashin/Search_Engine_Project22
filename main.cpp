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
    //mnt/c/users/18476/c++/searchData
    UserInterface parse;
    parse.run(argv[1]);
}
