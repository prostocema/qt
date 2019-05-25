#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QMainWindow>

namespace Ui {
class authorization;
}

class authorization : public QMainWindow
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = nullptr);
    ~authorization();

private slots:
    void on_actionExit_triggered();

    void on_wokey_clicked();

private:
    Ui::authorization *ui;
};

#endif // AUTHORIZATION_H
