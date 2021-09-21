// STL
#include <iostream>
#include <stdio.h>
#include <cctype>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <memory>


// Own Libraries
#include "Tokens.h"
#include "Analyzer.h"

int main()
{
    LexicalAnalyzer myAnalyzer("..\\src\\source.txt");
    Tag tok = Tag::UNKNOWN;
    while (tok != Tag::E_O_F)
    {
        Token tmp = myAnalyzer.explore();
        std::cout << tmp << std::endl;
        tok = tmp.get_token_tag();
    }
        
    return 0;
}