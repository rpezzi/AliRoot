//-*- Mode: C++ -*-
// $Id: AliHLTCALOConstants.h $

//* This file is property of and copyright by the ALICE HLT Project        * 
//* ALICE Experiment at CERN, All rights reserved.                         *
//* See cxx source for full Copyright notice                               */

/// @file   AliHLCaloConstants.h
/// @author Svein Lindal
/// @date   
/// @brief  Class containing constants for PHOS and EMCAL
///         loaded libraries


#include "Rtypes.h"
#include "TString.h"
#ifndef ALIHLTCALOCONSTANTS_H
#define ALIHLTCALOCONSTANTS_H

// #define  ALTROMAXSAMPLES   1008  /**<The maximum number of samples of the ALTRO*/ 
// #define  ALTROMAXPRESAMPLES  15  //Constant 
// #define  NGAINS  2
// #define  HIGHGAIN  1
// #define  LOWGAIN  0
// #define  MAXBINVALUE  1023 //Constant
// #define  MAXHOSTS 20 // For the onlinedisplay
// #define  DEFAULTEVENTPORT 42001


// #define TEST  AliHLTCaloConstants::GetTEST()


class AliHLTCaloConstants
{

private:
  // extern static int TEST;
  //  const static int TEST = 10;
  // const int TEST = 10;
  // int GetTEST() const {  return TEST; };
public:
  // const static int fgkTEST = 10;
  const static int  fgkALTROMAXSAMPLES    =  1008;    /**<The maximum number of samples of the ALTRO*/   
  const static int  fgkALTROMAXPRESAMPLES =  15;  //Constant 
  const static int  fgkNGAINS = 2;
  const static int  fgkHIGHGAIN = 1;
  const static int  fgkLOWGAIN = 0;
  const static int  fgkMAXBINVALUE = 1023; //Constant
  const static int  fgkMAXHOSTS = 20; // For the onlinedisplay
  const static int  fgkDEFAULTEVENTPORT = 42001;

  //  const static int GetTEST()  {  return fgkTEST; }; 
  AliHLTCaloConstants();
  virtual ~AliHLTCaloConstants();
   // virtual void InitConstants() = 0; 

  static  Int_t GetALTROMAXSAMPLES()    { return  fgkALTROMAXSAMPLES; }; 
  static  Int_t GetNGAINS()       { return fgkNGAINS; }; 	
  static  Int_t GetHIGHGAIN()     { return fgkHIGHGAIN; };
  static  Int_t GetLOWGAIN()      { return fgkLOWGAIN; }; 
  static  Int_t GetMAXBINVALUE()  { return fgkMAXBINVALUE; }; 	

  
  Int_t GetNDATATYPES() const { return fkNDATATYPES; } ; 				       	
  Int_t GetCSPSPERFEE() const {  return fkCSPSPERFEE; }; 			       		
  
  Int_t GetNZROWSRCU() const { return fkNZROWSRCU;}
  Int_t GetNXCOLUMNSRCU() const { return fkNXCOLUMNSRCU;} 
  Int_t GetNZROWSMOD() const { return fkNZROWSMOD;} 
  Int_t GetNXCOLUMNSMOD() const { return fkNXCOLUMNSMOD;} 
  Int_t GetNMODULES() const { return fkNMODULES;} 
  Int_t GetNRCUS() const { return fkNRCUS;} 
  Int_t GetNRCUSPERMODULE() const { return fkNRCUSPERMODULE;} 
  Int_t GetNRCUSPERTOTAL() const { return fkNRCUSPERTOTAL;} 
  Int_t GetNFEECS() const { return fkNFEECS;} 
  Int_t GetDDLOFFSET() const { return fkDDLOFFSET; }
  Int_t GetNALTROS() {  return fkNALTROS; }; 					
  Int_t GetNALTROCHANNELS() const { return fkNALTROCHANNELS; }; 					
  Int_t GetNBRANCHES() const { return fkNBRANCHES; }; 					
 
  //   static AliHLTCaloConstants* Instance();

   // EMCAL specific
  Float_t GetCELLSTEP() const { return fkCELLSTEP; }
  Float_t GetMAXCELLSTEPETA() const { return fkMAXCELLSTEPETA; }  //FR
  Float_t GetMINCELLSTEPETA() const { return fkMINCELLSTEPETA; }  //FR
  Float_t GetCELLSTEPPHI() const { return fkCELLSTEPPHI; }        //FR
  Float_t GetCELLHEIGHT() const { return fkCELLHEIGHT; }        //FR
  Float_t GetCELLANGLE() const { return fkCELLANGLE; }        //FR
  Float_t GetRADLENGTH() const { return fkRADLENGTH; }        //FR
  Float_t GetCRITICENERGY() const { return fkCRITICENERGY; }        //FR
  Float_t GetCJ() const { return fkCJ;} //FR
  //  virtual Int_t GetDDLOFFSET() const = 0;
  TString GetDETNAME() { return fkDETNAME; };
  
  //  static AliHLTCaloConstants *fgInstance;

  // AliHLTCaloConstants *fgInstance;


protected:
  

  TString fkDETNAME;
  Float_t fkCELLSTEP; //Constant
  Float_t fkMAXCELLSTEPETA;
  Float_t fkMINCELLSTEPETA;
  Float_t fkCELLSTEPPHI;
  Float_t fkCELLHEIGHT;
  Float_t fkCELLANGLE;
  Float_t fkRADLENGTH;
  Float_t fkCRITICENERGY;
  Float_t fkCJ;
  Int_t fkDDLOFFSET;   //Constant

  Int_t fkNZROWSRCU; /**<Number of rows per module*/ 
  Int_t fkNXCOLUMNSRCU;//Constant
  Int_t fkNZROWSMOD;  /**<Number of rows per module*/ 
  Int_t fkNXCOLUMNSMOD;  /**<Number of columns per module*/ 
  Int_t fkNMODULES;   /**<Number of modules of the EMCAL detector*/
  Int_t fkNRCUS;   /**<Number of RCUs per Module*/
  Int_t fkNRCUSPERMODULE;   /**<Number of RCUs per Module*/
  Int_t fkNRCUSPERTOTAL; /**<Total number of RCUs for EMCAL*/
  Int_t fkNFEECS;  /**<Number of Frontend cards per branch*/

private:
  const Int_t fkNALTROS;  /**<Number of ALTROs per frontend card*/
  const Int_t fkNALTROCHANNELS;  //Constant
  const Int_t fkNBRANCHES; //Constant
  const Int_t fkCSPSPERFEE; //Constant
  const Int_t fkNDATATYPES;          //Constant
  const Int_t fkMAXHOSTS;                  //Constant
  const Int_t fkDEFAULTEVENTPORT;          //Constant
  ClassDef(AliHLTCaloConstants, 1);
};


#define  ALTROMAXSAMPLES    AliHLTCaloConstants::fgkALTROMAXSAMPLES    /**<The maximum number of samples of the ALTRO*/   
#define  ALTROMAXPRESAMPLES AliHLTCaloConstants::fgkALTROMAXPRESAMPLES  //Constant 
#define  NGAINS             AliHLTCaloConstants::fgkNGAINS
#define  HIGHGAIN           AliHLTCaloConstants::fgkHIGHGAIN
#define  LOWGAIN            AliHLTCaloConstants::fgkLOWGAIN
#define  MAXBINVALUE        AliHLTCaloConstants::fgkMAXBINVALUE //Constant
#define  MAXHOSTS           AliHLTCaloConstants::fgkMAXHOSTS // For the onlinedisplay
#define  DEFAULTEVENTPORT   AliHLTCaloConstants::fgkDEFAULTEVENTPORT

//#define TEST  AliHLTCaloConstants::GetTEST()
//#define TEST  AliHLTCaloConstants::TEST



#endif
