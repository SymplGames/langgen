#pragma once

#include <string>
#include <stdio.h>
#include <bitset>
#include <chrono>    
#include <ctime>   
#include <thread>

#include "debug/debug.h"

using namespace std;

/**
 * LangGen generates a language when created.
 * @PARAM:DictoaryPath - The path to the dictionary that is used to gather words. 
 * @PARAM:BigramPath - The path to our bigrams.
 * @PARAM:InLanguageType - The type of language we make.
       Supported Types: 
            Alphabetic - Pairs syllables to an alphabet. Similar to English.
            Phonetic - Pairs syllables to phonetic groups. Simliar to Japanese.
            Binary - Converts the word to binary.
            Numeric - TODO
 * @PARAM:InOutputFileName - The filename to use when writing the generated language.
 * @PARAM:InAppendDateTime - If true, we append date time to the output file. 
        This is also passed to the logger.
 * @PARAM:InTickRate - Determines how fast we generate a word. If <= 0 we don't wait.
 * @PARAM:InNumWords - This can be used to limit the number of words the generator makes. 
        If <= 0, we will gather the number of words from the length of the dictionary.
*/

class LangGen
{

private:

    std::time_t start; //Start time.
    std::time_t end; //End Time.
    Logger* logger; //Logging util
    bool generating; //Used to control the state of the generation loop.
    bool append_date_time; //If true, we append date time.
    int num_words; //The number of words to make. 
    int counter; //Determines what index we are at for generation.
    float tick_rate; //Determines how fast we generate a word. If <=0 we don't wait.
    string dict_path; //The path to the words we use to make our language.
    string bigram_path; //The path to the bigrams we use to make a word.
    string output_name; //The file name to use to write a file.
    string language_type; //The language type.
    string output; //The output string.
    string dictionary; //The words to gather.
    string bigrams; //The bigrams to gather.

private:

    /**
     * Fast helper to get date time.
    */
    inline string FastTime();

    /**
     * Clear all generated values.
    */
    void ClearValues();

protected:

    /**
     * Generate the language.
     * @PARAM: &Error - A helper value that can be used for debugging.
     * @PARAM: &ErrorCode - A helper value that can be used for debugging.
     * @RETURN: false if a condition fails.
    */
    inline bool Ensure(string& Error, int& ErrorCode);

    /**
     * Load a file and return the data as a string.
     * @PARAM:FileName - The full name of the file we are looking for.
     * @RETURN: All file data as string.
    */
    inline string LoadFile(string FileName, ifstream& FileToStore);

    /**
     * Make a new word based on the given base word.
     * Base word determines the length of the generated word.
     * @PARAM:BaseWord - The word that we are 'translating' to the new language. 
     * @RETURN: The made word.
    */
    inline string MakeWord(string BaseWord);

    /**
     * Get a string of random bigrams based on the BaseWord.
     * @TODO:Make sure to use the word to help gather bigrams.
     * @PARAM:BaseWord - The word that we are 'translating' to the new language. 
     * @RETURN: A string of bigrams for the new word.
    */
    inline string GetBigrams(string BaseWord);

public:

    LangGen(
        string InDictionaryPath, string InBigramPath, string& Error,
        string InLanguageType = "phonetic", string InOutputFileName = "langgen", 
        bool InAppendDateTime = true, int InNumWords = -420, float InTickRate = 0.f
    );

    ~LangGen();

    inline std::time_t Start(){return start;}
    inline std::time_t End(){return end;}
    inline Logger* GetLogger(){return logger;}
    inline bool Generating(){return generating;}
    inline bool AppendDateTime(){return append_date_time;}
    inline int NumWords(){return num_words;}
    inline int Counter(){return counter;}
    inline float TickRate(){return tick_rate;}
    inline string DictPath(){return dict_path;}
    inline string BigramPath(){return bigram_path;}
    inline string OutputName(){return output_name;}
    inline string LanguageType(){return language_type;}
    inline string Output(){return output;}
    inline string Dictionary(){return dictionary;}
    inline string Bigrams(){return bigrams;}

    /**
     * Generate the language.
     * #PARAM: &Error - A helper value that can be used for debugging.
     * @RETURN: Status code.
    */
    int Generate(string& Error);

    /**
     * Destroy the generator.
     * @RETURN: Status code.
    */
    int EndGeneration(bool Destroy = true);

};
