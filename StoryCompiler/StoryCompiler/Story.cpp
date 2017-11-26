#include <string>

using namespace std;


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
			Pascal(operation, path, flags);
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

