#include <iostream>
#include <regex>
#include <sstream>
#include <queue>
#include <cstring>
#include <fstream>

#include "DynamicBitSet.h"
#include "InvertedIndex.h"
#include "SortStation.h"

using namespace std;

string ReadTitle(ifstream & ifs){
    string title;
    smatch smtitle;
    do{
        if (!getline(ifs, title)) return "";
    }while (title[0] != '<');
    regex_search(title, smtitle, regex("\\btitle=\"(.*)\">"));
    return smtitle[1];
}

inline 
void ToLower(string & s){
    transform(s.begin(),
                s.end(),
                s.begin(),
                [](char c) {
                    return (isalnum(c) || c == '\'' || c == '-' ? tolower(c) : ' ');
                    }
                );
}

string ReadArticle(ifstream & ifs){
    string article, tmp;
    while (getline(ifs, tmp)){
        if (tmp == "</doc>") break;
        else article += tmp + ' ';
    }
    ToLower(article);
    return article;
}

void Parsing(vector <string> *titles, CInvertedIndex * ii, ifstream & ifs){
    string title, word;
    stringstream ss;
    uint count = 1;

    while ((title = ReadTitle(ifs)) != ""){
        titles->push_back(title);
        ss.str(ReadArticle(ifs));
        while (ss >> word){
            ii->Insert(word, count);
        }
        ++count;
    }
}

vector<string> ParceToWords(const string & str){
    stringstream ss(str);
    vector <string> words;
    string word;
    while (ss >> word){
        words.push_back(word);
    }
    return words;
}

DynamicBitSet MakeTitles(CInvertedIndex& ii, const string & expression, size_t titlesCount){
    string reversedRecord = SortStation(expression);
    auto tokens = ParceToWords(reversedRecord);
    queue<DynamicBitSet> expr;
    DynamicBitSet dbs1, dbs2;
    for (auto token : tokens){
        if (isOperator(token)){
            dbs1 = expr.front();
            expr.pop();
            switch (token[0])
            {
            case '&':
                dbs2 = expr.front();
                expr.pop();
                dbs1 &= dbs2;
                expr.push(dbs1);
                break;
            case '|':
                dbs2 = expr.front();
                expr.pop();
                dbs1 |= dbs2;
                expr.push(dbs1);
                break;
            case '~':
                dbs1.Not(titlesCount);
                expr.push(dbs1);
                break;
            }
        } else {
            expr.push(ii.Get(token));
        }
    }
    return expr.front();
}

int main(int argc, char *argv[]){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    vector<string> titles;
    CInvertedIndex ii;
    string stringTitle, expression;
    ifstream ifs;
    ofstream ofs;
    DynamicBitSet dbs;

    bool isIndex = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "index") == 0) isIndex = true;
        else if (strcmp(argv[i], "search") == 0) isIndex = false;
        else if (strcmp(argv[i], "--input") == 0) ifs.open(argv[i + 1]);
        else if (strcmp(argv[i], "--output") == 0) ofs.open(argv[i + 1]);
    }

    cout << ifs.is_open() << " " << ofs.is_open() << endl;

    if (isIndex){
        Parsing(&titles, &ii, ifs);
        for (auto title : titles) ofs << title << " ";
        ofs << "\n";
        ii.Write(ofs);
    } else {
        getline(ifs, stringTitle);
        titles = ParceToWords(stringTitle);
        ii.Read(ifs);

        while (getline(ifs, expression)){
            dbs = MakeTitles(ii, expression, titles.size());
            for (decltype(dbs.Size())i = 0; i < dbs.Size(); ++i)
                if (dbs.Get(i)) ofs << titles[i] << "\n";
        }
    }
    return 0;
}
