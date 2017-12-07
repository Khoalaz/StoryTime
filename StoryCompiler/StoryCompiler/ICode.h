#pragma once

class ICodeNode;

class ICode
{
public:
	/**
	* Destructor.
	*/
	virtual ~ICode() {};

	/**
	* Get the root node.
	* @return the root node.
	*/
	virtual ICodeNode *get_root() const = 0;

	/**
	* Set and return the root node.
	* @param node the node to set as root.
	* @return the root node.
	*/
	virtual ICodeNode *set_root(ICodeNode *node) = 0;
};