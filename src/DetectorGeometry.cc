
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

#include "ActiveDetector.hh"


DetectorGeometry::DetectorGeometry( ){

    geo_param.AddDoubleParameter("world_x", 1.*m);
    geo_param.AddDoubleParameter("world_y", 1.*m);
    geo_param.AddDoubleParameter("world_z", 1.*m);

    geo_param.AddDoubleParameter("wood_ox", 0.7*m);
    geo_param.AddDoubleParameter("wood_oy", 0.7*m);
    geo_param.AddDoubleParameter("wood_oz", 0.7*m);

    geo_param.AddDoubleParameter("wood_thickness", 1.3*cm);

    geo_param.AddDoubleParameter("quartz_cell_od", 7*cm);
    geo_param.AddDoubleParameter("quartz_cell_thickness", 2.5*mm);
    geo_param.AddDoubleParameter("quartz_cell_length", 7*cm);

    geo_param.AddDoubleParameter("src_dia", 2.54*cm);
    geo_param.AddDoubleParameter("src_thickness", 3.175*mm);
    
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
	
	G4Material* vacuum = nistman->FindOrBuildMaterial("G4_Galactic");
    G4Material* air = nistman->FindOrBuildMaterial( "G4_AIR" );
    G4Material* wood = nistman->FindOrBuildMaterial( "G4_CELLULOSE_CELLOPHANE" );
    G4Material* quartz = nistman->FindOrBuildMaterial( "G4_SILICON_DIOXIDE" );
    G4Material* polyethylene = nistman->FindOrBuildMaterial( "G4_POLYETHYLENE" );

    G4double pc_density = 0.8761*g/cm3;
    G4Element* elemC = new G4Element( "Carbon", "C", 6, 12*g/mole);
    G4Element* elemH = new G4Element( "Hydrogen", "H", 1, 1.01*g/mole);
    G4Material* pceudocumene = new G4Material( "Pceudocumene", pc_density, 2);
    pceudocumene->AddElement( elemC, 9);
    pceudocumene->AddElement( elemH, 12);

    G4Element* elemN = new G4Element( "Nitrogen", "N", 7, 14.*g/mole);
    G4Element* elemO = new G4Element( "Oxygen", "O", 8, 16.*g/mole);
    G4Material* ppo = new G4Material( "PPO", 1.06*g/cm3, 4);
    ppo->AddElement( elemC, 15);
    ppo->AddElement( elemH, 11);
    ppo->AddElement( elemN, 1);
    ppo->AddElement( elemO, 1);

    G4double ppo_conc = 0.003;  // g/mL, or g/cm3
    G4Material* cocktail = new G4Material( "LS_cocktail", pc_density , 2);
    cocktail->AddMaterial( pceudocumene, pc_density/(pc_density+ppo_conc));
    cocktail->AddMaterial( ppo, ppo_conc/(pc_density+ppo_conc));

	//-------------------------world---------------------------------------
    G4double world_hx = geo_param.GetDouble("world_x", 1)/2;
    G4double world_hy = geo_param.GetDouble("world_y", 1)/2;
    G4double world_hz = geo_param.GetDouble("world_z", 1)/2; // G4Box is specified with half length
	G4Box* world_solid  = new G4Box( "world_solid", world_hx, world_hy, world_hz);
	G4LogicalVolume* world_logical  = new G4LogicalVolume( world_solid, air, "world_logical" );
	G4VPhysicalVolume* world_physical = new G4PVPlacement( 0, G4ThreeVector(0,0,0), "world", world_logical, NULL, false, 0);

	//-------------------------wood dark box---------------------------------------
    G4double wood_x = geo_param.GetDouble("wood_ox", 1)/2;
    G4double wood_y = geo_param.GetDouble("wood_ox", 1)/2;
    G4double wood_z = geo_param.GetDouble("wood_ox", 1)/2;
	G4Box* woodbox_solid  = new G4Box( "woodbox_solid", wood_x, wood_y, wood_z);
	G4LogicalVolume* woodbox_logical  = new G4LogicalVolume( woodbox_solid, wood, "woodbox_logical" );
	G4VPhysicalVolume* woodbox_physical = new G4PVPlacement( 0, G4ThreeVector(0,0,0), woodbox_logical, "woodbox", world_logical, false, 0);

	//-------------------------air inside the dark box---------------------------------------
    G4double wood_thick = geo_param.GetDouble("wood_thickness", 0.1);
	G4Box* woodbox_inside_solid  = new G4Box( "woodbox_inside_solid", wood_x-wood_thick, wood_y-wood_thick, wood_z-wood_thick);
	G4LogicalVolume* woodbox_inside_logical  = new G4LogicalVolume( woodbox_inside_solid, air, "woodbox_inside_logical" );
	G4VPhysicalVolume* woodbox_inside_physical = new G4PVPlacement( 0, G4ThreeVector(0,0,0), woodbox_inside_logical, "woodbox_inside", woodbox_logical, false, 0);

	//-------------------------quartz scintillator cell---------------------------------------
    G4double cell_r = geo_param.GetDouble("quartz_cell_od", 1)/2;
    G4double cell_hl = geo_param.GetDouble("quartz_cell_length", 1)/2;
    G4Tubs* qzcell_solid = new G4Tubs( "quartz_cell_solid", 0, cell_r, cell_hl, 0, 2*CLHEP::pi );
    G4LogicalVolume* qzcell_logical = new G4LogicalVolume( qzcell_solid, quartz, "quartz_cell_logical");

    G4ThreeVector qzcell_pos( -wood_x + 3*wood_thick + cell_r, 0, 0 );
    G4VPhysicalVolume* qzcell_physical = new G4PVPlacement(0, qzcell_pos, qzcell_logical, "quartz_cell", woodbox_inside_logical, false, 0);

	//-------------------------scintillator cocktail---------------------------------------
    G4double liqscint_r = cell_r - geo_param.GetDouble("quartz_cell_thickness", 1);
    G4double liqscint_hl = cell_hl - geo_param.GetDouble("quartz_cell_thickness", 1);
    G4Tubs* liqscint_solid = new G4Tubs( "liqscint_solid", 0, liqscint_r, liqscint_hl, 0, 2*CLHEP::pi );
    G4LogicalVolume* liqscint_logical = new G4LogicalVolume( liqscint_solid, cocktail, "liqscint_logical");

    G4VPhysicalVolume* liqscint_physical = new G4PVPlacement(0, G4ThreeVector(0,0,0), liqscint_logical, "liqscint", qzcell_logical, false, 0);

	//-------------------------disk source for calibration---------------------------------------
    G4double src_r = geo_param.GetDouble("src_dia", 1)/2;
    G4double src_hh = geo_param.GetDouble("src_thickness", 1)/2;
    G4Tubs* src_solid = new G4Tubs( "src_solid", 0, src_r, src_hh, 0, 2*CLHEP::pi );
    G4LogicalVolume* src_logical = new G4LogicalVolume( src_solid, polyethylene, "src_logical");

    G4ThreeVector src_pos( -wood_x - src_hh, 0, 0 );
    G4cout << "Source position : " << src_pos << G4endl;
    G4RotationMatrix* src_rot = new G4RotationMatrix;
    src_rot->rotateY(90*deg);
    G4VPhysicalVolume* src_physical = new G4PVPlacement( src_rot, src_pos, src_logical, "src_disk", world_logical, false, 0);

	G4SDManager* sdman = G4SDManager::GetSDMpointer();

	G4String sd_name_liqscint = "pc_liq_scint";
	ActiveDetector* sd_liq_scint = new ActiveDetector( sd_name_liqscint);

	sdman->AddNewDetector( sd_liq_scint );
	liqscint_logical->SetSensitiveDetector( sd_liq_scint );

    #ifdef DEBUG
    	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
        G4cout << "The following detectors are activated:\n";
        sdman->ListTree();
    #endif

	return world_physical;
}


DetectorGeometry::~DetectorGeometry(){}

