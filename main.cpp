#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    srand(time(0));

    QFile cssFile("./SyNet.qss");
    cssFile.open(QFile::ReadOnly);
    QString qssTheme {QLatin1String(cssFile.readAll())};
    a.setStyleSheet(qssTheme);
    w.show();
    return a.exec();
}
