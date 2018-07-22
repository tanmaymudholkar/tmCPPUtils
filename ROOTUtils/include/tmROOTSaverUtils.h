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
#include "TGraph2D.h"

namespace tmROOTSaverUtils {
  TCanvas* saveObjects(TObjArray *objectArray, std::string canvasName="", TFile* outputFile=NULL, std::string outputDocumentName="", int canvas_xPixels=1024, int canvas_yPixels=768, int customOptStat=-1, std::string customPaintTextFormat="", std::string customPlotOptions="", bool enableLogX=false, bool enableLogY=false, bool enableLogZ=false, double customXRangeLow=0, double customXRangeHigh=0, double customYRangeLow=0, double customYRangeHigh=0, double customZRangeLow=0, double customZRangeHigh=0);

  TCanvas* saveSingleObject(TObject *object, std::string canvasName="", TFile* outputFile=NULL, std::string outputDocumentName="", int canvas_xPixels=1024, int canvas_yPixels=768, int customOptStat=-1, std::string customPaintTextFormat="", std::string customPlotOptions="", bool enableLogX=false, bool enableLogY=false, bool enableLogZ=false, double customXRangeLow=0, double customXRangeHigh=0, double customYRangeLow=0, double customYRangeHigh=0, double customZRangeLow=0, double customZRangeHigh=0);

  void printObjectInfo(TObject* object);
}

#endif
