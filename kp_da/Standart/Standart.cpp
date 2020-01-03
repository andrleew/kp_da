#include <iostream>
#include <queue>
#include <fstream>
#include <functional>

#include "DynamicBitSet.h"
#include "InvertedIndex.h"
#include "SortStation.h"
#include "Parcer.h"

using namespace std;

enum eMode{
    eModeIndex,
    eModeSearch,
    eModeUnknown
};

struct TArgvParcer{
    ifstream inputFile, indexFile;
    ofstream outputFile;
    eMode mode = eModeUnknown;
    bool isFoolOutput = false;

};

DynamicBitSet MakeTitles(CInvertedIndex& ii, const string & expression, size_t titlesCount){
    string reversedRecord = SortStation(expression);
    auto tokens = Split(reversedRecord);
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

TArgvParcer* ArgvParcer(const int argc, char * argv[]){
    TArgvParcer* argvParcer = new TArgvParcer();
    for (int i = 1; i < argc; ++i){
        if (strcmp(argv[i], "index") == 0) argvParcer->mode = eModeIndex;
        else if (strcmp(argv[i], "search") == 0) argvParcer->mode = eModeSearch;
        else if (strcmp(argv[i], "--input") == 0) argvParcer->inputFile.open(argv[++i], ios::binary);
        else if (strcmp(argv[i], "--output") == 0) argvParcer->outputFile.open(argv[++i], ios::binary);
        else if (strcmp(argv[i], "--index") == 0) argvParcer->indexFile.open(argv[++i], ios::binary);
        else if (strcmp(argv[i], "--full-output") == 0) argvParcer->isFoolOutput = true;
    }
    return argvParcer;
}

void Index(TArgvParcer & argvParcer){
    CInvertedIndex ii;
    vector <string> titles;
    stringstream outbuf;
    Parsing(titles, ii, argvParcer.inputFile);

    copy(titles.begin(), titles.end(), ostream_iterator<string>(outbuf, "%20"));
    outbuf << "\n";
    argvParcer.outputFile.write(outbuf.str().data(), outbuf.str().size());
    // argvParcer.outputFile << "\n";
    ii.Write(argvParcer.outputFile);

    argvParcer.inputFile.close();
    argvParcer.outputFile.close();
}

void Search(TArgvParcer & argvParcer){
    CInvertedIndex ii;
    string str;
    getline(argvParcer.indexFile, str);
    vector <string> titles;

    size_t pos;
    while ((pos = str.find("%20")) != string::npos){
        titles.push_back(str.substr(0, pos));
        str.erase(0, pos + 3);
    }

    ii.Read(argvParcer.indexFile);
    cout << ii.Size() << "\n";


    // copy(titles.begin(), titles.end(), ostream_iterator<string> (cout, "%20"));
    // cout << "\n";
    // ii.Print();
    DynamicBitSet dbs;

    while (getline(argvParcer.inputFile, str)){
        dbs = MakeTitles(ii, str, titles.size());
        for (decltype(dbs.Size())i = 0; i < dbs.Size(); ++i)
            if (dbs.Get(i)) argvParcer.outputFile << titles[i] << "\n";
    }
}

function <void (TArgvParcer&)> GetMainFunction(const TArgvParcer& argvParcer){
    if (argvParcer.mode == eModeIndex) return Index;
    else if (argvParcer.mode == eModeSearch) return Search;
    else throw -1;
}

int main(int argc, char *argv[]){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto argvParcer = ArgvParcer(argc, argv);
    auto MainFunction = GetMainFunction(*argvParcer);
    MainFunction(*argvParcer);

    delete argvParcer;
    return 0;
}
