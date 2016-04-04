#include "FileLoader.h"

FileLoader::FileLoader(QObject *parent) : QThread(parent)
{
    isRunning = false;
    isRestart = false;
}

void FileLoader::run()
{
    //нить потока создана
pointStart:
    isRestart = false;
    isRunning = true;
    m_timer = new QTimer;
    m_timer->setInterval(m_delay);
    connect(m_timer, SIGNAL(timeout()), SLOT(updateInfo()), Qt::DirectConnection);
    m_timer->start();
    //Запускаем цикл обработки событий
    exec();
    //Завершился цикл обработки событий
    m_timer->stop();

    isRunning = false;
    if(isRestart) goto pointStart;
    //нить потока удалена
}

void FileLoader::startLoad()
{
    //MovesStorage::Inst()->loadFile();
    if( !isRunning ) start();
}

void FileLoader::updateInfo()
{

}

void FileLoader::setFilename(QString fileName)
{

}
