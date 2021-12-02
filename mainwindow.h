#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QListView>
#include <QRandomGenerator>
#include <QMessageBox>
#include <ctime>
#include "Storage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    QString lessonName = "No Lesson";
    Storage storage;
    QVector<WordPair> trainingLesson;
    int rnd;
    int hints, errors;
};
#endif // MAINWINDOW_H
