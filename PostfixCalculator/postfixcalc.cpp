#include "postfixcalc.h"
#include "ui_postfixcalc.h"
#include <QPixmap>
#include <math.h>


using namespace std;

double num1, num2;

PostfixCalc::PostfixCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PostfixCalc)
{


    ui->setupUi(this);
    QPixmap pix(":/images/img/Postfix-dia.svg");
    int w=ui->image2->width();
    int h = ui->image2->height();

    ui->image2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


    connect(ui->btn0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->stepen,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->plus,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->minus,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->mult,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->divide,SIGNAL(clicked()),this,SLOT(digits_numbers()));


    connect(ui->plus_minus,SIGNAL(clicked()),this,SLOT(operations()));

    connect(ui->stepen,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->plus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->minus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->mult,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->divide,SIGNAL(clicked()),this,SLOT(math_operations()));

    connect(ui->c,SIGNAL(clicked()),this,SLOT(on_c_clicked()));

     connect(ui->btnspace,SIGNAL(clicked()),this,SLOT(on_space_clicked()));

     ui->divide->setCheckable(true);
     ui->plus->setCheckable(true);
     ui->minus->setCheckable(true);
     ui->mult->setCheckable(true);
     ui->stepen->setCheckable(true);
}

PostfixCalc::~PostfixCalc()
{
    delete ui;
}


void PostfixCalc::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();

     double all_numbers;
     QString new_label;

     if (ui->result->text().contains(".") && button->text() == "0")
         {
             new_label = ui->result->text() + button->text();
         } else if (ui->result->text().contains(' '))
         {
             new_label = ui->result->text() + button->text();
         } else
         if ((ui->result->text().contains("1") or ui->result->text().contains("2")

              or ui->result->text().contains("3") or ui->result->text().contains("4")

               or ui->result->text().contains("5") or ui->result->text().contains("6")

                or ui->result->text().contains("7") or ui->result->text().contains("8")

                 or ui->result->text().contains("9") or ui->result->text().contains("0")) &&
                  (button->text()=="+" or button->text()=="-" or button->text()=="^" or button->text()=="*" or button->text()=="/"))
         {
             new_label = ui->result->text()+ button->text();
         }
         else{

     all_numbers = (ui->result->text() + button->text()).toDouble();
     new_label = QString::number(all_numbers,'g', 15);
}
     ui->result->setText(new_label);
}


void PostfixCalc::on_space_clicked()
{
    if (!(ui->result->text().contains(' ')))
            ui->result->setText(ui->result->text() + " ");
}


void PostfixCalc::on_dot_clicked()
{
    if (!(ui->result->text().contains('.')))
   ui->result->setText(ui->result->text() + ".");
}

void PostfixCalc::operations()
{
 QPushButton *button = (QPushButton *)sender();
 double all_numbers;
 QString new_label;
 if (button->text() == "+/-")
 {
 all_numbers = (ui->result->text()).toDouble();
 all_numbers = all_numbers * -1;
 new_label = QString::number(all_numbers,'g', 15);
 ui->result->setText(new_label);
}
 else if (button->text() == "space")
 {
 all_numbers = (ui->result->text()).toDouble();
 ui->result->setText(ui->result->text() + " ");
 new_label = QString::number(all_numbers, 'g', 15);
 ui->result->setText(new_label);
 }
}


void PostfixCalc::on_c_clicked()
{
    ui->plus->setChecked(false);
    ui->minus->setChecked(false);
    ui->mult->setChecked(false);
    ui->divide->setChecked(false);

    ui->result->setText("0");
}


void PostfixCalc::math_operations()
{
    QPushButton* button = (QPushButton*)sender();
        string str = ui->result->text().toStdString();
        string t = str;
        num1 = stod(str.erase(str.find(' ')));
        num2 = stod(t.erase(0, t.find(' ')).erase(t.length()-1));
        button->setChecked(true);
}


void PostfixCalc::on_equally_clicked()
{
    double label_number, eql = num2;
       QString new_label;
       int a = eql;

       if (ui->plus->isChecked()){
           label_number = num1 + eql;
           new_label = QString::number(label_number, 'g', 15);
           ui->result->setText(new_label);
           ui->plus->setChecked(false);

       } else if (ui->minus->isChecked()){
           label_number = num1 - eql;
           new_label = QString::number(label_number, 'g', 15);
           ui->result->setText(new_label);
           ui->minus->setChecked(false);

       }else if (ui->divide->isChecked()){
           if(eql==0)
           {
               ui->result->setText("На 0 делить нельзя!");
           } else {
           label_number = num1 / eql;
           new_label = QString::number(label_number, 'g', 15);
           ui->result->setText(new_label);
           }
           ui->divide->setChecked(false);
       }else if (ui->mult->isChecked()){
           label_number = num1 * eql;
           new_label = QString::number(label_number, 'g', 15);
           ui->result->setText(new_label);
           ui->mult->setChecked(false);

       }else if (ui->stepen->isChecked()){
           if(a == eql)
           {
           label_number = pow(num1, eql);
           new_label = QString::number(label_number, 'g', 15);
           ui->result->setText(new_label);
           ui->mult->setChecked(false);
           }
           else
           {
               ui->result->setText("Error!!!");
           }
       }
}



