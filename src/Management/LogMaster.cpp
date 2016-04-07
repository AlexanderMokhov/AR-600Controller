#include "LogMaster.h"

LogMaster * LogMaster::m_inst = 0;

LogMaster::LogMaster()
{
    time_t seconds = time(NULL);

    tm* timeInfo = localtime(&seconds);
    char buffer[80];
    char* format = "%d_%b_%Y_%H_%M_%S";
    strftime(buffer, 80, format, timeInfo);

    fileName = "Logs/log_" + std::string(buffer) + ".txt";
    m_vector.clear();
    numberLastStrings = 0;

    addLine("Запись работы системы начата");
}

std::vector<std::string> LogMaster::getLastStrings()
{
    m_locker.lock();

    std::vector<std::string> retVector;
    for(int i = m_vector.size() - numberLastStrings; i < m_vector.size(); i++)
        retVector.push_back(m_vector.at(i));

    m_vector.clear();
    numberLastStrings = 0;

    m_locker.unlock();
    return retVector;
}

void LogMaster::addLine(std::string text)
{
    m_locker.lock();
    std::ofstream outFile;
    outFile.open(this->fileName, std::ios::app);

    time_t seconds = time(NULL);

    tm* timeInfo = localtime(&seconds);
    char buffer[80];
    char* format = "%d.%b.%Y %H:%M:%S";
    strftime(buffer, 80, format, timeInfo);

    outFile << buffer << " - " << text << endl;/**/
    outFile.close();
    m_vector.push_back(text);

    numberLastStrings++;

    m_locker.unlock();
}

