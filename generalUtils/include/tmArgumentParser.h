#ifndef TMARGUMENTPARSER_H
#define TMARGUMENTPARSER_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>

struct argumentCharacteristicsStruct {
  std::string defaultValueString_;
  bool isRequired_;
  std::string description_;
};

class tmArgumentParser {
  std::string programDescription_;
  std::map<std::string, argumentCharacteristicsStruct> argumentCharacteristics_;
  std::vector<std::string> allowedArgumentNames_;
  std::map<std::string, std::string> passedStringValues_;

 public:
  tmArgumentParser(std::string programDescription);
  ~tmArgumentParser();
  void addArgument(std::string argumentName, std::string defaultValueString, bool isRequired, std::string description);

  void setPassedStringValues(int argc, char** argv);

  void printCallingSyntax();

  std::string getArgumentString(std::string argumentName);
};

#endif
