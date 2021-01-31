#include "langgen.h"

namespace fs = std::filesystem;
namespace cs = std::chrono;
namespace ts = std::this_thread;

LangGen::LangGen(
        string InDictionaryPath, string InBigramPath, string& Error,
        string InLanguageType = "Phonetic", string InOutputFileName = "langgen", 
        bool InAppendDateTime = true, int InNumWords = -420, float InTickRate = 0.f
)
{
    string the_abs_path = std::experimental::filesystem::path("LangGen");
    string log_path = the_abs_path + "output/logs/" + InOutputFileName + ".log";
    string suffix =  AppendDateTime() ? "_"+ FastTime() + ".txt" : ".txt";
    logger = new Logger(InOutputFileName+":",log_path);
    num_words = InNumWords;
    dict_path =   the_abs_path + "/config/dictionaries/" + InDictionaryPath; 
    bigram_path = the_abs_path + "/config/dictionaries/" + InBigramPath;
    append_date_time = InAppendDateTime;
    output_name = the_abs_path + "/output/" + InOutputFileName + suffix; 
    output_name += ".txt";
    tick_rate = InTickRate;
    language_type = InLanguageType;
    ClearValues();
    logger->Log("---------------------------New LangGen: " + OutputName() + "---------------------------");
}

LangGen::~LangGen()
{
    ClearValues();
    delete(logger);
}

string LangGen::FastTime()
{
    std::time_t time = cs::system_clock::to_time_t(end);
    return std::ctime(&time)
}

void LangGen::ClearValues()
{
    logger->Log("Clearing Values...");
    generating = false;
    counter = 0;
    dictionary = "";
    bigrams = ""; 
    output = ""; 
}

bool LangGen::Ensure(string& Error, int& ErrorCode)
{
    logger->Log("   Begin Ensure...");
    ErrorCode = 0;
    Error = "   ^_^^^_^Ensure Success! Generation can begin!^_^^_^";
    if(NumWords() <= 0)
    {
        logger->Log("   NumWords() == 0. Trying to set NumWords() to Dictionary().len...");
        num_words = Dictionary().len();
        if(NumWords() <= 0)
        {
            logger->Log("   #_##_#Generation failed! NumWords() == 0!#_##_#");
            Error = "ERROR! NumWords() == 0!";
            ErrorCode = 1;
            return false;
        }
    }
    if(!sizeof(Bigrams())>0)
    {
        logger->Log("   #_##_#No Bigrams!#_##_#");
        Error = "No Bigrams";
        ErrorCode = 2;
        return false;
    }
    return true;
}

int LangGen::Generate(string& Error)
{
    ifstream dict_file;
    ifstream big_file; //If we have issues holding the string in memory, these files can be used to help.
    int code = 0;
    int temp = 0;
    float rate = TickRate();
    string err = "";
    string temp_dict = "";
    string temp_word = "";
    auto start = std::chrono::system_clock::now();
    logger->Log("---------------------------Generation Started!---------------------------");
    logger->Log("---------------------------Start Time = "+FastTime()+"---------------------------");
    //Prep values.
    dictionary = LoadFile(DictionaryPath(),dict_file);
    bigrams = LoadFile(BigramPath(),big_file);
    temp_dict = Dictionary();
    //Make sure values are valid.
    if(!Ensure(err,code))
    {
        Error = err;
        return code;
    }
    //Generate.
    while(Generating())
    {   temp_word = temp_dict[x];
        output += MakeWord(temp_word);
        counter ++;
        if(rate > 0.f)
        {
            temp ++;
            ts::sleep_for(cs::seconds(rate));
        }
    }
    logger->Log("---------------------------Generation Complete!---------------------------");
    Error = Output();
    EndGeneration();
    return 0;
}

int LangGen::EndGeneration(bool Destroy)
{
    end = FastTime();
    cs::duration<double> elapsed_seconds = End()-Start();
    logger->Log("---------------------------Request End Generation!---------------------------");
    logger->Log("---------------------------End Time = "+FastTime()+"---------------------------");
    logger->Log("---------------------------Total Elapsed Time (Seconds) = "+ elapsed_seconds.count() + "---------------------------");
    //Clear values.
    if(Destroy)
    {
        ts::sleep_for(cs::seconds(1));
        logger->Log("---------------------------Good Bye!---------------------------");
        //delete(this);
    }
    return 0;
}

string LangGen::LoadFile(string FileName, ifstream& FileToStore)
{
    string data = ""
    logger.log("    Start load file: "+ FileName);
    //Open and validate file.
    ifstream myfile(FileName);
    //Make sure we have a valid filename.
    if(FileName == "")
    {
        logger.log("    Filename was empty!");
        return data;
    }
    //Check if file is open.
    if (!myfile.is_open())
    {
        logger.log("    File is not open!");
    }
    //Get file data if we don't have a file to store.
    if(!file_to_store)
    {
        while (getline(myfile,line))
        {
            data += line + "\n";
        }
    }
    FileToStore = myfile;
    myfile.close();
    logger.log("    End load file: "+ FileName);
    return data;
}

string LangGen::MakeWord(string BaseWord)
{
    logger->Log("    Making word...");
    string new_word;
    //Make sure word isn't empty.
    if(BaseWord == "")
    {
        //Get the bigrams based on the word.
        logger->Log("    Word was empty!");
        new_word = BaseWord + GetBigrams(BaseWord) + "\n";
        return new_word;
    }
    logger->Log("    Made word: "+ new_word);
    return new_word;
}

string GetBigrams(string BaseWord)
{
    srand (time(NULL)); //Make rand stream.
    int rand_int = 0; //Rand int
    float bigramf; //The letter as a float
    float bigramfstore; //The word as a float
    string bigram; //The full bigram
    string tbigrams = Bigrams(); //All bigrams
    string ltype = LanguageType();
    logger->Log("   Getting Bigram for word:" + BaseWord);
    //For each letter in the word...
    for(auto& letter : BaseWord)
    {  
        rand_int = rand() % sizeof(BaseWord);

        bigramf = std::stof(bigram);
        //Determine the gathered bigram based on LanguageType().
        if(ltype == "Alphabetic")
        {
            //Rand bigram. TODO.
            bigram += tbigrams[rand_int];
        }
            //Get a random phonetic bigram.
        else if (ltype == "Phonetic")
        {
            bigram += tbigrams[rand_int];
        }
            //Convert text to binary.
        else if (ltype == "Binary")
        {
            bigram += bitset<8>(letter.c_str()[i]);
        }
        //Convert text to hex
        else if(ltype == "Hex")
        {
            bigram += std::stoul(letter, 0, 16);
        }
        //Weird text math idea that I had.
        else if(ltype == "Numeric_Addition")
        {
            bigramfstore += bigramf;
            bigram += std::to_string(bigramfstore);
        }
        else if(ltype == "Numeric_Subtraction")
        {
            bigramfstore -= bigramf;
            bigram += std::to_string(bigramfstore);
        }
        else if(ltype == "Numeric_Multiplication")
        {
            bigramfstore *= bigramf;
            bigram += std::to_string(bigramfstore);
        }
        else if(ltype == "Numeric_Division")
        {
            bigramfstore /= bigramf;
            bigram += std::to_string(bigramfstore);
        }
 
    }
    logger->Log("    New Bigram for word:" + BaseWord + " = " + bigram);
    return bigram;
}