#include "ExpressionTree.h"
using namespace std;

int  NumberNode::execute() 
{
	return m_number;
}
int SumNode::execute()
{
	return m_left->execute() + m_right->execute();
}
int MultiNode::execute()
{
	return m_left->execute() * m_right->execute();
}
int MinusNode::execute() 
{
	return m_left->execute() -  m_right->execute();
}
AbstractNode* parse(string str) 
{
	for (int i = 0; i < str.size(); ++i) 
	{
		if (str[i] == '+')
		{
			AbstractNode* a1 = parse(str.substr(0, i));
			AbstractNode* a2 = parse(str.substr(i + 1, str.size() - i));
			return new SumNode(a1, a2);
		}
	}
	for (int i = str.size() - 1; i >= 0 ; --i)
	{
		if (str[i] == '-')
		{
			AbstractNode* a1 = parse(str.substr(0, i));
			AbstractNode* a2 = parse(str.substr(i + 1, str.size() - i));
			return new MinusNode(a1, a2);
		}
	}
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '*')
		{
			AbstractNode* a1 = parse(str.substr(0, i));
			AbstractNode* a2 = parse(str.substr(i + 1, str.size() - i));
			return new MultiNode(a1, a2);
		}
	}
	return new NumberNode(stoi(str));
}