#include <iostream>
#include <vector>
#include <fstream>

#include <unistd.h>

using namespace std;

const size_t uniq = 1000;

string genString(size_t length){
    string s;
    for (size_t i = 0; i < length; ++i)
        s += rand() % 26 + (rand() % 2 ? 'a' : 'A');
    return s;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    srand(time(0));
    int n, m;

    vector<string> vec(uniq);
    for (string& s : vec) s = genString(rand() % 5 + 5);
    cin >> n >> m;

    cout << n << " " << m << "\n";

    for (int k = 0; k < n; ++k){
        for (int i = 0; i < rand() % 100 + 5; ++i) cout << vec[rand() % uniq] << " ";
        cout << "\n";
    }

    for (int j = 0; j < m; ++j){
        for (int i = 0; i < rand() % 20 + 1; ++i) cout << vec[rand() % uniq] << " ";
        cout <<"\n";
    }
    
    return 0;
}
