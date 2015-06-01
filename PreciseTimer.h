#ifndef PRETIMER_H
#define PRETIMER_H

#include <stack>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>    // usleep()
#endif

// namespace, традиционно, с именем "ext", так что измените под ваши
// привычки именования, если надо.
namespace ext {

class PreciseTimer {
public:
#ifdef WIN32
  // Тип int64 для Windows
  typedef LONGLONG Counter;
#else
  // Тип int64 для UNIX
  typedef long long Counter;
#endif
  PreciseTimer();

  Counter millisec();
  Counter microsec();
  Counter cstart;
  Counter current;
  Counter prev;
  void start_mks(); //start mikrosecond timer
  void mark();
  void mark_mks();
  Counter release();
  double GetTimeSec(); // get curren time in second;
  unsigned long long GetTime();


  bool isIntervalTime(unsigned long long interval); // interval in nanosecond
  static void sleepMs(int ms);
private:
  // Тип стека для хранения отметок времени.
  typedef std::stack< Counter > Counters;

  // Стек для хранения отметок времени.
  Counters __counters;

#ifdef WIN32
  // Для Windows надо хранить системную частоту таймера.
  LARGE_INTEGER __freq;
#endif
};

} // ext

#endif // PRETIMER_H
