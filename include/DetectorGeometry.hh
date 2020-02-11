
#ifndef DETECTORGEOMETRY_H
	#define DETECTORGEOMETRY_H 1

#include "G4VUserDetectorConstruction.hh"

#include "DetectorGeometryMessenger.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "tls.hh"


struct TargetGeometry{

    G4double world_length;
    G4double world_radius;

    G4String target_material;
    G4double target_density;

    G4String shape;

    G4double target_length;
    G4double target_radius;
    G4double coating_length;

    G4String coating_material;
    G4double coating_density;
};



class DetectorGeometry : public G4VUserDetectorConstruction{

public:

	DetectorGeometry();
		//!< Constructor.

	~DetectorGeometry();
		//!< Destructor.
		//
        //
	virtual	G4VPhysicalVolume* Construct();
		//!< should return constructed *PhysicalVolume.

private:

    TargetGeometry geom;
        //!< Structure to hold information about the geometry of the setup.

    DetectorGeometryMessenger* msgr;
        //!< fmessegner
};

#endif
