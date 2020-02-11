#ifndef TRACKINFO_H
	#define TRACKINFO_H 1


#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


// Structure that contains output information for each particle/track.

struct TrackInfo{

    int ID;
        // particle ID
    G4int parentID;
        // particle parentID. 0 if it is primary
    G4int pid;
        // particle ID, Geant4's PDG encoding to see particle type.

    G4ThreeVector ri;
        // particle initial position
    G4ThreeVector pi;
        // particle initial momentum
    G4double Ei;
        // particle initial energy
    G4double ti;
        // particle initial time
    
    G4ThreeVector rf;
        // particle final position, either before killed or before exiting the sensitive detector
    G4ThreeVector pf;
        // particle final momentum
    G4double Ef;
        // final energy
    G4double tf;
        // particle final time

    G4double edep_coating;
        // energy deposit in coating material
    G4double edep_target;
        // energy deposit in target material

};

#endif


