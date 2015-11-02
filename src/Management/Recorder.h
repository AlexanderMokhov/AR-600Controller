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
private:
    QTimer *mTimer;
    int mDelay;
    int mDuration;
    bool isRunning;
    bool isRestart;
    void SaveData();

public:
    explicit Recorder(QObject *parent = 0);
    ~Recorder();
    void run();
    void StartWriting();
    void StopWriting();
    void SetParam(int delay, long duration);

private slots:
    void WriteRecord();
signals:
    void UpdateTime(long time);

};

#endif // RECORDER_H
