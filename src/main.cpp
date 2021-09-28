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
    LexicalAnalyzer variablesAnalyzer("vars.txt");
    LexicalAnalyzer conditionalsAnalyzer("conditionals.txt");
    LexicalAnalyzer buclesAnalyzer("bucles.txt");
    LexicalAnalyzer functionsAnalyzer("functions.txt");
    
    std::cout << "analyzing variables: \n";
    variablesAnalyzer.analyze_src_code();
    
    std::cout << "analyzing conditionals: \n";
    conditionalsAnalyzer.analyze_src_code();
    
    std::cout << "analyzing bucles: \n";
    buclesAnalyzer.analyze_src_code();
    
    std::cout << "analyzing functions: \n";
    functionsAnalyzer.analyze_src_code();


    return 0;
}