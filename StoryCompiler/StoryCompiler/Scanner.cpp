#include "Scanner.h"

Scanner::Scanner(Source *source) : source(source), token(nullptr)
{
}

Scanner::~Scanner()
{
}

Token *Scanner::current_token() { return token; }

Token *Scanner::next_token(Token *prev_token) throw (string)
{
	if (prev_token != nullptr) delete prev_token;
	token = extract_token();
	return token;
}

char Scanner::current_char() throw (string)
{
	return source->current_char();
}

char Scanner::next_char() throw (string)
{
	return source->next_char();
}

bool Scanner::at_eol() throw (string)
{
	return source->at_eol();
}

bool Scanner::at_eof() throw (string)
{
	return source->at_eof();
}

void Scanner::skip_to_next_line() throw (string)
{
	source->skip_to_next_line();
}