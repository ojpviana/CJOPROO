#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Esta linha irá imprimir a versão do Qt no painel "Saída do Aplicativo"
    qDebug() << "Usando a versão do Qt:" << QT_VERSION_STR;
    MainWindow w;
    w.setWindowTitle("To-Do List & Pomodoro");
    w.show();
    return a.exec();
}
