
#include "TrackingAction.hh"
#include "HistoManager.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


TrackingAction::TrackingAction( HistoManager* h ):G4UserTrackingAction(){
    histo = h;
}


void TrackingAction::PreUserTrackingAction(const G4Track* track){

    G4int id = track->GetTrackID();

    if( ! histo->find(id) ){
        TrackInfo data;

        data.ID = track->GetTrackID();
        data.parentID = track->GetParentID();
        data.pid = track->GetDynamicParticle()->GetPDGcode();

        data.ri = data.rf = track->GetPosition();
        data.pi = data.pf = track->GetMomentumDirection();
            // this method is called when the track is just created.
            // it is OK even if the final state is not correct
            // since initial state will no longer be updated, but final state will be by event action

        data.Ei = data.Ef = track->GetKineticEnergy();

        data.ti = data.tf = track->GetGlobalTime();

        data.edep_coating = data.edep_target = 0;

        histo->update( data, true );    
        //G4cout << "Inserting initial track --- " << data.ID << ' ' << data.parentID << ' ' << data.ri << ' ' << data.pi << ' ' << data.Ei << ' ' << data.ti << G4endl;
    }
  
}


void TrackingAction::PostUserTrackingAction(const G4Track* track){
}



