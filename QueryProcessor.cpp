//
// Created by Karina Shin on 4/19/2022.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(){}

void QueryProcessor::parseQuery(string& q, DSAVLTree<Word>& words, DSAVLTree<Word>& orgs, DSAVLTree<Word>& people, StopWord& stop)//parse query
{
    this->query = q;
    int space;
    while (space != -1)
    {
        space = query.find(" ");//for first word
        Word curr(query.substr(0, space));
        curr.toLower();
        if (specialStopCheck(stop, curr.getStr()))
        {
            query = query.substr(space + 1);//cut off word
            continue;//skip stop words
        }

        if (curr.getStr() == "and" || curr.getStr() == "or"){
            vector<Word> wordList = parseAndOr();
            if (curr.getStr() == "and"){//perform corresponding set operation
                for (int i = 0; i < wordList.size(); i++){
                    intersection(wordList.at(i), words);
                }
            }
            else{
                for (int i = 0; i < wordList.size(); i++)
                    setUnion(wordList.at(i), words);
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

            if (words.contains(word1)){
                complement(words.find(words.getRoot(), word1).getDocs());
            }
            else
                cout << word1.getStr() << " is not found." << endl;
        }
        else if (curr.getStr() == "org"){
            query = query.substr(space + 1);//cut off operator
            Word org(findPersonOrg());

            if (orgs.contains(org)){
                addPersonOrg(orgs.find(orgs.getRoot(), org).getDocs());
                queryWords.push_back(orgs.find(orgs.getRoot(), org));
            }
            else
                cout << org.getStr() << " is not found." << endl;
        }
        else if (curr.getStr() == "person"){
            query = query.substr(space + 1);//cut off operator KEEP
            Word person(findPersonOrg());
            if (people.contains(person)){
                addPersonOrg(people.find(people.getRoot(), person).getDocs());//index has to include only those that have this person
                queryWords.push_back(people.find(people.getRoot(), person));
            }
            else
                cout << person.getStr() << " is not found." << endl;
        }
        else{//just a term
            Word term(curr);
            term.stemming();
            if (words.contains(term)){
                addTerm(words.find(words.getRoot(), term).getDocs());
                queryWords.push_back(words.find(words.getRoot(), term));
            }
            else
                cout << term.getStr() << " is not found." << endl;
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
    while (check)
    {
        Word word;
        space = query.find(" ");
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
    Word person(name);

    return person;
}

void QueryProcessor::setUnion(Word& word, DSAVLTree<Word> &tree)
{
    vector<Document> temp;
    if (tree.contains(word)){
        queryWords.push_back(tree.find(tree.getRoot(), word));
        temp = tree.find(tree.getRoot(), word).getDocs();
    }
    else
        cout << word.getStr() << " not found" << endl;

    for (int i = 0; i < temp.size(); i++)
    {
        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), temp.at(i));
        if (it == finalIndex.end()){//doc of a exists in final, only add docs that are in word.getDocs and final
            finalIndex.push_back(temp.at(i));//add the docs that contain the word from the finalIndex
        }
    }
}

void QueryProcessor::intersection(Word& word, DSAVLTree<Word>& tree)//AND keyword
{
    vector<Document> finalList;
    if (finalIndex.size() == 0)//first word
    {
        if (tree.contains(word))
        {
            queryWords.push_back(tree.find(tree.getRoot(), word));
            vector<Document> temp = tree.find(tree.getRoot(), word).getDocs();
            for (int i = 0; i < temp.size(); i++)
                finalIndex.push_back(temp.at(i));
        }
        else
            cout << word.getStr() << " not found" << endl;
    }
    else
    {
        vector<Document> temp;
        if (tree.contains(word)){
            queryWords.push_back(tree.find(tree.getRoot(), word));
            temp = tree.find(tree.getRoot(), word).getDocs();
        }
        else
            cout << word.getStr() << " not found" << endl;
        for (int i = 0; i < temp.size(); i++)
        {
            vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), temp.at(i));
            if (it != finalIndex.end()){//doc of a exists in final, only add docs that are in word.getDocs and final
                finalList.push_back(*it);//add the docs that contain the word from the finalIndex
            }
        }
        finalIndex.clear();
        finalIndex = finalList;//should only contain docs that contain the word
    }
}

void QueryProcessor::addTerm(vector<Document>& a)
{
    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (finalIt == finalIndex.end()){//if the doc is NOT in the final index, add it
            finalIndex.push_back(a.at(i));
        }
    }
}

void QueryProcessor::complement(vector<Document>& a)//delete set a from finalIndex set
{
    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (it != finalIndex.end())//doc of a exists in final
            finalIndex.erase(it);//remove that index from final
    }
}

void QueryProcessor::addPersonOrg(vector<Document>& a)//remove any docs from final that don't include the person/org
{
    //if finalIndex already has values, remove any docs that don't contain person/org
    //else: query only has person/org keywords, just add the files that contain the person/org
    vector<Document> personList;
    if (finalIndex.size() > 0)
    {
        for (int i = 0; i < a.size(); i++)//used to be finalIndex.size();
        {//get person/org document index list from doc parser (a), each file in finalIndex should be in the person/orgs index
            vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
            if (it != finalIndex.end()){//doc of person/org list exists in final index, keep
                personList.push_back(*it);
            }
        }
        finalIndex.clear();
        finalIndex = personList;
    }
    else{//finalIndex doesn't have any other values in it
        for (int i = 0; i < a.size(); i++)
        {
            vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
            if (it == finalIndex.end())//doc of a does NOT exist in final
                finalIndex.push_back(a.at(i));//add files with person/org
        }
    }
}

void QueryProcessor::rankIndex()
{
    cout << "Rank index" << endl;
    cout << "finalIndex size " << finalIndex.size() << endl;
    cout << "query words size: " << queryWords.size() << endl;
    vector<int> freqs; //corresponding total freqs for each doc in finalIndex
    for (int queryIndex = 0; queryIndex < finalIndex.size(); queryIndex++)//for every doc in final index
    {
        int sum = 0;
        for (int i = 0; i < queryWords.size(); i++)//for every word in query
        {
            //if its an OR query, not every word will be in every file of finalIndex
            //get the each words frequency in the current doc and add them all together
            vector<Document>::iterator it = find(queryWords.at(i).getDocs().begin(), queryWords.at(i).getDocs().end(), finalIndex.at(queryIndex));
            if (it != queryWords.at(i).getDocs().end())//this word is present in the doc
                sum += queryWords.at(i).getDocFreq(finalIndex.at(queryIndex));//add total freq of each word for this doc
        }
        freqs.push_back(sum);
    }
    cout << "done with for loop" << endl;
    //result: total frequency for each doc

    //get the top 15 docs with the highest freq
    for (int n = 0; n < 15; n++){
        if (n > freqs.size() || freqs.size() == 0)//less that 15 docs in the finalIndex
            break;
        int highest = freqs.at(0);
        int index = 0;
        for (int i = 1; i < freqs.size(); i++)//find the next highest freq
        {
            if (freqs.at(i) > highest){//get highest freq
                highest = freqs.at(i);
                index = i;
            }
        }
        best.push_back(finalIndex.at(index));//get the corresponding doc for that freq
        freqs.erase(freqs.begin() + index);
        finalIndex.erase(finalIndex.begin() + index);
    }
}

bool QueryProcessor::specialStopCheck(StopWord& stop, string& word)
{
    if (word == "and" || word == "or" || word == "not")//exclude key words
        return false;
    else if (stop.isStopWord(word))
        return true;
    return false;
}

void QueryProcessor::clearFinal()//reset all vectors for next query
{
    finalIndex.erase(finalIndex.begin(), finalIndex.end());
    queryWords.erase(queryWords.begin(), queryWords.end());
    best.erase(best.begin(), best.end());
}

vector<Document>& QueryProcessor::getFinal() { return finalIndex; }
vector<Document>& QueryProcessor::getBest() { return best; }
