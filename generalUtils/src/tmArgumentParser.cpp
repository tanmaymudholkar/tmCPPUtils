#include "../include/tmArgumentParser.h"

tmArgumentParser::tmArgumentParser(std::string programDescription) {
  programDescription_ = programDescription;
}

tmArgumentParser::~tmArgumentParser() {}

void tmArgumentParser::addArgument(std::string argumentName, std::string defaultValueString, bool isRequired, std::string description) {
  argumentCharacteristicsStruct temp;
  temp.defaultValueString_ = defaultValueString;
  temp.isRequired_ = isRequired;
  temp.description_ = description;
  argumentCharacteristics_[argumentName] = temp;
  allowedArgumentNames_.push_back(argumentName);
}

void tmArgumentParser::setPassedStringValues(int argc, char** argv) {
  // set passed string values
  for (int argCounter = 1; argCounter < argc; ++argCounter) {
    std::string argument = argv[argCounter];
    std::smatch regexMatch;
    if (argument == "-h" || (argument == "help" || argument == "h")) {
      printCallingSyntax();
      std::exit(EXIT_SUCCESS);
    }
    if (std::regex_match(argument, regexMatch, std::regex("^([^=]+)=([^=]+)$"))) {
      if (!(regexMatch.size() == 3)) {
        std::cout << "ERROR in parsing supplied argument (" << argument << ") as arg=value." << std::endl;
        std::cout << "regex matches: " << std::endl;
        for (unsigned regexMatchCounter = 1; regexMatchCounter < regexMatch.size(); ++regexMatchCounter) {
          std::cout << "regexMatch[" << regexMatchCounter << "]: " << regexMatch[regexMatchCounter] << std::endl;
        }
        printCallingSyntax();
        std::exit(EXIT_FAILURE);
      }
      std::cout << "Setting: passedStringValues_[\"" << regexMatch[1] << "\"] = \"" << regexMatch[2] << "\"" << std::endl;
      if (std::find(allowedArgumentNames_.begin(), allowedArgumentNames_.end(), regexMatch[1]) == allowedArgumentNames_.end()) {
        std::cout << "ERROR: passed argument \"" << regexMatch[1] << "\" not recognized" << std::endl;
        printCallingSyntax();
        std::exit(EXIT_FAILURE);
      }
      passedStringValues_[regexMatch[1]] = regexMatch[2];
    }
    else{
      std::cout << "ERROR: Argument " << argCounter << " not in the format arg=val; passed argument = " << argument << std::endl;
      printCallingSyntax();
      std::exit(EXIT_FAILURE);
    }
  }

  // check that all required values are present
  for(auto argumentName : allowedArgumentNames_) {
    argumentCharacteristicsStruct characteristics = argumentCharacteristics_[argumentName];
    if (characteristics.isRequired_) {
      if (passedStringValues_.find(argumentName) == passedStringValues_.end()) {
        std::cout << "ERROR: Argument \"" << argumentName << "\" is compulsory but not passed"<< std::endl;
        printCallingSyntax();
        std::exit(EXIT_FAILURE);
      }
    }
  }
}

void tmArgumentParser::printCallingSyntax() {
  std::cout << "Program description: " << programDescription_ << std::endl;
  std::cout << "Syntax: " << std::endl
            << "./programName arg1=value1 arg2=value2..."
            << "where valueN cannot contain the \"=\" character and argN can be one of the following:" << std::endl;

  std::cout << "List of COMPULSORY arguments, in the format argument ==> description" << std::endl;
  for (auto allowedArgument : allowedArgumentNames_) {
    argumentCharacteristicsStruct characteristics = argumentCharacteristics_[allowedArgument];
    if (characteristics.isRequired_) {
      std::cout << allowedArgument << " ==> " << characteristics.description_ << std::endl;
    }
  }

  std::cout << "List of OPTIONAL arguments, in the format argument ==> default value ==> description" << std::endl;
  for (auto allowedArgument : allowedArgumentNames_) {
    argumentCharacteristicsStruct characteristics = argumentCharacteristics_[allowedArgument];
    if (!(characteristics.isRequired_)) {
      std::cout << allowedArgument << " ==> " << characteristics.defaultValueString_ << " ==> " << characteristics.description_ << std::endl;
    }
  }
}

std::string tmArgumentParser::getArgumentString(std::string argumentName) {
  argumentCharacteristicsStruct characteristics = argumentCharacteristics_[argumentName];
  std::string stringValue;
  if (passedStringValues_.find(argumentName) != passedStringValues_.end()) stringValue = passedStringValues_[argumentName];
  else stringValue = characteristics.defaultValueString_;
  return stringValue;
}
