#pragma once
#pragma warning( disable : 4290 )

#include "Source.h"
#include "Token.h"

class Scanner
{
public:
	/**
	* Constructor
	* @param source the source to be used with this scanner.
	*/
	Scanner(Source *source);

	/**
	* Destructor.
	*/
	virtual ~Scanner();

	/**
	* @return the current token.
	*/
	Token *current_token();

	/**
	* @param prev_token the previous token.
	* @return the next token from the source.
	* @throw a string message if an error occurred.
	*/
	Token *next_token(Token *prev_token) throw (string);

	/**
	* @return the current character from the source.
	* @throw a string message if an error occurred.
	*/
	char current_char() throw (string);

	/**
	* @return the next character from the source.
	* @throw a string message if an error occurred.
	*/
	char next_char() throw (string);

	/**
	* Call the source's at_eol() method.
	* @return true if at the end of the source line, else return false.
	* @throw a string message if an error occurred.
	*/
	bool at_eol() throw (string);

	/**
	* Call the source's at_eof() method.
	* @return true if at the end of the source file, else return false.
	* @throw a string message if an error occurred.
	*/
	bool at_eof() throw (string);

	/**
	* Call the source's skip_to_next_line() method.
	* @throw a string message if an error occurred.
	*/
	void skip_to_next_line() throw (string);

protected:
	Source *source;

	/**
	* Extract the next token from the source.
	* Implemented by the language-specific scanner subclasses.
	* @return the token.
	* @throw a string message if an error occurred.
	*/
	virtual Token *extract_token() throw (string) = 0;

private:
	Token *token;
};