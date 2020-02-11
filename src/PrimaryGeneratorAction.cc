
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"

#include "PrimaryGeneratorAction.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction(){

    fParticleGun = new G4GeneralParticleSource ();

}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){

    delete fParticleGun;

}

void PrimaryGeneratorAction::GeneratePrimaries( G4Event* anEvent ){

    fParticleGun->GeneratePrimaryVertex(anEvent);
}



