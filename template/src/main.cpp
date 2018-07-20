#include "../include/main.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello world!" << std::endl;

  std::cout << "Current directory is: " << tmMiscUtils::getCWD() << std::endl;

  std::cout << "Constructing example argument parser..." << std::endl;
  tmArgumentParser argumentParser = tmArgumentParser("Template parser.");
  argumentParser.addArgument("arg", "defaultValue", false, "argument example.");
  argumentParser.setPassedStringValues(argc, argv);

  std::string argValue = argumentParser.getArgumentString("arg");
  std::cout << "Argument \"arg\" is set to \"" << argValue << "\"" << std::endl;

  std::cout << "Constructing example progress bar without counter..." << std::endl;
  tmProgressBar* progressBarNoCounter = new tmProgressBar();
  progressBarNoCounter->initialize();
  for (double fractionCompleted = 0; fractionCompleted <= 1; fractionCompleted += 0.002) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    progressBarNoCounter->updateBar(fractionCompleted);
  }
  delete progressBarNoCounter;
  
  std::cout << "Constructing example progress bar with counter, without initializing. Should print a warning..." << std::endl;
  tmProgressBar* progressBar = new tmProgressBar(10000);
  for (int testCounter = 0; testCounter < 10000; ++testCounter) {
    double fractionCompleted = 1.0*testCounter/10000;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    progressBar->updateBar(fractionCompleted, testCounter);
  }
  delete progressBar;
  return 0;
}
