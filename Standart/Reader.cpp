#include <iostream>
#include <vector>

using namespace std;

string ReadTitle() {
    string title;
    do {
        if (!getline(cin, title)) break;
    } while (title[0] != '<');
    // ...
    return title;
}

string ReadArticle() {
    string article, tmp;
    while (getline(cin, tmp, '/')) {
        if (tmp[tmp.size() - 1] == '<') break;
        else article += " " + tmp;
    }
    return article;
}

int main() {
    string s;
    size_t count = 0;
    while (!ReadTitle().empty()){
        ReadArticle();
        ++count;
    }
    cout << count << "\n";
    return 0;
}