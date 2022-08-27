
#ifndef C_PARSE_INI_FILE_H_
#define C_PARSE_INI_FILE_H_

#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

#define COMMENT_CHAR '#'

class ParseINI {
public:
    ParseINI();
    
    ~ParseINI();
    
    bool ReadConfig(const string &filename, map<string, string> &mContent, const char *section);
    
    bool AnalyseLine(const string &line, string &key, string &val);
    
    void Trim(string &str);
    
    bool IsSpace(char c);
    
    bool IsCommentChar(char c);
    
    void PrintConfig(const map<string, string> &mContent);

private:
    std::string m_INIPath;
};

#endif
