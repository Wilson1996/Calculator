/*
 * @Descripttion: 
 * @version: 
 * @Author: WillissTaan(Wilson.T@sjtu.edu.cn)
 * @Date: 2020-02-04 13:02:04
 * @Last Modified by: WillissTaan
 * @Last Modified Time: Do not edit
 */
#include "expression_evaluation.h"

bool ExpressionEvaluation::extractInput(const QString &input)
{
    items.clear();
    QString substr;
    for (int i = 0; i < input.size(); ++i)
    {
        if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'
                || input[i] == '(' || input[i] == ')')
        {
            if(substr.size() != 0)
            {
                items.push_back(new InputItem(substr.toDouble()));
                substr.clear();
            }
            if(input[i] == '(' || input[i] == ')')
                items.push_back(new InputItem(input[i], BRACKT));
            else
                items.push_back(new InputItem(input[i], OPER));
        }
        else
        {
            substr.push_back(input[i]);
        }
    }
    if(substr.size() != 0)
    {
        items.push_back(new InputItem(substr.toDouble()));
    }

    //debug
    for(auto iter = items.begin(); iter != items.end(); ++iter)
    {
        if((*iter)->type == NUMBER)
            qDebug() << (*iter)->val.number << " ";
        else
            qDebug() << (*iter)->val.oper << " ";
    }

    return true;
}

int ExpressionEvaluation::getPriority(QChar op)const
{
    int prior = 0;
    switch (op.toLatin1())
    {
    case '+':
    case '-':
        prior = 1;
        break;
    case '*':
    case '/':
        prior = 2;
        break;
    default:
//        err = INVALID_OPER;
        break;
    }
    return prior;
}

double ExpressionEvaluation::_calculateTwoNums(double first, double second, QChar op)const
{
    switch (op.toLatin1())
    {
    case '+': return first + second;
    case '-': return first - second;
    case '*': return first * second;
    case '/': return first / second;
    default: return 0;
    }
}

void ExpressionEvaluation::inorder2postorder(QVector<InputItem*>& postOrder)const
{
    QStack<InputItem*> s_ops;
    for(int i = 0; i < items.size(); ++i)
    {
        if(items[i]->type == NUMBER)
            postOrder.push_back(items[i]);
        else if(items[i]->type == OPER)
        {
            while(true)
            {
                if(s_ops.empty() || (s_ops.top()->type == BRACKT && s_ops.top()->val.oper == '('))
                {
                    s_ops.push(items[i]);
                    break;
                }
                else if(getPriority(items[i]->val.oper) > getPriority(s_ops.top()->val.oper))
                {
                    s_ops.push(items[i]);
                    break;
                }
                else
                    postOrder.push_back(s_ops.pop());
            }
        }
        else if(items[i]->type == BRACKT)
        {
            if(items[i]->val.oper == '(')
                s_ops.push(items[i]);
            else
            {
                while(!s_ops.empty() && s_ops.top()->val.oper != '(')
                {
                    postOrder.push_back(s_ops.pop());
                }
                if(!s_ops.empty())
                    s_ops.pop();
            }
        }
    }
    while(!s_ops.empty())
        postOrder.push_back(s_ops.pop());

    //debug
//    for(auto iter = postOrder.begin(); iter != postOrder.end(); ++iter)
//    {
//        if((*iter)->type == NUMBER)
//            qDebug() << (*iter)->val.number << " ";
//        else
//            qDebug() << (*iter)->val.oper << " ";
//    }
}

double ExpressionEvaluation::_calculate(const QVector<InputItem*>& postOrder)const
{
    QStack<double> nums;
    for(int i = 0; i < postOrder.size(); ++i)
    {
        if(postOrder[i]->type == NUMBER)
            nums.push(postOrder[i]->val.number);
        else
        {
            double second = nums.pop();
            double first = nums.pop();
            nums.push(_calculateTwoNums(first, second, postOrder[i]->val.oper));
        }
    }
    return nums.pop();
}

ExpressionEvaluation::ExpressionEvaluation()
{

}

ExpressionEvaluation::~ExpressionEvaluation()
{
    for (auto iter = items.begin(); iter != items.end(); ++iter)
    {
        if (*iter != nullptr)
            delete (*iter);
    }
	for(int i = 0; i < items.size(); ++i)
	{
		
	}
}

double ExpressionEvaluation::calculate(const QString &expression)
{
    extractInput(expression);
    QVector<InputItem*> postOrder;
    inorder2postorder(postOrder);
    return _calculate(postOrder);
}
