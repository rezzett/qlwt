#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QListView>
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
    void on_addLesonInput_textChanged(const QString &arg1);

    void on_addLessonBtn_clicked();


    void on_lessonsList_itemClicked(QListWidgetItem *item);

    void on_lessonsList_itemDoubleClicked(QListWidgetItem *item);

    void on_wordInput_textChanged(const QString &arg1);

    void on_translatedInput_textChanged(const QString &arg1);

    void on_addWordPairBtn_clicked();

    void on_wordsList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QString lessonName = "No Lesson";
    Storage storage;
};
#endif // MAINWINDOW_H
