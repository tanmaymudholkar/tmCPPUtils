#include "../include/main.h"

void writeVectorToFile(std::vector<std::string> vectorToWrite, std::string outputFileName) {
  std::ofstream outputFile;
  outputFile.open(outputFileName.c_str());
  for (auto element: vectorToWrite) {
    outputFile << element << std::endl;
  }
  outputFile.close();
}

std::vector<std::string> getListOfROOTBranchesInGivenDirectory(const std::string& directoryName) {
  std::vector<std::string> listOfROOTBranchesInDirectory;
  std::cout << "Entering directory: " << directoryName << std::endl;
  gDirectory->cd(directoryName.c_str());
  std::cout << "Current directory: ";
  gDirectory->pwd();
  for (const auto&& key: *(gDirectory->GetListOfKeys())) {
    std::cout << "Found key with name: " << key->GetName() << std::endl;
    TObject *rootObject = gDirectory->Get(key->GetName());
    bool inheritsFromTDirectoryFile = rootObject->InheritsFrom("TDirectoryFile");
    std::cout << "Corresponding object does" << (inheritsFromTDirectoryFile ? " " : " NOT ") << "inherit from TDirectoryFile" << std::endl;
    bool inheritsFromTTree = rootObject->InheritsFrom("TTree");
    std::cout << "Corresponding object does" << (inheritsFromTTree ? " " : " NOT ") << "inherit from TTree" << std::endl;
    delete rootObject;
    if (inheritsFromTDirectoryFile) {
      for (auto rootBranchInGivenDirectory: getListOfROOTBranchesInGivenDirectory(key->GetName())) {
        listOfROOTBranchesInDirectory.push_back(rootBranchInGivenDirectory);
      }
    }
    else if (inheritsFromTTree) {
      TTree *foundTree = (TTree*)(gDirectory->Get(key->GetName()));
      TObjArray* listOfBranches = foundTree->GetListOfBranches();
      for (int branchCounter = 0; branchCounter < listOfBranches->GetEntries(); ++branchCounter) {
        // std::cout << "Found branch with name: " << (*listOfBranches)[branchCounter]->GetName() << ", title: " << (*listOfBranches)[branchCounter]->GetTitle() << std::endl;
        listOfROOTBranchesInDirectory.push_back((*listOfBranches)[branchCounter]->GetName());
      }
    }
  }
  std::cout << "Leaving directory..." << std::endl;
  gDirectory->cd("..");
  std::cout << "Current directory: ";
  gDirectory->pwd();
  return listOfROOTBranchesInDirectory;
}

std::vector<std::string> getListOfROOTBranches(const std::string& inputFilePath) {
  std::vector<std::string> listOfROOTBranches;
  auto inputFile = new TFile(inputFilePath.c_str(), "READ");
  if (!(inputFile->IsOpen())) {
    std::cout << "ERROR in opening file with path " << inputFilePath << std::endl;
    std::exit(EXIT_FAILURE);
  }
  for (const auto&& key: *inputFile->GetListOfKeys()) {
    std::cout << "Found key with name: " << key->GetName() << std::endl;
    TObject *rootObject = inputFile->Get(key->GetName());
    bool inheritsFromTDirectoryFile = rootObject->InheritsFrom("TDirectoryFile");
    std::cout << "Corresponding object does" << (inheritsFromTDirectoryFile ? " " : " NOT ") << "inherit from TDirectoryFile" << std::endl;
    delete rootObject;
    if (inheritsFromTDirectoryFile) {
      for (auto rootBranchInGivenDirectory: getListOfROOTBranchesInGivenDirectory(key->GetName())) {
        listOfROOTBranches.push_back(rootBranchInGivenDirectory);
      }
    }
  }
  inputFile->Close();
  return listOfROOTBranches;
}

void checkArguments(const std::map<std::string, std::string>& inputArguments, const std::vector<std::string>& expectedArguments) {
  for (auto expectedArgumentsIterator = expectedArguments.begin(); expectedArgumentsIterator != expectedArguments.end(); ++expectedArgumentsIterator) {
    if (inputArguments.find(*expectedArgumentsIterator) == inputArguments.end()) {
      std::cout << "ERROR: argument \"" << *expectedArgumentsIterator << "\" expected but not found in list of input arguments" << std::endl;
      std::cout << "Provided arguments: " << std::endl;
      for (auto inputArgumentsIterator = inputArguments.begin(); inputArgumentsIterator != inputArguments.end(); ++inputArgumentsIterator) {
        std::cout << "inputArguments[\"" << inputArgumentsIterator->first << "\"]: \"" << inputArgumentsIterator->second << "\"" << std::endl;
      }
      std::exit(EXIT_FAILURE);
    }
  }
}

std::map<std::string, std::string> parseArguments(int argc, char *argv[]) {
  std::map<std::string, std::string> inputArguments;
  if (argc != 3) {
    std::cout << "ERROR: Expected exactly 2 arguments: \"input\", the path to the input file, and \"output\", the name path to the output file." << std::endl
              << "Syntax: listROOTBranches input=<input path> output=<output path>" << std::endl
              << "Currently passed arguments: " << std::endl;
    for (int argCounter = 1; argCounter < argc; ++argCounter) {
      std::cout << "arg[" << argCounter << "] = " << argv[argCounter] << std::endl;
    }
    std::exit(EXIT_FAILURE);
  }
  for (int argCounter = 1; argCounter < argc; ++argCounter) {
    std::string argument = argv[argCounter];
    std::smatch regexMatch;
    if (std::regex_match(argument, regexMatch, std::regex("^([^=]+)=([^=]+)$"))) {
      if (!(regexMatch.size() == 3)) {
        std::cout << "ERROR in parsing supplied argument (" << argument << ") as arg=value." << std::endl;
        std::cout << "regex matches: " << std::endl;
        for (unsigned regexMatchCounter = 1; regexMatchCounter < regexMatch.size(); ++regexMatchCounter) {
          std::cout << "regexMatch[" << regexMatchCounter << "]: " << regexMatch[regexMatchCounter] << std::endl;
        }
        std::exit(EXIT_FAILURE);
      }
      std::cout << "Setting: inputArguments[\"" << regexMatch[1] << "\"] = \"" << regexMatch[2] << "\"" << std::endl;
      inputArguments[regexMatch[1]] = regexMatch[2];
    }
    else{
      std::cout << "ERROR: Argument " << argCounter << " not in the format arg=val; passed argument = " << argument << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  return inputArguments;
}

int main(int argc, char *argv[]) {
  std::map<std::string, std::string> inputArguments = parseArguments(argc, argv);
  std::vector<std::string> expectedArguments = {"input", "output"};
  checkArguments(inputArguments, expectedArguments);
  std::vector<std::string> listOfROOTBranches = getListOfROOTBranches(inputArguments["input"]);
  writeVectorToFile(listOfROOTBranches, inputArguments["output"]);
  return 0;
}
