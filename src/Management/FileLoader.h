#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include <stdlib.h>
#include "MoveController.h"

class FileLoader : public QThread
{
    Q_OBJECT
public:
    //public methods
    explicit FileLoader(QObject *parent = 0);
    void run();
    void setFilename(QString fileName);
    void startLoad();

signals:
    void updateLoad(int percent);

private:
    //private variable
    QTimer *m_timer;
    int m_delay;
    bool isRunning;
    bool isRestart;

public slots:
    void updateInfo();
};

#endif // FILELOADER_H
