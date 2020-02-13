
#include "EventAction.hh"

#include <cmath>
#include <vector>

using std::vector;



EventAction::EventAction( /*HistoManager* h):histo(h*/){}


EventAction::~EventAction(){}


void EventAction::BeginOfEventAction(const G4Event* evt){

//    histo->clear();
//    histo->SetEventID( evt->GetEventID() );

}


void EventAction::EndOfEventAction(const G4Event* evt){
    
    // retrieve detector hit information from SD manager.
	G4SDManager* sdman = 0;
	sdman = G4SDManager::GetSDMpointer();
	if( sdman==0 ) {
		G4cout<<"Pointer to sensitive detector cannot be retrieved. Probably it is not enabled.\n";
		return;
	}

	vector<G4String> det_names;
	vector<G4double> det_energies;

	det_names.push_back( "pc_liq_scint" );


    //G4VHitsCollection* hc = evt->GetHCofThisEvent()->GetHC(0);
    //G4cout << "    "  
    //       << hc->GetSize() << " hits stored in this event" << G4endl;
        // in multithreading mode, above lines cause seg fault.
    
    // iterate over detector hits

	for( unsigned int n=0; n<det_names.size(); n++){

		G4int collectionID = -1;

        #ifdef DEBUG
            G4cout << "Inspecting detector name " << det_names[n] << G4endl;
            G4cout << "Retrieving collection ID from " + det_names[n] + "_hitcol" << G4endl;
            G4cout << "Sensitive detector includes the following items: " << G4endl;
            sdman->ListTree();
            G4cout << "With the following hit collection names: " << G4endl;

            for( int i=0; i<sdman->GetHCtable()->entries(); i++ )
                G4cout << '\t' << sdman->GetHCtable()->GetHCname(i)<<G4endl;
        #endif

		collectionID = sdman->GetCollectionID( det_names[n] + "_hitcol");

		if(collectionID ==-1){
            #ifdef DEBUG
    			G4cout<<"Collection name is wrong...\nExiting...\n";
            #endif
            return;
		}
        else{
            #ifdef DEBUG
                G4cout << "Collection ID retrieved: " << collectionID << G4endl;
            #endif
        }

		G4int NofHits = 0;
		DetectorHit* hit;
        TrackInfo data;
        G4double edep = 0;

		if(evt->GetHCofThisEvent()){
			DetectorHitsCollection* Detector_HC = (DetectorHitsCollection*)evt->GetHCofThisEvent()->GetHC(collectionID);
			if(Detector_HC){
				NofHits = Detector_HC->GetSize();
			}

			for( int i=0; i<NofHits; i++){
				hit = (*Detector_HC)[i];

                data.ID = hit->GetTrackID();
                data.parentID = hit->GetParentID();
                data.pid = hit->GetParticleID();

                data.rf = hit->GetPosition();
                data.pf = hit->GetMomentum();

                data.Ef = hit->GetEkin();
                data.tf = hit->GetGlobalTime();

                //histo->update( data );
                //histo->add_edep( data.ID, hit->GetEdep(), det_names[n] );
                edep += hit->GetEdep();
                G4cerr << edep/keV << G4endl;
			}
		}
	}

    //histo->write();

}
