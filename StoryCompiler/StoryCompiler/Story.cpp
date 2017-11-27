#include "Story.h"

using namespace std;

const string FLAGS = "[-ixlafcr]";
const string USAGE =
"Usage: Story execute|compile " + FLAGS + " <source file path>";

int main(int argc, char *args[])
{
	/*try
	{
		
		// Operation.
		string operation = args[1];
		if ((operation != "compile") && (operation != "execute"))
		{
			throw USAGE;
		}
		// Flags.
		string flags = "";
		int i = 1;
		while ((++i < argc) && (args[i][0] == '-'))
		{
			flags += string(args[i]).substr(1);
		}

		
		// Source path.
		if (i < argc)
		{
			string path = args[i];
			Story(operation, path, flags);
		}
		else
		{
			throw string("Missing source file.");
		}
	}
	catch (string& msg)
	{
		cout << "***** ERROR: " << msg << endl;
	}*/

	string operation = "";
	string path = "Storysrc.txt";
	string flags = "";
	Story(operation, path, flags);
	
	return 0;
}

Story::Story(string operation, string file_path, string flags)
	throw (string)
{
	ifstream input;
	input.open(file_path);
	if (input.fail())
	{
		throw string("Failed to open source file " + file_path);
	}

	intermediate = flags.find('i') != string::npos;
    xref         = flags.find('x') != string::npos;
    lines        = flags.find('l') != string::npos;
    assign       = flags.find('a') != string::npos;
    fetch        = flags.find('f') != string::npos;
    call         = flags.find('c') != string::npos;
    returnn      = flags.find('r') != string::npos;
}

Story::~Story()
{
	//if (parser != nullptr) delete parser;
	//if (source != nullptr) delete source;
	//if (icode != nullptr) delete icode;
	//if (symtab_stack != nullptr) delete symtab_stack;
	//if (backend != nullptr) delete backend;
}

void Story::message_received(Message& message)
{
	MessageType type = message.get_type();

	switch (type)
	{
	case SOURCE_LINE:
	{
		string line_number = message[LINE_NUMBER];
		string line_text = message[LINE_TEXT];

		printf(SOURCE_LINE_FORMAT.c_str(),
			stoi(line_number), line_text.c_str());
		break;
	}

	case PARSER_SUMMARY:
	{
		string line_count = commafy(message[LINE_COUNT]);
		string error_count = message[ERROR_COUNT];
		string elapsed_time = message[ELAPSED_TIME];

		printf(PARSER_SUMMARY_FORMAT.c_str(),
			line_count.c_str(), stoi(error_count),
			stof(elapsed_time));
		break;
	}

	case INTERPRETER_SUMMARY:
	{
		string execution_count = commafy(message[EXECUTION_COUNT]);
		string error_count = message[ERROR_COUNT];
		string elapsed_time = message[ELAPSED_TIME];

		printf(INTERPRETER_SUMMARY_FORMAT.c_str(),
			execution_count.c_str(), stoi(error_count),
			stof(elapsed_time));
		break;
	}

	case COMPILER_SUMMARY:
	{
		string instruction_count = commafy(message[INSTRUCTION_COUNT]);
		string elapsed_time = message[ELAPSED_TIME];

		printf(COMPILER_SUMMARY_FORMAT.c_str(),
			instruction_count.c_str(), stof(elapsed_time));
		break;
	}

	case AT_LINE:
	{
		if (lines)
		{
			string line_number = message[LINE_NUMBER];
			printf(LINE_FORMAT.c_str(), stoi(line_number));
		}
		break;
	}

	case ASSIGN:
	{
		if (assign)
		{
			string line_number = message[LINE_NUMBER];
			string variable_name = message[VARIABLE_NAME];
			string value_str = message[RESULT_VALUE];

			printf(ASSIGN_FORMAT.c_str(),
				stoi(line_number), variable_name.c_str(),
				value_str.c_str());
		}
		break;
	}

	case FETCH:
	{
		if (fetch)
		{
			string line_number = message[LINE_NUMBER];
			string variable_name = message[VARIABLE_NAME];
			string value_str = message[RESULT_VALUE];

			printf(FETCH_FORMAT.c_str(),
				stoi(line_number), variable_name.c_str(),
				value_str.c_str());
		}
		break;
	}

	case CALL:
	{
		if (call)
		{
			string line_number = message[LINE_NUMBER];
			string routine_name = message[VARIABLE_NAME];

			printf(CALL_FORMAT.c_str(),
				stoi(line_number), routine_name.c_str());
		}
		break;
	}

	case RETURN:
	{
		if (call)
		{
			string line_number = message[LINE_NUMBER];
			string routine_name = message[VARIABLE_NAME];

			printf(RETURN_FORMAT.c_str(),
				stoi(line_number), routine_name.c_str());
		}
		break;
	}

	case SYNTAX_ERROR:
	{
		string token_type = message[TOKEN_TYPE];
		string line_text = message[LINE_TEXT];
		string position = message[POSITION];
		string token_text = message[TOKEN_TEXT];
		string error_message = message[ERROR_MESSAGE];

		int space_count = PREFIX_WIDTH + stoi(position);
		string flag = "";

		// Spaces up to the error position.
		for (int i = 1; i < space_count; ++i) flag += " ";

		// A pointer to the error followed by the error message.
		flag += "^\n*** " + error_message;

		// Text, if any, of the bad token.
		if (token_text.length() > 0)
		{
			flag += " [at \"" + token_text + "\"]\n";
		}

		cout << flag;
		break;
	}

	case RUNTIME_ERROR:
	{
		string line_number = message[LINE_NUMBER];
		string error_message = message[ERROR_MESSAGE];

		printf(RUNTIME_ERROR_FORMAT.c_str(),
			stoi(line_number), error_message.c_str());
		break;
	}

	default: break;
	}
}

string Story::commafy(string str)
{
	int pos = str.length() - 3;

	while (pos > 0)
	{
		str.insert(pos, ",");
		pos -= 3;
	}

	return str;
}

const string Story::SOURCE_LINE_FORMAT = "%03d %s\n";

const string Story::PARSER_SUMMARY_FORMAT =
string("\n%20s source lines.\n%20d syntax errors.\n") +
string("%20.2f seconds total parsing time.\n");

const string Story::INTERPRETER_SUMMARY_FORMAT =
string("\n%20s statements executed.\n") +
string("%20d runtime errors.\n") +
string("%20.2f seconds total execution time.\n");

const string Story::COMPILER_SUMMARY_FORMAT =
string("\n%20s instructions generated.\n") +
string("%20.2f seconds total code generation time.\n");

const string Story::LINE_FORMAT = ">>> AT LINE %03d\n";

const string Story::ASSIGN_FORMAT = ">>> AT LINE %03d: %s = %s\n";

const string Story::FETCH_FORMAT = ">>> AT LINE %03d: %s : %s\n";

const string Story::CALL_FORMAT = ">>> AT LINE %03d: CALL %s\n";

const string Story::RETURN_FORMAT = ">>> AT LINE %03d: RETURN FROM %s\n";

const string Story::RUNTIME_ERROR_FORMAT =
"*** RUNTIME ERROR AT LINE %03d: %s\n";

const int Story::PREFIX_WIDTH = 5;
