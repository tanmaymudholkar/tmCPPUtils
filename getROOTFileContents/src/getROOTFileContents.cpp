#include "../include/getROOTFileContents.h"

void printListOfROOTObjects(std::vector<objectDescriptionStruct> listOfROOTObjects, const std::string& outputFileName) {
  std::streambuf * outputBuffer;
  std::ofstream outputFile;
  if (outputFileName.empty()) {
    outputBuffer = std::cout.rdbuf();
  }
  else {
    outputFile.open(outputFileName.c_str());
    if (!(outputFile.is_open())) {
      std::cout << "ERROR in opening file to write to: " << outputFileName << std::endl;
      std::exit(EXIT_FAILURE);
    }
    outputBuffer = outputFile.rdbuf();
  }
  std::ostream outputStream(outputBuffer);

  for (const auto& objectDescription: listOfROOTObjects) {
    outputStream << "path: " << objectDescription.path << ", name:   " << objectDescription.objectName << ", title: " << objectDescription.objectTitle << ", type: " << objectDescription.objectType << std::endl;
  }

  if (outputFile.is_open()) outputFile.close();
}

std::vector<objectDescriptionStruct> getListOfROOTObjectsInGivenDirectory(const std::string& directoryName, const std::vector<std::string>& filterTypes) {
  std::vector<objectDescriptionStruct> listOfROOTObjectsInGivenDirectory;
  std::cout << "Entering directory: " << directoryName << std::endl;
  gDirectory->cd(directoryName.c_str());
  std::cout << "Current directory: ";
  gDirectory->pwd();
  for (const auto&& key: *(gDirectory->GetListOfKeys())) {
    // std::cout << "Found key with name: " << key->GetName() << std::endl;
    TObject *rootObject = gDirectory->Get(key->GetName());
    objectDescriptionStruct objectDescription;
    objectDescription.path = std::string(gDirectory->GetPath());
    objectDescription.objectName = std::string(rootObject->GetName());
    objectDescription.objectTitle = std::string(rootObject->GetTitle());
    objectDescription.objectType = std::string(rootObject->ClassName());
    if (!(filterTypes.empty())) {
      for (const auto& filterType: filterTypes) {
        if ((objectDescription.objectType == filterType) || rootObject->InheritsFrom(filterType.c_str())) {
          listOfROOTObjectsInGivenDirectory.push_back(objectDescription);
          break;
        }
      }
    }
    else listOfROOTObjectsInGivenDirectory.push_back(objectDescription);
    bool inheritsFromTDirectoryFile = rootObject->InheritsFrom("TDirectoryFile");
    // std::cout << "Corresponding object does" << (inheritsFromTDirectoryFile ? " " : " NOT ") << "inherit from TDirectoryFile" << std::endl;
    bool inheritsFromTTree = rootObject->InheritsFrom("TTree");
    // std::cout << "Corresponding object does" << (inheritsFromTTree ? " " : " NOT ") << "inherit from TTree" << std::endl;
    if (inheritsFromTDirectoryFile) {
      for (const auto& ROOTObjectInGivenDirectory: getListOfROOTObjectsInGivenDirectory(std::string(key->GetName()), filterTypes)) {
        listOfROOTObjectsInGivenDirectory.push_back(ROOTObjectInGivenDirectory);
      }
    }
    else if (inheritsFromTTree) {
      TTree *foundTree = (TTree*)(gDirectory->Get(key->GetName()));
      TObjArray* listOfBranches = foundTree->GetListOfBranches();
      for (int branchCounter = 0; branchCounter < listOfBranches->GetEntries(); ++branchCounter) {
        // std::cout << "Found branch with name: " << (*listOfBranches)[branchCounter]->GetName() << ", title: " << (*listOfBranches)[branchCounter]->GetTitle() << std::endl;
        objectDescriptionStruct branchDescription;
        branchDescription.path = std::string(gDirectory->GetPath()) + std::string(foundTree->GetName()) + std::string("_treeContents");
        branchDescription.objectName = std::string((*listOfBranches)[branchCounter]->GetName());
        branchDescription.objectTitle = std::string((*listOfBranches)[branchCounter]->GetTitle());
        branchDescription.objectType = "TBranch";
        if (!(filterTypes.empty())) {
          for (const auto& filterType: filterTypes) {
            if (filterType == std::string("TBranch")) listOfROOTObjectsInGivenDirectory.push_back(branchDescription);
          }
        }
        else listOfROOTObjectsInGivenDirectory.push_back(branchDescription);
      }
    }
  }
  std::cout << "Leaving directory..." << std::endl;
  gDirectory->cd("..");
  std::cout << "Current directory: ";
  gDirectory->pwd();
  return listOfROOTObjectsInGivenDirectory;
}

std::vector<objectDescriptionStruct> getListOfROOTObjects(const std::string& inputFilePath, const std::vector<std::string>& filterTypes) {
  std::vector<objectDescriptionStruct> listOfROOTObjects;
  TFile *inputFile = TFile::Open(inputFilePath.c_str(), "READ");
  if (!(inputFile->IsOpen())) {
    std::cout << "ERROR in opening file with path " << inputFilePath << std::endl;
    std::exit(EXIT_FAILURE);
  }
  // for (const auto&& key: *inputFile->GetListOfKeys()) {
  //   // std::cout << "Found key with name: " << key->GetName() << std::endl;
  //   TObject *rootObject = inputFile->Get(key->GetName());
  //   objectDescriptionStruct objectDescription;
  //   objectDescription.path = std::string(gDirectory->GetPath());
  //   objectDescription.objectName = std::string(rootObject->GetName());
  //   objectDescription.objectTitle = std::string(rootObject->GetTitle());
  //   objectDescription.objectType = std::string(rootObject->ClassName());
  //   if (!(filterTypes.empty())) {
  //     for (const auto& filterType: filterTypes) {
  //       if ((objectDescription.objectType == filterType) || rootObject->InheritsFrom(filterType.c_str())) listOfROOTObjects.push_back(objectDescription);
  //     }
  //   }
  //   else listOfROOTObjects.push_back(objectDescription);
  //   bool inheritsFromTDirectoryFile = rootObject->InheritsFrom("TDirectoryFile");
  //   // std::cout << "Corresponding object does" << (inheritsFromTDirectoryFile ? " " : " NOT ") << "inherit from TDirectoryFile" << std::endl;
  //   if (inheritsFromTDirectoryFile) {
  //     std::vector<objectDescriptionStruct> listOfROOTObjectsInGivenDirectory = getListOfROOTObjectsInGivenDirectory(std::string(key->GetName()), filterTypes);
  //     for (const auto& ROOTObjectInGivenDirectory : listOfROOTObjectsInGivenDirectory) {
  //       listOfROOTObjects.push_back(ROOTObjectInGivenDirectory);
  //     }
  //   }
  // }

  for (const auto& ROOTObjectInGivenDirectory : getListOfROOTObjectsInGivenDirectory(std::string("/"), filterTypes)) {
    listOfROOTObjects.push_back(ROOTObjectInGivenDirectory);
  }
  
  inputFile->Close();
  return listOfROOTObjects;
}

int main(int argc, char *argv[]) {
  gROOT->SetBatch();
  tmArgumentParser argumentParser = tmArgumentParser("Recursively enter all possible TDirectories starting from / of a given ROOT file and get list of all available ROOT objects, including branches in trees.");
  argumentParser.addArgument("inputFile", "", true, "Full path to input file.");
  argumentParser.addArgument("filterTypes", "", false, "Colon-separated list of all types for which to enable printing -- remember that this is case-sensitive. If left blank, objects of all types will be printed; otherwise, only objects of any type in the list or inheriting from any type in the list are printed.");
  argumentParser.addArgument("outputFile", "", false, "Full path to output file. Leave blank for output to STDOUT.");
  argumentParser.setPassedStringValues(argc, argv);
  std::vector<objectDescriptionStruct> listOfROOTObjects = getListOfROOTObjects(argumentParser.getArgumentString("inputFile"), tmMiscUtils::getSplitString(argumentParser.getArgumentString("filterTypes"), ":"));
  printListOfROOTObjects(listOfROOTObjects, argumentParser.getArgumentString("outputFile"));
  return 0;
}
