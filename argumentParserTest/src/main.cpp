#include "../include/main.h"

int main(int argc, char** argv) {
  std::cout << "Testing argument parser..." << std::endl;
  tmArgumentParser argumentParser = tmArgumentParser("Program to test argument parser.");
  argumentParser.addArgument("string_required", "", true, "string required.");
  argumentParser.addArgument("string_default", "teststr", false, "string default.");
  argumentParser.addArgument("int_required", "", true, "int required.");
  argumentParser.addArgument("int_default", "5", false, "int default.");
  argumentParser.addArgument("float_required", "", true, "float required.");
  argumentParser.addArgument("float_default", "2.718", false, "float default.");
  argumentParser.addArgument("double_required", "", true, "double required.");
  argumentParser.addArgument("double_default", "3.1415926", false, "double default.");
  argumentParser.setPassedStringValues(argc, argv);
  
  std::string stringRequired = argumentParser.getArgumentString("string_required");
  std::string stringDefault = argumentParser.getArgumentString("string_default");
  std::cout << "stringRequired = " << stringRequired
            << ", stringDefault = " << stringDefault << std::endl;

  int intRequired = std::stoi(argumentParser.getArgumentString("int_required"));
  int intDefault = std::stoi(argumentParser.getArgumentString("int_default"));
  std::cout << "intRequired = " << intRequired
            << ", intDefault = " << intDefault << std::endl;

  float floatRequired = std::stof(argumentParser.getArgumentString("float_required"));
  float floatDefault = std::stof(argumentParser.getArgumentString("float_default"));
  std::cout << "floatRequired = " << floatRequired
            << ", floatDefault = " << floatDefault << std::endl;

  double doubleRequired = std::stod(argumentParser.getArgumentString("double_required"));
  double doubleDefault = std::stod(argumentParser.getArgumentString("double_default"));
  std::cout << "doubleRequired = " << doubleRequired
            << ", doubleDefault = " << doubleDefault << std::endl;

  return 0;
}
