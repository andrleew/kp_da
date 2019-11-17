#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "InvertedIndex.h"

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
            , [](char c) -> char
                { return (isalnum(c) ? tolower(c) : ' ');});
}

void GenerateMap(map<size_t, size_t>* m, const vector<string> & words, CInvertedIndex & cii){
    m->clear();
    auto textNumbers = cii.Get(words[0]);
    for (auto text : textNumbers){
        m->insert(make_pair(text, 1));
    }
    for (size_t i = 1; i < words.size(); ++i){
        textNumbers = cii.Get(words[i]);
        for (auto text : textNumbers){
            auto it = m->find(text);
            if (it != m->end()) ++it->second;
        }
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
        GenerateMap(&texts_count, words, ii);
        l = MakeResultVector(texts_count, words.size());
        cout << l.size() << " " << CountSum(l) << "\n";
    }

    return 0;
}   