#include <iostream>
#include <queue>
#include <fstream>
#include <functional>

#include "DynamicBitSet.h"
#include "InvertedIndex.h"
#include "SortStation.h"
#include "Parcer.h"

using namespace std;

const string TITLE_SUFFIX = ".title";

enum eMode{
    eModeIndex,
    eModeSearch,
    eModeUnknown
};

struct TArgvParcer{
    ifstream inputFile;
    string indexFile, outputFile;
    eMode mode = eModeUnknown;
    bool isFoolOutput = false;
};

DynamicBitSet MakeTitles(InvertedIndex& ii, const string & expression, size_t titlesCount){
    string reversedRecord = SortStation(expression);
    auto tokens = Split(reversedRecord);
    for (auto& token : tokens)
        if (!isOperator(token)) ii.RunGet(token);
    auto bits = ii.GetAll();
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
            expr.push(bits[token]);
        }
    }
    return expr.front();
}

TArgvParcer* ArgvParcer(const int argc, char * argv[]){
    TArgvParcer* argvParcer = new TArgvParcer();
    for (int i = 1; i < argc; ++i){
        if (strcmp(argv[i], "index") == 0) argvParcer->mode = eModeIndex;
        else if (strcmp(argv[i], "search") == 0) argvParcer->mode = eModeSearch;
        else if (strcmp(argv[i], "--input") == 0) argvParcer->inputFile.open(argv[++i]);
        else if (strcmp(argv[i], "--output") == 0) argvParcer->outputFile = argv[++i];
        else if (strcmp(argv[i], "--index") == 0) argvParcer->indexFile = argv[++i];
        else if (strcmp(argv[i], "--full-output") == 0) argvParcer->isFoolOutput = true;
    }
    return argvParcer;
}

void Index(TArgvParcer & argvParcer){
    InvertedIndex ii;
    vector <string> titles;
    stringstream outbuf;
    ofstream titleFile (argvParcer.outputFile + TITLE_SUFFIX);
    Parsing(titles, ii, argvParcer.inputFile);

    copy(titles.begin(), titles.end(), ostream_iterator<string>(outbuf, "%20"));
    outbuf << "\n";
    titleFile.write(outbuf.str().data(), outbuf.str().size());
    ii.Write(argvParcer.outputFile);

    cout << ii.Size() << "\n";

    argvParcer.inputFile.close();
    titleFile.close();
}

void SplitByP20(const std::string& str, vector <string> & titles) {
    string title;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '%') {
            if (str[++i] == '2') {
                if (str[++i] == '0') {
                    titles.push_back(title);
                    title.clear();
                    continue;
                } else title += "%2";
            } else title += "%";
        }
        title += str[i];
    }
}

void Search(TArgvParcer & argvParcer){
    InvertedIndex ii;
    ifstream ifs (argvParcer.indexFile + TITLE_SUFFIX);
    vector <string> titles;
    string str;
    getline(ifs, str);
    ifs.close();

    SplitByP20(str, titles);

    ii.Read(argvParcer.indexFile);
    cout << ii.Size() << "\n";


    // copy(titles.begin(), titles.end(), ostream_iterator<string> (cout, "%20"));
    // cout << "\n";
    // ii.Print();
    DynamicBitSet dbs;

    while (getline(argvParcer.inputFile, str)){
        dbs = MakeTitles(ii, str, titles.size());
//        for (decltype(dbs.Size())i = 0; i < dbs.Size(); ++i)
//            if (dbs.Get(i)) argvParcer.outputFile << titles[i] << "\n";
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
