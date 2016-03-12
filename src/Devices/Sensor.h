#ifndef SENSOR_H
#define SENSOR_H

#include "Device.h"

class Sensor : public Device
{
public:
    //public methods
    Sensor();
    ~Sensor(){;}
    Sensor( int number,
           int channel,
           std::string name,
           std::string nameLog,
           int param );

    int getValue(){ return m_value; }
    std::string getNameLog(){ return m_nameLog; }
    int getParam(){ return m_param; }

    void setValue( int value ){ m_value = value; }
    void setNameLog( std::string nameLog ){ m_nameLog = nameLog; }
    void setParam( int param ){ m_param = param; }

private:
    //private variable
    std::string     m_nameLog;
    int             m_param;
    int             m_value;

};

#endif // SENSOR_H
