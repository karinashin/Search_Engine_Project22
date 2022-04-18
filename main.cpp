#include <iostream>
#include <string>
#include <fstream>
#include "include/rapidjson/document.h"
#include "DocParser.h"
#include "DSAVLTree.h"
#include "Word.h"

using namespace std;
int main(int argc, char** argv) {
    DocParser parse;
    cout << "parsing..." << endl;
    parse.getFiles(argv[1]);
    cout << "done!" << endl;
//    cout << parse.getWordTree().getRoot()->getData().getStr() << endl;
//    cout << parse.getWordTree().getCount();
//    Word w("investors");
    Word w(argv[2]);
    w.stemming();
    parse.getWordTree().find(parse.getWordTree().getRoot(), w).printDocs();
}
