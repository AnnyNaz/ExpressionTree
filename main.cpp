#include <iostream>
#include <string>

#include "ExpressionTree.h" 
namespace TestSystem
{
    static bool passed_flag = true;

    template <typename T>
    bool testEquals(const char* name, const T& left, const T& right)
    {
        bool res = left == right;
        static int i = 0;
        std::cout << "Test "
            << name << " - "
            << (res ? "Passed!" : "Failed!")
            << std::endl;
        if (!res)
        {
            passed_flag = false;
            std::cout << ">>> " << left << " != " << right << std::endl;
        }
        return res;
    };

    void result()
    {
        if (passed_flag)
        {
            std::cout << "\nAll tests were passed SUCCESSFULLY!!!" << std::endl;
        }
        else
        {
            std::cout << "\nSome tests were FAILED!!!" << std::endl;
        }
    }
}

void nodesTest(const std::string& test_name, AbstractNode* node, int result)
{
    TestSystem::testEquals(test_name.c_str(), node->execute(), result);
    delete node;
}

void parserTest(const std::string& str, int result)
{
    auto node = parse(str);
    auto test_name = "parsing : " + str + " == " + std::to_string(result);
    TestSystem::testEquals(test_name.c_str(), parse(str)->execute(), result);
    delete node;
}

int main()
{
    // the first part

    nodesTest("NumberNode: 25",

        new NumberNode(25)

        , 25);

    nodesTest("SumNode: 2+3",

        new SumNode(
            new NumberNode(2),
            new NumberNode(3))

        , 5);

    nodesTest("MinusNode: 2-3",

        new MinusNode(
            new NumberNode(2),
            new NumberNode(3))

        , -1);

    nodesTest("MultiNode: 2*3",

        new MinusNode(
            new NumberNode(2),
            new NumberNode(3))

        , -1);

    nodesTest("Composition: 2*(2+3)",

        new MultiNode(
            new NumberNode(2),
            new SumNode(
                new NumberNode(3),
                new NumberNode(2)))

        , 10);
    AbstractNode* t1 = new MultiNode(
        new NumberNode(2),
        new SumNode(
            new NumberNode(3),
            new NumberNode(2)));
    std::cout<< t1->print() << std::endl;
    // the second part

    parserTest("5", 5);
    parserTest("550", 550);
    parserTest("2+2", 4);
    parserTest("15+70", 85);
    parserTest("10+20+30", 60);
    parserTest("4-4-4", -4);
    parserTest("2+3*2-1", 7);
    parserTest("10*4+1+1+3*20", 102);
    parserTest("4-4-4*6-8", -32);
    parserTest("(10*4+5)", 45);
    parserTest("(8-4)-(4-2)", 2);
    parserTest("((10*4+5))", 45);
    parserTest("(10+20)*3", 90);
    parserTest("(10+20)*3+5*(10+10)", 190);
    system("pause");
}