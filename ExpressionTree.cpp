#include "ExpressionTree.h"
using namespace std;
NumberNode::NumberNode(int num) :m_number(num) {};
CompositeNode::CompositeNode(AbstractNode* node1, AbstractNode* node2) :m_left(node1), m_right(node2) {};
SumNode::SumNode(AbstractNode* node1, AbstractNode* node2) :CompositeNode(node1, node2) { m_symbol = "+"; };
MultiNode::MultiNode(AbstractNode* node1, AbstractNode* node2) :CompositeNode(node1, node2) { m_symbol = "*"; };
MinusNode::MinusNode(AbstractNode* node1, AbstractNode* node2) :CompositeNode(node1, node2) { m_symbol = "-"; };
int  NumberNode::execute() const 
{
	return m_number;
}
int SumNode::execute() const
{
	return m_left->execute() + m_right->execute();
}
int MultiNode::execute() const
{
	return m_left->execute() * m_right->execute();
}
int MinusNode::execute()  const
{
	return m_left->execute() -  m_right->execute();
}
string NumberNode::print() const 
{
	return to_string(m_number);
}
CompositeNode::~CompositeNode()
{
	delete m_left;
	delete m_left;
}
NumberNode* NumberNode::clone() const
{
	return new NumberNode(*this);
}
MinusNode* MinusNode::clone() const
{
	return new MinusNode(*this);
}
MultiNode* MultiNode::clone() const
{
	return new MultiNode(*this);
}
SumNode* SumNode::clone() const
{
	return new SumNode(*this);
}

string CompositeNode::print() const
{
	return "(" + m_left->print() + ")" + m_symbol + "(" + m_right->print() + ")";
}
AbstractNode* abstractFactory(char symbol, AbstractNode* a1, AbstractNode* a2)
{
	if (symbol == '+')
		return new SumNode(a1, a2);
	if (symbol == '-')
		return new MinusNode(a1, a2);
	if (symbol == '*')
		return new MultiNode(a1, a2);
	return nullptr;
}

AbstractNode* parse(const std::string& str)
{
	int brackets;
	for (auto symbol : { '-', '+', '*' })
	{
		brackets = 0;
		for (int i = str.size(); i >= 0; --i)
		{
			if (str[i] == '(')
				++brackets;
			else if (str[i] == ')')
				--brackets;
			else if (brackets == 0 && str[i] == symbol)
			{
				AbstractNode* a1 = parse(str.substr(0, i));
				AbstractNode* a2 = parse(str.substr(i + 1, str.size() - i));
				return abstractFactory(str[i], a1, a2);
			}
		}
	}
	if (str[0] == '(' && str[str.size() - 1] == ')')
		return parse(str.substr(1, str.size() - 2));

	return new NumberNode(stoi(str));
}

