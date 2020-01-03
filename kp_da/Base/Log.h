#ifndef LOG_H

#include <string>
#include <iostream>
#include <fstream>

class Log{
public:
    Log(const std::string& fileName = "logFile.txt", bool enableConsole = true);
    ~Log();

    void EnableConsole();
    void DisableConsole();
    void Message(const std::string&);
    void Debug(const std::string&);
    void Error(const std::string&);

    void operator()(const std::string& fileName, bool enableConsole = true){
        _logFile.open(fileName, std::ios_base::app);
        _isConsoleEnabled = enableConsole;
    }
private:
    void _Print(const std::string&);

    std::ofstream _logFile;
    bool _isConsoleEnabled;

};

#endif // LOG_H