#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    storage.load();
    storage.loadLessons();
    ui->setupUi(this);
    ui->addLessonBtn->setDisabled(true);
    ui->wordInput->setDisabled(true);
    ui->translatedInput->setDisabled(true);
    ui->addWordPairBtn->setDisabled(true);
    auto lessons = storage.getLessons();
    for(auto& lesson: lessons) {
        ui->lessonsList->addItem(lesson);
    }
}

MainWindow::~MainWindow()
{
    storage.save();
    delete ui;
}


void MainWindow::on_addLesonInput_textChanged(const QString &str)
{
    // TODO restrict lesson name length
    if(!str.isEmpty()) ui->addLessonBtn->setDisabled(false);
    else ui->addLessonBtn->setDisabled(true);
}

void MainWindow::on_addLessonBtn_clicked()
{
    ui->lessonsList->addItem(ui->addLesonInput->text());
    ui->addLesonInput->setText("");
}


void MainWindow::on_lessonsList_itemClicked(QListWidgetItem *item)
{
    if(lessonName == item->text()) return;
    lessonName = item->text();
    ui->addLessonTitle->setText(lessonName);
    ui->wordInput->setDisabled(false);
    ui->translatedInput->setDisabled(false);
    storage.loadCurrentLesson(lessonName);
    auto currentLesson = storage.getCurrentLesson();
    ui->wordsList->clear();
    for(auto& wp: currentLesson) ui->wordsList->addItem(wp.word);

}

void MainWindow::on_lessonsList_itemDoubleClicked(QListWidgetItem *item)
{
    // TODO  create func for update titles
    if(lessonName == item->text()) {
        storage.removeLesson(lessonName);
        ui->wordsList->clear();
        lessonName = "No Lesson";
        ui->addLessonTitle->setText(lessonName);
        ui->wordInput->setDisabled(true);
        ui->wordInput->setText("");
        ui->translatedInput->setDisabled(true);
        ui->translatedInput->setText("");
    }
    delete item;
}

void MainWindow::on_wordInput_textChanged(const QString &str)
{
    if(!str.isEmpty() and !ui->translatedInput->text().isEmpty())
        ui->addWordPairBtn->setDisabled(false);
    else
        ui->addWordPairBtn->setDisabled(true);
}


void MainWindow::on_translatedInput_textChanged(const QString &str)
{
    if(!str.isEmpty() and !ui->wordInput->text().isEmpty())
        ui->addWordPairBtn->setDisabled(false);
    else
        ui->addWordPairBtn->setDisabled(true);

}

void MainWindow::on_addWordPairBtn_clicked()
{
    storage.addLessonRecord(WordPair(ui->wordInput->text(),ui->translatedInput->text(), lessonName));
    ui->wordsList->addItem(ui->wordInput->text());
    ui->wordInput->setText("");
    ui->translatedInput->setText("");
}

void MainWindow::on_wordsList_itemDoubleClicked(QListWidgetItem *item)
{
   storage.deletelLessonRecord(item->text());
   delete item;
}
