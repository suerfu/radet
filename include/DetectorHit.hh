#ifndef DETECTORHIT_hh
	#define DETECTORHIT_hh 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"

#include "tls.hh"

class DetectorHit: public G4VHit{

public:

	DetectorHit();

	virtual ~DetectorHit();

	DetectorHit( const DetectorHit& right);

	const DetectorHit& operator =( const DetectorHit& right);

	int operator==( const DetectorHit& right) const;

	inline void * operator new( size_t);

	inline void operator delete( void* aHit);

	virtual void Draw();

	virtual void Print();
	
private:

	//G4String name;

    G4int trackID;
    G4int parentID;
    G4int pid;
        // particle ID

	G4ThreeVector r;
        // location
	G4ThreeVector p;
        // momentum
    G4double t;
        // proper time
    
    G4double ekin;
        // particle's kinetic energy
	G4double edep;
        // energy deposit

public:

	//void SetParticleName( G4String n){name = n;}
	//G4String GetParticleName(){return name;}

    void SetTrackID( G4int i){ trackID = i;}
    G4int GetTrackID(){ return trackID; }
        // used to identify particle

    void SetParentID( G4int i){ parentID = i;}
    G4int GetParentID(){ return parentID; }
        // used to track parent particle

    void SetParticleID( G4int i){ pid = i;}
    G4int GetParticleID(){ return pid; }
        // used to identify type of particle, i.e. electron, gamma, etc.

    void SetPosition( G4ThreeVector i){ r = i;}
    G4ThreeVector GetPosition(){ return r; }

    void SetMomentum( G4ThreeVector i){ p = i;}
    G4ThreeVector GetMomentum(){ return p; }

    void SetGlobalTime( G4double i){ t = i;}
    G4double GetGlobalTime(){ return t; }

	void SetEdep( G4double E){edep = E;}
	G4double GetEdep(){ return edep; }

	void SetEkin( G4double E){ekin = E;}
	G4double GetEkin(){ return ekin; }

};

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;

//extern G4Allocator<DetectorHit> DetectorHitAllocator;

extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;

inline void* DetectorHit::operator new(size_t){
    if( !DetectorHitAllocator )
        DetectorHitAllocator = new G4Allocator<DetectorHit>;
	return (void*) DetectorHitAllocator->MallocSingle();
}

inline void DetectorHit::operator delete( void *aHit){
	DetectorHitAllocator->FreeSingle( (DetectorHit*) aHit);
}

#endif
