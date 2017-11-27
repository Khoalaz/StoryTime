#include "Source.h"

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

	// Need to read the next line?
	else if (current_pos > line_text.length()) {
		read_line();
		return next_char();
	}

	// Return the character at the current position.
	else return line_text[current_pos];
}