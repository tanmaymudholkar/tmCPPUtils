#ifndef TMPROGRESSBAR_H
#define TMPROGRESSBAR_H

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>

struct hoursMinutesSeconds {
  int hours;
  int minutes;
  float seconds;
};

class tmProgressBar {
  int counterMaxValue_;
  int nDigits_counterMaxValue_;
  double fractionCompletedAtLastCheck_;
  bool hasBeenInitialized_;
  std::chrono::system_clock::time_point timeAtLastCheck_;
  hoursMinutesSeconds getGuessTimeRemaining(double secondsSinceLastCheck, double fractionCompleted);
  std::string getBuffer(double fractionCompleted, int counterCurrentValue = 0);
 public:
  tmProgressBar(int counterMaxValue = 0);
  ~tmProgressBar();
  void initialize();
  void updateBar(double fractionCompleted, int counterCurrentValue = 0);
  void terminate();
};

#endif
