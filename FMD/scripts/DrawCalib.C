#ifndef __CINT__
#include <AliCDBManager.h>
#include <AliCDBStorage.h>
#include <AliFMDCalibDrawer.h>
#include <TSystem.h>
#include <TGFrame.h>
#include <TGButton.h>
#include <TGLayout.h>
#include <TGButtonGroup.h>
#include <TGNumberEntry.h>
#include <TGTextEntry.h>
#include <TCanvas.h>
#include <TError.h>
#include <TGLabel.h>
#else
class TGMainFrame;
class TGNumberEntry;
class TGTextEntry;
class TGHButtonGroup;
class TGVButtonGroup;
class TGCheckButton;
class TGTextButton;
class TGLayoutHints;
class TCanvas;
class TGLabel;
class TGHorizontalFrame;
class AliFMDCalibDrawer;
class TGGroupFrame;

#endif


class Menu 
{
public:
  TGMainFrame       fMain;
  TGGroupFrame      fSetup;
  TGLabel           fLRun;
  TGNumberEntry     fRun;  
  TGLabel           fLOCDB;
  TGTextEntry       fOCDB; 
  TGTextButton      fInit;
  TGHorizontalFrame fBottom;
  TGGroupFrame      fWhere;
  TGHorizontalFrame fFDet;
  TGLabel           fLDet;
  TGNumberEntry     fDet;
  TGHorizontalFrame fFRing;
  TGLabel           fLRing;
  TGTextEntry       fRing;
  TGHorizontalFrame fFSec;
  TGLabel           fLSec;
  TGNumberEntry     fSec;
  TGHorizontalFrame fFStr;
  TGLabel           fLStr;
  TGNumberEntry     fStr;
  TGVButtonGroup    fSelection;
  TGCheckButton     fPedestal;
  TGCheckButton     fNoise;
  TGCheckButton     fGain;
  TGCheckButton     fDead;
  TGCheckButton     fRate;
  TGCheckButton     fRange;
  TGCheckButton     fThreshold;
  TGTextButton      fDraw;
  TGLayoutHints     fLayout;

  AliFMDCalibDrawer fCD;
  TCanvas*          fCPedestal;
  TCanvas*          fCNoise;
  TCanvas*          fCGain;
  TCanvas*          fCDead;
  TCanvas*          fCRate;
  TCanvas*          fCRange;
  TCanvas*          fCThreshold;

  Menu(const Menu&)
    : fMain(gClient->GetRoot()), 
      fSetup(&fMain, "Setup", kHorizontalFrame), 
      fLRun(&fSetup, "Run: "),
      fRun(&fSetup, 0, 8, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber), 
      fLOCDB(&fSetup, "OCDB:"),
      fOCDB(&fSetup, "run"),       
      fInit(&fSetup, "Init"),
      fBottom(&fMain),
      fWhere(&fBottom, "From where", kVerticalFrame),
      fFDet(&fWhere), 
      fLDet(&fFDet, "Detector:"),
      fDet(&fFDet, -1, 1, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax,
	   -1, 3), 
      fFRing(&fWhere),
      fLRing(&fFRing,"Ring:"),
      fRing(&fFRing, ""), 
      fFSec(&fWhere),
      fLSec(&fFSec,"Sector:"),
      fSec(&fFSec, -1, 1, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax,
	   -1, 39), 
      fFStr(&fWhere),
      fLStr(&fFStr,"Strip:"),
      fStr(&fFStr, -1, 1, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax,
	   -1, 511), 
      fSelection(&fBottom, "what"),
      fPedestal(&fSelection, "Pedestal"), 
      fNoise(&fSelection, "Noise"), 
      fGain(&fSelection, "Gain"), 
      fDead(&fSelection, "Dead"), 
      fRate(&fSelection, "Rate"), 
      fRange(&fSelection, "Range"), 
      fThreshold(&fSelection, "Threshold"),
      fDraw(&fMain, "Draw"),
      fLayout(kLHintsExpandX, 2, 2, 2, 2),
      fCPedestal(0),
      fCNoise(0),
      fCGain(0),
      fCDead(0),
      fCRate(0),
      fCRange(0),
      fCThreshold(0)
  {}
  Menu& operator=(const Menu&) { return *this; }
  

  Menu(Int_t runNo=0)
    : fMain(gClient->GetRoot()), 
      fSetup(&fMain, "Setup", kHorizontalFrame), 
      fLRun(&fSetup, "Run: "),
      fRun(&fSetup, runNo, 8, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber), 
      fLOCDB(&fSetup, "OCDB:"),
      fOCDB(&fSetup, "run"),       
      fInit(&fSetup, "Init"),
      fBottom(&fMain),
      fWhere(&fBottom, "From where", kVerticalFrame),
      fFDet(&fWhere), 
      fLDet(&fFDet, "Detector:"),
      fDet(&fFDet, -1, 1, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax,
	   -1, 3), 
      fFRing(&fWhere),
      fLRing(&fFRing,"Ring:"),
      fRing(&fFRing, ""), 
      fFSec(&fWhere),
      fLSec(&fFSec,"Sector:"),
      fSec(&fFSec, -1, 1, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax,
	   -1, 39), 
      fFStr(&fWhere),
      fLStr(&fFStr,"Strip:"),
      fStr(&fFStr, -1, 1, -1, TGNumberFormat::kNESInteger,
	   TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax,
	   -1, 511), 
      fSelection(&fBottom, "what"),
      fPedestal(&fSelection, "Pedestal"), 
      fNoise(&fSelection, "Noise"), 
      fGain(&fSelection, "Gain"), 
      fDead(&fSelection, "Dead"), 
      fRate(&fSelection, "Rate"), 
      fRange(&fSelection, "Range"), 
      fThreshold(&fSelection, "Threshold"),
      fDraw(&fMain, "Draw"),
      fLayout(kLHintsExpandX, 2, 2, 2, 2),
      fCPedestal(0),
      fCNoise(0),
      fCGain(0),
      fCDead(0),
      fCRate(0),
      fCRange(0),
      fCThreshold(0)
  {
    fSetup.AddFrame(&fLRun,  &fLayout);
    fSetup.AddFrame(&fRun,   &fLayout);
    fSetup.AddFrame(&fLOCDB, &fLayout);
    fSetup.AddFrame(&fOCDB,  &fLayout);
    fSetup.AddFrame(&fInit,  &fLayout);

    fFDet.AddFrame(&fLDet,  &fLayout);
    fFDet.AddFrame(&fDet,   &fLayout);
    fFRing.AddFrame(&fLRing,&fLayout);
    fFRing.AddFrame(&fRing, &fLayout);
    fFSec.AddFrame(&fLSec,  &fLayout);
    fFSec.AddFrame(&fSec,   &fLayout);
    fFStr.AddFrame(&fLStr,  &fLayout);
    fFStr.AddFrame(&fStr,   &fLayout);

    fWhere.AddFrame(&fFDet,       &fLayout);
    fWhere.AddFrame(&fFRing,      &fLayout);
    fWhere.AddFrame(&fFSec,       &fLayout);
    fWhere.AddFrame(&fFStr,       &fLayout);
    
    fBottom.AddFrame(&fWhere,     &fLayout);
    fBottom.AddFrame(&fSelection, &fLayout);

    fMain.AddFrame(&fSetup,      &fLayout);
    fMain.AddFrame(&fBottom,     &fLayout);
    fMain.AddFrame(&fDraw,       &fLayout);

    fRing.SetAlignment(kTextRight);
    fRing.SetInsertMode(TGTextEntry::kReplace);
    fRing.SetMaxLength(1);

    fMain.MapSubwindows();
    fMain.Resize(fMain.GetDefaultSize());
    fMain.MapWindow();
    
    fDraw.Connect("Clicked()", "Menu", this, "Handle()");
    fInit.Connect("Clicked()", "Menu", this, "Init()");

    AliCDBManager* cdb = AliCDBManager::Instance();
    if (cdb->GetDefaultStorage())
      fOCDB.SetText(cdb->GetDefaultStorage()->GetURI().Data());
    fCD.Init(runNo);
  }
  TCanvas* MakeCanvas(const char* name, const char* title)
  {
    TCanvas* ret = new TCanvas(name, title, 1200, 900);
    ret->SetFillColor(0);
    ret->SetFillStyle(0);
    ret->SetBorderMode(0);
    ret->SetBorderSize(0);
    return ret;
  }
  void ClearCanvas(TCanvas* c)
  {
    c->Clear();
    c->SetTopMargin(0.02);
    c->SetRightMargin(0.02);
    c->SetBottomMargin(0.10);
    c->SetLeftMargin(0.10);
    c->cd();
  }
  void Init()
  {
    const Char_t* ocdb = fOCDB.GetText();
    Int_t         run  = fRun.GetIntNumber();
    Info("Init", "Initialising for run %d, OCDB @ %s", run, ocdb);
    fCD.Init(run, ocdb);
  }
  void Handle()
  {
    // static Short_t oD;
    // static Char_t  oR;
    // static Short_t oS;
    // static Short_t oT;
    Short_t d = fDet.GetIntNumber();
    Char_t  r = fRing.GetText()[0];
    Short_t s = fSec.GetIntNumber();
    Short_t t = fStr.GetIntNumber();
    Info("Handle", "D=%d, R=%c, S=%d, T=%d", d, (r == '\0' ? '-' : r), s, t);
    if (fPedestal.IsOn()) { 
      Info("Handle", "Will draw pedestals");
      if (!fCPedestal) fCPedestal = MakeCanvas("peds", "Pedestals");
      ClearCanvas(fCPedestal);
      fCD.DrawPedestals(d, r, s, t);
    }
    if (fNoise.IsOn()) { 
      Info("Handle", "Will draw noises");
      if (!fCNoise) fCNoise = MakeCanvas("noises", "Noises");
      ClearCanvas(fCNoise);
      fCD.DrawNoise(d, r, s, t);
    }
    if (fGain.IsOn()) { 
      Info("Handle", "Will draw gains");
      if (!fCGain) fCGain = MakeCanvas("gains", "Gains");
      ClearCanvas(fCGain);
      fCD.DrawGains(d, r, s, t);
    }
    if (fDead.IsOn()) { 
      Info("Handle", "Will draw deads");
      if (!fCDead) fCDead = MakeCanvas("deads", "Deads");
      ClearCanvas(fCDead);
      fCD.DrawDead(d, r, s, t);
    }
    if (fRate.IsOn()) { 
      Info("Handle", "Will draw rates");
      if (!fCRate) fCRate = MakeCanvas("rates", "Rates");
      fCRate->Clear();
      fCRate->cd();
      fCD.DrawRates(d, r, s, t);
    }
    if (fRange.IsOn()) { 
      Info("Handle", "Will draw ranges");
      if (!fCRange) fCRange = MakeCanvas("ranges", "Ranges");
      fCRange->Clear();
      fCRange->cd();
      fCD.DrawRanges(d, r, s, t);
    }
    if (fThreshold.IsOn()) { 
      Info("Handle", "Will draw thresholds");
      if (!fCThreshold) fCThreshold = MakeCanvas("thresholds", "Thresholds");
      fCThreshold->Clear();
      fCThreshold->cd();
      fCD.DrawThresholds(d, r, s, t);
    }
  }
};

      
void
DrawCalib(Long_t runNo=145167, const char* store=0)
{
#ifdef __CINT__
  gSystem->Load("libFMDutil");
#endif

  AliCDBManager* cdb = AliCDBManager::Instance();
  if (!store || store[0] == '\0') cdb->SetDefaultStorageFromRun(runNo);
  else cdb->SetDefaultStorage(store);
  cdb->SetRun(runNo);

  Menu* m = new Menu(runNo);
  // cd->DrawPedestals(d,r,s,t);
}  
#ifdef __MAKECINT__
#pragma link C++ class Menu;
#endif

#ifndef __CINT__
#include <TApplication.h>
#include <cstdlib>
/*
  To compile: 

  g++ -c `root-config --cflags --glibs` -L$ALICE_ROOT/lib/tgt_${ALICE_TARGET} \
    -I${ALICE_ROOT}/include -I../ -lGeom -lMinuit -lPhysics -lVMC -lXMLParser \
    -lProofPlayer -lSTEERBase -lSTEER -lCDB -lESD -lRAWDatabase -lRAWDatarec \
    -lANALYSIS -lFMDbase -lFMDrec -lFMDutil DrawCalib.C 
*/

int main(int argc, char** argv) { 
  int runNo = 145167;
  if (argc > 1) runNo = atoi(argv[1]);
  
  TApplication app("app", 0, 0);

  DrawCalib(runNo);

  app.Run();

  return 0;
}
#endif

  
