#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "InvertedIndex.h"
#include "DynamicBitSet.h"

// #define DEBUG
#define RELEASE

const uint32_t MOD = 1000000007;

using namespace std;

inline void
ok() { 
    #ifdef DEBUG
        cout << "ok" << endl;    
    #endif // DEBUG
}

void ToLower(string & str){
    transform(str.begin()
            , str.end()
            , str.begin()
            , [](char c) { return tolower(c);});
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

vector <uint> MakeResultVector (CInvertedIndex& cii, vector<string> words){
    DynamicBitSet dbs = cii.Get(words[0]);
    for (size_t i = 1; i < words.size(); ++i) dbs &= cii.Get(words[i]);
    return dbs.ToVector();
}

size_t CountSum(vector <uint> & textIndexes){
    size_t sum = 0;
    for (size_t i = 0; i < textIndexes.size(); ++i){
        // std::cout << textIndexes[i] << endl;
        sum += textIndexes[i] * i;
        sum %= MOD;
    }
    return sum;
}

int main()
{
    #ifdef RELEASE
    cin.tie(0);
    ios::sync_with_stdio(false);
    #endif
    CInvertedIndex ii;
    string str;
    size_t n, m;
    vector <uint> l;
    vector <string> words;
    map <size_t, size_t> texts_count;
    cin >> n >> m;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 1; i <= n; ++i)
    {
        getline(cin, str);
        ToLower(str);
        for (auto word : ParceToWords(str)){
            ii.Insert(word, i);
        }
    }

    for (size_t i = 0; i < m; ++i)
    {
        getline(cin, str);
        ToLower(str);
        words = ParceToWords(str);
        l = MakeResultVector(ii, words);
        cout << l.size() << " " << CountSum(l) << "\n";
    }

    return 0;
}   