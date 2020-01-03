#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const size_t MOD = 1000000007;

inline
void ToLower(string& str){
    transform(str.begin(), str.end(), str.begin(), 
    [] (char c) { return tolower(c); });
}

void Parsing(unordered_map<string, vector<int>>& words, size_t count){
    int k = 1;
    string str;
    stringstream ss;
    while (count-- && getline(cin, str)){
        if (str.empty()){
            ++count;
            continue;
        }
        ToLower(str);
        ss.str(str);
        while (ss >> str){
            auto it = words.find(str);
            if (it == words.end()) it = words.insert(make_pair(str, vector<int>())).first;
            if (it->second.empty() || it->second[it->second.size() - 1] != k) it->second.push_back(k);
        }
        ss.clear();
        ++k;
    }
}

void Answers(const unordered_map<string, vector<int>>& words,size_t count){
    string str;
    stringstream ss;
    map<size_t, size_t> m;
    size_t k;
    while (count-- && getline(cin, str)){
        if (str.empty()){
            ++count;
            continue;
        }
        ToLower(str);
        ss.str(str);
        k = 0;
        while (ss >> str){
            ++k;
            auto it = words.find(str);
            if (it == words.end()) continue;
            for (auto el : it->second){
                auto iter = m.find(el);
                if (iter == m.end()) iter = m.insert (make_pair(el, 0)).first;
                ++iter->second;
            }
        }
        size_t sum = 0, count = 0;
        for (auto el : m){
            if (el.second == k){
                sum = (sum + el.first * count) % MOD;
                ++count;
            }
        }
        m.clear();
        ss.clear();
        cout << count << " " << sum << "\n";
    }
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    size_t n, m;
    unordered_map<string, vector<int>> words;
    cin >> n >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Parsing(words, n);
    // for (auto el : words){
    //     cout << el.first;
    //     for (auto word : el.second){
    //         cout << " " << word;
    //     }
    //     cout << "\n";
    // }
    Answers(words, m);

    return 0;
}