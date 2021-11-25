#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addLessonBtn->setDisabled(true);
    ui->wordInput->setDisabled(true);
    ui->translatedInput->setDisabled(true);
    ui->addWordPairBtn->setDisabled(true);
}

MainWindow::~MainWindow()
{
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
    lessonName = item->text();
    ui->addLessonTitle->setText(lessonName);
    ui->wordInput->setDisabled(false);
    ui->translatedInput->setDisabled(false);

}

void MainWindow::on_lessonsList_itemDoubleClicked(QListWidgetItem *item)
{
    // TODO  create func for update titles
    if(lessonName == item->text()) {
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
