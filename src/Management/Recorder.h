#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include <stdlib.h>

#include "RecordController.h"

class Recorder : public QThread
{
    Q_OBJECT
public:
    //public methods
    explicit Recorder(QObject *parent = 0);
    ~Recorder();

    void run();
    void StartWriting();
    void StopWriting();
    void SetParam(int delay, long duration);

signals:
    void UpdateTime(long time);

private:
    //private variable
    QTimer *mTimer;
    int mDelay;
    int mDuration;
    bool isRunning;
    bool isRestart;

    //private methods
    void SaveData();

private slots:
    void WriteRecord();
};

#endif // RECORDER_H
