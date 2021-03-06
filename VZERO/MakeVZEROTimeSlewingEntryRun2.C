void MakeVZEROTimeSlewingEntryRun2()
{

  AliCDBManager *man = AliCDBManager::Instance();
  man->SetDefaultStorage("local://./OCDB");

  // Creation of the time slewing OCDB object
  // x = ADC charge / TDC threshold
  TF1 *slew = new TF1("TimeSlewing","[0]*TMath::Power(x,[1])",1,1024);
  slew->SetParameter(0,8.0);
  slew->SetParameter(1,-5.0e-1);
	
  TObjString str("VZERO Time-slewing correction");

  AliCDBMetaData *md= new AliCDBMetaData(); // metaData describing the object
  md->SetResponsible("Brigitte Cheynis");
  md->SetBeamPeriod(0);
  md->SetAliRootVersion(gSystem->Getenv("ARVERSION"));
  md->SetComment("Time-slewing correction for Run2 used in reconstruction and MC simulation");
  md->PrintMetaData();

  AliCDBStorage *storLoc = man->GetDefaultStorage();
  AliCDBId id("VZERO/Calib/TimeSlewing",215011,AliCDBRunRange::Infinity());

  storLoc->Put(slew, id, md);

  storLoc->Delete();
  delete md;

}
