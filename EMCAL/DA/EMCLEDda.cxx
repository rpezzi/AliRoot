/*
  EMCAL DA for online calibration: for LED studies
  
  Contact: silvermy@ornl.gov
  Run Type: PHYSICS or STANDALONE
  DA Type: MON 
  Number of events needed: continously accumulating for all runs, rate ~0.1-1 Hz
  Input Files: argument list
  Output Files: RESULT_FILE=EMCALLED.root, to be exported to the DAQ FXS
  fileId:  FILE_ID=EMCALLED    
  Trigger types used: CALIBRATION_EVENT 
*/
/*
  This process reads RAW data from the files provided as command line arguments
  and save results (class itself) in a file (named from RESULT_FILE define - 
  see below).
*/

#define RESULT_FILE  "EMCALLED.root"
#define FILE_ID "signal"
#define AliDebugLevel() -1
#define FILE_SIGClassName "emcCalibSignal"
const int kNRCU = 4;
/* LOCAL_DEBUG is used to bypass daq* calls that do not work locally */
//#define LOCAL_DEBUG 1 // comment out to run normally                                                            
extern "C" {
#include <daqDA.h>
}
#include "event.h" /* in $DATE_COMMON_DEFS/; includes definition of event types */
#include "monitor.h" /* in $DATE_MONITOR_DIR/; monitor* interfaces */

#include "stdio.h"
#include "stdlib.h"

// ROOT includes
#include <TFile.h> 
#include <TROOT.h> 
#include <TPluginManager.h> 
#include <TSystem.h> 

//
//AliRoot includes
//
#include "AliRawReader.h"
#include "AliRawReaderDate.h"
#include "AliRawEventHeaderBase.h"
#include "AliCaloRawStreamV3.h"
#include "AliCaloAltroMapping.h"
#include "AliLog.h"
#include "AliDAQ.h"

//
// EMC calibration-helper algorithm includes
//
#include "AliCaloCalibSignal.h"

/*
  Main routine, EMC signal detector algorithm 
  Arguments: list of DATE raw data files
*/

int main(int argc, char **argv) { // Main routine, EMC signal detector algorithm 

  AliLog::SetClassDebugLevel("AliCaloRawStreamV3",-5);
  AliLog::SetClassDebugLevel("AliRawReaderDate",-5);
  AliLog::SetModuleDebugLevel("RAW",-5);

  if (argc<2) {
    printf("Wrong number of arguments\n");
    return -1;  
  }

  /* magic line - for TStreamerInfo */
  gROOT->GetPluginManager()->AddHandler("TVirtualStreamerInfo",
					"*",
					"TStreamerInfo",
					"RIO",
					"TStreamerInfo()"); 

  /* another magic line - for TMinuit */
  gROOT->GetPluginManager()->AddHandler("ROOT::Math::Minimizer",
                                        "Minuit",
                                        "TMinuitMinimizer",
                                        "Minuit",
                                        "TMinuitMinimizer(const char*)");  

  int i, status;
  
  /* log start of process */
  printf("EMCAL DA started - %s\n",__FILE__);
  
  Int_t emcID = AliDAQ::DetectorID("EMCAL"); // bit 18..

  /* declare monitoring program */
  status=monitorDeclareMp( __FILE__ );
  if (status!=0) {
    printf("monitorDeclareMp() failed : %s\n",monitorDecodeError(status));
    return -1;
  }
  /* define wait event timeout - 1s max */
  monitorSetNowait();
  monitorSetNoWaitNetworkTimeout(1000);
  
  /* Retrieve mapping files from DAQ DB */ 
  const char* mapFiles[kNRCU] = {"RCU0A.data","RCU1A.data","RCU0C.data","RCU1C.data"};
  
  for(Int_t iFile=0; iFile<kNRCU; iFile++) {
    int failed = daqDA_DB_getFile(mapFiles[iFile], mapFiles[iFile]);
    if(failed) { 
      printf("Cannot retrieve file %d : %s from DAQ DB. Exit now..\n",
	     iFile, mapFiles[iFile]);
#ifdef LOCAL_DEBUG
#else
      return -1;
#endif
    }
  }
  
  /* Open mapping files */
  AliCaloAltroMapping *mapping[kNRCU];
  TString path = "./";
  path += "RCU";
  TString path2;
  TString side[] = {"A","C"};//+ and - pseudorapidity supermodules
  for(Int_t j = 0; j < 2; j++){
    for(Int_t i = 0; i < 2; i++) {
      path2 = path;
      path2 += i;
      path2 += side[j]; 
      path2 += ".data";
      mapping[j*2 + i] = new AliCaloAltroMapping(path2.Data());
    }
  }
  
  /* Retrieve cut=parameter file from DAQ DB */ 
  const char* parameterFile = {"EMCALLEDda.dat"};
  
  int failed = daqDA_DB_getFile(parameterFile, parameterFile);
  if (failed) { 
    printf("Cannot retrieve file : %s from DAQ DB. Exit now..\n",
	   parameterFile);
#ifdef LOCAL_DEBUG
#else
    return -1;
#endif
  }
  
  /* set up our analysis classes */  
  AliCaloCalibSignal * calibSignal = new AliCaloCalibSignal(AliCaloCalibSignal::kEmCal); 
  calibSignal->SetAltroMapping( mapping );
  calibSignal->SetParametersFromFile( parameterFile );
  
  AliRawReader *rawReader = NULL;
  int nevents=0;
  
  /* loop over RAW data files */
  for ( i=1; i<argc; i++ ) {
    
    /* define data source : this is argument i */
    printf("Processing file %s\n", argv[i]);
    status=monitorSetDataSource( argv[i] );
    if (status!=0) {
      printf("monitorSetDataSource() failed. Error=%s. Exiting ...\n", monitorDecodeError(status));
      return -1;
    }
    
    /* read until EOF */
    struct eventHeaderStruct *event;
    eventTypeType eventT;

    for ( ; ; ) { // infinite loop
      
      /* check shutdown condition */
      if (daqDA_checkShutdown()) {break;}
      
      /* get next event (blocking call until timeout) */
      status=monitorGetEventDynamic((void **)&event);
      if (status==MON_ERR_EOF) {
	printf ("End of File %d (%s) detected\n", i, argv[i]);
	break; /* end of monitoring file has been reached */
      }
      if (status!=0) {
	printf("monitorGetEventDynamic() failed : %s\n",monitorDecodeError(status));
	break;
      }
      
      /* retry if got no event */
      if (event==NULL) {
	continue;
      }
      eventT = event->eventType; /* just convenient shorthand */
      /* only look at calibration events */
      if ( eventT != calibrationEvent ) {
	free(event);    
	continue;
      }
      
      /* only look at events where EMCAL was included */
      if (! TEST_DETECTOR_IN_PATTERN(event->eventDetectorPattern, emcID) ) {
	free(event);    
	continue;
      }

      nevents++; // count how many acceptable events we have
      
      //  Signal calibration
      rawReader = new AliRawReaderDate((void*)event);
      calibSignal->SetRunNumber(event->eventRunNb);
      calibSignal->ProcessEvent(rawReader);
      delete rawReader;
      
      /* free resources */
      free(event);    
      
    } //until EOF
  } // loop over files
  
  // calculate average values also, for the LED info
  calibSignal->SetUseAverage(kTRUE);
  calibSignal->Analyze();
  
  // by default, we only save the full info in debug mode  
#ifdef LOCAL_DEBUG
#else
  // reset the full trees, when we are not in debug mode
  calibSignal->GetTreeAmpVsTime()->Reset();
  calibSignal->GetTreeLEDAmpVsTime()->Reset();
#endif
  
  //
  // write class to rootfile
  //
  
  printf ("%d calibration events processed.\n",nevents);
  
  TFile f(RESULT_FILE, "recreate");
  if (!f.IsZombie()) { 
    f.cd();
    calibSignal->Write(FILE_SIGClassName);
    f.Close();
    printf("Objects saved to file \"%s\" as \"%s\".\n", 
	   RESULT_FILE, FILE_SIGClassName); 
  } 
  else {
    printf("Could not save the object to file \"%s\".\n", 
	   RESULT_FILE);
  }
  
  //
  // closing down; see if we can delete our analysis helper(s) also
  //
  delete calibSignal;
  for(Int_t iFile=0; iFile<kNRCU; iFile++) {
    if (mapping[iFile]) delete mapping[iFile];
  }
  
  /* store the result file on FES */
#ifdef LOCAL_DEBUG
#else
  status = daqDA_FES_storeFile(RESULT_FILE, FILE_ID);
  status = daqDA_DB_storeFile(RESULT_FILE, RESULT_FILE); // also to DAQ DB
#endif
  
  return status;
}
