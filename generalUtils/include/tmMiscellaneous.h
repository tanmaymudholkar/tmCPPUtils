#ifndef TMMISCELLANEOUS_H
#define TMMISCELLANEOUS_H

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>

namespace tmMiscUtils{
  std::string getCWD();
  std::vector<std::string> getSplitString(std::string inputString, std::string splitCharacter);
}

#endif
