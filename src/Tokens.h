#ifndef TOKENS_H_
#define TOKENS_H_
#include <iostream>
#include <string>

enum class Tag
{
	// starting main
	MAIN,
	// Data Types
	INT, // for integers
	FLOAT, // for decimals
	BOOL, // for booleans
	STRING, // for string datatypes

	// Logical operators
	AND, // && logical and
	OR, // || logical or
	NEG, // ! logical negation

	// Relational operators
	EQ, // == equal
	NE, // != not equal
	LE, // < less than
	LEQ, // <= less or equal 
	GE, // > greater than
	GEQ, // >= greater or equal 

	// Aritmetic operators
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
	LBRACKET, // { left bracket
	RBRACKET, // } right bracket

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
	BREAK, // para realizar breaks
	PRINT, // para imprimir variables o expresiones
	TRUE, // true
	FALSE, // false
	//  general token for identifiers
	IDENTIFIER,
	// general token for numbers
	NUM, // integral numbers
	REAL, // real numbers
	// general token for strings
	STR, // "some_string"
	
	E_O_F, // end of file token

	// tokens for unknown lexemes
	UNKNOWN, // this token is for unknown characters
	UNKNOWN_NUMBER, // this token is for UNKNOWN (Error) number lexemes
	UNKNOWN_OPERATOR, // this token is for UNKNOWN operators, e.g. only "&" or "|" or "!"
	UNKNOWN_STRING // this token is for UNKNOWN (Error) strings, e.g "abc$ (where $ means EOF)
};

class Token
{
private:
	Tag token_tag_;
	std::string lexeme_;
	int line_; // line where it is located the token
public:
	enum class TYPE_ANALYSIS {LEXICAL, SINTACTIC};
	Token();
	Token(Tag entry_token_tag, const std::string& entry_lexeme, int entry_line = 0);
	// getters
	Tag get_token_tag() const;
	std::string get_token_tag_as_str(TYPE_ANALYSIS type_analysis) const;
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
		const Token and_symbol(Tag::AND, "&&");
		return and_symbol;
	}

	const Token get_or() {
		static Token or_symbol(Tag::OR, "||");
		return or_symbol;
	}

	const Token get_neg() {
		static Token neg_symbol(Tag::NEG, "!");
		return neg_symbol;
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

	const Token get_left_bracket() {
		static Token left_bracket(Tag::LBRACKET, "{");
		return left_bracket;
	}

	const Token get_right_bracket() {
		static Token right_bracket(Tag::RBRACKET, "}");
		return right_bracket;
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
		static Token E_O_F(Tag::E_O_F, "$" + '\0');
		return E_O_F;
	}
	
private:
	SPTokens() {}
	~SPTokens() {}
};


#endif // !TOKENS_H_
