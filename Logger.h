#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <stdlib.h>
#include <QTime>
#include "DeviceLogController.h"

class Logger : public QThread
{
    Q_OBJECT
private:
    QTimer *mTimer;
    int mDelay;
    int mDuration;
    bool isRunning;
    void SaveData();

public:
    explicit Logger(QObject *parent = 0);
    ~Logger();
    void run();
    void StartWriting();
    void StopWriting();
    void SetParam(int delay, long duration);

private slots:
    void WriteRecord();
};

#endif // LOGGER_H
