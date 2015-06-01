#include "PreciseTimer.h"
namespace ext{

//возвращает время в секундах
double PreciseTimer::GetTimeSec(){
        double ts = GetTime()/1e6;
        return ts;
}

//возвращает время в микросекундах
unsigned long long PreciseTimer::GetTime(){
    current = microsec();
    return current - cstart;
}

void PreciseTimer::start_mks(){
    cstart = microsec();
}

void PreciseTimer::mark() {
  __counters.push(millisec());
}

void PreciseTimer::mark_mks() {
  __counters.push(microsec());
}

bool PreciseTimer::isIntervalTime(unsigned long long interval){
    bool result;
    current = microsec();
    if (current - prev > interval) {
            prev = current;
            result = true;
        } else {
            result = false;
        }
    return result;
}

PreciseTimer::Counter PreciseTimer::release() {
  if( __counters.empty() ) return -1;
  Counter val = millisec() - __counters.top();
  __counters.pop();
  return val;
}

#ifdef WIN32

PreciseTimer::PreciseTimer() {
  // Для Windows в конструкторе получаем системную частоту таймера
  // (количество тиков в секунду).
  if (!QueryPerformanceFrequency(&__freq))
    __freq.QuadPart = 0;
}

PreciseTimer::Counter PreciseTimer::millisec() {
  LARGE_INTEGER current;
  if (__freq.QuadPart == 0 || !QueryPerformanceCounter(&current))
    return 0;
  // Пересчитываем количество системных тиков в миллисекунды.
  return current.QuadPart / (__freq.QuadPart / 1e3);
}

PreciseTimer::Counter PreciseTimer::microsec(){
  LARGE_INTEGER current;
  if (__freq.QuadPart == 0 || !QueryPerformanceCounter(&current))
    return 0;
  return current.QuadPart / (__freq.QuadPart / 1e6);
}

void PreciseTimer::sleepMs(int ms) {
  Sleep(ms);
}

#else // WIN32

PreciseTimer::PreciseTimer() {}

PreciseTimer::Counter PreciseTimer::millisec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

PreciseTimer::Counter PreciseTimer::microsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1e6 + tv.tv_usec;
}

void PreciseTimer::sleepMs(int ms) {
  usleep(ms * 1000);
}

#endif
}
