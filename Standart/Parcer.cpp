#include "Parcer.h"

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
    std::string title;
    std::smatch smtitle;
    do{
        if (!getline(is, title)) return "";
    }while (title[0] != '<');
    regex_search(title, smtitle, std::regex("\\btitle=\"(.*)\">"));
    return smtitle[1];
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
    std::istream_iterator<std::string> begin(ss);
    return std::vector<std::string>(begin, std::istream_iterator<std::string>());
}

void Parsing(std::vector<std::string>& titles, CInvertedIndex& ii, std::istream& is){
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