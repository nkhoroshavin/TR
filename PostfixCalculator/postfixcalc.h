#ifndef POSTFIXCALC_H
#define POSTFIXCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PostfixCalc; }
QT_END_NAMESPACE

class PostfixCalc : public QMainWindow
{
    Q_OBJECT

public:

    PostfixCalc(QWidget *parent = nullptr);
    ~PostfixCalc();

private slots:

    void digits_numbers();

    void on_dot_clicked();

    void operations();

    void on_equally_clicked();

    void on_c_clicked();

    void math_operations();

    void on_space_clicked();



private:
    Ui::PostfixCalc *ui;

};
#endif // POSTFIXCALC_H
