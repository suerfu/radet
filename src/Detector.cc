
#include "Detector.hh"
#include "DetectorHit.hh"


Detector::Detector(G4String sd_name):G4VSensitiveDetector( sd_name ){

	collectionID = -1;
	collectionName.insert( sd_name + "_hitcol" );
    G4cout << "Setting " << sd_name << " as active detector with collection name " << sd_name+"_hitcol"<<G4endl;
    //detector_name = sd_name;
}


Detector::~Detector(){}


void Detector::Initialize(G4HCofThisEvent* HCE){

	//if(collectionID<0)
	//	collectionID = GetCollectionID(0);

	hitsCollection = new DetectorHitsCollection( "detector", collectionName[0]);

    collectionID = G4SDManager::GetSDMpointer()->GetCollectionID( collectionName[0] );
	HCE->AddHitsCollection( collectionID, hitsCollection);
}


G4bool Detector::ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist){

	DetectorHit* aHit = new DetectorHit();

    aHit->SetTrackID( aStep->GetTrack()->GetTrackID() );
    aHit->SetParentID( aStep->GetTrack()->GetParentID());
	aHit->SetParticleID(aStep->GetTrack()->GetDynamicParticle()->GetPDGcode());

	aHit->SetPosition( aStep->GetPostStepPoint()->GetPosition());
	aHit->SetPosition( aStep->GetPostStepPoint()->GetMomentum());
    aHit->SetGlobalTime( aStep->GetPostStepPoint()->GetGlobalTime());

    aHit->SetEkin(aStep->GetPostStepPoint()->GetKineticEnergy());
	aHit->SetEdep(aStep->GetTotalEnergyDeposit());

	hitsCollection->insert( aHit );

	return true;
}


void Detector::EndOfEvent(G4HCofThisEvent* HCE){
}
