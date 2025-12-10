#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Usando a versão do Qt:" << QT_VERSION_STR;
    MainWindow w;
    w.setWindowTitle("To-Do List & Pomodoro");
    w.show();
    return a.exec();
}

