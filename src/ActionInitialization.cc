
#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"


ActionInitialization::ActionInitialization( HistoManager* histo) : G4VUserActionInitialization(), h(histo){}


ActionInitialization::~ActionInitialization(){}


void ActionInitialization::BuildForMaster() const{
//    SetUserAction( new RunAction( h ) );
}


void ActionInitialization::Build() const{
    SetUserAction( new PrimaryGeneratorAction );
//    SetUserAction( new RunAction( h ) );
//    SetUserAction( new EventAction( h ) );
//    SetUserAction( new TrackingAction( h ) );
}  

