#ifndef TMROOTSAVERUTILS_H
#define TMROOTSAVERUTILS_H

#include <cstdlib>
#include <iostream>

#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TH1.h"

namespace tmROOTSaverUtils {
  TCanvas* saveObjects(TObjArray *objectArray, std::string canvasName="", TFile* outputFile=NULL, std::string outputDocumentName="", int canvas_xPixels=1024, int canvas_yPixels=768, int customOptStat=-1, std::string customPaintTextFormat="", std::string customPlotOptions="", bool enableLogX=false, bool enableLogY=false, bool enableLogZ=false, double customXRangeLow=0, double customXRangeHigh=0, double customYRangeLow=0, double customYRangeHigh=0, double customZRangeLow=0, double customZRangeHigh=0);

  TCanvas* saveSingleObject(TObject *object, std::string canvasName="", TFile* outputFile=NULL, std::string outputDocumentName="", int canvas_xPixels=1024, int canvas_yPixels=768, int customOptStat=-1, std::string customPaintTextFormat="", std::string customPlotOptions="", bool enableLogX=false, bool enableLogY=false, bool enableLogZ=false, double customXRangeLow=0, double customXRangeHigh=0, double customYRangeLow=0, double customYRangeHigh=0, double customZRangeLow=0, double customZRangeHigh=0) {
    TObjArray *singleObjectArray = new TObjArray(1);
    singleObjectArray->Add(object);
    return saveObjects(singleObjectArray, canvasName, outputFile, outputDocumentName, canvas_xPixels, canvas_yPixels, customOptStat, customPaintTextFormat, customPlotOptions, enableLogX, enableLogY, enableLogZ, customXRangeLow, customXRangeHigh, customYRangeLow, customYRangeHigh, customZRangeLow, customZRangeHigh);
  }

  void printObjectInfo(TObject* object) {
    std::cout << "Object info: name = " << object->GetName()
              << ", title = " << object->GetTitle()
              << ", class = " << object->ClassName() << std::endl;
  }
}

#endif
