#include "kommi.h"
#include "ui_kommi.h"
#include <QPixmap>

int k=0;
int mas_result[12];
QString strok="";
int n=0;

Kommi::Kommi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kommi)
{
    ui->setupUi(this);

    QPixmap pix(":/image/image/png-clipart-computer-icons-tool-icon-design-others-building-text.png");
    int w=ui->image->width();
    int h = ui->image->height();

    ui->image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

Kommi::~Kommi()
{
    delete ui;
}

int mas[6][6]{
       {-1,-1,-1,-1,-1,-1},
       {-1,-1,-1,-1,-1,-1},
       {-1,-1,-1,-1,-1,-1},
       {-1,-1,-1,-1,-1,-1},
       {-1,-1,-1,-1,-1,-1},
       {-1,-1,-1,-1,-1,-1}
};


void Kommi::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    int z = 210;
    double th=2*M_PI/6;
    for (int i = 0; i < 6; i++)
    {
            for (int j = 0; j < 6; j++)
            {
                if(i!=j)
                {
                    int x1 = 260 + cos(th * i) * z;
                    int y1 = 270 - sin(th * i) * z;
                    int x2 = 260 + cos(th * j) * z;
                    int y2 = 270 - sin(th * j) * z;

                    painter.setPen(QPen(Qt::darkYellow, 5, Qt::SolidLine));
                    painter.drawLine(x1, y1, x2, y2);
                }
            }
     }
     for (int i = 0; i < 6; i++)
     {
            painter.setPen(QPen(Qt::black, 5, Qt::SolidLine));
            painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            painter.drawEllipse(240 + cos(th * i) * z, 250 - sin(th * i) * z, 50, 50);
            painter.setPen(QPen(Qt::black, 5, Qt::DotLine));
            painter.drawText(260 + cos(th * i) * z, 280 - sin(th * i) * z, QString::number(i+1));
     }

     int x1,x2,y1,y2,i=0;
     while(i<12)
     {
            if (ui->Nomer->text().toInt()!=0)
            {
                    x1 = 260 + cos(th * (mas_result[i]-1)) * z;
                    x2 = 260 + cos(th * (mas_result[i+1]-1)) * z;
                    y1 = 270 - sin(th * (mas_result[i]-1)) * z;
                    y2 = 270 - sin(th * (mas_result[i+1]-1)) * z;
                    painter.setPen(QPen(Qt::black, 5, Qt::DotLine));
                    painter.drawLine(x1, y1, x2, y2);
            }
            i+=2;
     }
     for(int i=0;i<6;i++)
     {
            if(ui->Nomer->text().toInt()==i+1)
            {
                painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
                painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
                painter.drawEllipse(240 + cos(th * i) * z, 250 - sin(th * i) * z, 50, 50);
            }
            painter.setPen(QPen(Qt::black, 5, Qt::SolidLine));
            painter.drawText(260 + cos(th * i) * z, 280 - sin(th * i) * z, QString::number(i+1));
     }
    painter.end();
}
double Rating_zero(int k, int l)
{
    double min = 1000, sum;
    for (int i = 0;i < 6; i++)
    {
        if (l != i && mas[k][i] != -1 && mas[k][i] < min)
            min = mas[k][i];
    }
    sum = min;
    min = 1000;
    for (int i = 0; i < 6; i++)
    {
        if (k != i && mas[i][l] != -1 && mas[i][l] < min)
            min = mas[i][l];
    }
    sum = sum + min;
    return sum;
}
void Reduction(int k, int l)
{
    for (int i = 0; i < 6; i++)
    {
        mas[k][i] = -1;
    }

    for (int i = 0; i < 6; i++)
    {
        mas[i][l] = -1;
    }
}
void Paths()
{
    double mas_di[6];
    double mas_dj[6];
    double min = 10000;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (mas[i][j] < min && mas[i][j] != -1)
                           min = mas[i][j];
        }
        mas_di[i] = min;
        if (min == 10000)
            mas_di[i] = 0;
        min = 10000;
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (mas[i][j] != -1)
                mas[i][j] = mas[i][j] - mas_di[i];
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (mas[j][i] < min && mas[j][i] != -1)
                min = mas[j][i];
        }
        mas_dj[i] = min;
        if (min == 10000)
            mas_dj[i] = 0;
        min = 10000;
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (mas[j][i] != -1)
                mas[j][i] = mas[j][i] - mas_dj[i];
        }
    }

    int str = 0, st = 0;
    double max = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (mas[i][j] == 0)
            {
                if (Rating_zero(i, j) > max)
                {
                    str = i;
                    st = j;
                    max = Rating_zero(i, j);
                }
            }
        }
    }
    if (str == 0 && st == 0)
    {
        n=0;
        return;
    }
    Reduction(str, st);
    str++;
    st++;
    mas_result[k*2]=str;
    mas_result[k*2+1]=st;

    k++;
    if (k != 6)
        Paths();
    k=0;
}

void Answer(int n)
{
    int i=0;
    int current = 0;
    while (i<12)
    {
        if(n==mas_result[i])
        {
            strok=strok+" → "+QString::number(mas_result[i+1]);
            current=i+1;
        }
        i += 2;
    }
    n=mas_result[current];
    k++;
    if (k != 6)
       Answer(n);
}

void Kommi::on_reshit_clicked()
{
    mas[0][1]=ui->i0j1->text().toInt();
    mas[0][2]=ui->i0j2->text().toInt();
    mas[0][3]=ui->i0j3->text().toInt();
    mas[0][4]=ui->i0j4->text().toInt();
    mas[0][5]=ui->i0j5->text().toInt();

    mas[1][0]=ui->i1j0->text().toInt();
    mas[1][2]=ui->i1j2->text().toInt();
    mas[1][3]=ui->i1j3->text().toInt();
    mas[1][4]=ui->i1j4->text().toInt();
    mas[1][5]=ui->i1j5->text().toInt();

    mas[2][0]=ui->i2j0->text().toInt();
    mas[2][1]=ui->i2j1->text().toInt();
    mas[2][3]=ui->i2j3->text().toInt();
    mas[2][4]=ui->i2j4->text().toInt();
    mas[2][5]=ui->i2j5->text().toInt();

    mas[3][0]=ui->i3j0->text().toInt();
    mas[3][1]=ui->i3j1->text().toInt();
    mas[3][2]=ui->i3j2->text().toInt();
    mas[3][4]=ui->i3j4->text().toInt();
    mas[3][5]=ui->i3j5->text().toInt();

    mas[4][0]=ui->i4j0->text().toInt();
    mas[4][1]=ui->i4j1->text().toInt();
    mas[4][2]=ui->i4j2->text().toInt();
    mas[4][3]=ui->i4j3->text().toInt();
    mas[4][5]=ui->i4j5->text().toInt();

    mas[5][0]=ui->i5j0->text().toInt();
    mas[5][1]=ui->i5j1->text().toInt();
    mas[5][2]=ui->i5j2->text().toInt();
    mas[5][3]=ui->i5j3->text().toInt();
    mas[5][4]=ui->i5j4->text().toInt();

    int mas_copy[6][6];
    for(int i=0;i<6;i++)
    {
        for (int j=0;j<6;j++)
        {
        mas_copy[i][j]=mas[i][j];
        }
    }

    n= ui->Nomer->text().toInt();
    Paths();

    if(n>0 && n<=6)
    {
        repaint();
        strok = QString::number(n);
        Answer(n);

        int sum=0;
        int i=0;
        while(i<12)
          {
             sum = sum + mas_copy[mas_result[i]-1][mas_result[i+1]-1];
             i+=2;
          }

        ui->Way->setText(strok);
        ui->Sum->setText(QString::number(sum));
    }
    else
    {
        ui->Way->setText("Error!!!");
        ui->Sum->setText("0");
    }
}
