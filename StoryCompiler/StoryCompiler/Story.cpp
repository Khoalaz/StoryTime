#include "Story.h"

using namespace std;

const string FLAGS = "[-ixlafcr]";
const string USAGE =
"Usage: Pascal execute|compile " + FLAGS + " <source file path>";

int main(int argc, char *args[])
{
	try
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
	}

	return 0;
}

Story::Story(string operation, string file_path, string flags)
	throw (string)
{
	ifstream input;
	/*input.open(file_path);
	if (input.fail())
	{
		throw string("Failed to open source file " + file_path);
	}*/
}