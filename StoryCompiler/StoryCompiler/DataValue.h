#pragma once

#include <iostream>
#include <string>

using namespace std;

enum class ValueType
{
	STRING, DIGIT, NONDIGIT, LOGIC,
};

constexpr ValueType NONDIGIT = ValueType::NONDIGIT;
constexpr ValueType DIGIT = ValueType::DIGIT;
constexpr ValueType STRING = ValueType::STRING;
constexpr ValueType LOGIC = ValueType::LOGIC;

class DataValue
{
public:
	ValueType type;
	union
	{
		double d;
		char c;
		bool b;
		string s;
	};

	DataValue() : type((ValueType)-1) {};
	DataValue(const double d) : type(ValueType::DIGIT), d(d) {}
	DataValue(const char c) : type(ValueType::NONDIGIT), c(c) {}
	DataValue(const bool b) : type(ValueType::LOGIC), b(b) {}

	DataValue(const string s) : type(ValueType::STRING)
	{
		new (&this->s) string(s);
	}

	DataValue(const DataValue& orig)
	{
		this->type = orig.type;

		switch (orig.type)
		{
		case ValueType::DIGIT:   this->d = orig.d; break;
		case ValueType::NONDIGIT:    this->c = orig.c; break;
		case ValueType::LOGIC: this->b = orig.b; break;
		case ValueType::STRING:  new (&this->s) string(orig.s); break;
		}
	}

	~DataValue() {}

	string display() const
	{
		switch (type)
		{
		case ValueType::DIGIT:   return to_string(this->d);
		case ValueType::NONDIGIT:    return string(1, this->c);
		case ValueType::LOGIC: return to_string(this->b);
		case ValueType::STRING:  return this->s;

		default: return "";
		}
	}
};