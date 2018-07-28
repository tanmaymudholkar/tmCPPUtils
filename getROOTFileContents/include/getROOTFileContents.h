#include <streambuf>
#include <ostream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <regex>
#include <vector>
#include <map>

#include "TROOT.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TList.h"
#include "TTree.h"
#include "TObjArray.h"

#include "tmArgumentParser.h"
#include "tmMiscellaneous.h"

struct objectDescriptionStruct {
  std::string path;
  std::string objectName;
  std::string objectTitle;
  std::string objectType;
};
