
#ifndef DETECTORGEOMETRYMESSENGER_H 
    #define DETECTORGEOMETRYMESSENGER_H  1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorGeometry;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;


class DetectorGeometryMessenger: public G4UImessenger{

public:

    DetectorGeometryMessenger( DetectorGeometry* );

    virtual ~DetectorGeometryMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
private:

    DetectorGeometry*  fdetgeom;

    G4UIdirectory*           fdir1;
    G4UIdirectory*           fdir2;

    G4UIcmdWithAString*      fcmd1;
    G4UIcmdWithAString*      fcmd2;

//    G4UIcmdWithADoubleAndUnit* fStepMaxCmd;
};

#endif
