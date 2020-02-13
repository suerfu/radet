
#ifndef DETECTORGEOMETRY_H
	#define DETECTORGEOMETRY_H 1

#include "G4VUserDetectorConstruction.hh"

#include "DetectorGeometryMessenger.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "tls.hh"

#include <string>
#include <map>

class DetectorGeometryParameter{

public:

    DetectorGeometryParameter(){}

    ~DetectorGeometryParameter(){}

    void AddIntParameter( std::string ss, G4int a){
        par_int[ss] = a;
    }
    
    bool FindIntParameter( std::string ss ){
        return par_int.find(ss)!=par_int.end();
    }

    int GetInt( std::string ss, int def){
        if( FindIntParameter(ss) )
            return par_int[ss];
        else
            return def;
    }

    void AddDoubleParameter( std::string ss, G4double a){
        par_double[ss] = a;
    }
    
    bool FindDoubleParameter( std::string ss ){
        return par_double.find(ss)!=par_double.end();
    }

    G4double GetDouble( std::string ss, G4double def){
        if( FindDoubleParameter(ss) )
            return par_double[ss];
        else
            return def;
    }

    void AddVectorParameter( std::string ss, G4ThreeVector a){
        par_vector[ss] = a;
    }

    bool FindVectorParameter( std::string ss ){
        return par_vector.find(ss)!=par_vector.end();
    }

    G4ThreeVector GetVector( std::string ss, G4ThreeVector def){
        if( FindVectorParameter(ss) )
            return par_vector[ss];
        else
            return def;
    }

    void AddStringParameter( std::string ss, std::string a){
        par_string[ss] = a;
    }

    bool FindStringParameter( std::string ss ){
        return par_string.find(ss)!=par_string.end();
    }

    std::string GetString( std::string ss, std::string def){
        if( FindStringParameter(ss) )
            return par_string[ss];
        else
            return def;
    }


private:

    std::map<std::string, G4int> par_int;

    std::map<std::string, G4double> par_double;

    std::map<std::string, G4ThreeVector> par_vector;

    std::map<std::string, std::string> par_string;

    DetectorGeometryParameter( const DetectorGeometryParameter& ) = delete;
    DetectorGeometryParameter& operator=( const DetectorGeometryParameter& ) = delete;

};



class DetectorGeometry : public G4VUserDetectorConstruction{

public:

	DetectorGeometry();
		//!< Constructor.

	~DetectorGeometry();
		//!< Destructor.
        
	virtual	G4VPhysicalVolume* Construct();
		//!< should return constructed *PhysicalVolume.

private:

    DetectorGeometryParameter geo_param;
        //!< Structure to hold information about the geometry of the setup.

    DetectorGeometryMessenger* msgr;
        //!< fmessegner
};

#endif
