#ifndef MENU_H
#define MENU_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <openssl/evp.h>
#include <openssl/aes.h>


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
    QString checktel(QString tel)
    {
        for (int i = 0; i < 10; i++) {
            if(tel[i] > 47 and tel[i] < 58){
                if (tel[0] != '7'){
                    tel[0] = '7';
                continue;
                }
            }
            else {
                QMessageBox box;
                box.setText("Используйте цифры");
                box.exec();
                break;
            }
            return tel;
        }
    }
    int checkindex(QString index)
    {
        for (int i = 0; i < 6; ++i) {
            if (index[i]>47 and index[i]<58){
                continue;
            }
            else {
                QMessageBox box;
                box.setText("Используйте цифры");
                box.exec();
                break;
            }
        }
    }
    QString checkfio(QString fio)
    {
        for(int i = 0; i < fio.size(); i++){
            if(fio[i] < 97 or fio[i] > 122){
                QMessageBox box;
                box.setText("Используйте буквы");
                box.exec();
                break;
            }
            else {
                continue;
            }
        }
            return fio;
    }
    void slotWrite(QString);
    void slotDisconnect();
    void SendCrypt(QString mes)
    {

    unsigned char *key = (unsigned char *) "0123456789abcdeF0123456789abcdeF";
    unsigned char *iv = (unsigned char *) "1234567887654321";

    unsigned char out_buf[256];
    QByteArray text = mes.toLocal8Bit();
    text.append("#");
    EVP_CIPHER_CTX *ctx;
    unsigned char *ert = reinterpret_cast<unsigned char *>(text.data());
    int t = text.size();
    int k = strlen((char*)ert);

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    int crypLen;
    int len;
    EVP_EncryptUpdate(ctx, out_buf,&len, ert, t);
    crypLen = len;
    EVP_EncryptFinal_ex(ctx, out_buf + len, &len);
    crypLen += len;

    text = QByteArray((char*)out_buf, crypLen);

    qDebug() << "decrypted text:"<< text << endl;
    client_socket->write(text);

    }
private slots:
    void on_pokazlp_clicked();

    void on_addus_clicked();

    void on_deletelp_clicked();

    void on_wokey_clicked();

    void hide();

    void antihide();

    void on_changepass_clicked();

    void on_changqau_clicked();

    void on_findlp_clicked();

    void on_showbb_clicked();

    void on_addbb_clicked();

    void on_findbb_clicked();

    void on_deletebb_clicked();

    void on_change_clicked();

private:
    Ui::menu *ui;
    QString result;
    QTcpSocket *client_socket;
    QMessageBox box;
};

#endif // MENU_H
