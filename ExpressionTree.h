#include <string>

class AbstractNode 
{
	public:
		virtual int execute() = 0;
};
class NumberNode : public AbstractNode 
{
	public:
		NumberNode(int num) :m_number(num) {};
		int execute();
	private:
		int m_number;
};
class CompositeNode : public AbstractNode
{
	public:
		CompositeNode(AbstractNode* node1, AbstractNode* node2) :m_left(node1), m_right(node2) {};
	protected:
		AbstractNode* m_left,* m_right;
}; 
class SumNode : public CompositeNode
{
	public:
		SumNode(AbstractNode* node1, AbstractNode* node2) :CompositeNode(node1, node2) {};
		int execute();
};
class MultiNode: public CompositeNode
{
	public:
		MultiNode(AbstractNode* node1, AbstractNode* node2) :CompositeNode(node1, node2) {};
		int execute();
};
class MinusNode : public CompositeNode
{
	public:
		MinusNode(AbstractNode* node1, AbstractNode* node2) :CompositeNode(node1, node2) {};
		int execute();
};
AbstractNode* parse(std::string str);