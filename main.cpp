#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "include/rapidjson/document.h"
#include "DocParser.h"
#include "DSAVLTree.h"
#include "Word.h"
#include "QueryProcessor.h"
#include "UserInterface.h"

using namespace std;
int main(int argc, char** argv) {
    //TODO LIST: Rank indexes, make persistence file (figure out how to erase contents of file), figure out publication info, try to combine fine/contains
    //add a check for if the word is not found
    UserInterface parse;
    parse.run(argv[2]);
//    parse.parseDocs(argv[2]);//absolute path
//    Word w(argv[1]);//search term
//    w.stemming();
//    parse.getDocParser().getOrgTree().inOrder(parse.getDocParser().getOrgTree().getRoot());
}
