
#include "DetectorGeometry.hh"

#include "G4NistManager.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"

#include "Detector.hh"


DetectorGeometry::DetectorGeometry( ){
    geom = TargetGeometry();

    msgr = new DetectorGeometryMessenger( this );
}


G4VPhysicalVolume* DetectorGeometry::Construct(){


	//-------------------------Cleanup old geometry-----------------------
	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();

	//-------------------------Define materials used----------------------
	G4NistManager* nistman = G4NistManager::Instance();
	
	G4Material* Vacuum = nistman->FindOrBuildMaterial("G4_Galactic");
    G4Material* TargetMat = nistman->FindOrBuildMaterial( "G4_W" );
    G4Material* CoatingMat = nistman->FindOrBuildMaterial( geom.coating_material);


	//-------------------------world---------------------------------------
	G4Tubs* world_solid  = new G4Tubs( "world_solid", 0*m, 10*cm, 1*m, 0, 2*CLHEP::pi);
	G4LogicalVolume* world_logical  = new G4LogicalVolume( world_solid, TargetMat, "world_logical" );
	G4VPhysicalVolume* world_physical = new G4PVPlacement( 0, G4ThreeVector(0,0,0), "world_physical", world_logical, NULL, false, 0);

    /*
	//-------------------------target body--------------------------------------

	G4LogicalVolume* target_logical;
	G4LogicalVolume* coating_logical;

    if( geom.shape=="square" ){
	    G4Box* target_solid = new G4Box( "target_solid", geom.target_radius, geom.target_radius, geom.target_length/2);
        G4Box* coating_solid = new G4Box( "coating_solid", geom.target_radius, geom.target_radius, geom.coating_length/2);

        target_logical = new G4LogicalVolume( target_solid, TargetMat, "target_logical");
        coating_logical = new G4LogicalVolume( coating_solid, CoatingMat, "coating_logical");
    }
    else{
	    G4Tubs* target_solid = new G4Tubs( "target_solid", 0, geom.target_radius, geom.target_length/2, 0, 2*CLHEP::pi);
	    G4Tubs* coating_solid = new G4Tubs( "coating_solid", 0, geom.target_radius, geom.coating_length/2, 0, 2*CLHEP::pi);

        target_logical = new G4LogicalVolume( target_solid, TargetMat, "target_logical");
        coating_logical = new G4LogicalVolume( coating_solid, CoatingMat, "coating_logical");
    }

	G4VPhysicalVolume* target_physical = new G4PVPlacement( 0, G4ThreeVector(0,0,0), target_logical, "target", world_logical, false, 0);

	G4VPhysicalVolume* coating_physical = new G4PVPlacement( 0, G4ThreeVector(0,0,(geom.target_length+geom.coating_length)/2), coating_logical, "coating", world_logical, false, 0);


    //--------------------make both target and coating volume sensitive to incoming particles-----------------

	G4SDManager* sdman = G4SDManager::GetSDMpointer();

	G4String sd_coating_name = "sd_coating";
	Detector* sd_coating = new Detector( sd_coating_name);

	sdman->AddNewDetector( sd_coating);
	coating_logical->SetSensitiveDetector( sd_coating );
    G4cout << sd_coating_name << " set as active detector\n";

//	G4String sd_target_name = "sd_target";
//	Detector* sd_target = new Detector( sd_target_name);
//    G4cout << sd_target_name << " set as active detector\n";

//	sdman->AddNewDetector( sd_target);
//	target_logical->SetSensitiveDetector( sd_target );

//    #ifdef DEBUG
    	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
        G4cout << "The following detectors are activated:\n";
        sdman->ListTree();
//    #endif
    */
	return world_physical;
}


DetectorGeometry::~DetectorGeometry(){}

