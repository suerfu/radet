
#include "DetectorGeometryMessenger.hh"
#include "DetectorGeometry.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"


DetectorGeometryMessenger::DetectorGeometryMessenger( DetectorGeometry* dm ) : G4UImessenger(){

    fdetgeom = dm;

    G4String dir1 = "/test/";
    G4String dir2 = "/test/material";

    fdir1 = new G4UIdirectory( dir1 );
    fdir1->SetGuidance( "Simple test." );

    fdir2 = new G4UIdirectory( dir2 );
    fdir2->SetGuidance( "Detector construction control" );

    fcmd1 = new G4UIcmdWithAString( (dir2+"setMaterial").c_str(), this);
    fcmd1->SetGuidance("Select Material of the Target.");
    fcmd1->SetParameterName( "choice", false);
    fcmd1->AvailableForStates( G4State_PreInit, G4State_Idle);

    fcmd2 = new G4UIcmdWithAString( (dir2+"setChamberMaterial").c_str(), this);
    fcmd2->SetGuidance( "Select Material of the Chamber." );
    fcmd2->SetParameterName( "choice", false);
    fcmd2->AvailableForStates( G4State_PreInit, G4State_Idle);

}


DetectorGeometryMessenger::~DetectorGeometryMessenger(){
  delete fdir1;
  delete fdir2;
  delete fcmd1;
  delete fcmd2;
}


void DetectorGeometryMessenger::SetNewValue(G4UIcommand* command,G4String newValue){

    if( command == fcmd1 ){
//        fdetgeom->SetTargetMaterial(newValue);
        G4cout << "New Value Set!" << G4endl;
    }

//    if( command == fChamMatCmd ){
//        fDetectorConstruction->SetChamberMaterial(newValue);
//    }

//    if( command == fStepMaxCmd ) {
//        fDetectorConstruction->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
//    }
//    // Do not forget to apply fdetgeom -> UpdateGeometry();
}

