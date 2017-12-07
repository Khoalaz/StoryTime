#include "ICodeFactory.h"


ICode *ICodeFactory::create_icode()
{
	return new ICodeImpl();
}

ICodeNode *ICodeFactory::create_icode_node(const ICodeNodeType type)
{
	return new ICodeNodeImpl(type);
}