#include "langgen.h"
#include <string>

using namespace std;

/**
 * Main.
 * @ARG: 0 - The Dictionary File Name.
 * @ARG: 1 - The Bigrams File Name.
 * @ARG: 2 - The language type.
 * @ARG: 3 - The Output File name (without extension).
 * @ARG: 4 - Determines if we append date time.
 * @ARG: 5 - The number of words to make.
 * @ARG: 6 - The Tick Rate. 
 * ex. ./LangGen "english.txt" "bigrams_phonetic.txt" "Phonetic" "langgen" true -420 0.f
*/

int main(int argc, char **argv)
{ 
    LangGen* gen;
    bool append_dt = true;
    int num = -420;
    int status = 0;
    bool state = false;
    float tick_rate = 0.f;
    float f1 = 0.f;
    float f2 = 0.f;
    char argdt = *argv[5];
    string dict_path = "english.txt";
    string big_path = "bigrams_phonetic.txt";
    string lang_type = "Phonetic";
    string output_name = "langgen";
    string err = "";
    if(argc>=2)
    {
        dict_path = std::string(1,*argv[1]);
        if(sizeof(argv)>=3)
        {
            big_path = std::string(1,*argv[2]);
        }
        if(sizeof(argv)>=4)
        {
            lang_type = std::string(1,*argv[3]);
        }
        if(sizeof(argv)>=5)
        {
            output_name = std::string(1,*argv[4]);
        }
        if(sizeof(argv)>=6)
        {
            if( argdt == 'y' ||argdt == 'Y' ||argdt == 'True' ||argdt == 'true' ||argdt == 'Yes' ||argdt == 'yes'  )
            {
                state = true;
            }
            append_dt = state;
        }
        if(sizeof(argv)>=7)
        {
            f1 = (int)(*argv[6]);
        }
        if(sizeof(argv)>=8)
        {
            f2 = (float)(*argv[7]);
        }
    }
    gen = new LangGen(dict_path,big_path,err,lang_type,output_name,append_dt,f1,f2);
    if(gen)
    {
        status = gen->Generate(err);
        delete(gen);
    }
    return status;
}