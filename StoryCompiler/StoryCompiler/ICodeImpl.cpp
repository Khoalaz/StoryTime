#include "ICodeImpl.h"

ICodeNode *ICodeImpl::get_root() const { return root; }

ICodeNode *ICodeImpl::set_root(ICodeNode *node)
{
	root = node;
	return node;
}