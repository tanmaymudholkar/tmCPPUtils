#include "../include/tmMiscellaneous.h"

std::string tmMiscUtils::getCWD() {
  char buff[FILENAME_MAX]; // FILENAME_MAX is defined in stdio.h
  getcwd(buff, FILENAME_MAX); // getcwd is in unistd.h
  return std::string(buff);
}
