#pragma once

#include <string>
#include "TypeSpec.h"

using namespace std;

class TypeFactory
{
public:
	/**
	* Create a type specification of a given form.
	* @param form the form.
	* @return the type specification.
	*/
	static TypeSpec *create_type(const TypeForm form);

	/**
	* Create a string type specification.
	* @param value the string value.
	* @return the type specification.
	*/
	static TypeSpec *create_string_type(const string value);
};