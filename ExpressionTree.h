#include <string>
#include <unordered_map>

class AbstractNode 
{
	public:
		virtual int execute() const = 0;
		virtual std::string print() const = 0;
		virtual AbstractNode* clone() const = 0;
};
class NumberNode : public AbstractNode 
{
	public:
		NumberNode(int num);
		int execute() const override;
		std::string print() const override;
		NumberNode* clone() const override;

	private:
		int m_number;
};
class CompositeNode : public AbstractNode
{
	public:
		CompositeNode(AbstractNode* node1, AbstractNode* node2);
		std::string print() const override;
		
		virtual ~CompositeNode();
	protected:
		AbstractNode* m_left,* m_right;
		std::string m_symbol = "";
}; 
class SumNode : public CompositeNode
{
	public:
		SumNode(AbstractNode* node1, AbstractNode* node2);
		int execute() const override;
		SumNode* clone() const override;
};
class MultiNode: public CompositeNode
{
	public:
		MultiNode(AbstractNode* node1, AbstractNode* node2);
		int execute() const override;
		MultiNode* clone() const override;
};
class MinusNode : public CompositeNode
{
	public:
		MinusNode(AbstractNode* node1, AbstractNode* node2);
		int execute() const override;
		MinusNode* clone() const override;
};







AbstractNode* parse(const std::string& str);