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

    UserInterface parse;
    cout << "parsing..." << endl;
    parse.parseDocs(argv[2]);//absolute path
    cout << "done!" << endl;
    Word w(argv[1]);//search term
    w.stemming();

    Word org("wall street journal");
    Word p("cramer");
    parse.getDocParser().getWordTree().find(parse.getDocParser().getWordTree().getRoot(), w).printDocs();
    parse.getDocParser().getOrgTree().find(parse.getDocParser().getOrgTree().getRoot(), org).printDocs();
    parse.getDocParser().getPersonTree().find(parse.getDocParser().getPersonTree().getRoot(), p).printDocs();

//    parse.getWordTree().find(parse.getWordTree().getRoot(), w)->getData().printDocs();

}
