#include "Parcer.h"

#include <algorithm>

inline 
void ToLower(std::string & s){
    transform(s.begin(),
                s.end(),
                s.begin(),
                [](char c) {
                    return (isalnum(c) ? tolower(c) : ' ');
                    }
                );
}

std::string ReadTitle(std::istream& is){
    std::string title, res;
    do{
        if (!getline(is, title)) return "";
    }while (title[0] != '<');
    for (size_t i = title.size() - 3; i > 0 && title[i] != '\"'; --i){
        res += title[i];
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::string ReadArticle(std::istream& is){
    std::string article, tmp;
    while (getline(is, tmp)){
        if (tmp == "</doc>") break;
        else article += tmp + ' ';
    }
    ToLower(article);
    return article;
}

std::vector <std::string> Split(const std::string & str){
    std::stringstream ss (str);
    std::vector <std::string> res;
    std::string word;
    while (ss >> word) res.push_back(word);
    return res;
}

void Parsing(std::vector<std::string>& titles, InvertedIndex& ii, std::istream& is){
    std::string title, word;
    std::stringstream ss;
    uint count = 1;

    while ((title = ReadTitle(is)) != ""){
        titles.push_back(title);
        ss.str(ReadArticle(is));
        while (ss >> word){
            ii.Insert(word, count);
        }
        ss.clear();
        ++count;
    }

}