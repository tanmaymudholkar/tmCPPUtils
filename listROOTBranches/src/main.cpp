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

int main(int argc, char *argv[]) {
  tmArgumentParser argumentParser = tmArgumentParser("Recursively enters all possible TDirectories starting from / of a given ROOT file, gets list of all available ROOT branches, and writes them to an output file.");
  argumentParser.addArgument("input", "", true, "Full path to input file.");
  argumentParser.addArgument("output", "", true, "Full path to output file.");
  argumentParser.setPassedStringValues(argc, argv);
  std::vector<std::string> listOfROOTBranches = getListOfROOTBranches(argumentParser.getArgumentString("input"));
  writeVectorToFile(listOfROOTBranches, argumentParser.getArgumentString("output"));
  return 0;
}
