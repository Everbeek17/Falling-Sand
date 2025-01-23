#ifdef DEBUG

#include <chrono>

#include <debug_functions.h>

Timer::Timer() {}

void Timer::start() {
  start_time = std::chrono::high_resolution_clock::now();
  end_time = start_time;
}
void Timer::stop() {
  end_time = std::chrono::high_resolution_clock::now();
}
double Timer::get_elapsed_time() const {
  std::chrono::duration<double> duration = end_time - start_time;
  return duration.count();
}

#endif