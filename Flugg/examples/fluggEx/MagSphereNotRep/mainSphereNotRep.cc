// $Id$
// Flugg tag $Name$

#include "FGeometryInit.hh"
#include "MyDetectorConstruction.hh"

#define flukam flukam_

extern "C" void flukam(const G4int & GeoFlag);

int main() {

  FGeometryInit* theFGeometryInit = FGeometryInit::GetInstance();
  
  theFGeometryInit
    ->setDetConstruction(new MyDetectorConstruction());

//flag for geometry:
// 1 for GEANT4
// 0 for FLUKA
// 2 for Rubbia
    const G4int flag = 1;

//call fortran
    flukam(flag);

//end
  return 0;
}




