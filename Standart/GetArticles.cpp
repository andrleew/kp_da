#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2) return 0;
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ifstream ifs (argv[1]);
    string str;
    size_t n;
    cin >> n;
    while (n--){
        while (getline(ifs, str)){
            cout << str << "\n";
            if (str == "</doc>") break;
        }
    }
    return 0;
}