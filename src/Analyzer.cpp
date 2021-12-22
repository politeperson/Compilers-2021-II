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

	reserve_initial_words();
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
				return Token(Tag::NUM, "" + tmp, line_); 
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
		
		return SPTokens::instance().get_eof(); // return EOF token
	}

	try
	{
		char c = ' ', aux_c;
		
		c = jump_unnecesary_characters(); // we pass over empty spaces, tabs or code comentaries

		// OPERATOR
		Token auxiliar_token = explore_operator(c);
		// it means we've found an operator token
		if (auxiliar_token.get_token_tag() != Tag::UNKNOWN) return auxiliar_token;

		// NUMBERS
		auxiliar_token = explore_number(c);
		// it means we've found a number token
		if (auxiliar_token.get_token_tag() != Tag::UNKNOWN) return auxiliar_token;

		// IDENTIFIERS
		auxiliar_token = explore_identifier(c);
		// it means we've found an identifier token
		if (auxiliar_token.get_token_tag() != Tag::UNKNOWN) return auxiliar_token;

		// STRINGS
		auxiliar_token = explore_string(c);
		// it means we've found an string token
		if (auxiliar_token.get_token_tag() != Tag::UNKNOWN) return auxiliar_token;

		if (eof_src_code() && c == '\n')
			return SPTokens::instance().get_eof();
		// if it isn't any known lexeme, then return an unknown token
		return Token(Tag::UNKNOWN, std::string({ c }), line_);
	}
	catch (std::ifstream::failure e)
	{
		// eofbit reached
		std::cerr << "End of File reached" << std::endl;
		return Token();
	}
}

// prints the tokens of lexical analysis
// show lexical errors
// return the input for our grammar
std::string LexicalAnalyzer::analyze_src_code()
{
	// first we must reserve initial reserved words
	reserve_initial_words();
	
	// restarting position
	src_code_.seekg(0, src_code_.end); // going to the end of the file
	src_code_length_ = src_code_.tellg(); // getting length of the source code
	src_code_.seekg(0, src_code_.beg); // returning to beginning
	file_pos_ = src_code_.tellg(); // 0
	line_ = 1; // restart line

	Tag tok = Tag::UNKNOWN;
	int tmp_line_ = line_;

	std::vector<Token> lexical_errors;
	std::string input_for_grammar = "";

	while (tok != Tag::E_O_F)
	{
		Token tmp = explore();
		tok = tmp.get_token_tag();
		if(tmp.get_line() == 0) tmp.set_line(line_); // set current line, only for print purposes
		
		if(tmp_line_ != line_)
		{
			std::cout << "\n";
			tmp_line_ = line_;
		}

		if(tok == Tag::E_O_F)
			break;

		if(tok == Tag::UNKNOWN || tok == Tag::UNKNOWN_NUMBER || tok == Tag::UNKNOWN_OPERATOR || tok == Tag::UNKNOWN_STRING)
			lexical_errors.push_back(tmp);
		else
		{
			std::cout << tmp << " ";
			input_for_grammar += tmp.get_token_tag_as_str(Token::TYPE_ANALYSIS::SINTACTIC) + ",";
		}

		tok = tmp.get_token_tag();
	}
	std::cout << "\n";
	if (!lexical_errors.empty())
	{
		std::cout << "Some errors were found:\n";
		for(auto& error : lexical_errors)
			std::cout <<"See line: " << error.get_line() << " , " << error << std::endl;
	}
	std::cout << "\n";
	input_for_grammar.pop_back();
	return input_for_grammar;
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
		else return Token(Tag::UNKNOWN_OPERATOR, "&", line_);
	}
	case '|': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '|') { getcharacter(); return SPTokens::instance().get_or(); }
		else return Token(Tag::UNKNOWN_OPERATOR, "|", line_);
	}
	case '=': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '=') { getcharacter(); return SPTokens::instance().get_eq(); }
		else return SPTokens::instance().get_assign(); // = assignation
	}
	case '!': {
		if (!eof_src_code()) aux_c = peekcharacter();
		if (aux_c == '=') { getcharacter();  return SPTokens::instance().get_ne(); }
		else return SPTokens::instance().get_neg(); // ! logical negation
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
	case '{':
		return SPTokens::instance().get_left_bracket(); // left bracket
	case '}':
		return SPTokens::instance().get_right_bracket(); // left bracket
	case ',':
		return SPTokens::instance().get_comma(); // comma
	case ';':
		return SPTokens::instance().get_dotcomma(); // dot comma
	}
	return Token(); // default case
}

Token LexicalAnalyzer::explore_number(char c) 
{
	// check if the entry is a number
	if (std::isdigit(c)) {
		// number
		std::string val;
		do
		{
			val += c;
			if (eof_src_code()) break;
			c = getcharacter();
		} while (std::isdigit(c));
		
		// if reached end of file, I return a number token
		if(eof_src_code()) return Token(Tag::NUM, val, line_);
		
		// not a real number
		if (preanalysis_ != '.') {
			file_pos_--;
			// backtrack one character
			src_code_.seekg(file_pos_, src_code_.beg);
			return Token(Tag::NUM, val, line_);
		}

		val += preanalysis_; // a number of the form e.g.: "456."
		if (!eof_src_code()) {
			// getting next character to determine if it is a good real number
			c = getcharacter(); 
			
			// can be a number of the form: 54.<... or 54. 56, etc
			// we only return the lexeme of the number
			if (!std::isdigit(c)) {
				file_pos_--;
				src_code_.seekg(file_pos_, src_code_.beg);
				return Token(Tag::UNKNOWN_NUMBER, val, line_);
			}
			val += c;
			// if we reached the end of the file after the reading we return a real number tag
			if (eof_src_code()) return Token(Tag::REAL, val, line_);
			do
			{
				c = getcharacter();
				if (std::isdigit(c))
					val += c;
				else break;
			} while (!eof_src_code());

			file_pos_--;
			src_code_.seekg(file_pos_, src_code_.beg);
			return Token(Tag::REAL, val, line_); // is a real number
		}
		// means we reach a real number not ending in digits, e.g.: 456.$ (where $ means EOF) 
		return Token(Tag::UNKNOWN_NUMBER, val, line_); // is not a number
	}
	return Token(Tag::UNKNOWN, "", line_);
}

Token LexicalAnalyzer::explore_identifier(char c)
{
	// checking for identifiers
	if (std::isalpha(c))
	{
		std::string id;
		do
		{
			id += c;
			if (eof_src_code()) break;
			c = getcharacter();
		} while (std::isalpha(c) || std::isdigit(c));

		if (!eof_src_code())
		{
			file_pos_--;
			src_code_.seekg(file_pos_, src_code_.beg);
		}
		// we found a reserved word
		if (words_table_.find(id) != words_table_.end()) return words_table_[id];

		Token new_identifier(Tag::IDENTIFIER, id, line_);
		reserve(new_identifier);
		return new_identifier;
	}
	return Token(Tag::UNKNOWN, ""); // AN UNKNOWN TOKEN
}

Token LexicalAnalyzer::explore_string(char c)
{
	// checking for strings
	if (c == '\"')
	{
		std::string str;
		do {
			str += c;
			if (eof_src_code()) break;
			c = getcharacter();
		} while (c != '\"');

		// we reached EOF and string is not finished 
		if (c != '\"') return Token(Tag::UNKNOWN_STRING, str, line_);
		
		Token new_str(Tag::STR, str + c, line_);
		reserve(new_str); // reserve the string
		return new_str;
	}
	return Token(Tag::UNKNOWN, "");
}

char LexicalAnalyzer::jump_unnecesary_characters()
{
	char c = ' ';
	while (!eof_src_code()) // while we do not reach end of file on the document
	{
		c = getcharacter();
		if (c == '\t' || c == ' ' || c == '\r') continue;
		else if (c == '!') {
			if (eof_src_code()) return c; // return a logical negation "!" lexeme
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

void LexicalAnalyzer::reserve_initial_words()
{
	words_table_.clear();
	// reserving reserved words
	reserve(Token(Tag::MAIN, "main"));
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
	reserve(Token(Tag::BREAK, "break"));
	reserve(Token(Tag::PRINT, "print"));
	// booleans lexemes
	reserve(SPTokens::instance().get_True()); // true
	reserve(SPTokens::instance().get_False()); // false
	// data types
	reserve(Token(Tag::INT, "int"));
	reserve(Token(Tag::FLOAT, "float"));
	reserve(Token(Tag::BOOL, "bool"));
	reserve(Token(Tag::STRING, "string"));
}