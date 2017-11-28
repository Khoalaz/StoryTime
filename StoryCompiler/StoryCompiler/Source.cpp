#include "Source.h"

const char Source::END_OF_LINE = '\n';
const char Source::END_OF_FILE = (char)0;

Source::Source(istream &reader): reader(reader), line_number(0), current_pos(-2) // set position to -2 to read the first source line
{
}

int Source::get_line_number() const 
{ 
	return line_number; 
}

int Source::get_position() const 
{ 
	return current_pos; 
}

char Source::current_char() throw (string)
{
	if (current_pos == -2) 
	{
		read_line();
		return next_char();
	}
	else if (reader.eof())
	{
		return END_OF_FILE;
	}
	else if ((current_pos == -1) || (current_pos == line_text.length())) 
	{
		return END_OF_LINE;
	}
	else if ((unsigned int)current_pos > line_text.length()) {
		read_line();
		return next_char();
	}
	else
	{
		return line_text[current_pos];
	}
}

char Source::next_char() throw (string)
{
	++current_pos;
	return current_char();
}

char Source::peek_char() throw (string)
{
	current_char();

	if (reader.eof()) return END_OF_FILE;

	int next_pos = current_pos + 1;
	return (unsigned int)next_pos < line_text.length() ? line_text[next_pos]
		: END_OF_LINE;
}

bool Source::at_eol() throw (string)
{
	return current_pos == line_text.length();
}

bool Source::at_eof() throw (string)
{
	// First time?
	if (current_pos == -2)  read_line();

	return reader.eof();
}

void Source::skip_to_next_line() throw (string)
{
	current_pos = line_text.length() + 1;
}

void Source::read_line() throw (string)
{
	getline(reader, line_text);

	if (reader.eof()) return;
	if (reader.fail() || reader.bad()) throw string("Source input failure.");

	current_pos = -1;

	if (reader.good())
	{
		int line_length = line_text.length();
		if ((line_length > 0) && (line_text[line_length - 1] == '\r'))
		{
			line_text.resize(--line_length);
		}

		++line_number;

		// Send a source line message containing the line number
		// and the line text to all the listeners.
		Message message(SOURCE_LINE,
			LINE_NUMBER, to_string(line_number),
			LINE_TEXT, line_text);
		send_message(message);
	}
}

void Source::add_message_listener(MessageListener *listener)
{
	message_handler.add_listener(listener);
}

void Source::send_message(Message& message) const
{
	message_handler.send_message(message);
}