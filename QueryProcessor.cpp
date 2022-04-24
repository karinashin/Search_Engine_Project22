//
// Created by Karina Shin on 4/19/2022.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(){}
QueryProcessor::QueryProcessor(DSAVLTree<Word>& w, DSAVLTree<Word>& o, DSAVLTree<Word>& p)
{
//    words = w;//TODO error
//    orgs = o;
//    people = p;
}

void QueryProcessor::parseQuery(string& query, StopWord& stop)//parse query
{
    std::cout << "NEW QUERY: " << query << std::endl;
    int space;
    while (space != -1)
    {
        space = query.find(" ");
        string curr = query.substr(0, space);
        if (stop.isStopWord(curr))
            continue;//skip stop words

        if (curr == "AND" || curr == "OR"){//2 arg operators
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1(query.substr(0, space));//guaranteed to have first word
            word1.stemming();
            std::cout << word1.getStr() << std::endl;
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");//find next word
            Word word2;
            if (space != -1){//not at the end of the line
                word2 = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                word2 = query;//second word is rest of query
                query = "";//empty query
            }
            word2.stemming();
            std::cout << word2.getStr() << std::endl;

            if (curr == "AND"){//perform corresponding set operation
                std::cout << "intersection" << std::endl;
                intersection(words.find(words.getRoot(), word1).getDocs(), words.find(words.getRoot(), word2).getDocs());
            }
            else{
                std::cout << "union" << std::endl;
                setUnion(words.find(words.getRoot(), word1).getDocs(), words.find(words.getRoot(), word2).getDocs());
            }
        }
        else if (curr == "NOT"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1;
            if (space != -1){//not at the end of the line
                word1 = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                word1 = query;//second word is rest of query
                query = "";//empty query
            }
            word1.stemming();
            std::cout << word1 << std::endl;
            std::cout << "complement" << std::endl;
            complement(words.find(words.getRoot(), word1).getDocs());
        }
        else if (curr == "ORG"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word org;
            if (space != -1){//not at the end of the line
                org = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                org = query;//second word is rest of query
                query = "";//empty query
            }
            org.stemming();
            std::cout << org << std::endl;
            std::cout << "org intersection" << std::endl;
            addPersonOrg(orgs.find(orgs.getRoot(), org).getDocs());
            //org.getDocs() returns index where this org appears
        }
        else if (curr == "PERSON"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word person;
            if (space != -1){//not at the end of the line
                person = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                person = query;//second word is rest of query
                query = "";//empty query
            }
            person.stemming();
            std::cout << person << std::endl;
            std::cout << "person intersection" << std::endl;
            addPersonOrg(people.find(people.getRoot(), person).getDocs());//index has to include only those that have this person
        }
        else{//just a term
            Word term(curr);
            term.stemming();
            std::cout << term << std::endl;
            std::cout << "standard union" << std::endl;
            setUnion(finalIndex, words.find(words.getRoot(), term).getDocs());
            query = query.substr(space + 1);
            space = query.find(" ");
        }
    }
}

void QueryProcessor::setUnion(vector<Document>& a, vector<Document>& b)//OR keyword
{
    //add indexes of a and b into finalIndex if they aren't already
    std::cout << "union" << std::endl;
    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (it == finalIndex.end())//if the doc is NOT in the final index, add it
            finalIndex.push_back(a.at(i));
    }
    for (int i = 0; i < b.size(); i++)
    {
        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), b.at(i));
        if (it == finalIndex.end())//if the doc is NOT in the final index, add it
            finalIndex.push_back(b.at(i));
    }
}

void QueryProcessor::intersection(vector<Document>& a, vector<Document>& b)//AND keyword
{
    //AND a and b together and add to the final index, no duplicates
    //only add if the document is in both a and b
    std::cout << "intersection" << std::endl;

    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator it = find(b.begin(), b.end(), a.at(i));//look for each element of a in b
        if (it != b.end())//doc exits in b
        {
            vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), *it);
            if (finalIt == finalIndex.end())//if the doc is NOT in the final index, add it
                finalIndex.push_back(*it);
        }
    }
}

void QueryProcessor::complement(vector<Document>& a)//delete set a from finalIndex set
{
    std::cout << "complement" << std::endl;
    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (it != finalIndex.end())//doc of a exists in final
            finalIndex.erase(it);//remove that index from final
    }
}

void QueryProcessor::addPersonOrg(vector<Document>& a)//remove any docs from final that don't include the person/org
{
    vector<Document> temp;//TODO might be inefficient to make a new vector and copy elements over
    for (int i = 0; i < finalIndex.size(); i++)
    {
        vector<Document>::iterator it = find(a.begin(), a.end(), finalIndex.at(i));
        if (it != a.end())//doc of a exists in final
            temp.push_back(finalIndex.at(i));
    }
    finalIndex = temp;
}