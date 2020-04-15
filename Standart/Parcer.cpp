#include "Parcer.h"

#include <algorithm>

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
 
bool isEndWith(const std::string& orig, const std::string& ending) {
    if (orig.size() < ending.size()) return false;
    size_t begin = orig.size() - ending.size();
    for (size_t i = 0; i < ending.size(); ++i)
        if (orig[begin + i] != ending[i]) return false;
    return true;
}

std::string ReadArticle(std::istream& is){
    std::string article, tmp;
    const std::string ending = "</doc";
    bool endArticle = false;
    while (!endArticle && getline(is, tmp, '>')) {
        if (isEndWith(tmp, ending)) {
            tmp.erase(tmp.end() - ending.size(), tmp.end());
            endArticle = true;
        } else
            tmp += '>';
        article += tmp + ' ';
    }
//    while (getline(is, tmp)){
//        if (tmp == "</doc>") break;
//        else article += tmp + ' ';
//    }
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
    std::string title;
    uint count = 1;

    while (!(title = ReadTitle(is)).empty()){
        titles.push_back(title);
        for (const auto& word : Split(ReadArticle(is))) {
            ii.Insert(word, count);
        }
        ++count;
    }

}