//
// Created by Karina Shin on 4/19/2022.
//

#ifndef INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJ_QUERYPROCESSOR_H

#include <string>
#include <vector>
#include <algorithm>
#include "Document.h"
#include "DSAVLTree.h"
#include "Word.h"
#include "StopWord.h"
#include "DocParser.h"

class QueryProcessor {
private:
    string query;
    vector<Document> finalIndex;//list of documents that contains the query info
    vector<Word> queryWords;//words in the query, make sure its the actual Word object from the tree (has the doc list)
    vector<Document> best;//list of top 15 results according to freq

public:
    QueryProcessor();

    void parseQuery(string& query, DSAVLTree<Word>& words, DSAVLTree<Word>& orgs, DSAVLTree<Word>& people, StopWord& stop);//parse query
    vector<Word> parseAndOr();
    Word findPersonOrg();//get the full name of the person being searched for (accounts for those w/first+last

    void setUnion(vector<Word> a, DSAVLTree<Word>& tree);//OR keyword
    void intersection(Word& word, DSAVLTree<Word> & tree);//AND keyword
    void addTerm(vector<Document>& a);//add a single term's docs to the final
    void complement(vector<Document>& a);//set subtraction
    void addPersonOrg(vector<Document>& a);//remove any docs that don't include the given person or org

    void rankIndex();//rank the documents in the final index by relevancy/frecuency
    bool specialStopCheck(StopWord& stop, string& word);

    void clearFinal();//resets all vectors for next query
    vector<Document>& getFinal();
    vector<Document>& getBest();//returns the top 15 ranked documents
};


#endif //INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
