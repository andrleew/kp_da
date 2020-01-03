#include "Log.h"

Log::Log(const std::string& fileName, bool enableConsole)
: _logFile(fileName),
  _isConsoleEnabled(enableConsole)
{}

Log::~Log(){
    _logFile << "---------------------------\n";
    _logFile.close();
}

void Log::_Print(const std::string& str){
    if (_isConsoleEnabled) std::cout << str << std::endl;
    if (_logFile.is_open()) _logFile << str << "\n";
    else std::cout << "FILE NOT OPENED" << std::endl;
}

void Log::DisableConsole(){
    _isConsoleEnabled = false;
}

void Log::EnableConsole(){
    _isConsoleEnabled = true;
}

void Log::Error(const std::string& str){
    _Print(std::string ("!!!! Error: ") + str);
}

void Log::Message(const std::string& str){
    _Print(std::string("++++ Message: ") + str);
}

void Log::Debug(const std::string& str){
    _Print(std::string("~~~~ Debug: ") + str);
}