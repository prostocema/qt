#include "authorization.h"
#include "ui_authorization.h"
#include <iostream>
#include <cstring>
#include "string"
#include "fstream"
#include "QMessageBox"
#include <QDebug>
#include <menu.h>

using namespace std;

authorization::authorization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
}

authorization::~authorization()
{
    delete ui;
}

void authorization::on_actionExit_triggered()
{
    close();
}

fstream check()
{
fstream file;
file.open("D:\\Uchiha\\qt\\works\\superrrproga\\bd.json", ios::binary | ios::in);
return file;
}

struct logpass
{
    QString log, pass, whoami;

};

QString Autho(QString logforcheck,QString passforcheck)
{
    fstream file;

    file = check();
        if (!file.is_open())
            return "";

        vector <logpass> kektor;
        string line;
        QString templine;

        logpass tempstr;

                    QString qami = tempstr.whoami;

        while(!file.eof())
        {
        getline(file, line, '}');
        unsigned long long int start, end;
        if(line.size() > 20)
        {

           start = line.find("log") + 7;
           end = line.find("pass") - 4;
           templine = QString::fromStdString(line.substr(start, end - start));
           tempstr.log = templine;

           start = line.find("pass") + 8;
           end = line.find("whoami") - 4;
           templine = QString::fromStdString(line.substr(start, end - start));
           tempstr.pass = templine;

           start = line.find("whoami") + 10;
           end = line.find(";") - 1;
           templine = QString::fromStdString(line.substr(start, end - start));
           tempstr.whoami = templine;
           kektor.push_back(tempstr);
        }
        for(int i = 0; i < kektor.size(); i++)
        {
            QString log1 = kektor[i].log;
            QString pass1 = kektor[i].pass;
            QString whoami1 = kektor[i].whoami;

            if (log1 == logforcheck && pass1 == passforcheck)
                return whoami1;
        }
    }


        }

void authorization::on_wokey_clicked()
{
    QString logforcheck = ui->login->text();
    QString passforcheck = ui->password->text();
    QMessageBox Box;
    if(Autho(logforcheck,passforcheck) == "admin"){
        menu menu;
        menu.setModal(true);
        hide();
        menu.exec();
    }
        else
     {
        Box.setText("user");
        Box.exec();
     }
}
