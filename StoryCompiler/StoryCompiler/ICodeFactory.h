#pragma once
#include "ICode.h"
#include "ICodeImpl.h"
#include "ICodeNodeImpl.h"
#include "ICode.h"
#include "ICodeNode.h"

class ICodeFactory
{
public:
	/**
	* Create and return an intermediate code implementation.
	* @return the intermediate code implementation.
	*/
	static ICode *create_icode();

	/**
	* Create and return a node implementation.
	* @param type the node type.
	* @return the node implementation.
	*/
	static ICodeNode *create_icode_node(const ICodeNodeType type);
};