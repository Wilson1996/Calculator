/*
 * @Descripttion: 
 * @version: 
 * @Author: WillissTaan(Wilson.T@sjtu.edu.cn)
 * @Date: 2020-02-04 13:02:04
 * @Last Modified by: WillissTaan
 * @Last Modified Time: Do not edit
 */
#include "expression_evaluation.h"


bool ExpressionEvaluation::isOpeartor(const QChar& ch)const
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/'
            || ch == '(' || ch == ')' || ch == '%');
}

int ExpressionEvaluation::getPriority(const QChar& op)const
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
    case 'm':
        prior = 10;
        break;
    case '%':
        prior = 9;
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
    case 'm': return first - second;
    case '%': return second * 0.01;
    default: return 0;
    }
}

double ExpressionEvaluation::string2double(const QString& str)const
{
    bool OK = false;
    double res = str.toDouble(&OK);
    if(OK)
        return res;
    else
    {
        if(str.back() == "π")
        {
            QString substr = str;
            substr = substr.remove(substr.size()-1, 1);
            return substr.size()==0? PI: substr.toDouble()*PI;
        }
        else if(str.back() == "e")
        {
            QString substr = str;
            substr = substr.remove(substr.size()-1, 1);
            return substr.size()==0? NATURAL_NUM: substr.toDouble()*NATURAL_NUM;
        }
    }
    return res;
}

bool ExpressionEvaluation::extractInput(const QString &input)
{
    items.clear();
    QString substr;
    bool isMinus = false;
    for (int i = 0; i < input.size(); ++i)
    {
        if(input[i] == '\n')
            break;
        if(isOpeartor(input[i]))
        {
            if(substr.size() != 0)
            {
                items.push_back(new InputItem(string2double(substr)));
                substr.clear();
            }
            if(input[i] == '-' && (i == 0 || input[i-1] == '('))
                items.push_back(new InputItem('m', OPER));  //m means minus
            else if(input[i] == '(' || input[i] == ')')
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
        items.push_back(new InputItem(string2double(substr)));
    }
//    //debug
//    for(auto iter = items.begin(); iter != items.end(); ++iter)
//    {
//        if((*iter)->type == NUMBER)
//            qDebug() << (*iter)->val.number << " ";
//        else
//            qDebug() << (*iter)->val.oper << " ";
//    }
    return true;
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
    for(auto iter = postOrder.begin(); iter != postOrder.end(); ++iter)
    {
        if((*iter)->type == NUMBER)
            qDebug() << (*iter)->val.number << " ";
        else
            qDebug() << (*iter)->val.oper << " ";
    }
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
            double first;
            if(nums.empty() || postOrder[i]->val.oper == 'm' || postOrder[i]->val.oper == '%')
                first = 0;
            else
                first = nums.pop();
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
}

double ExpressionEvaluation::calculate(const QString &expression)
{
    extractInput(expression);
    QVector<InputItem*> postOrder;
    inorder2postorder(postOrder);
    return _calculate(postOrder);
}
