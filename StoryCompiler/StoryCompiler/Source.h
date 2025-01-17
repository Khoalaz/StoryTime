#pragma once
#pragma warning( disable : 4290 )

#include <iostream>
#include <fstream>
#include <string>

#include "MessageHandler.h"
#include "MessageListener.h"
#include "MessageProducer.h"

using namespace std;

class Source : public MessageProducer
{
public:
	/**
	* Constructor.
	* @param reader the reader for the source program
	*/
	Source(istream &reader);

	/**
	* Getter.
	* @return the current source line number.
	*/
	int get_line_number() const;

	/**
	* Getter.
	* @return the position of the next source character in the
	* current source line.
	*/
	int get_position() const;

	/**
	* Return the source character at the current position.
	* @return the source character at the current position.
	* @throw a string message if an error occurred.
	*/
	char current_char() throw (string);

	/**
	* Consume the current source character and return the next character.
	* @return the next source character.
	* @throw a string message if an error occurred.
	*/
	char next_char() throw (string);

	/**
	* Return the source character following the current character without
	* consuming the current character.
	* @return the following character.
	* @throw a string message if an error occurred.
	*/
	char peek_char() throw (string);

	/**
	* @return true if at the end of the line, else return false.
	* @throw a string message if an error occurred.
	*/
	bool at_eol() throw (string);

	/**
	* @return true if at the end of the file, else return false.
	* @throw a string message if an error occurred.
	*/
	bool at_eof() throw (string);

	/**
	* Skip the rest of the current input line
	* by forcing the next read to read a new line.
	* @throw a string message if an error occurred.
	*/
	void skip_to_next_line() throw (string);

	/**
	* Add a message listener to the listener list.
	* Implementation of wci::message::MessageProducer.
	* @param listener the message listener to add.
	*/
	void add_message_listener(MessageListener *listener);

	/**
	* Send a message.
	* Implementation of wci::message::MessageProducer.
	* @param message the message to send.
	*/
	void send_message(Message& message) const;

	static const char END_OF_LINE;
	static const char END_OF_FILE;

private:
	istream& reader;                  // reader for the source program
	string line_text;                 // source line text
	int line_number;                  // current source line number
	int current_pos;                  // current source line position
	MessageHandler message_handler;

	/**
	* Read the next source line.
	* @throw a string message if an error occurred.
	*/
	void read_line() throw (string);
};