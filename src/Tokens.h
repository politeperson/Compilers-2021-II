#pragma once
#ifndef TOKENS_H_
#define TOKENS_H_
#include <iostream>
#include <string>

enum class Tag
{
	// logical operators
	AND, // && logical and
	OR, // || logical or
	EQ, // == equal
	NE, // != not equal

	// comparison operators
	LE, // < less than
	LEQ, // <= less or equal 
	GE, // > greater than
	GEQ, // >= greater or equal 

	// aritmetic operators
	PLUS, // + plus
	MINUS, // - minus
	MULT, // * multiplication and scalar product
	DIV, // "/" division means inverse for matrix, error for vectors

	// assignation operator
	ASSIGN, // = assignation

	// individual tokens for delimiters
	LPAR, // ( left parenthesis
	RPAR, // ) right parethesis
	COMMA, // , comma
	DOTCOMMA, // ; dot and comma

	// individual tokens for reserved words
	IF,
	ENDIF,
	ELSE,
	WHILE,
	ENDWHILE,
	FOR,
	ENDFOR,
	FUNCTION,
	RETURN,
	ENDFUNCTION,
	TRUE,
	FALSE,
	//  general token for identifiers
	IDENTIFIER,
	// general token for numbers
	NUMBER, // integral numbers
	REAL, // real numbers
	// general token for strings
	STRING,
	// token for unknown lexemes
	UNKNOWN,
	E_O_F // end of file token
};

class Token
{
private:
	Tag token_tag_;
	std::string lexeme_;
	int line_; // line where it is located the token

public:
	Token();
	Token(Tag entry_token_tag, const std::string& entry_lexeme, int entry_line = 0);
	// getters
	Tag get_token_tag() const;
	std::string get_token_tag_as_str() const;
	std::string get_lexeme() const;
	int get_line() const;

	// setters
	void set_token_tag(Tag new_token_tag);
	void set_lexeme(const std::string& new_lexeme);
	void set_line(int new_line);

	// printing
	friend std::ostream& operator<<(std::ostream& os, const Token& tok);
	~Token();
};


////////////////////////////////////////////////////////////
// 
//  A CLASS FOR HANDLING SPECIAL TOKENS
//
////////////////////////////////////////////////////////////


// Special TOKENS
class SPTokens
{
public:

	static SPTokens& instance() {
		static SPTokens* instance = new SPTokens();
		return *instance;
	}
	const Token get_and() { 
		static Token and(Tag::AND, "&&");
		return and; 
	}

	const Token get_or() {
		static Token or (Tag::OR, "||");
		return or;
	}
	
	const Token get_eq() {
		static Token eq (Tag::EQ, "==");
		return eq;
	}

	const Token get_ne() {
		static Token ne(Tag::NE, "!=");
		return ne;
	}
	
	const Token get_le() {
		static Token le(Tag::LE, "<");
		return le;
	}

	const Token get_leq() {
		static Token leq(Tag::LEQ, "<=");
		return leq;
	}

	const Token get_ge() {
		static Token ge(Tag::GE, ">");
		return ge;
	}

	const Token get_geq() {
		static Token geq(Tag::GEQ, ">=");
		return geq;
	}

	const Token get_plus() {
		static Token plus(Tag::PLUS, "+");
		return plus;
	}

	const Token get_minus() {
		static Token minus(Tag::MINUS, "-");
		return minus;
	}

	const Token get_mult() {
		static Token mult(Tag::MULT, "*");
		return mult;
	}

	const Token get_div() {
		static Token div(Tag::DIV, "/");
		return div;
	}

	const Token get_assign() {
		static Token assign(Tag::ASSIGN, "=");
		return assign;
	}

	const Token get_lpar() {
		static Token lpar(Tag::LPAR, "(");
		return lpar;
	}

	const Token get_rpar() {
		static Token rpar(Tag::RPAR, ")");
		return rpar;
	}
	
	const Token get_comma() {
		static Token comma(Tag::COMMA, ",");
		return comma;
	}
	
	const Token get_dotcomma() {
		static Token dotcomma(Tag::DOTCOMMA, ";");
		return dotcomma;
	}

	const Token get_True() {
		static Token True(Tag::TRUE, "true");
		return True;
	}
	
	const Token get_False() {
		static Token False(Tag::FALSE, "false");
		return False;
	}

	const Token get_eof() {
		static Token E_O_F(Tag::E_O_F, "" + '\0');
		return E_O_F;
	}
	
private:
	SPTokens() {}
	~SPTokens()
	{}
};


#endif // !TOKENS_H_
