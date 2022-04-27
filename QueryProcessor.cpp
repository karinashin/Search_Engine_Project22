//
// Created by Karina Shin on 4/19/2022.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(){}

void QueryProcessor::parseQuery(string& q, DSAVLTree<Word>& words, DSAVLTree<Word>& orgs, DSAVLTree<Word>& people, StopWord& stop)//parse query
{
    this->query = q;
    std::cout << "NEW QUERY: " << query << std::endl;
    int space;
    while (space != -1)
    {
        space = query.find(" ");//for first word
        Word curr(query.substr(0, space));
        curr.toLower();
        cout << curr.getStr() << endl;
        if (specialStopCheck(stop, curr.getStr()))
            continue;//skip stop words

        if (curr.getStr() == "and" || curr.getStr() == "or"){
            if (curr.getStr() == "and"){//perform corresponding set operation
                std::cout << "intersection" << std::endl;
                intersection(parseAndOr(), words);//TODO add case for if word isn't in tree
            }
            else{
                std::cout << "union" << std::endl;
                setUnion(parseAndOr(), words);
            }
        }
        else if (curr.getStr() == "not"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1;
            if (space != -1){//not at the end of the line
                word1 = query.substr(0, space);
                query = query.substr(space + 1);
            }
            else{//reached end of line
                word1 = query;//second word is rest of query
                query = "";//empty query
            }
            word1.stemming();
            std::cout << word1 << std::endl;
            std::cout << "complement" << std::endl;
            complement(words.find(words.getRoot(), word1).getDocs());
        }
        else if (curr.getStr() == "org"){
            query = query.substr(space + 1);//cut off operator
            Word org(findPersonOrg());
            std::cout << "org intersection" << std::endl;
            addPersonOrg(orgs.find(orgs.getRoot(), org).getDocs());
        }
        else if (curr.getStr() == "person"){
            query = query.substr(space + 1);//cut off operator KEEP
            cout << "query: " << query << endl;
            Word person(findPersonOrg());
            std::cout << "person intersection" << std::endl;
            addPersonOrg(people.find(people.getRoot(), person).getDocs());//index has to include only those that have this person
        }
        else{//just a term
            Word term(curr);
            term.stemming();
            addTerm(words.find(words.getRoot(), term).getDocs());
            query = query.substr(space + 1);
        }
        space = query.find(" ");//to check if youve reached the end of the query
    }

    rankIndex();
}

vector<Word> QueryProcessor::parseAndOr()
{
    bool check = true;
    vector<Word> args;//words to "and" or "or" together

    int space = query.find(" ");
    query = query.substr(space + 1);//cut off operator
    cout << "query: " << query << endl;
    while (check)
    {
        Word word;
        space = query.find(" ");
        cout << space << endl;
        if (space != -1){//not at the end of the line
            if (query.substr(0, space) != "AND" && query.substr(0, space) != "OR" && query.substr(0, space) != "NOT" && query.substr(0, space) != "PERSON" && query.substr(0, space) != "ORG")
            {//if its not a key word
                word = query.substr(0, space);
                word.stemming();
                args.push_back(word);
                query = query.substr(space + 1);
            }
            else
                break;//reached a key word
        }

        else{//reached end of line
            word = query;//word is rest of query
            query = "";//empty query
            word.stemming();
            args.push_back(word);
            break;
        }
    }

//    cout << "args: " << endl;
//    for (int i = 0; i < args.size(); i++)
//        cout << args.at(i) << endl;

    return args;
}

Word QueryProcessor::findPersonOrg()//operator is already removed from query
{
    int count = 0;
    int space = query.find(" ");
    string curr;// = query.substr(0, space);
    string name = "";// = curr;//first word

    while ((curr != "AND" && curr != "OR" && curr != "NOT" && curr != "ORG" && curr != "PERSON") || space != -1)
    {
        if (space != -1){//not at the end of the line
            curr = query.substr(0, space);
            query = query.substr(space + 1);
        }
        else{//reached end of line
            curr = query;//second word is rest of query
            query = "";//empty query
            if (count != 0)
                name += " ";
            name += curr;
            break;
        }
        cout << curr << endl;
        if (count != 0)
            name += " ";
        name += curr;
        space = query.find(" ");
        count++;
    }
    cout << "Name: " << name << endl;
    Word person(name);

    return person;
}

//void QueryProcessor::setUnion(vector<Document>& a, vector<Document>& b)//OR keyword
//{
//    //add indexes of a and b into finalIndex if they aren't already
//    std::cout << "union" << std::endl;
//    for (int i = 0; i < a.size(); i++)
//    {
//        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
//        if (it == finalIndex.end()){//if the doc is NOT in the final index, add it
//            finalIndex.push_back(a.at(i));
//        }
//    }
//    for (int i = 0; i < b.size(); i++)
//    {
//        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), b.at(i));
//        if (it == finalIndex.end())//if the doc is NOT in the final index, add it
//            finalIndex.push_back(b.at(i));
//    }
//}

//void QueryProcessor::intersection(vector<Document>& a, vector<Document>& b)//AND keyword
//{
//    //AND a and b together and add to the final index, no duplicates
//    //only add if the document is in both a and b
//    std::cout << "intersection" << std::endl;
//
//    for (int i = 0; i < a.size(); i++)
//    {
//        vector<Document>::iterator it = find(b.begin(), b.end(), a.at(i));//look for each element of a in b
//        if (it != b.end())//doc exits in b
//        {
//            vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), *it);
//            if (finalIt == finalIndex.end())//if the doc is NOT in the final index, add it
//                finalIndex.push_back(*it);
//        }
//    }
//}

void QueryProcessor::setUnion(vector<Word> a, DSAVLTree<Word>& tree)//OR keyword
{
    for (int i = 0; i < a.size(); i++)//for every word object in the OR operator
    {
//        cout << a.at(i).getStr() << endl;
        vector<Document> temp = tree.find(tree.getRoot(), a.at(i)).getDocs();
        for (int d = 0; d < temp.size(); d++)//for every doc in the Word objects index
        {
            vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), temp.at(d));
            if (it == finalIndex.end()){//if the doc is NOT in the final index, add it
                finalIndex.push_back(temp.at(d));
            }
        }
    }
}

void QueryProcessor::intersection(vector<Word> a, DSAVLTree<Word>& tree)//AND keyword
{
    bool check = true;
    vector<Document> temp = tree.find(tree.getRoot(), a.at(0)).getDocs();
    for (int i = 0; i < temp.size(); i++)//for each doc of the first word (Word)
    {
        vector<Document>::iterator it;
        for (int j = 1; j < a.size(); j++){//check if the doc is in every other docs index (a.at(j))
            vector<Document> other = tree.find(tree.getRoot(), a.at(j)).getDocs();
            it = find(other.begin(), other.end(), temp.at(i));//look for each element of a in b
            if (it == other.end())//doc does NOT exit in another words index
            {
                check = false;
                break;//don't add doc to final index
            }
        }
        if (check){//if the doc is in all word's indexes
            vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), *it);
            if (finalIt == finalIndex.end())//if the doc is NOT in the final index, add it
                finalIndex.push_back(*it);
        }
    }
}

void QueryProcessor::addTerm(vector<Document>& a)
{
    cout << "addTerm" << endl;
    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (finalIt == finalIndex.end()){//if the doc is NOT in the final index, add it
            finalIndex.push_back(a.at(i));
//            cout << "added new " << endl;
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
    for (int i = 0; i < a.size(); i++)//TODO resulting files should all contain the person or org
    {
        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (it == finalIndex.end())//doc of a does NOT exist in final
            finalIndex.push_back(a.at(i));
    }
}

void QueryProcessor::rankIndex()
{
    //TODO
}

bool QueryProcessor::specialStopCheck(StopWord& stop, string& word)
{
    if (word == "AND" || word == "OR" || word == "NOT")//exclude key words
        return false;
    else if (stop.isStopWord(word))
        return true;
    return false;
}

void QueryProcessor::clearFinal()
{
    finalIndex.erase(finalIndex.begin(), finalIndex.end());
}

vector<Document>& QueryProcessor::getFinal() { return finalIndex; }
