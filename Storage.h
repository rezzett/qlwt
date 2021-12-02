#ifndef STORAGE_H
#define STORAGE_H
#include <QString>
#include <QDataStream>
#include <QVector>
#include <QFile>
#include <algorithm>
#include <QDebug>

struct WordPair {
    QString word;
    QString translated;
    WordPair(const QString& w = "", const QString& t = ""):
        word(w), translated(t){}
};

inline QDataStream& operator << (QDataStream& out, const WordPair& wp) {
    out << wp.word << wp.translated;
    return out;
}

inline QDataStream& operator >> (QDataStream& in,  WordPair& wp) {
    in >> wp.word >> wp.translated;
    return in;
}

class Storage {
    QVector<WordPair> words;
    QVector<WordPair> trainingWords;
    QVector<QString> lessons;
public:
    // save and load  =====================================
    void loadWords(const QString& lessonName) {
        QFile readFile(lessonName +".txt");
        readFile.open(QFile::ReadOnly);
        QDataStream rf(&readFile);
        while(!rf.atEnd()) {
            WordPair tmp;
            rf >> tmp;
            words.push_back(tmp);
        }
        readFile.close();
    }

    void saveWords(const QString& lessonName) {
        QFile writeFile(lessonName + ".txt");
        writeFile.open(QFile::ReadWrite);
        QDataStream wf(&writeFile);
        for(auto& word: words) {
            wf << word;
        }
        writeFile.close();
    }

    void loadLessons() {
        QFile readFile("lessons.txt");
        readFile.open(QFile::ReadOnly);
        QDataStream rf(&readFile);
        while(!rf.atEnd()) {
            QString tmp;
            rf >> tmp;
            lessons.push_back(tmp);
        }
        readFile.close();
    }

    // lessons interface =====================================
    void saveLessons() {
        QFile writeFile("lessons.txt");
        writeFile.open(QFile::ReadWrite);
        QDataStream wf(&writeFile);
        for(auto& lesson: lessons) {
            wf << lesson;
        }
        writeFile.close();
    }

    const QVector<Qstring>& getLessons() const { return lessons;}

    void addLesson(const QString& newLesson) {
        lessons.push_back(newLesson);
        saveLessons();
    }

    void deleteLesson(const QString& delName) {
        lessons.erase(std::remove_if(lesson.begin(), lessons.end(), [&delName](const QString& item){ return item == delName;}));
        QFile::remove(delName + ".txt");
        saveLessons();
    }

    // words interface =====================================
    const QVector<QString>& getWords() const { return words; }

    int getWordsSize() const { return words.size(); }

    void addWord(const WordPair& newWP, const QString& lessonName) {
        words.push_back(newWP);
        saveWords(lessonName);
    }

    void deleteWord(const QString& delName, const Qstring& lessonName) {
        lessons.erase(std::remove_if(words.begin(), words.end(), [&delName](const WordPair& item){ return item.word == delName;}));
        saveWords(lessonName);
    }

    // training words interface =====================================
    void setUpTrainingWords() {
        trainingWords = words;
    }

    const QVector<WordPair>& getTrainingWords() const { return trainingWords; }

    int getTrainingSize() const { return trainingWords.size(); }

    void removeTrainingWord(int idx) {
        trainingWords.erase(trainingWords.begin() + idx);
    }






};

#endif // STORAGE_H
