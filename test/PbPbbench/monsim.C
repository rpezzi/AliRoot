void monsim(Int_t nev=1){ 
  gSystem->Load("liblhapdf");
  gSystem->Load("libEGPythia6");
  gSystem->Load("libpythia6");
  gSystem->Load("libAliPythia6");
  gSystem->Load("libgeant321");
  
  gSystem->Load("libHIJING");
  gSystem->Load("libTHijing");

  // MonaLisa monitoring
  gSystem->Load("libNet");
  gSystem->Load("libMonaLisa");

  new TMonaLisaWriter("aliendb3.cern.ch", "Simulation PbPb", gSystem->Getenv("TEST_PLATFORMID"), gSystem->Getenv("TEST_PLATFORMID"), "global");

  gROOT->LoadMacro("sim.C");
  sim(nev);
  if (gMonitoringWriter) gMonitoringWriter->SendProcessingProgress(1,1,kTRUE);  

  // Send the size of the raw.root file

  FileStat_t buf;
  gSystem->GetPathInfo("./raw.root",buf);

  TList *valuelist = new TList();
  valuelist->SetOwner(kTRUE);

  TMonaLisaValue* valdouble = new TMonaLisaValue("raw.root size",buf.fSize);
  valuelist->Add(valdouble);

  if (gMonitoringWriter) gMonitoringWriter->SendParameters(valuelist);
  delete valuelist;

  printf("#Test finished successfully#\n");
} 
