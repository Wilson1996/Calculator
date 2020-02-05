#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , calculator(new ExpressionEvaluation)
{
    ui->setupUi(this);
    connect(ui->B_0,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"0"); });
    connect(ui->B_1,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"1"); });
    connect(ui->B_2,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"2"); });
    connect(ui->B_3,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"3"); });
    connect(ui->B_4,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"4"); });
    connect(ui->B_5,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"5"); });
    connect(ui->B_6,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"6"); });
    connect(ui->B_7,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"7"); });
    connect(ui->B_8,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"8"); });
    connect(ui->B_9,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"9"); });
    connect(ui->B_pi,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"π"); });
    connect(ui->B_naturalNum,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"e"); });
    connect(ui->B_plus,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"+"); });
    connect(ui->B_minus,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"-"); });
    connect(ui->B_multi,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"*"); });
    connect(ui->B_divide,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"/"); });
    connect(ui->B_dot,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"."); });
    connect(ui->B_leftBrackt,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"("); });
    connect(ui->B_rightBrackt,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+")"); });
    connect(ui->B_percent,&QPushButton::clicked,[this]()
            { this->ui->display->setText(this->ui->display->toPlainText()+"%"); });
    connect(ui->B_AC,&QPushButton::clicked,[this]()
            { this->ui->display->clear(); });
    connect(ui->B_del,&QPushButton::clicked,[this]()
            {
                QString _text = ui->display->toPlainText();
                ui->display->setText(_text.remove(_text.size()-1,1));
            });
    connect(ui->B_equal, &QPushButton::clicked, [this]()
            {
                double res = calculator->calculate(ui->display->toPlainText());
//                QString s_res = QString("%1").arg(res);
                QString s_res = QString::number(res, 'g', 15);
                QStringList s_list = ui->display->toPlainText().split('\n');
                ui->display->setText(s_list[0] + "\n\n=" + s_res);
            });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete calculator;
}

