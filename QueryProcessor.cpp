//
// Created by Karina Shin on 4/19/2022.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(DSAVLTree<Word>& w, DSAVLTree<Word>& o, DSAVLTree<Word>& p)
{
//    words = w;//TODO error
//    orgs = o;
//    people = p;
}

void QueryProcessor::parseQuery(string& query)//parse query
{
    int space = query.find(" ");
//    bool end = false;
    while (space != -1)
    {
        string curr = query.substr(0, space);
        if (curr == "AND" || curr == "OR"){//2 arg operators
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1(query.substr(0, space));//guaranteed to have first word

            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word2(query.substr(0, space));
            query = query.substr(space + 1);
//            if (space != -1){//not at the end of the line
//                word2 = query.substr(0, space);
//            }//second word
//            else{//reached end of line
//                word2 = query;//second word is rest of query
//                end = true;
//            }

            if (curr == "AND")//perform correspondingset operation
                intersection(words.find(words.getRoot(), word1).getDocs(), words.find(words.getRoot(), word2).getDocs());
            else
                setUnion(words.find(words.getRoot(), word1).getDocs(), words.find(words.getRoot(), word2).getDocs());
        }
        else if (curr == "NOT"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1(query.substr(0, space));
            query = query.substr(space + 1);
            complement(words.find(words.getRoot(), word1).getDocs());
        }
        else if (curr == "ORG"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word org(query.substr(0, space));
            query = query.substr(space + 1);
            intersection(finalIndex, orgs.find(orgs.getRoot(), org).getDocs());
            //org.getDocs() returns index where this org appears
        }
        else if (curr == "PERSON"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word person(query.substr(0, space));
            query = query.substr(space + 1);
            intersection(finalIndex, people.find(people.getRoot(), person).getDocs());
        }
        else{//just a term
            Word term(curr);
            setUnion(finalIndex, words.find(words.getRoot(), term).getDocs());
            query = query.substr(space + 1);
            space = query.find(" ");
        }
//        if (end)
//            break;//finished query

//        query = query.substr(space + 1);
//        space = query.find(" ");
    }
}

void QueryProcessor::setUnion(vector<Document>& a, vector<Document>& b)//OR keyword
{

}

void QueryProcessor::intersection(vector<Document>& a, vector<Document>& b)//AND keyword
{

}

void QueryProcessor::complement(vector<Document>& a)//delete set a from finalIndex set
{

}