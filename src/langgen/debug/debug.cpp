#include <iostream>

#include "debug/debug.h"

using namespace std;

Logger::Logger(string InLogPrefix,string InLogFileName)
{
    prefix = InLogPrefix;
    file_name = InLogFileName;
    log_file.open(LogFileName());
}

Logger::~Logger()
{
    log_file.close();
}

void Logger::Log(string Message)
{
    string log = LogPrefix() + Message 
    cout << log;
    if(log_file.is_open())
    {
        log_file << log+"\n";
    }
}