#ifndef LOGMASTER_H
#define LOGMASTER_H

#include <vector>
#include <string>
#include <mutex>
#include <fstream>
#include <ctime>

using namespace std;

class LogMaster
{
public:
    //public methods
    static LogMaster* Inst(){return m_inst;}
    static void Init(){delete m_inst; m_inst = new LogMaster;}


    std::vector<std::string> getLastStrings();
    void addLine(std::string text);

private:
    LogMaster();
    ~LogMaster(){}
    LogMaster(LogMaster const&);

    //private variable
    static LogMaster* m_inst;

    std::string fileName;

    std::vector<std::string> m_vector;
    unsigned int numberLastStrings;
    std::mutex m_locker;
};

#endif // LOGMASTER_H
