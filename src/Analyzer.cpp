#include "Analyzer.h"


// PUBLIC METHODS
// CONTRUCTOR
LexicalAnalyzer::LexicalAnalyzer(const std::string& entry_path_src_code)
{
	path_src_code_ = entry_path_src_code; // assigning path source code
	src_code_.open(path_src_code_.c_str(), std::ifstream::binary); // opening file in binary configuration
	if (!src_code_.is_open()) // close the program if file is not encountered
	{
		std::cerr << "Couldn't open source file " << path_src_code_ << std::endl;
		std::cerr << "verify if it is located at the same address of this program...\n";
		exit(1);
	}
	src_code_.exceptions(std::ifstream::eofbit); // exceptions that we will throw are eofbit
	
	// assigning metadata of the src_code
	src_code_.seekg(0, src_code_.end); // going to the end of the file
	src_code_length_ = src_code_.tellg(); // getting length of the source code
	src_code_.seekg(0, src_code_.beg); // returning to beginning
	file_pos_ = src_code_.tellg(); // 0

	// reserved words
	reserve(Token(Tag::IF, "if"));
	reserve(Token(Tag::ENDIF, "endif"));
	reserve(Token(Tag::ELSE, "else"));
	reserve(Token(Tag::WHILE, "while"));
	reserve(Token(Tag::ENDWHILE, "endwhile"));
	reserve(Token(Tag::ENDFOR, "for"));
	reserve(Token(Tag::ENDFOR, "endfor"));
	reserve(Token(Tag::FUNCTION, "function"));
	reserve(Token(Tag::RETURN, "return"));
	reserve(Token(Tag::ENDFUNCTION, "endfunction"));

	reserve(SPTokens::instance().get_True());
	reserve(SPTokens::instance().get_False());
}

// DESTRUCTOR
LexicalAnalyzer::~LexicalAnalyzer()
{
	words_table_.clear();
	src_code_.close(); // close the source code file
}


// assigning Words to our table of Words
void LexicalAnalyzer::reserve(Token w)
{
	words_table_[w.get_lexeme()] = w;
}

bool LexicalAnalyzer::eof_src_code()
{
	// if we reached the end of the file and there is not more characters into the buffer
	// we do not get the end of the source code
	return file_pos_ == src_code_length_;
}

char LexicalAnalyzer::getcharacter()
{
	char c = ' '; // the character to return
	
	src_code_.get(c);
	file_pos_ = src_code_.tellg(); // updating the source code pointer
	
	preanalysis_ = c; // copying returned character to local variable
	return c;
}

char LexicalAnalyzer::peekcharacter()
{
	return src_code_.peek(); // peek from the last character obtained on the file
}

Token LexicalAnalyzer::explore()
{
	if (eof_src_code()) { 
		// there is something that is missing yet
		if (preanalysis_ != ' ') {
			char tmp = preanalysis_;
			if (std::isdigit(preanalysis_)) { // check if it's a number 
				preanalysis_ = ' '; // preanalysis become empty
				return Token(Tag::NUMBER, "" + tmp, line_); 
			}
			if (std::isalpha(preanalysis_)) // check if it's an identifier
			{
				preanalysis_ = ' ';
				return Token(Tag::IDENTIFIER, "" + tmp, line_);
			}
			Token tmp_tok = explore_operator(preanalysis_);
			if (tmp_tok.get_token_tag() != Tag::UNKNOWN)
			{
				preanalysis_ = ' ';
				return tmp_tok;
			}
			preanalysis_ = ' ';
			return Token(Tag::UNKNOWN, "" + tmp, line_); // is an unknown lexeme
		}
		
		return SPTokens::instance().get_eof(); 
	}

	try
	{
		char c = ' ', aux_c;
		c = jump_unnecesary_characters(); // we pass over empty spaces, tabs or code comentaries

		Token token_operator = explore_operator(c);
		// it means we've found a token
		if (token_operator.get_token_tag() != Tag::UNKNOWN) return token_operator;

		// check if the entry is a number
		if (std::isdigit(c)) {
			// number
			std::string val;
			do
			{
				val += c;
				c = getcharacter();
			} while (std::isdigit(c));

			// not a real number
			if (preanalysis_ != '.') return Token(Tag::NUMBER, val, line_);
			
			val += preanalysis_;
			c = getcharacter();
			do {
				val += c;
				c = getcharacter();
			} while (std::isdigit(c));
			return Token(Tag::REAL, val, line_);
		}
		// checking for identifiers
		if (std::isalpha(c))
		{
			std::string id;
			do
			{
				id += c;
				c = getcharacter();
			} while (std::isalpha(c) || std::isdigit(c));
			if (words_table_.find(id) != words_table_.end()) return words_table_[id];
			Token new_identifier(Tag::IDENTIFIER, id, line_);
			reserve(new_identifier);
			return new_identifier;
		}
		// checking for strings
		if (c == '\"')
		{
			std::string str;
			do {
				str += c;
				c = getcharacter();
			} while (c != '\"');
			Token new_str(Tag::STRING, str, line_);
			reserve(new_str);
			return new_str;
		}
		// if it isn't any known lexeme, then return an unknown token
		Token unknown_tok(Tag::UNKNOWN, "" + c, line_);
		return unknown_tok;
	}
	catch (std::ifstream::failure e)
	{
		// eofbit reached
		std::cerr << "End of File reached" << std::endl;
		return Token();
	}
}

// PRIVATE METHODS
Token LexicalAnalyzer::explore_operator(char c)
{
	char aux_c = ' ';
	switch (c)
	{
		// LOGICAL AND ARITMETIC OPERATORS
	case '&': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '&') { getcharacter(); return SPTokens::instance().get_and(); }
		else return Token(Tag::UNKNOWN, "&", line_);
	}
	case '|': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '|') { getcharacter(); return SPTokens::instance().get_or(); }
		else return Token(Tag::UNKNOWN, "|", line_);
	}
	case '=': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '=') { getcharacter(); return SPTokens::instance().get_eq(); }
		else return SPTokens::instance().get_assign();
	}
	case '!': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '=') { getcharacter();  return SPTokens::instance().get_ne(); }
		else return Token(Tag::UNKNOWN, "!", line_);
	}
	case '<': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '=') { getcharacter(); return SPTokens::instance().get_leq(); } // less or equal
		else return SPTokens::instance().get_le(); // < less than 
	}
	case '>': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '=') { getcharacter(); return SPTokens::instance().get_geq(); } // less or equal
		else return SPTokens::instance().get_ge(); // > greater than
	}
			// ARITHMETIC OPERATORS
	case '+':
		return SPTokens::instance().get_plus(); // + plus
	case '-':
		return SPTokens::instance().get_minus();
	case '*':
		return SPTokens::instance().get_mult();
	case '/':
		return SPTokens::instance().get_div();

		// DELIMITERS
	case '(':
		return SPTokens::instance().get_lpar(); // left parenthesis
	case ')':
		return SPTokens::instance().get_rpar(); // right parenthesis
	case ',':
		return SPTokens::instance().get_comma(); // comma
	case ';':
		return SPTokens::instance().get_dotcomma(); // dot comma
	}
	return Token(); // default case
}

char LexicalAnalyzer::jump_unnecesary_characters()
{
	char c = ' ';
	while (!eof_src_code()) // while we do not reach end of file on the document
	{
		c = getcharacter();
		if (c == '\t' || c == ' ') continue;
		else if (c == '!') {
			if (eof_src_code()) return c; // return an unknown "!" lexeme
			if (peekcharacter() == '!') { // reading comentary
				while (!eof_src_code() && getcharacter() != '\n');
				line_++;
				continue; // continue the searching for empty spaces
			}
			break; // breaking the loop since it's posible to find the <!=> operator
		}
		else if (c == '\n') line_++;
		else break;
	}
	return c; // you return c, because isn't an unnecesary character
}
