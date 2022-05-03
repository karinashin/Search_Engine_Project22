//
// Created by Karina Shin on 4/9/2022.
//

#include "DocParser.h"
DocParser::DocParser() {}

void DocParser::parse(const string& filename, StopWord& stop) {
    numDocs++;

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
        space = text.find(" ");
        Word curr(text.substr(0, space));
        curr.toLower();//remove caps
        curr.removePunc();//remove punctuation
        curr.stemming();
        if (stop.isStopWord(curr.getStr())){
            text = text.substr(space + 1);//cut off curr word
            space = text.find(" ");
            continue;//don't add to tree
        }

        if (curr.getStr().empty()){//don't insert an empty string
            text = text.substr(space + 1);
            space = text.find(" ");
            continue;
        }

        //put unique words into the avl tree
        if (!words.contains(curr)){//if the word is not already in the tree/new unique word
            curr.incrFreq(currDoc);
            words.insert(curr);
        }
        else{
            words.find(words.getRoot(), curr).incrFreq(currDoc);//index document on object in tree
        }

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

DSAVLTree<Word>& DocParser::getWordTree() { return words; }
DSAVLTree<Word>& DocParser::getOrgTree() { return orgs; }
DSAVLTree<Word>& DocParser::getPersonTree() { return people; }

int DocParser::getNumDocs() { return numDocs; }
