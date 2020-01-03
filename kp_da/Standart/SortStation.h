#ifndef SORT_STATION_H
#define SORT_STATION_H

#include <iostream>
#include <string>
#include <stack>
#include <sstream>

inline 
bool isOperator( const std::string& s )
{ return s.size() == 1 && (s[0] == '&' || s[0] == '|' || s[0] == '~' ); }

std::string SortStation(const std::string&);

#endif // !SORT_STATION_H

