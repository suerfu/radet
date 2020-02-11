
#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

#include "HistoManager.hh"


class TrackingAction : public G4UserTrackingAction{

public:

    TrackingAction( HistoManager* h );
    ~TrackingAction(){ };
    
    virtual void  PreUserTrackingAction(const G4Track*);
    virtual void  PostUserTrackingAction(const G4Track*);


private:
    
    HistoManager* histo;

};


#endif

    
