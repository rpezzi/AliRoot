#ifndef ALI_TPC_COMPOSED_CORRECTION_H
#define ALI_TPC_COMPOSED_CORRECTION_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/// \class AliTPCComposedCorrection
/// \brief AliTPCComposedCorrection class
///
/// This class is creating a correction that is composed out of smaller
/// corrections.
/// There are two ways the sub-corrections can be combined into this one:
/// 1. kParallel: All corrections are applied at the given position x and
///   the dx terms are summed up (this commutes).
/// 2. kQueue: The corrections are called in order. The first one at the
///   given position x resulting in dx1, the second one is called at
///   the corrected position (x+dx1) resulting in dx2, the third one
///   is then called at position (x+dx1+dx2) and so forth. dx=dx1+dx2+...
///   is returned.
/// For the inverse of the correction this is taken into account by reversing
/// the order the corrections are applied in the kQueue case (no issue for
/// kParallel).
///
/// \author Magnus Mager, Stefan Rossegger, Jim Thomas
/// \date 27/04/2010

#include "AliTPCCorrection.h"
#include "TVectorD.h"

class TCollection;
class TTimeStamp;

class AliTPCComposedCorrection : public AliTPCCorrection {
public:
  enum CompositionType {kParallel,kQueue, kQueueResidual};

  AliTPCComposedCorrection();
  AliTPCComposedCorrection(TCollection *corrections,CompositionType mode);
  virtual ~AliTPCComposedCorrection();
  virtual Bool_t AddCorrectionCompact(AliTPCCorrection* corr, Double_t weight);
  void SetOmegaTauT1T2(Float_t omegaTau,Float_t t1,Float_t t2);

  TCollection* GetCorrections() const {return fCorrections;}
  void SetCorrections(const TCollection *corrections) {fCorrections=(TCollection*)corrections;}
  CompositionType GetMode() const {return fMode;}
  void SetMode(CompositionType mode) {fMode=mode;}

  virtual void GetCorrection(const Float_t x[],const Short_t roc,Float_t dx[]);
  virtual void GetDistortion(const Float_t x[],const Short_t roc,Float_t dx[]);
  virtual  AliTPCCorrection * GetSubCorrection(Int_t ipos);
  virtual  AliTPCCorrection * GetSubCorrection(const char * cname);

  virtual void Print(Option_t* option="") const;

  // initialization and update functions
  virtual void Init();
  virtual void Update(const TTimeStamp &timeStamp);
  void SetWeights(TVectorD * weights){fWeights= (TVectorD*) weights->Clone();}
  const  TVectorD * GetWeights() const {return fWeights;}

private:
  TCollection *fCorrections; ///< The corrections this one is composed of.
  CompositionType fMode;     ///< The way to apply the corrections (see general class documentation)
  TVectorD        *fWeights;  ///< optional vector with weights - used for fit benchmarking
  AliTPCComposedCorrection & operator = (const AliTPCComposedCorrection &); // dummy assignment operator
  AliTPCComposedCorrection(const AliTPCComposedCorrection&); //dummy copy contructor

  /// \cond CLASSIMP
  ClassDef(AliTPCComposedCorrection,2);
  /// \endcond
};


#endif
