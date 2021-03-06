/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// $Id$
// $MpId: $

//
// Test macro for drawing slat motifs with real contours
// Christian Finck, Subatech
//
#if !defined(__CINT__) || defined(__MAKECINT__)

// MUON includes
#include "AliMpStationType.h"
#include "AliMpStation12Type.h"
#include "AliMpPlaneType.h"
#include "AliMpDataProcessor.h"
#include "AliMpDataMap.h"
#include "AliMpDataStreams.h"
#include "AliMpSt345Reader.h"
#include "AliMpPCB.h"
#include "AliMpSlat.h"
#include "AliMpVPainter.h"
#include "AliMpMotifReader.h"
#include "AliMpMotifType.h"
#include "AliMpMotifPosition.h"
#include "AliMpMotif.h"
#include "AliMpSlatMotifMap.h"
#include "AliMpDataStreams.h"

#include "TVector2.h"
#include "TCanvas.h"

#endif

void testGraphicsMotif(Option_t* motifType = "R43", Double_t padsizex=5.0, Double_t padsizey=0.5)
{
  // Warning : this function leaks memory. But should be fine as only used 
  // interactively to check a few motifs at once...
  //
  AliMpDataProcessor mp;
  AliMpDataMap* dataMap = mp.CreateDataMap("data");
  AliMpDataStreams dataStreams(dataMap);

  AliMp::StationType station = AliMp::kStation345;
  AliMq::Station12Type station12 = AliMq::kNotSt12;
  AliMp::PlaneType plane = AliMp::kBendingPlane;
  
  AliMpMotifReader reader(dataStreams, station, station12, plane);
  AliMpMotifType* type = reader.BuildMotifType(motifType);
  if (!type)
  {
    cerr << "Motif not found" << endl;
    return;
  }
  type->Print("G");
  AliMpMotif* motif = new AliMpMotif(motifType,type,padsizex,padsizey);
  AliMpMotifPosition* pos = new AliMpMotifPosition(0,motif,0,0);
  AliMpVPainter* painter = AliMpVPainter::CreatePainter(pos);
  if (!painter)
  {
    cerr << "Could not get a painter !" << endl;
    return;
  }
  new TCanvas(motifType,motifType);
  painter->Draw("PT");
}

//112230N
//112233NR3
//220000N
//122000NR1
//112200NR2
void testGraphicsSlat(AliMp::PlaneType planeType = AliMp::kBendingPlane, 
	              Option_t* option = "PMCI",
		      Bool_t saveJPG = false)
{
  // P plane
  // M motif
  // P pad
  // I indices

  AliMpDataProcessor mp;
  AliMpDataMap* dataMap = mp.CreateDataMap("data");
  AliMpDataStreams dataStreams(dataMap);

  AliMpSlatMotifMap* motifMap = new AliMpSlatMotifMap();
  AliMpSt345Reader* reader = new AliMpSt345Reader(dataStreams, motifMap);

  // PMPT to get manu channels numbering
  
  Char_t *slatName[19] = {"122000SR1", "112200SR2", "122200S", "222000N", "220000N",
			  "122000NR1", "112200NR2", "122200N",
			  "122330N", "112233NR3", "112230N", "222330N", "223300N", "333000N", "330000N",
			  "112233N", "222333N", "223330N", "333300N"};
			  
  TCanvas *c1[19];
  Char_t c1Name[255];
  Char_t c1NameJpg[255];
  
  for (Int_t i = 0; i < 19; i++) {
    sprintf(c1Name, "%s%d", "c1", i);
    c1[i]= new TCanvas(c1Name,slatName[i],10,10,1200,800);     

    Char_t* slatType = slatName[i];

    AliMpSlat* slat = reader->ReadSlat(slatType, planeType);
    AliMpVPainter* painter = AliMpVPainter::CreatePainter(slat);
    painter->Draw(option);
  
    if (planeType == AliMp::kNonBendingPlane)
      sprintf(c1NameJpg, "%s%s", slatName[i], "_NonBending.jpg");
    else 
      sprintf(c1NameJpg, "%s%s", slatName[i], "_Bending.jpg");
    
    if (saveJPG) c1[i]->Print(c1NameJpg);
  }
}

void testGraphicsPCB(const char* pcbName="S2B",
                      Option_t* option = "MZT",
                      Bool_t savePNG = false)
{
  
  TCanvas* c = new TCanvas(pcbName,pcbName,10,10,1200,800);     
    
  AliMpDataProcessor mp;
  AliMpDataMap* dataMap = mp.CreateDataMap("data");
  AliMpDataStreams dataStreams(dataMap);

  AliMpSlatMotifMap* motifMap = new AliMpSlatMotifMap();
  AliMpSt345Reader* reader = new AliMpSt345Reader(dataStreams, motifMap);
  AliMpPCB* pcb = reader->ReadPCB(pcbName);
  if (!pcb) 
  {
    cerr << "PCB " << pcbName << " does not exist" << endl;
    return;
  }
  
  AliMpVPainter* painter = AliMpVPainter::CreatePainter(pcb);
  painter->Draw(option);
    
  if (savePNG) c->Print(Form("%s-%s.png",pcbName,option));
  
}
