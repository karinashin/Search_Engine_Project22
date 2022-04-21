#include <iostream>
#include <string>
#include <fstream>
#include "include/rapidjson/document.h"
#include "DocParser.h"
#include "DSAVLTree.h"
#include "Word.h"
#include "QueryProcessor.h"

using namespace std;
int main(int argc, char** argv) {
//    DocParser parse;
//    cout << "parsing..." << endl;
//    parse.getFiles(argv[2]);//absolute path
//    cout << "done!" << endl;
//    Word w(argv[1]);//search term
//    w.stemming();
//    parse.getWordTree().find(parse.getWordTree().getRoot(), w).printDocs();

    QueryProcessor q;
    string see = "OR facebook instagram NOT bankruptcy ORG snap PERSON cramer";
    q.parseQuery(see);

//    DSAVLTree<Word> num;
//    Word a("a");
//    Word b("b");
//    Word c("c");
//    Word d("d");
//    Word e("e");
//    Word f("f");
//
//    num.insert(c);
//    num.insert(a);
//    num.insert(b);
//    num.insert(e);
//    num.insert(d);
//    num.insert(f);

//    string text = "Hello this is a sentence with GIRAFFES";
//    int space;//index of space character
//    while (space != -1)
//    {
//        space = text.find(" ");
//        Word curr(text.substr(0, space));
//        cout << "current: " << curr.getStr() << endl;
//        text = text.substr(space + 1);//cut off curr word
//    }
}
