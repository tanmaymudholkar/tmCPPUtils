#include "../include/tmMiscellaneous.h"

std::string tmMiscUtils::getCWD() {
  char buff[FILENAME_MAX]; // FILENAME_MAX is defined in stdio.h
  getcwd(buff, FILENAME_MAX); // getcwd is in unistd.h
  return std::string(buff);
}

std::vector<std::string> tmMiscUtils::getSplitString(std::string inputString, std::string splitCharacter) {
  if (!(splitCharacter.length() == 1)) {
    std::cout << "ERROR: splitCharacter must be a single character" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::vector<std::string> outputString;
  if (inputString.length() == 0) return outputString;
  std::string runningElement;
  for (auto character: inputString) {
    std::string characterString = std::string(1, character);
    if (characterString == splitCharacter) {
      outputString.push_back(runningElement);
      runningElement = std::string();
    }
    else runningElement += character;
  }
  outputString.push_back(runningElement);
  return outputString;
}
