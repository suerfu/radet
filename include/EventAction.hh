#ifndef EventAction_HH
    #define EventAction_HH 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "RunAction.hh"
#include "HistoManager.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "DetectorHit.hh"
#include "ActiveDetector.hh"

#include <fstream>


class EventAction : public G4UserEventAction {

public:
	EventAction( /*HistoManager* h*/ );

	~EventAction();

public:

	virtual void	BeginOfEventAction(const G4Event*);

	virtual void	EndOfEventAction(const G4Event*);

private:

	RunAction* fRunAction;

//	HistoManager* histo;
};

#endif    
