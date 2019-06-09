#include "menu.h"
#include "ui_menu.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include <fstream>
#include <vector>
#include <QtDebug>
#include "authorization.h"
#include <QDatetime>
#include <QTime>



using namespace std;

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    client_socket = new QTcpSocket(this);
    client_socket->connectToHost("127.0.0.1",33333);
    connect(client_socket,SIGNAL(connected()),SLOT(slotConnect));
    connect(client_socket,SIGNAL(readyRead()),SLOT(slotRead));
    connect(client_socket,SIGNAL(disconnected()),SLOT(slotDisconnect()));
    hide();
}
void menu::slotConnect(int socketDescriptor)
{
    client_socket = new QTcpSocket(this);
    client_socket->setSocketDescriptor(socketDescriptor);

    connect(client_socket,SIGNAL(readyRead()),SLOT(slot_readyRead));
    connect(client_socket,SIGNAL(disconnected()),SLOT(slot_disconnect()));
}

QString menu::slotRead()
{
//        QByteArray array;
//        QString temp;
        result.clear();
        client_socket->waitForReadyRead(2000);
        while(client_socket->bytesAvailable() > 0)
        {
            result = client_socket->readAll();
        }

    return result;
}

void menu::slotWrite(QString request)
{
        QByteArray array;
        QString temp;
        client_socket->waitForBytesWritten(200);
        SendCrypt(request);
}

void::menu::slotDisconnect()
{

}

void menu::hide()
{
    ui->frame->setVisible(false);
    ui->frame_3->setVisible(false);
    ui->frame_4->setVisible(false);
    ui->tableView->setVisible(false);

}

void menu::antihide()
{
    ui->frame->setVisible(true);
    ui->frame_3->setVisible(true);
    ui->frame_4->setVisible(true);
    ui->tableView->setVisible(true);
}

void menu::on_wokey_clicked()
{
    QString logforcheck = ui->login->text();
    QString passforcheck = ui->password->text();
    QMessageBox Box;

    QString str4serv = "authoriz&" + logforcheck + "&" + passforcheck;
    slotWrite(str4serv);


    result=slotRead();
    qDebug()<<result;

    if(result == "admin"){
        this->setWindowTitle("Админ");
        ui->frame_5->hide();
        antihide();

    }
    else if (result == "user")
     {
        this->setWindowTitle("Юзер");
        ui->frame_5->hide();
        ui->frame_4->setVisible(true);
     }
    else if (result == "manag"){
        this->setWindowTitle("мэнэджэр");
        ui->frame_5->hide();
        //ui->frame_2->setVisible(true);
        //ui->delete_2->hide();
        ui->tableView->setVisible(true);
    }
    else {
        QMessageBox::warning(this, "error..", "Что-то пошло не так...");
    }

}

void menu::on_pokazlp_clicked()
{
    QString str4serv = "showlp&";
    slotWrite(str4serv);
    client_socket->waitForBytesWritten(200);


    result=slotRead();

    string str = result.toStdString();
    unsigned long long q, i;
    string temp;

    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
        horizontalHeader.append("log");
        horizontalHeader.append("pass");
        horizontalHeader.append("whoami");

        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableView->verticalHeader()->setVisible(false);

        for ( i = 0; i < str.size(); i++) {

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString::fromStdString(temp));
            model->setItem(i, 0, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 1, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 2, item);
        }
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
}

void menu::on_addus_clicked()
{
    QString logs, passs, whoamis;
    logs = ui->logEdit->text();
    passs = ui->passEdit->text();
    whoamis = ui->list->currentText();

    if (logs == ""){
        box.setText("Вы забыли ввести логин");
        box.exec();
     }
    else if (passs == ""){
        box.setText("Вы забыли ввести пароль");
        box.exec();
    }
    else {
        box.setText("Вы точно уверенны, что хотите добавить пользователя под ТАКИМ никнеймом?");
        box.exec();
        QString str4serv = "addlp&" + logs + "&" + passs + "&" + whoamis + "&";
        slotWrite(str4serv);
        qDebug()<<str4serv;
        client_socket->waitForBytesWritten(200);

        client_socket->waitForReadyRead(1000);
        result = slotRead();

        ui->logEdit->clear();
        ui->passEdit->clear();
        ui->list->currentText();

        box.setText("Пользователь добавлен");
        if(result == "succsesfull")
            box.exec();

        menu::on_pokazlp_clicked();
    }

}

void menu::on_findlp_clicked()
{
    QString logs;
    logs = ui->logEdit->text();
    QString str4serv = "findlp&" + logs + "&";
    slotWrite(str4serv);
    qDebug()<<str4serv;
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(1000);
    result = slotRead();


    string str = result.toStdString();
    unsigned long long q, i;
    string temp;

    q = str.find("&");
    temp = str.substr(0, q);
    if (QString::fromStdString(temp) == logs)
    {
    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
        horizontalHeader.append("log");
        horizontalHeader.append("pass");
        horizontalHeader.append("whoami");

        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableView->verticalHeader()->setVisible(false);

        for ( i = 0; i < str.size(); i++) {

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString::fromStdString(temp));
            model->setItem(i, 0, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 1, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 2, item);
        }
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();

    box.setText("Пользователь найден");
        box.exec();
    }
    else {
        box.setText("Я не нашёл такого пользователя :c");
        box.exec();
    }

}

void menu::on_deletelp_clicked()
{
    QString logs;
    logs = ui->logEdit->text();
    QString str4serv = "deletelp&" + logs + "&";
    slotWrite(str4serv);
    qDebug()<<str4serv;
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(1000);
    result = slotRead();

    box.setText("Пользователь удалён");
    if(result == "succsesfull")
        box.exec();
    ui->logEdit->clear();

    menu::on_pokazlp_clicked();
}

void menu::on_changqau_clicked()
{
    QString logs, status;
    logs = ui->logEdit->text();
    status = ui->list->currentText();
    QString str4serv = "changelp&" + logs + "&" + status + "&";
    slotWrite(str4serv);
    qDebug()<<str4serv;
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(1000);
    result = slotRead();

    box.setText("Статус изменен");
    if(result == "succsesfull")
        box.exec();

    menu::on_pokazlp_clicked();
}

void menu::on_changepass_clicked()
{
    QString log, pass, rpass;
    log = ui->login->text();
    pass = ui->passforchan->text();
    rpass = ui->repeatpass->text();
    QString str4serv = "changepass&" + log + "&" + pass + "&" + rpass + "&";
    slotWrite(str4serv);
    qDebug()<<str4serv;
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(1000);
    result = slotRead();

    box.setText("Пароль изменен");
    if(result == "succsesfull")
        box.exec();
    else {
        box.setText("Чего то не хватает");
        box.exec();
    }
}
////////// ↑↑↑login
void menu::on_showbb_clicked()
{
    QString str4serv = "showbb&";
    slotWrite(str4serv);
    client_socket->waitForBytesWritten(200);

    result=slotRead();

    string str = result.toStdString();
    unsigned long long q, i;
    string temp;

    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
        horizontalHeader.append("ID");
        horizontalHeader.append("Цена");
        horizontalHeader.append("Конструкция");
        horizontalHeader.append("Металл");
        horizontalHeader.append("Поставщик");
        horizontalHeader.append("Телефон пост.");
        horizontalHeader.append("Работник");
        horizontalHeader.append("Дата");
        horizontalHeader.append("Индекс");

        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableView->verticalHeader()->setVisible(false);

        for ( i = 0; i < str.size(); i++) {

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString::fromStdString(temp));
            model->setItem(i, 0, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 1, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 2, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 3, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 4, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 5, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 6, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 7, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 8, item);

        }
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
}

void menu::on_addbb_clicked()
{
    QString price, construction, metal, provider, phone, worker, index;
    price = ui->price->text();
    construction = ui->name->text();
    metal = ui->metal->text();
    provider = ui->provider->text();
    phone = ui->phprovider->text();
    phone = checktel(phone);
    worker = ui->worker->text();
    QDateTime date = QDateTime::currentDateTime();
    QString dates = date.toString("dd/MM/yyyy");
    index = ui->index->text();

    if ((price == "")||(construction == "")||(metal == "")||(provider == "")||(phone == "")||(worker == "")||(index == ""))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Неувязочка", "Вы что то забыли ввести, продолжить?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (index == ""){
                box.setText("Индекс нужно ввести.");
                box.exec();
        }
            else
            {
                QString str4serv = "addbb&" +price+ "&" +construction+ "&" +metal+ "&" +provider+ "&" + checktel(phone)+ "&" +worker+ "&" +dates+ "&" +checkindex(index)+ +"&";
                slotWrite(str4serv);
                qDebug()<<str4serv;
                client_socket->waitForBytesWritten(200);

                client_socket->waitForReadyRead(1000);
                result = slotRead();

                ui->price->clear();
                ui->name->clear();
                ui->metal->clear();
                ui->provider->clear();
                ui->phprovider->clear();
                ui->worker->clear();
                ui->index->clear();

                box.setText("Запись добавлена");
                if(result == "succsesfull")
                    box.exec();

                menu::on_showbb_clicked();
            }
        }
    }
    else
    {
        QString str4serv = "addbb&" +price+ "&" +construction+ "&" +metal+ "&" +provider+ "&" +phone+ "&" +worker+ "&" +dates+ "&" +index+ +"&";
        slotWrite(str4serv);
        qDebug()<<str4serv;
        client_socket->waitForBytesWritten(200);

        client_socket->waitForReadyRead(1000);
        result = slotRead();

        ui->price->clear();
        ui->name->clear();
        ui->metal->clear();
        ui->provider->clear();
        ui->phprovider->clear();
        ui->worker->clear();
        ui->index->clear();

        box.setText("Запись добавлена");
        if(result == "succsesfull")
            box.exec();

        menu::on_showbb_clicked();
    }

}

void menu::on_findbb_clicked()
{
    QString index;
    index = ui->index->text();
    QString str4serv = "findbb&" + index + "&";
    slotWrite(str4serv);
    qDebug()<<str4serv;
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(1000);
    result = slotRead();

    string str = result.toStdString();
    unsigned long long q, i;
    string temp;

    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
        horizontalHeader.append("ID");
        horizontalHeader.append("Цена");
        horizontalHeader.append("Конструкция");
        horizontalHeader.append("Металл");
        horizontalHeader.append("Поставщик");
        horizontalHeader.append("Телефон пост.");
        horizontalHeader.append("Работник");
        horizontalHeader.append("Дата");
        horizontalHeader.append("Индекс");

        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableView->verticalHeader()->setVisible(false);

        for ( i = 0; i < str.size(); i++) {

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString::fromStdString(temp));
            model->setItem(i, 0, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 1, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 2, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 3, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 4, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 5, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 6, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 7, item);

            q = str.find("&");
            temp = str.substr(0, q);
            str.erase(0, q+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(i, 8, item);

        }
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
}

void menu::on_deletebb_clicked()
{
    QString index;
    index = ui->index->text();
    QString str4serv = "deletebb&" + index + "&";
    slotWrite(str4serv);
    qDebug()<<str4serv;
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(1000);
    result = slotRead();

    box.setText("Запись удалена");
    if(result == "succsesfull")
        box.exec();
    ui->index->clear();

    menu::on_showbb_clicked();
}

void menu::on_change_clicked()
{
    QString price, construction, metal, provider, phone, worker, date, index;
    price = ui->price->text();
    construction = ui->name->text();
    metal = ui->metal->text();
    provider = ui->provider->text();
    phone = ui->phprovider->text();
    worker = ui->worker->text();
    index = ui->index->text();
    QString str4serv = "change&" +price+ "&" +construction+ "&" +metal+ "&" +provider+ "&" +phone+ "&" +worker+ "&" +date+ "&" +index+ +"&";
    slotWrite(str4serv);
    qDebug()<<str4serv;
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(1000);
    result = slotRead();

    box.setText("Запись изменена");
    if(result == "succsesfull")
        box.exec();

    menu::on_showbb_clicked();
}

menu::~menu()
{
    delete ui;
}

