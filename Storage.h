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
    QString lesson;
    WordPair(const QString& w = "", const QString& t = "", const QString& lsn = ""):
        word(w), translated(t), lesson(lsn) {}
};

inline QDataStream& operator << (QDataStream& out, const WordPair& wp) {
    out << wp.word << wp.translated << wp.lesson;
    return out;
}

inline QDataStream& operator >> (QDataStream& in,  WordPair& wp) {
    in >> wp.word >> wp.translated >> wp.lesson;
    return in;
}

class Storage {
    QVector<WordPair> records;
    QVector<WordPair> currentLesson;
    QVector<QString> lessons;
public:
    void load() {
        QFile readFile("data.txt");
        readFile.open(QFile::ReadOnly);
        QDataStream rf(&readFile);
        while(!rf.atEnd()) {
            WordPair tmp;
            rf >> tmp;
            records.push_back(tmp);
        }
        readFile.close();
    }

    void save() {
        QFile writeFile("data.txt");
        writeFile.open(QFile::ReadWrite);
        QDataStream wf(&writeFile);
        for(auto& record: records) {
            wf << record;
        }
        writeFile.close();
    }

    void loadCurrentLesson(const QString& lessonName) {
        std::copy_if(records.begin(), records.end(), std::back_inserter(currentLesson), [&lessonName](WordPair item) {
            return item.lesson == lessonName;
        });
    }

    const QVector<WordPair>& getCurrentLesson() const {
        return currentLesson;
    }

    const QVector<QString>& getLessons() const {
        return lessons;
    }

    void addLessonRecord(const WordPair& wp) {
        currentLesson.append(wp);
        records.append(wp);
    }

    void loadLessons() {
        for(auto& record: records) {
           if(lessons.contains(record.lesson)) continue;
           lessons.append(record.lesson);
        }
    }

};

#endif // STORAGE_H
