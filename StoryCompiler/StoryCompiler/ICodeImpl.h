#pragma once
#include "ICode.h"

class ICodeImpl : public ICode
{
public:
	/**
	* Get the root node.
	* @return the root node.
	*/
	ICodeNode *get_root() const;

	/**
	* Set and return the root node.
	* @param node the node to set as root.
	* @return the root node.
	*/
	ICodeNode *set_root(ICodeNode *node);

private:
	ICodeNode *root;
};