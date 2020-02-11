
#ifndef RADIATIONPHYSICS_H 
#define RADIATIONPHYSICS_H 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"


class RadiationPhysics : public G4VUserPhysicsList{

public:

    explicit RadiationPhysics();

    virtual ~RadiationPhysics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

private:

    G4bool IsHadron( G4String );

};

#endif






