//
// Created by Karina Shin on 4/9/2022.
//

#include "DocParser.h"
DocParser::DocParser()
{
    ifstream stop;//make the stop words AVL tree
    stop.open("stopWords.txt");
    string curr;
    while (getline(stop, curr))//make an avl tree of stop words
    {
        string s = curr.substr(0, curr.length()-1);//cut off end char
        stops.insert(s);
    }
}

DocParser::DocParser(DSAVLTree<string>& stopWords)
{
    //TODO
}

void DocParser::parse(const string& filename) {
    cout << "NEW DOC: " << filename << endl;
    //TODO parse for org and person, put unique ones into avl tree
    //parse main text
    rapidjson::Document doc;

    //for every file in the folder
    ifstream stream;
    stream.open(filename);

    string wholeFile;
    string temp;
    while (getline(stream, temp))
        wholeFile += temp;

    stream.close();

    doc.Parse(wholeFile.c_str());
    if (!doc.IsObject()) cout << "somethings wrong" << endl;

    //make Document object for current file
    string title = doc["title"].GetString();
    string date = doc["thread"]["published"].GetString();
    string id = doc["uuid"].GetString();
    string pub = doc["thread"]["site"].GetString();//TODO wheres the pub? this is the site name

    Document currDoc(title, pub, date, filename, id);

    string text = doc["text"].GetString();

    int space;
    while (space != -1)//WORDS
    {
//        text = text.substr(space);//cut off curr word
        space = text.find(" ");
        Word curr(text.substr(0, space));
//        cout << "current: " << curr.getStr() << endl;
        curr.toLower();//remove caps
        if (isStopWord(curr.getStr())){
            text = text.substr(space + 1);//cut off curr word
            space = text.find(" ");
            continue;//don't add to tree
        }
        curr.removePunc();//remove punctuation
        curr.stemming();
//        cout << "current: " << curr.getStr() << endl;
        //put unique words into the avl tree

        if (!words.contains(curr)){//if the word is not already in the tree/new unique word
            curr.incrFreq(currDoc);
            words.insert(curr);
//            cout << "inserted " << curr.getStr() << endl;
        }
        else{
            words.find(words.getRoot(), curr).incrFreq(currDoc);//index document on object in tree
//            curr.incrFreq(currDoc);//indexes a temporary variable, not the actual Word object in the tree
        }
        text = text.substr(space + 1);//cut off curr word
    }
}

void DocParser::getFiles(const string& directory)
{
    for (const auto & entry : fs::recursive_directory_iterator(directory)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                parse(filename);
            }
        }
    }
}

vector<Document>& DocParser::findIndex(Word& obj)
{
    return words.find(words.getRoot(), obj).getDocs();
}

bool DocParser::isStopWord(string& str)
{
    return stops.contains(str);//if str is in the avl tree, its a stop word
}

vector<Document>& DocParser::findWordIndex(Word& w) { return w.getDocs(); }
vector<Document>& DocParser::findOrgIndex(Word& org) { return org.getDocs(); }
vector<Document>& DocParser::findPersonIndex(Word& p) {return p.getDocs(); }

DSAVLTree<Word>& DocParser::getWordTree() { return words; }
DSAVLTree<Word>& DocParser::getOrgTree() { return orgs; }
DSAVLTree<Word>& DocParser::getPersonTree() { return people; }
