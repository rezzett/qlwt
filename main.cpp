#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>


int main(int argc, char *argv[])
{
    QDir dir("qlwtdata");
    if(!dir.exists()) dir.mkpath(".");
    QApplication a(argc, argv);
    MainWindow w;
    srand(time(0));

    QFile theme("qlwtdata/theme.txt");
    theme.open(QFile::ReadOnly);
    QTextStream stream(&theme);
    QString themeName = stream.readLine();
    theme.close();
    if(themeName.isEmpty()) themeName = "Fibrary";

    QFile cssFile("./qlwtdata/" + themeName + ".qss");
    cssFile.open(QFile::ReadOnly);
    QString qssTheme {QLatin1String(cssFile.readAll())};
    a.setStyleSheet(qssTheme);
    w.show();
    return a.exec();
}
