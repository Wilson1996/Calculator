/*
 * @Descripttion: 
 * @version: 
 * @Author: WillissTaan(Wilson.T@sjtu.edu.cn)
 * @Date: 2020-02-03 16:03:33
 * @Last Modified by: WillissTaan
 * @Last Modified Time: Do not edit
 */
#ifndef EXPRESSION_EVALUATION_H
#define EXPRESSION_EVALUATION_H

#include <QStack>
#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>

enum TYPE{NUMBER, OPER};

struct InputItem
{
    union
    {
        double number;
        char oper;
    }val;
    TYPE type;
    InputItem(double v){val.number = v; type = NUMBER;}
    InputItem(QChar v){val.oper = v.toLatin1(); type = OPER;}
};

class ExpressionEvaluation
{
private:
    // std::stack<double> nums;
    // std::stack<char> ops;
    QVector<InputItem*> items;

    bool extractInput(const QString& input);
    // void inorder2preorder(const std::)
    // void inorder2postorder(const std::)
public:
    ExpressionEvaluation();
    ~ExpressionEvaluation();
    double calculate(const QString& expression);
};


#endif // !__EXPRESSION_EVALUATION_H
