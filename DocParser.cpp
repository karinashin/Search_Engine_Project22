//
// Created by Karina Shin on 4/9/2022.
//

#include "DocParser.h"
DocParser::DocParser() {}

void DocParser::parse(const string& filename, StopWord& stop) {
    cout << "NEW DOC: " << filename << endl;
    numDocs++;

    //TODO parse for org and person, put unique ones into avl tree
    //TODO write to persistence file
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

    Document currDoc(title, pub, date, filename, id);//make doc object for this file

    //checks
    doc["entities"].IsObject();
    doc["entities"].IsArray();

    for (auto &v : doc["entities"]["persons"].GetArray()) {//parse for person
        Word person(v["name"].GetString());
        if (!people.contains(person)){//if the word is not already in the tree/new unique word
            person.incrFreq(currDoc);
            people.insert(person);
        }
        else{
            people.find(people.getRoot(), person).incrFreq(currDoc);//index document on object in tree
        }
    }
    for (auto &v : doc["entities"]["organizations"].GetArray()) {//parse for orgs
        Word o(v["name"].GetString());
        if (!orgs.contains(o)){//if the word is not already in the tree/new unique word
            o.incrFreq(currDoc);
            orgs.insert(o);
        }
        else{
            orgs.find(orgs.getRoot(), o).incrFreq(currDoc);//index document on object in tree
        }
    }

    string text = doc["text"].GetString();

    int space;
    while (space != -1)//WORDS
    {
//        text = text.substr(space);//cut off curr word
        space = text.find(" ");
        Word curr(text.substr(0, space));
//        cout << "current: " << curr.getStr() << endl;
        curr.toLower();//remove caps
        if (stop.isStopWord(curr.getStr())){
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
//        std::cout << curr << std::endl;
//        Node<Word>*& found = words.find(words.getRoot(), curr);
//        if (found->getLeft() == nullptr && found->getRight() == nullptr && !(found->getData() == curr)){//curr is not in tree
//            cout << "seg fault" << endl;
//            words.insert(curr);
//        }
//        curr.incrFreq(currDoc);

        text = text.substr(space + 1);//cut off curr word
    }
}

void DocParser::getFiles(const string& directory, StopWord& stop)
{
    for (const auto & entry : fs::recursive_directory_iterator(directory)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                parse(filename, stop);
            }
        }
    }
}

void DocParser::persistenceIndex()//read in persistence file to index words
{

}

//vector<Document>& DocParser::findIndex(Word& obj)
//{
//    return words.find(words.getRoot(), obj).getDocs();
////    return words.find(words.getRoot(), obj)->getData().getDocs();
//}

//vector<Document>& DocParser::findWordIndex(Word& w) { return w.getDocs(); }
//vector<Document>& DocParser::findOrgIndex(Word& org) { return org.getDocs(); }
//vector<Document>& DocParser::findPersonIndex(Word& p) {return p.getDocs(); }

DSAVLTree<Word>& DocParser::getWordTree() { return words; }
DSAVLTree<Word>& DocParser::getOrgTree() { return orgs; }
DSAVLTree<Word>& DocParser::getPersonTree() { return people; }

int DocParser::getNumDocs() { return numDocs; }
