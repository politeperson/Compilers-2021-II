#pragma once
#ifndef ANALYZER_H_
#define ANALYZER_H_
#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>

#include "Tokens.h"

class LexicalAnalyzer
{
public:
	LexicalAnalyzer(const std::string& entry_path_src_code);
	void reserve(Token w);
	char getcharacter();
	char peekcharacter();
	bool eof_src_code();

	Token explore();
	~LexicalAnalyzer();

private:
	int line_ = 1;
	char preanalysis_ = ' ';
	std::map<std::string, Token> words_table_;

	const int BLOCKS_SIZE_ = 10; // by default the block size of the buffer is this
	int file_pos_, src_code_length_;


	std::string path_src_code_; // the path of the source code
	std::ifstream src_code_; // here will be the source code

	Token explore_operator(char c);
	char jump_unnecesary_characters();
};


#endif // ANALYZER_H_
