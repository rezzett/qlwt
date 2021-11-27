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
    void on_addLesonInput_textChanged(const QString &arg1);

    void on_addLessonBtn_clicked();


    void on_lessonsList_itemClicked(QListWidgetItem *item);

    void on_lessonsList_itemDoubleClicked(QListWidgetItem *item);

    void on_wordInput_textChanged(const QString &arg1);

    void on_translatedInput_textChanged(const QString &arg1);

    void on_addWordPairBtn_clicked();

    void on_wordsList_itemDoubleClicked(QListWidgetItem *item);

    void on_startTrainBtn_clicked();

    void on_answerInput_textChanged(const QString &arg1);

    void on_okBtn_clicked();

    void on_hintBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString lessonName = "No Lesson";
    Storage storage;
    QVector<WordPair> trainingLesson;
    int rnd;
    int hints, errors;
};
#endif // MAINWINDOW_H
