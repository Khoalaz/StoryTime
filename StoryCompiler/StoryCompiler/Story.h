#pragma warning( disable : 4290 )
#include <string>
#include <iostream>
#include <fstream>

#include "MessageListener.h"


using namespace std;

class Story : public MessageListener
{
public:
	/**
	* Constructor.
	* Compile or interpret a Story source program.
	* @param operation either "compile" or "execute".
	* @param filePath the source file path.
	* @param flags the command line flags.
	*/
	Story(string operation, string file_path, string flags)
		throw (string);

	/**
	* Destructor.
	*/
	virtual ~Story();

	/**
	* Receive a message sent by a message producer.
	* Implementation of wci::message::MessageListener.
	* @param message the message that was received.
	*/
	void message_received(Message& message);

private:
	//Parser      *parser;        // language-independent parser
	//Source      *source;        // input file source
	//ICode       *icode;         // generated intermediate code
	//SymTabStack *symtab_stack;  // generated symbol table stack
	//Backend     *backend;       // backend

	bool intermediate, xref, lines, assign, fetch, call, returnn;

	static const string SOURCE_LINE_FORMAT;
	static const string PARSER_SUMMARY_FORMAT;
	static const string INTERPRETER_SUMMARY_FORMAT;
	static const string COMPILER_SUMMARY_FORMAT;
	static const string LINE_FORMAT;
	static const string ASSIGN_FORMAT;
	static const string FETCH_FORMAT;
	static const string CALL_FORMAT;
	static const string RETURN_FORMAT;
	static const string RUNTIME_ERROR_FORMAT;

	static const int PREFIX_WIDTH;

	/**
	* Convert a number as a string to a string with commas.
	* @param str the number as a string.
	* @return the commafied number.
	*/
	string commafy(string str);
};