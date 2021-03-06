void Sim(const Int_t nevents=10,
	 const Int_t debLevel=0)
{
  //make simulation of MC events and merging
  //with previouly reconstructed Digits from 
  //raw event. We assume they are in dir "Bg"

  AliPHOSSimParam * phosSimParam = AliPHOSSimParam::GetInstance() ;

  AliLog::SetGlobalDebugLevel(debLevel);
  AliSimulation sim;
  sim.SetMakeSDigits("PHOS") ;
  sim.SetMakeDigits("PHOS") ;
//  sim.SetMakeDigitsFromHits("ITS TPC");
//  sim.SetMakeTrigger("PHOS");
  //Set path to reconstricted raw digits
  //and set number of simulated events per one raw
  sim.MergeWith("Bg/galice.root",1) ;
  phosSimParam->SetStreamDigits(1) ; //Mark this stream as digits and not SDigits

  sim.Run(nevents);


}
