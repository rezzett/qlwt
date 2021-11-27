#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), hints(0), errors(0)
{
    storage.load();
    storage.loadLessons();
    ui->setupUi(this);
    ui->addLessonBtn->setDisabled(true);
    ui->wordInput->setDisabled(true);
    ui->translatedInput->setDisabled(true);
    ui->addWordPairBtn->setDisabled(true);
    ui->okBtn->setDisabled(true);
    ui->hintBtn->setDisabled(true);
    ui->answerInput->setDisabled(true);
    ui->lessonIntrainLbl->setText(lessonName);
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
    ui->lessonIntrainLbl->setText(lessonName);
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
        storage.removeLesson(lessonName); // FIXXXXXXXXXXXXXXXXXXXXX after restart lesson with word restore
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

void MainWindow::on_startTrainBtn_clicked()
{
    if(storage.getCurrentLesson().size() > 0) {
        hints = errors = 0;
        ui->hintUsageLbl->setText("Hints: 0");
        ui->errCountLbl->setText("Errors: 0");
        trainingLesson = storage.getCurrentLesson();
        rnd = rand() % trainingLesson.size();
        ui->askLbl->setText(trainingLesson[rnd].translated);
        ui->wordCountLbl->setText("Words: " + QString::number(trainingLesson.size()) + "/" + QString::number(storage.getCurrentLesson().size()));
        ui->startTrainBtn->setDisabled(true);
        ui->answerInput->setDisabled(false);
        ui->hintBtn->setDisabled(false);
        ui->answerInput->setFocus();

    } else {
        QMessageBox::information(this,"No Lesson","Choose some lesson first!");
    }

}

void MainWindow::on_answerInput_textChanged(const QString &str)
{
    if(str.isEmpty()) ui->okBtn->setDisabled(true);
    else ui->okBtn->setDisabled(false);
}

void MainWindow::on_okBtn_clicked()
{
    ui->hintLbl->setText("");
   if(trainingLesson[rnd].word == ui->answerInput->text()) {
       ui->susccessLbl->setText("Success!");
       ui->susccessLbl->setStyleSheet("QLabel {color : green; }");
       trainingLesson.erase(trainingLesson.begin() + rnd);
       ui->wordCountLbl->setText("Words: " + QString::number(trainingLesson.size()) + "/" + QString::number(storage.getCurrentLesson().size()));
   } else {
       ui->susccessLbl->setText("Failed!");
       ui->susccessLbl->setStyleSheet("QLabel {color : red; }");
       ui->errCountLbl->setText("Errors: " + QString::number(++errors));
   }

   if(!trainingLesson.isEmpty()) {
       rnd = rand() % trainingLesson.size();
       ui->askLbl->setText(trainingLesson[rnd].translated);
       ui->answerInput->setText("");
   } else {
       ui->askLbl->setText("There are no words left");
       ui->susccessLbl->setStyleSheet("QLabel {color : ; }");
       ui->susccessLbl->setText("");
       ui->answerInput->setText("");
       ui->okBtn->setDisabled(true);
       ui->hintBtn->setDisabled(true);
       ui->startTrainBtn->setDisabled(false);
       ui->answerInput->setDisabled(true);
   }
}

void MainWindow::on_hintBtn_clicked()
{
    ui->hintLbl->setText(trainingLesson[rnd].word);
    ui->hintUsageLbl->setText("Hints: " + QString::number(++hints));
}
