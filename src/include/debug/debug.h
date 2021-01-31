#pragma once

#include <string>
#include <fstream>

/**
 * Logger is just a simple debug helper.
 * @PARAM:InLogPrefix - Used to give a unique prefix to the logger for easy file searching.
 * @PARAM:InLogFileName - The full filename to use when opening the log file.
*/
class Logger
{

private:

    ofstream log_file;
    string prefix;
    string file_name;

public:

    Logger(string InLogPrefix,string InLogFileName);

    ~Logger();

    /**
     * Getters
    */
    inline string LogPrefix(){return prefix;}
    inline string LogFileName(){return file_name;}

    /**
     * Print a string and write to the log file.
    */
    void Log(string message);

};