#ifndef COMPILER_H
#define COMPILER_H

#include <QObject>
#include <QFileSystemModel>
#include <QDebug>
#include <QProcess>

class Compiler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString output READ getOutput WRITE setOutput NOTIFY outputChanged);
public:
    explicit Compiler(QObject *parent = nullptr);

    Q_INVOKABLE void getFileName(QFileSystemModel* fileSystemModel, const QModelIndex &modelIndex);

public Q_SLOTS:
        void compile(QString outputFile);
        void run(QString arguments);
        QString getOutput();
        void setOutput(QString);
signals:
        void outputChanged();

private:
        QString path;
        QString file;
        QString output;
};

#endif // COMPILER_H
