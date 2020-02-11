#ifndef RunAction_h
	#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "HistoManager.hh"

//class G4Run;
//class G4ParticleDefinition;
//class G4Material;

class RunAction : public G4UserRunAction
{
public:
	RunAction( HistoManager* );

	~RunAction();
public:

	virtual void BeginOfRunAction(const G4Run*);

	virtual void EndOfRunAction(const G4Run*);

private:

	HistoManager* hm;
};

#endif
