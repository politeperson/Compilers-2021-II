#include <iostream>
#include "Tokens.h"

// CONSTRUCTOR
Token::Token()
{
	token_tag_ = Tag::UNKNOWN; // por defecto es un identificador
	lexeme_ = ""; // empty lexeme
	line_ = 0; // line 0 does not exist
}

Token::Token(Tag entry_token_tag, const std::string& entry_lexeme, int entry_line)
{
	token_tag_ = entry_token_tag;
	lexeme_ = entry_lexeme;
	line_ = entry_line;
}

// GETTERS
Tag Token::get_token_tag() const
{
	return token_tag_;
}

std::string Token::get_token_tag_as_str() const
{
	switch (token_tag_)
	{
		// Data Types
	case Tag::INT:
		return std::string("INT");
	case Tag::FLOAT:
		return std::string("FLOAT");
	case Tag::BOOL:
		return std::string("BOOL");
	case Tag::STR:
		return std::string("STR");
		// Logical Operators
	case Tag::AND:
		return std::string("AND");
	case Tag::OR:
		return std::string("OR");
		// Relational Operators
	case Tag::EQ:
		return std::string("EQ");
	case Tag::NE:
		return std::string("NEQ");
	case Tag::LE:
		return std::string("LE");
	case Tag::LEQ:
		return std::string("LEQ");
	case Tag::GE:
		return std::string("GE");
	case Tag::GEQ:
		return std::string("GEQ");
		// Arithmetic Operators
	case Tag::PLUS:
		return std::string("PLUS");
	case Tag::MINUS:
		return std::string("MINUS");
	case Tag::MULT:
		return std::string("MULT");
	case Tag::DIV:
		return std::string("DIV");
		// For assignation
	case Tag::ASSIGN:
		return std::string("ASSIGN");
		// Delimiters
	case Tag::LPAR:
		return std::string("LPAR");
	case Tag::RPAR:
		return std::string("RPAR");
	case Tag::COMMA:
		return std::string("COMMA");
	case Tag::DOTCOMMA:
		return std::string("DOTCOMMA");
		// Reserved words
	case Tag::IF:
		return std::string("IF");
	case Tag::ENDIF:
		return std::string("ENDIF");
	case Tag::ELSE:
		return std::string("ELSE");
	case Tag::WHILE:
		return std::string("WHILE");
	case Tag::ENDWHILE:
		return std::string("ENDWHILE");
	case Tag::FOR:
		return std::string("FOR");
	case Tag::ENDFOR:
		return std::string("ENDFOR");
	case Tag::FUNCTION:
		return std::string("FUNCTION");
	case Tag::RETURN:
		return std::string("FUNCTION");
	case Tag::ENDFUNCTION:
		return std::string("ENDFUNCTION");
	case Tag::TRUE:
		return std::string("TRUE");
	case Tag::FALSE:
		return std::string("FALSE");
		// Identifiers
	case Tag::IDENTIFIER:
		return std::string("IDENTIFIER");
		// Numbers
	case Tag::NUM:
		return std::string("NUMBER");
	case Tag::REAL:
		return std::string("REAL");
		// Strings of characters
	case Tag::STRING:
		return std::string("STRING");
		// End of File
	case Tag::E_O_F:
		return std::string("EOF");
		// Unknown tokens
	case Tag::UNKNOWN:
		return std::string("UNKNOWN");
	case Tag::UNKNOWN_NUMBER:
		return std::string("UNKNOWN_NUMBER");
	case Tag::UNKNOWN_OPERATOR:
		return std::string("UNKNOWN_OPERATOR");
	case Tag::UNKNOWN_STRING:
		return std::string("UNKNOWN_STRING");
	}
	return std::string(""); // thoreticaly we do not reach this part of the code
}

std::string Token::get_lexeme() const
{
	return lexeme_;
}

int Token::get_line() const
{
	return line_;
}

// SETTERS
void Token::set_token_tag(Tag new_token_tag)
{
	token_tag_ = new_token_tag;
}

void Token::set_lexeme(const std::string& new_lexeme)
{
	lexeme_ = new_lexeme;
}

void Token::set_line(int new_line)
{
	line_ = new_line;
}
// DESTRUCTOR
Token::~Token()
{
}

// printing function
std::ostream& operator<<(std::ostream& os, const Token& tok)
{
	if (!tok.line_) // line 0 doesn't exist 
	{
		os << "<" << tok.get_token_tag_as_str() << "," << tok.get_lexeme() << ">";
		return os;
	}
	os << "<" << tok.get_token_tag_as_str() << "," << tok.get_lexeme() << "," << tok.get_line() << ">";
	return os;
}
