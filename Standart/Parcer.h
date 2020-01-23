#ifndef PARCER_H
#define PARCER_H

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

#include "InvertedIndex.h"

std::string ReadTitle(std::istream &);
std::string ReadArticle(std::istream &);
std::vector <std::string> Split(const std::string&);

void Parsing(std::vector <std::string>&, InvertedIndex &, std::istream &);

#endif // !PARCER_H