#ifndef MENU_H
#define MENU_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDialog>


namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();
private slots:
    void slotConnect(int);
    QString slotRead();
    void slotWrite(QString);
    void slotDisconnect();
private slots:
    void on_pushButton_clicked();

    void on_find_clicked();

    void on_delete_2_clicked();

    void on_add_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pokazlp_clicked();

    void on_addus_clicked();

    void on_deletelp_clicked();

    void on_wokey_clicked();

    void hide();

    void antihide();

    void on_changepass_clicked();

    void on_changqau_clicked();

private:
    Ui::menu *ui;
    QString result;
    QTcpSocket *client_socket;
};

#endif // MENU_H
