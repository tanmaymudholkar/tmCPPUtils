#include "../include/tmProgressBar.h"

tmProgressBar::tmProgressBar(int counterMaxValue) {
  counterMaxValue_ = counterMaxValue;
  std::stringstream temp;
  temp << counterMaxValue;
  nDigits_counterMaxValue_ = temp.str().size(); // lol
  hasBeenInitialized_ = false;
}

void tmProgressBar::initialize() {
  startTime_ = std::chrono::system_clock::now();
  hasBeenInitialized_ = true;
}

hoursMinutesSeconds getGuessTimeRemaining(double secondsElapsed, double fractionCompleted) {
  hoursMinutesSeconds guess_timeRemaining;
  double timeRemainingEstimate_seconds = secondsElapsed*(1-fractionCompleted)/fractionCompleted;
  guess_timeRemaining.hours = (int)(timeRemainingEstimate_seconds/3600);
  double timeRemainingEstimate_seconds_moduloHours = timeRemainingEstimate_seconds - 3600.0*guess_timeRemaining.hours;
  guess_timeRemaining.minutes = (int)(timeRemainingEstimate_seconds_moduloHours/60);
  double timeRemainingEstimate_seconds_moduloMinutes = timeRemainingEstimate_seconds_moduloHours - 60.0*guess_timeRemaining.minutes;
  guess_timeRemaining.seconds = (float)(timeRemainingEstimate_seconds_moduloMinutes);
  return guess_timeRemaining;
}

std::string tmProgressBar::getBuffer(double fractionCompleted, int counterCurrentValue) {
  if (!(hasBeenInitialized_)) {
    std::cout << "Warning: initializer has not been called explicitly, initializing..." << std::endl;
    initialize();
  }
  if (fractionCompleted == 0) return "";
  std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
  std::chrono::duration<double> timeElapsed = currentTime - startTime_;
  double secondsElapsed = timeElapsed.count();
  hoursMinutesSeconds guess_timeRemaining = getGuessTimeRemaining(secondsElapsed, fractionCompleted);
  double percentCompleted = 100*fractionCompleted;
  int approxPercentCompleted = (int)(0.5 + percentCompleted);
  std::stringstream outputBuffer;
  outputBuffer << "   [";
  for (int completedCounter = 0; completedCounter < approxPercentCompleted; ++completedCounter) {
    outputBuffer << "+";
  }
  for (int completedCounter = approxPercentCompleted; completedCounter < 100; ++completedCounter) {
    outputBuffer << "-";
  }
  outputBuffer << "]   " << std::fixed << std::setprecision(1) << std::right << std::setw(5) << percentCompleted << "% done.";

  if (counterMaxValue_ > 0) {
    outputBuffer << " Progress: " << std::right << std::setw(nDigits_counterMaxValue_) << counterCurrentValue << " / " << counterMaxValue_ << ".";
  }

  outputBuffer << std::setw(6) << " ETA: "
               << std::right << std::setw(3) << guess_timeRemaining.hours << std::setw(4) << " h, "
               << std::setw(2) << guess_timeRemaining.minutes << std::setw(4) << " m, "
               << std::right << std::setw(4) << guess_timeRemaining.seconds << std::setw(4) << " s.";

  outputBuffer << std::setprecision(6);
  return outputBuffer.str();
}

void tmProgressBar::updateBar(double fractionCompleted, int counterCurrentValue) {
  std::cout << getBuffer(fractionCompleted, counterCurrentValue) << "\r";
  std::cout.flush();
}

void tmProgressBar::terminate() {
  std::cout << std::endl;
  if (hasBeenInitialized_) {
    counterMaxValue_ = 0;
    nDigits_counterMaxValue_ = 0;
    hasBeenInitialized_ = false;
  }
}

tmProgressBar::~tmProgressBar() {
  terminate();
}
