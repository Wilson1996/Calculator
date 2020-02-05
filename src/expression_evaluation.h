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

enum TYPE{NUMBER, OPER, BRACKT};
enum ERROR{NONE, INVALID_OPER, INVALID_BRACKT, INVALID_EXPRESSION};

struct InputItem
{
    union
    {
        double number;
        char oper;
    }val;
    TYPE type;
    InputItem(double v){val.number = v; type = NUMBER;}
    InputItem(QChar v, TYPE t = OPER){val.oper = v.toLatin1(); type = t;}
};

class ExpressionEvaluation
{
private:
    QVector<InputItem*> items;
    ERROR err;

    constexpr static const double PI = 3.14159265358979323846;
    constexpr static const double NATURAL_NUM = 2.71828182845904523536;

    bool isOpeartor(const QChar& ch)const;
    int getPriority(const QChar& op)const;
    double _calculateTwoNums(double first, double second, QChar oper)const;
    double string2double(const QString& str)const;
    bool extractInput(const QString& input);
    void inorder2postorder(QVector<InputItem*>& postOrder)const;
    double _calculate(const QVector<InputItem*>& postOrder)const;
public:
    ExpressionEvaluation();
    ~ExpressionEvaluation();
    double calculate(const QString& expression);
};


#endif // !__EXPRESSION_EVALUATION_H
