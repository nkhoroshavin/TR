#ifndef KOMMI_H
#define KOMMI_H

#include <QMainWindow>
#include <QPainter>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class Kommi; }
QT_END_NAMESPACE

class Kommi : public QMainWindow
{
    Q_OBJECT

public:
    Kommi(QWidget *parent = nullptr);
    ~Kommi();

private slots:
    void on_reshit_clicked();

private:
    Ui::Kommi *ui;

protected:
    void paintEvent(QPaintEvent*) override;

};
#endif // KOMMI_H
