#include "../include/main.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello world!" << std::endl;

  std::cout << "Current directory is: " << tmMiscUtils::getCWD() << std::endl;

  std::cout << "Constructing example argument parser..." << std::endl;
  tmArgumentParser argumentParser = tmArgumentParser("Template parser.");
  argumentParser.addArgument("arg", "defaultValue", false, "argument example.");
  argumentParser.addArgument("argumentsList", "", false, "example of argument that is meant to be input as a list of strings with a colon separating them. Empty by default.");
  argumentParser.addArgument("argumentsListOneElement", "test", false, "example of argument that is meant to be input as a list of strings with a colon separating them. Just one element by default.");
  argumentParser.addArgument("argumentsListFourElements", "test1:test2:test3:test4", false, "example of argument that is meant to be input as a list of strings with a colon separating them. Four elements by default.");
  argumentParser.setPassedStringValues(argc, argv);

  std::string argValue = argumentParser.getArgumentString("arg");
  std::cout << "Argument \"arg\" is set to \"" << argValue << "\"" << std::endl;

  std::vector<std::string> argumentsList = tmMiscUtils::getSplitString(argumentParser.getArgumentString("argumentsList"), ":");
  std::cout << "Vector argumentsList is: {";
  for (auto element: argumentsList) std::cout << element << ", ";
  std::cout << "}" << std::endl;

  std::vector<std::string> argumentsListOneElement = tmMiscUtils::getSplitString(argumentParser.getArgumentString("argumentsListOneElement"), ":");
  std::cout << "Vector argumentsListOneElement is: {";
  for (auto element: argumentsListOneElement) std::cout << element << ", ";
  std::cout << "}" << std::endl;

  std::vector<std::string> argumentsListFourElements = tmMiscUtils::getSplitString(argumentParser.getArgumentString("argumentsListFourElements"), ":");
  std::cout << "Vector argumentsListFourElements is: {";
  for (auto element: argumentsListFourElements) std::cout << element << ", ";
  std::cout << "}" << std::endl;

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

  TH1F *testHistogram = new TH1F("testHistogram", "Gaussian test;x", 100, -3, 3);
  for (int randomCounter = 0; randomCounter < 10000; ++randomCounter) testHistogram->Fill(gRandom->Gaus(0, 1));
  TFile *outputFile = TFile::Open("testOutputs/test.root", "RECREATE");
  tmROOTSaverUtils::saveSingleObject(testHistogram, "testCanvas", outputFile, "testOutputs/test.png", 1024, 768, 111111, "", "", false, false, false, -2.5, 2.5, 0, 0, 0, 0);
  outputFile->Close();
  return 0;
}
