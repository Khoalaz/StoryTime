#include "Token.h"

Token::Token(Source *source) throw (string)
	: type((TokenType)0), text(""), value(nullptr), source(source),
	line_number(source->get_line_number()),
	position(source->get_position())
{
}

Token::Token(const Token& orig)
{ 
	*this = orig; 
}

Token::~Token()
{
}

TokenType Token::get_type() const 
{ 
	return type; 
}

string Token::get_text() const 
{ 
	return text; 
}

DataValue *Token::get_value() 
{ 
	return value; 
}

int Token::get_line_number() const 
{ 
	return line_number; 
}

int Token::get_position() const { return position; }

void Token::extract() throw (string)
{
	text = to_string(current_char());
	next_char();  // consume current character
}

char Token::current_char() const throw (string)
{
	return source->current_char();
}

char Token::next_char() const throw (string)
{
	return source->next_char();
}

char Token::peek_char() const throw (string)
{
	return source->peek_char();
}