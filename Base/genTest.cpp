#include <iostream>
#include <vector>

using namespace std;

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
    
    int n, m, id1, id2;
    cin >> n >> m;
    cout << n << " " << m << "\n";
    vector<vector<string>> v(n, vector<string>());
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < rand() % 90 + 10; ++j){
            v[i].push_back(genString(rand() % 20 + 10));
        }
    }

    for (auto vec : v){
        for (auto s : vec) cout << s << " ";
        cout << "\n";
    }

    while (m--){
        for (int i = 0; i < rand() % 90 + 3; ++i){
            id1 = rand() % v.size();
            id2 = rand() % v[id1].size();
            cout << v[id1][id2] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
