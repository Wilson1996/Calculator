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
            items.push_back(new InputItem(input[i]));
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
    return 0;
}
