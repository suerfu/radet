
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorGeometry.hh"
#include "RadiationPhysics.hh"
#include "PrimaryGeneratorAction.hh"

void PrintHelp();


int main(int argc,char** argv){

    // first check commandline arguments to see if need to print usage.
	for(int i=1; i<argc;i++){
        if( strcmp( argv[i], "--help")==0 || strcmp( argv[i], "-h")==0 ){
            PrintHelp();
            return 0;
        }
    }

    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    G4RunManager* runman = new G4RunManager;

    // Geometry
	runman->SetUserInitialization( new DetectorGeometry() );

    // Physics list
    RadiationPhysics* phylist = new RadiationPhysics();
    runman->SetUserInitialization( phylist );

    // User customization
    runman->SetUserAction( new PrimaryGeneratorAction() );
    //runman->SetUserInitialization( new ActionInitialization( ) );
    

    G4UImanager* uiman = G4UImanager::GetUIpointer();

    // Detect interactive mode (if no arguments) and define UI session
    if ( argc == 1 ) {
        G4UIExecutive* ui = new G4UIExecutive( argc, argv);
        uiman->ApplyCommand( "/control/execute init.mac" );
            // execute default macro
        ui->SessionStart();
        delete ui;
    }
    else{
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        uiman->ApplyCommand( command+filename );
    }

    delete runman;
    
    return 0;
}



void PrintHelp(){
    G4cout << "Help!!!" << G4endl;
}
