#pragma once

#include <vector>
#include <map>
#include "SymTabEntry.h"

using namespace std;

/**
* Type specification form
*/
enum class TypeForm
{
	// to be "subclassed" by implementation-specific type forms
};

/**
* Type specification key
*/
enum class TypeKey
{
	// to be "subclassed" by implementation-specific type keys
};

class TypeSpec;  // forward declaration

				 /**
				 * Type value.
				 */
struct TypeValue
{
	DataValue *value;
	TypeSpec  *typespec;
	SymTab    *symtab;
	vector<SymTabEntry *> v;

	TypeValue()
		: value(nullptr), typespec(nullptr), symtab(nullptr) {}
	TypeValue(DataValue *value)
		: value(value), typespec(nullptr), symtab(nullptr) {}
	TypeValue(TypeSpec *typespec)
		: value(nullptr), typespec(typespec), symtab(nullptr) {}
	TypeValue(SymTab *symtab)
		: value(nullptr), typespec(nullptr), symtab(symtab) {}

	~TypeValue() {}
};

class TypeSpec
{
public:
	/**
	* Destructor.
	*/
	virtual ~TypeSpec() {}

	/**
	* Getter
	* @return the type form.
	*/
	virtual TypeForm get_form() const = 0;

	/**
	* Getter.
	* @return the type identifier (symbol table entry).
	*/
	virtual SymTabEntry *get_identifier() = 0;

	/**
	* Setter.
	* @param id the type identifier (symbol table entry).
	*/
	virtual void set_identifier(SymTabEntry *id) = 0;

	/**
	* Set an attribute of the specification.
	* @param key the attribute key.
	* @param value the attribute value.
	*/
	virtual void set_attribute(TypeKey key, TypeValue *value) = 0;

	/**
	* Get the value of an attribute of the specification.
	* @param key the attribute key.
	* @return the attribute value.
	*/
	virtual TypeValue *get_attribute(TypeKey key) = 0;

	/**
	* To be defined by an implementation subclass.
	* @return true if this is a StoryTime string type.
	*/
	virtual bool is_storytime_string() = 0;

	/**
	* To be defined by an implementation subclass.
	* @return the base type of this type.
	*/
	virtual TypeSpec *base_type() = 0;
};