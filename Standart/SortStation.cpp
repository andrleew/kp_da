#include "SortStation.h"

int getOperatorPriority(const std::string& s){
    switch (s[0])
    {
    case '|': return 0;
    case '&': return 1;
    case '~': return 2;
    default: return -1;
    }
}

inline
bool isLeftScobe( const std::string& s )
{ return s.size() == 1 && s[0] == '('; }

inline
bool isRightScobe( const std::string& s )
{ return s.size() == 1 && s[0] == ')'; }

bool isOperand( const std::string& s )
{ return s.size() > 1 || (!isOperator(s) && !isLeftScobe(s) && !isRightScobe(s)); }

void AddSpacesForComfort(std::string& s){
    std::string result;
    for (auto c : s){
        if (c == '(' || c == ')' || c == '~') result += std::string(" ") + c + ' ';
        else result += c;
    }
    s = result;
}

std::string SortStation(const std::string& str){
    std::string s = str;
    AddSpacesForComfort(s);
    std::stringstream ss(s);
    std::string token, result;
    std::stack <std::string> operators;
    while ( ss >> token ){
        if (isOperand(token)){
            result += token + ' ';
        } else if (isOperator(token)){
            while (!operators.empty() && 
                    isOperator(operators.top()) &&
                    getOperatorPriority(operators.top()) >= getOperatorPriority(token)){
                        result += operators.top() + ' ';
                        operators.pop();
            }
            operators.push(token);
        } else if (isLeftScobe(token)){
            operators.push(token);
        }
        else {
            while ( !operators.empty() && !isLeftScobe(operators.top())){
                result += operators.top() + ' ';
                operators.pop();
            }
            if ( !operators.empty() && isLeftScobe(operators.top()) ) operators.pop();
        }
    }
    while (!operators.empty()){
        result += operators.top() + ' ';
        operators.pop();
    }
    return result;
}