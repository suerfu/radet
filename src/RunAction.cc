
#include "RunAction.hh"
#include "G4RunManager.hh"


RunAction::RunAction( HistoManager* h ){

	hm = h;

    G4RunManager::GetRunManager()->SetPrintProgress(1000);     
}


RunAction::~RunAction(){}


void RunAction::BeginOfRunAction( const G4Run* run ){

    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    // clear information from previous run and set run ID for the new run for output.
    hm->SetRunID( run->GetRunID() );
}

void RunAction::EndOfRunAction(const G4Run* aRun){

    G4cout << "Run finished.\n";
}
