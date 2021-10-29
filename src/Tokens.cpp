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

std::string Token::get_token_tag_as_str(Token::TYPE_ANALYSIS type_analysis) const
{
	switch (token_tag_)
	{
		// main clause
	case Tag::MAIN:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "MAIN" : "main";
		// Data Types
	case Tag::INT:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "INT" : "int";
	case Tag::FLOAT:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "FLOAT" : "float";
	case Tag::BOOL:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "BOOL" : "bool";
	case Tag::STRING:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "STRING" : "string";
		// Logical Operators
	case Tag::AND:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "AND" : "and";
	case Tag::OR:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "OR" : "or";
	case Tag::NEG:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "NEG" : "!";
		// Relational Operators
	case Tag::EQ:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "EQ" : "eq";
	case Tag::NE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "NEQ" : "neq";
	case Tag::LE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "LE" : "le";
	case Tag::LEQ:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "LEQ" : "leq";
	case Tag::GE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "GE" : "ge";
	case Tag::GEQ:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "GEQ" : "geq";
		// Arithmetic Operators
	case Tag::PLUS:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "PLUS" : "+";
	case Tag::MINUS:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "MINUS" : "-";
	case Tag::MULT:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "MULT" : "*";
	case Tag::DIV:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "DIV" : "/";
		// For assignation
	case Tag::ASSIGN:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "ASSIGN" : "=";
		// Delimiters
	case Tag::LPAR:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "LPAR" : "(";
	case Tag::RPAR:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "RPAR" : ")";
	case Tag::LBRACKET:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "LBRACKET" : "{";
	case Tag::RBRACKET:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "RBRACKET" : "}";
	case Tag::COMMA:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "COMMA" : ",";
	case Tag::DOTCOMMA:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "DOTCOMMA" : ";";
		// Reserved words
	case Tag::IF:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "IF" : "if";
	case Tag::ENDIF:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "ENDIF" : "endif";
	case Tag::ELSE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "ELSE" : "else";
	case Tag::WHILE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "WHILE" : "while";
	case Tag::ENDWHILE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "ENDWHILE" : "endwhile";
	case Tag::FOR:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "FOR" : "for";
	case Tag::ENDFOR:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "ENDFOR" : "endfor";
	case Tag::FUNCTION:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "FUNCTION" : "function";
	case Tag::RETURN:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "RETURN" : "return";
	case Tag::ENDFUNCTION:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "ENDFUNCTION" : "endfunction";
	case Tag::TRUE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "TRUE" : "true";
	case Tag::FALSE:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "FALSE" : "false";
		// Identifiers
	case Tag::IDENTIFIER:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "IDENTIFIER" : "id";
		// Numbers
	case Tag::NUM:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "NUMBER" : "num";
	case Tag::REAL:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "REAL" : "real";
		// Strings of characters
	case Tag::STR:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "STR" : "str";
		// End of File
	case Tag::E_O_F:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "EOF" : "$";
		// Unknown tokens
	case Tag::UNKNOWN:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "UNKNOWN" : "unknown";
	case Tag::UNKNOWN_NUMBER:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "UNKNOWN_NUMBER" : "unknown_num";
	case Tag::UNKNOWN_OPERATOR:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "UNKNOWN_OPERATOR" : "unknown_op";
	case Tag::UNKNOWN_STRING:
		return type_analysis == Token::TYPE_ANALYSIS::LEXICAL? "UNKNOWN_STRING" : "unknown_str";
	}
	return std::string(""); // in theory we do not reach this part of the code
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
		os << "[" << tok.get_token_tag_as_str(Token::TYPE_ANALYSIS::LEXICAL) << "," << tok.get_lexeme() << "]";
		return os;
	}
	os << "[" << tok.get_token_tag_as_str(Token::TYPE_ANALYSIS::LEXICAL) << "," << tok.get_lexeme() << "," << tok.get_line() << "]";
	return os;
}
