#include "menu.h"
#include "ui_menu.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include <fstream>
#include <vector>
#include <QMessageBox>
#include <QtDebug>
#include "authorization.h"
#include <QtSql/QSqlDatabase>


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
        QByteArray array;
        QString temp;

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

        array=QByteArray::fromStdString(request.toStdString());

        client_socket->write(array);
}

void::menu::slotDisconnect()
{

}

void menu::hide()
{
    ui->frame->setVisible(false);
    ui->frame_2->setVisible(false);
    ui->frame_3->setVisible(false);
    ui->frame_4->setVisible(false);
    ui->tableView->setVisible(false);

}

void menu::antihide()
{
    ui->frame->setVisible(true);
    ui->frame_2->setVisible(true);
    ui->frame_3->setVisible(true);
    ui->frame_4->setVisible(true);
    ui->tableView->setVisible(true);
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

//QString Autho(QString logforcheck,QString passforcheck)
//{
//    fstream file;

//    file = check();
//        if (!file.is_open())
//            return "";

//        vector <logpass> kektor;
//        string line;
//        QString templine;

//        logpass tempstr;

//                    QString qami = tempstr.whoami;

//        while(!file.eof())
//        {
//        getline(file, line, '}');
//        unsigned long long int start, end;
//        if(line.size() > 20)
//        {

//           start = line.find("log") + 7;
//           end = line.find("pass") - 4;
//           templine = QString::fromStdString(line.substr(start, end - start));
//           tempstr.log = templine;

//           start = line.find("pass") + 8;
//           end = line.find("whoami") - 4;
//           templine = QString::fromStdString(line.substr(start, end - start));
//           tempstr.pass = templine;

//           start = line.find("whoami") + 10;
//           end = line.find(";") - 1;
//           templine = QString::fromStdString(line.substr(start, end - start));
//           tempstr.whoami = templine;
//           kektor.push_back(tempstr);
//        }
//        for(int i = 0; i < kektor.size(); i++)
//        {
//            QString log1 = kektor[i].log;
//            QString pass1 = kektor[i].pass;
//            QString whoami1 = kektor[i].whoami;

//            if (log1 == logforcheck && pass1 == passforcheck)
//                return whoami1;
//        }
//    }


//        }

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
        ui->frame_2->setVisible(true);
        ui->delete_2->hide();
        ui->tableView->setVisible(true);
    }
}

fstream opendb(){
    fstream opendb;
    opendb.open("D:\\Uchiha\\qt\\works\\superrrproga\\db.json", ios::binary | ios::in);
    return opendb;
}

fstream openbd()
{
fstream openbd;
openbd.open("D:\\Uchiha\\qt\\works\\superrrproga\\bd.json", ios::binary | ios::in);
return openbd;
}

struct structdb
{
    QString id, fio, tel, data;
};

struct structlp
{
    QString log, pass, whoami;
};

vector<structdb> parcing()
{

    fstream filedb;

    vector<structdb> kektor;
    structdb tempstr;

    string line;
    QString templine;

    filedb = opendb();
    if (filedb.is_open())
    {

    while(!filedb.eof())
    {
    getline(filedb, line, '}');
    unsigned long long int start, end;
    if(line.size() > 20)
    {
    start = line.find("id") + 6;
    end = line.find("fio") - 4;
    templine = QString::fromStdString(line.substr(start, end - start));
    tempstr.id = templine;

    start = line.find("fio") + 7;
    end = line.find("tel") - 4;
    templine = QString::fromStdString(line.substr(start, end - start));
    tempstr.fio = templine;

    start = line.find("tel") + 7;
    end = line.find("data") - 4;
    templine = QString::fromStdString(line.substr(start, end - start));
    tempstr.tel = templine;

    start = line.find("data") + 8;
    end = line.find(";") - 1;
    templine = QString::fromStdString(line.substr(start, end - start));
    tempstr.data = templine;
    kektor.push_back(tempstr);
    }

}
    }
    return kektor;
}

vector<structlp> parcinglp()
{

    fstream filebd;

    vector<structlp> kektor;
    structlp tempstr;

    string line;
    QString templine;

    filebd = openbd();
    if (filebd.is_open())
    {

    while(!filebd.eof())
    {
    getline(filebd, line, '}');
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
 //   qDebug()<<templine;
    kektor.push_back(tempstr);
    }

}
    }
    return kektor;
}

QString checkfio(QString fio)
{
    for(int i = 0; i < fio.size(); i++){
        if(fio[i] < 97 or fio[i] > 122){
            QMessageBox box;
            box.setText("Use please normalnie bukvi");
            box.exec();
            break;
        }
        else {
            continue;
        }
    }
        return fio;


}

QString checktel(QString tel)
{
    for (int i = 0; i < 10; i++) {
        if(tel[i] > 47 or tel[i] < 58){
            if (tel[0] != '8'){
                tel[0] = '8';
            continue;
            }
        }
        else {
            QMessageBox box;
            box.setText("Use please normalnie cifri");
            box.exec();
            break;

        }
        return tel;
    }
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    vector<structdb> kektor = parcing();
    vector<structdb>::iterator it;

    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
            horizontalHeader.append("id");
            horizontalHeader.append("fio");
            horizontalHeader.append("tel");
            horizontalHeader.append("data");

            model->setHorizontalHeaderLabels(horizontalHeader);

            QString str4serv = "show&";
            slotWrite(str4serv);

            result = slotRead();

            fstream filedb;
            filedb = opendb();
            if (!filedb.is_open())
            QMessageBox::warning(this,"error","file is not open");

            //Вывод в таблицу
            int i = 0;
            for (it = kektor.begin(); it < kektor.end(); it++) {

            item = new QStandardItem(it->id);
            model->setItem( i, 0,item);
            item = new QStandardItem(it->fio);
            model->setItem( i, 1,item);
            item = new QStandardItem(it->tel);
            model->setItem( i, 2,item);
            item = new QStandardItem(it->data);
            model->setItem( i, 3,item);
            i++;
            }


            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
}

void menu::on_find_clicked()
{
    fstream opendb;

    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
            horizontalHeader.append("id");
            horizontalHeader.append("fio");
            horizontalHeader.append("tel");
            horizontalHeader.append("data");

            model->setHorizontalHeaderLabels(horizontalHeader);


    vector<structdb> kektor = parcing();
    structdb tempstr;
    vector<structdb>::iterator it;

    QString find = ui->line_find->text();

    for (it = kektor.begin(); it < kektor.end(); it++) {
        if(it->id == find){
            item = new QStandardItem(it->id);
            model->setItem( 0, 0,item);
            item = new QStandardItem(it->fio);
            model->setItem( 0, 1,item);
            item = new QStandardItem(it->tel);
            model->setItem( 0, 2,item);
            item = new QStandardItem(it->data);
            model->setItem( 0, 3,item);
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}


void upload(vector<structdb> kektor)
{

    vector<structdb>::iterator it;

    fstream openfile;
    openfile.open("D:\\Uchiha\\qt\\works\\superrrproga\\db.json", ios::binary | ios::out | ios::trunc);
    for (it = kektor.begin();it < kektor.end(); it++) {
        QString shablon0 = "{\n\r\t\"id\": \"";
        QString shablon = "\", \"fio\": \"";
        QString shablon1 = "\", \"tel\": \"";
        QString shablon2 = "\", \"data\": \"";
        QString shablon3 = "\";\r\n}\r\n";
       // tempstr = kektor.;
        QString itog = shablon0 + it->id + shablon + it->fio + shablon1 + it->tel + shablon2 + it->data + shablon3;
        string itog2 = itog.toStdString();
        //loltor.push_back(itog2);
            openfile<<itog2;
     }

}

void uploadlp(vector<structlp> kektor)
{

    vector<structlp>::iterator it;

    fstream openbd;
    openbd.open("D:\\Uchiha\\qt\\works\\superrrproga\\bd.json", ios::binary | ios::out | ios::trunc);
    for (it = kektor.begin();it < kektor.end(); it++) {
        QString shablon0 = "{\n\r\t\"log\": \"";
        QString shablon = "\", \"pass\": \"";
        QString shablon1 = "\", \"whoami\": \"";
        QString shablon2 = "\";\r\n}\r\n";

        QString itog = shablon0 + it->log + shablon + it->pass + shablon1 + it->whoami + shablon2;
        string itog2 = itog.toStdString();
            openbd<<itog2;
    }
}


void menu::on_delete_2_clicked()
{
    vector<structdb> kektor = parcing();
    structdb tempstr;
    vector<structdb>::iterator it;
    QString find = ui->line_find->text();

    for (it = kektor.begin(); it < kektor.end(); it++) {
        if(it->id == find){
            kektor.erase(it);

        }
    }
    upload(kektor);
    menu::on_pushButton_clicked();

}

void menu::on_add_clicked()
{
    vector<structdb> kektor;
    vector<structdb>::iterator it;
    fstream openfile;
    openfile.open("D:\\Uchiha\\qt\\works\\superrrproga\\db.json", ios::binary | ios::app);

    QString ids = ui->line_id->text();
    QString fios = ui->line_fio->text();
    QString tels = ui->line_tel->text();
    QString datas = ui->dateEdit->text();

    fios = checkfio(fios);
    tels = checktel(tels);

        QString shablon0 = "{\n\r\t\"id\": \"";
        QString shablon = "\", \"fio\": \"";
        QString shablon1 = "\", \"tel\": \"";
        QString shablon2 = "\", \"data\": \"";
        QString shablon3 = "\";\r\n}\r\n";

        QString itog = shablon0 + ids + shablon + fios + shablon1 + tels + shablon2 + datas + shablon3;

        openfile<<itog.toStdString();
        menu::on_pushButton_clicked();

}

void menu::on_pushButton_3_clicked()
{
    vector<structdb> kektor = parcing();
    vector<structdb>::iterator it;
    QString find = ui->line_find->text();
    QString ids = ui->line_id->text();
    QString fios = ui->line_fio->text();
    QString tels = ui->line_tel->text();
    QString datas = ui->dateEdit->text();
    fstream openfile;
    openfile.open("D:\\Uchiha\\qt\\works\\superrrproga\\db.json", ios::binary | ios::out);
    for (it = kektor.begin(); it < kektor.end(); it++) {
        if(it->id == find)
        {
            if (fios != "")
            {
               it->fio = fios;
            }
            if (tels != "")
            {
               it->tel = tels;
            }
            if (datas != "")
            {
               it->data = datas;
            }
        }

    }
    upload(kektor);
    openfile.close();
    menu::on_pushButton_clicked();
}


void menu::on_pokazlp_clicked()
{
    vector<structlp> kektor = parcinglp();
    vector<structlp>::iterator it;

    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
            horizontalHeader.append("log");
            horizontalHeader.append("pass");
            horizontalHeader.append("whoami");

            model->setHorizontalHeaderLabels(horizontalHeader);

            fstream filebd;
            filebd = openbd();
            if (!filebd.is_open())
            QMessageBox::warning(this,"error","file is not open");

            //Вывод в таблицу
            int i = 0;
            for (it = kektor.begin(); it < kektor.end(); it++) {

            item = new QStandardItem(it->log);
            model->setItem( i, 0,item);
            item = new QStandardItem(it->pass);
            model->setItem( i, 1,item);
            item = new QStandardItem(it->whoami);
            model->setItem( i, 2,item);
            i++;
            }


                    ui->tableView->setModel(model);
                    ui->tableView->resizeColumnsToContents();
}

void menu::on_addus_clicked()
{
    vector<structlp> kektor;
    vector<structlp>::iterator it;
    fstream openfile;
    openfile.open("D:\\Uchiha\\qt\\works\\superrrproga\\bd.json", ios::binary | ios::app);

    QString logs = ui->logEdit->text();
    QString passs = ui->passEdit->text();
    QString whoamis = ui->list->currentText();

        QString shablon0 = "{\n\r\t\"log\": \"";
        QString shablon = "\", \"pass\": \"";
        QString shablon1 = "\", \"whoami\": \"";
        QString shablon2 = "\";\r\n}\r\n";

        QString itog = shablon0 + logs + shablon + passs + shablon1 + whoamis + shablon2;

        openfile<<itog.toStdString();
        menu::on_pokazlp_clicked();

}

void menu::on_deletelp_clicked()
{
    vector<structlp> kektor = parcinglp();
    structdb tempstr;
    vector<structlp>::iterator it;
    QString logfind = ui->logEdit->text();

    for (it = kektor.begin(); it < kektor.end(); it++) {
        if(it->log == logfind){
            kektor.erase(it);
            }
    }
    uploadlp(kektor);
    menu::on_pokazlp_clicked();
}


void menu::on_changepass_clicked()
{
    fstream openbd;
    vector<structlp> kektor = parcinglp();
    structlp tempstr;
    vector<structlp>::iterator it;

    QString logforcheck = ui->login->text();
    QString passforchg = ui->passforchan->text();
    QString repeat = ui->repeatpass->text();

    openbd.open("D:\\Uchiha\\qt\\works\\superrrproga\\db.json", ios::binary | ios::out);

    for (it = kektor.begin(); it < kektor.end(); it++) {
        if(it->log == logforcheck){
            if(passforchg == repeat){
                it->pass = passforchg;
            }
            else {
                QMessageBox box;
                box.setText("Необходимо ввести пароль повторно");
            }
        }
    }
    uploadlp(kektor);
    openbd.close();
    menu::on_pokazlp_clicked();

}

void menu::on_changqau_clicked()
{
    vector<structlp> kektor = parcinglp();
    //structdb tempstr;
    vector<structlp>::iterator it;
    QString logfind = ui->logEdit->text();
    QString whoau = ui->list->currentText();
    for (it = kektor.begin(); it < kektor.end(); it++) {
        if(it->log == logfind){
            it->whoami = whoau;
        }
    }
    uploadlp(kektor);
    menu::on_pokazlp_clicked();
}
