#include "Token.h"

Token::Token(Source *source) throw (string)
	: type((TokenType)0), text(""), value(nullptr), source(source),
	line_number(source->get_line_number()),
	position(source->get_position())
{
}