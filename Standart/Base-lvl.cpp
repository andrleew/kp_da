#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "InvertedIndex.h"
#include "DynamicBitSet.h"


#define DEBUG
// #define RELEASE

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
            , [](char c) -> char
                { return (isalnum(c) ? tolower(c) : ' ');});
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

vector <uint> MakeResultVector (const map<size_t, size_t> & m, size_t count){
    vector <uint> result;
    for (auto text : m){
        if (text.second == count) result.push_back(text.first);
    }
    return result;
}

size_t CountSum(vector <uint> & textIndexes){
    size_t sum = 0;
    for (size_t i = 0; i < textIndexes.size(); ++i){
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
    vector <string> words;
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
        DynamicBitSet dbs = ii.Get(words[0]);
        for (size_t i = 0; i < words.size(); ++i) {
            dbs &= ii.Get(words[i]);
        }
        for (decltype(dbs.Size())i = 0; i < dbs.Size(); ++i)
            if (dbs.Get(i)) cout << i << " ";
        cout << endl;
    }


    return 0;
}   