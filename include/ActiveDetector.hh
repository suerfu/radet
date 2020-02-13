#ifndef DETECTOR_HH
	#define DETECTOR_HH 1

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"

#include "DetectorHit.hh"
#include "G4HCofThisEvent.hh"

#include "G4Step.hh"
#include "G4String.hh"


class ActiveDetector: public G4VSensitiveDetector{

public:

	ActiveDetector( G4String name);

	virtual ~ActiveDetector();

	virtual void Initialize( G4HCofThisEvent* HCE);

	virtual G4bool ProcessHits( G4Step* step, G4TouchableHistory* ROhist);

	virtual void EndOfEvent(G4HCofThisEvent* HCE);

private:

	DetectorHitsCollection* hitsCollection;

	G4int collectionID;
};

#endif
