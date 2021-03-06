#include "../include/tmROOTSaverUtils.h"

TCanvas* tmROOTSaverUtils::saveObjects(TObjArray *objectArray, std::string canvasName, TFile* outputFile, std::string outputDocumentName, int canvas_xPixels, int canvas_yPixels, int customOptStat, std::string customPaintTextFormat, std::string customPlotOptions, bool enableLogX, bool enableLogY, bool enableLogZ, double customXRangeLow, double customXRangeHigh, double customYRangeLow, double customYRangeHigh, double customZRangeLow, double customZRangeHigh) {
  bool writeToFile = true;
  int nObjects = objectArray->GetEntriesFast();
  if (nullptr == objectArray || nObjects == 0) {
    std::cout << "ERROR: saveObject called with nonexistent or zero-sized object array" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  if (canvasName == "") {
    std::cout << "ERROR: saveObject called with an empty canvas name" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  if (nullptr == outputFile) {
    std::cout << "outputFile is nullptr; not saving histograms to file." << std::endl;
    writeToFile = false;
  }
  if (!(writeToFile) && outputDocumentName == "") {
    std::cout << "ERROR: saveObject called with no output file and no output document name." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  if (!(customOptStat == -1)) gStyle->SetOptStat(customOptStat);
  if (!(customPaintTextFormat == "")) gStyle->SetPaintTextFormat(customPaintTextFormat.c_str());
  
  TCanvas *canvas = new TCanvas(canvasName.c_str(), canvasName.c_str(), canvas_xPixels, canvas_yPixels);
  canvas->SetBorderSize(0);
  canvas->SetFrameBorderMode(0);
  if(enableLogX) gPad->SetLogx();
  if(enableLogY) gPad->SetLogy();
  if(enableLogZ) gPad->SetLogz();
  
  // TObject *firstObject = objectArray->At(0);
  // if (nullptr == firstObject) {
  //   std::cout << "ERROR: First object in array is null." << std::endl;
  //   std::exit(EXIT_FAILURE);
  // }
  TObject *firstObject = objectArray->At(0);
  if (firstObject->InheritsFrom("TH1")) {
    TH1* firstHistogram = (TH1*)(firstObject);
    if (nullptr == firstHistogram) {
      std::cout << "ERROR: Unable to cast first object in array to TH1." << std::endl;
      std::exit(EXIT_FAILURE);
    }
    std::cout << "Drawing first object..." << std::endl;
    printObjectInfo(firstHistogram);
    if (customPlotOptions != "") firstHistogram->Draw(customPlotOptions.c_str());
    else firstHistogram->Draw();
    if (customXRangeHigh > customXRangeLow) firstHistogram->GetXaxis()->SetRangeUser(customXRangeLow, customXRangeHigh);
    if (customYRangeHigh > customYRangeLow) firstHistogram->GetYaxis()->SetRangeUser(customYRangeLow, customYRangeHigh);
    if (customZRangeHigh > customZRangeLow) firstHistogram->GetZaxis()->SetRangeUser(customZRangeLow, customZRangeHigh);
    if (writeToFile) outputFile->WriteTObject(firstHistogram);
    // Rest of the objects in the objarray need to be drawn with option "same"
    for (int objectIndex = 1; objectIndex < nObjects; ++objectIndex) {
      TObject *currentObject = objectArray->At(objectIndex);
      if (currentObject->InheritsFrom("TH1")) {
        TH1* castObject = (TH1*)(currentObject);
        if (nullptr == castObject) {
          std::cout << "ERROR: Unable to cast object at index " << objectIndex << " to TH1" << std::endl;
          std::exit(EXIT_FAILURE);
        }
        std::cout << "Drawing object at index: " << objectIndex << std::endl;
        printObjectInfo(castObject);
        castObject->Draw("same");
        if (writeToFile) outputFile->WriteTObject(castObject);
      }
      else if (std::string(currentObject->ClassName()) == "TLegend") {
        TLegend *castObject = (TLegend*)(currentObject);
        if (nullptr == castObject) {
          std::cout << "ERROR: Unable to cast object at index " << objectIndex << " to TLegend" << std::endl;
          std::exit(EXIT_FAILURE);
        }
        std::cout << "Drawing legend, object index: " << objectIndex << std::endl;
        printObjectInfo(castObject);
        castObject->Draw();
        if (writeToFile) outputFile->WriteTObject(castObject);
      }
      else {
        std::cout << "ERROR: The first object inherits from TH1, but object at index " << objectIndex << " does not, and is also not a TLegend. Object details:" << std::endl;
        printObjectInfo(currentObject);
        std::exit(EXIT_FAILURE);
      }
    }
  }
  else if (std::string(firstObject->ClassName()) == "TGraph2D") {
    if (nObjects > 1) {
      std::cout << "ERROR: Only one TGraph2D supported at a time for now" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    TGraph2D* graph2D = (TGraph2D*)(firstObject);
    if (nullptr == graph2D) {
      std::cout << "ERROR: Unable to cast to TGraph2D." << std::endl;
      std::exit(EXIT_FAILURE);
    }
    std::cout << "Drawing 2D graph..." << std::endl;
    printObjectInfo(graph2D);
    if (customPlotOptions != "") graph2D->Draw(customPlotOptions.c_str());
    if (customXRangeHigh > customXRangeLow) graph2D->GetXaxis()->SetRangeUser(customXRangeLow, customXRangeHigh);
    if (customYRangeHigh > customYRangeLow) graph2D->GetYaxis()->SetRangeUser(customYRangeLow, customYRangeHigh);
    if (customZRangeHigh > customZRangeLow) graph2D->GetZaxis()->SetRangeUser(customZRangeLow, customZRangeHigh);
    if (writeToFile) outputFile->WriteTObject(graph2D);
  }
  else if (std::string(firstObject->ClassName()) == "TLegend") {
    std::cout << "ERROR: First TObject in array cannot be TLegend, please move it down the array. First object details: " << std::endl;
    printObjectInfo(firstObject);
    std::exit(EXIT_FAILURE);
  }
  else {
    std::cout << "ERROR: First TObject in array has unsupported type. Currently supported: all derived from TH1, and TGraph2D. Problematic object details: " << std::endl;
    printObjectInfo(firstObject);
    std::exit(EXIT_FAILURE);
  }
  if (!(outputDocumentName == "")) canvas->SaveAs(outputDocumentName.c_str());
  if (writeToFile) outputFile->WriteTObject(canvas);
  return canvas;
}

TCanvas* tmROOTSaverUtils::saveSingleObject(TObject *object, std::string canvasName, TFile* outputFile, std::string outputDocumentName, int canvas_xPixels, int canvas_yPixels, int customOptStat, std::string customPaintTextFormat, std::string customPlotOptions, bool enableLogX, bool enableLogY, bool enableLogZ, double customXRangeLow, double customXRangeHigh, double customYRangeLow, double customYRangeHigh, double customZRangeLow, double customZRangeHigh) {
  TObjArray *singleObjectArray = new TObjArray(1);
  singleObjectArray->Add(object);
  return saveObjects(singleObjectArray, canvasName, outputFile, outputDocumentName, canvas_xPixels, canvas_yPixels, customOptStat, customPaintTextFormat, customPlotOptions, enableLogX, enableLogY, enableLogZ, customXRangeLow, customXRangeHigh, customYRangeLow, customYRangeHigh, customZRangeLow, customZRangeHigh);
}

void tmROOTSaverUtils::printObjectInfo(TObject* object) {
  std::cout << "Object info: name = " << object->GetName()
            << ", title = " << object->GetTitle()
            << ", class = " << object->ClassName() << std::endl;
}
