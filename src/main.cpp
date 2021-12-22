// STL
#include <iostream>
#include <stdio.h>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <stdlib.h>
#include <string>

// Own Libraries
#include "Tokens.h"
#include "Analyzer.h"
void start_parsing(std::string input, std::string filename_no_ext)
{
    std::string input_str = "\"" + input + "\"";
    std::string parse_tree_str = "\"parse_tree_" + filename_no_ext + ".png\"";
    std::string parse_results_str = "\"parse_results_" + filename_no_ext + ".txt\"";
    std::string command = "bash start_parsing.sh " + input_str + " " + parse_tree_str + " " + parse_results_str;
    system(command.c_str());
}


int main(int argc, char *argv[])
{
    std::string filename(argv[1]);
    std::string filename_no_ext = filename.substr(0, filename.find("."));
    LexicalAnalyzer LexAnalyzer(filename);
    
    std::cout << "analyzing file: " << filename << "\n";

    std::string input_for_grammar = LexAnalyzer.analyze_src_code();

    std::cout << "returning input for grammar: \n";
    std::cout << input_for_grammar << "\n\n";
    start_parsing(input_for_grammar, filename_no_ext);


    return 0;
}