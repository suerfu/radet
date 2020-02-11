
#include "RadiationPhysics.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

// *** Processes and models

// gamma
#include "G4PenelopePhotoElectricModel.hh"
#include "G4PenelopeComptonModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4PenelopeRayleighModel.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"
#include "G4PhotoElectricEffect.hh"

// e- and e+
#include "G4eMultipleScattering.hh"
#include "G4UniversalFluctuation.hh"

#include "G4eIonisation.hh"
#include "G4PenelopeIonisationModel.hh"

#include "G4eBremsstrahlung.hh"
#include "G4PenelopeBremsstrahlungModel.hh"

// e+ only
#include "G4eplusAnnihilation.hh"
#include "G4PenelopeAnnihilationModel.hh"

// mu
/*
#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4MuBremsstrahlungModel.hh"
#include "G4MuPairProductionModel.hh"
*/
#include "G4hBremsstrahlungModel.hh"
#include "G4hPairProductionModel.hh"

// hadrons
#include "G4hMultipleScattering.hh"
//#include "G4MscStepLimitType.hh"

#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"
#include "G4ePairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4alphaIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"

// msc models
//#include "G4UrbanMscModel.hh"
#include "G4GoudsmitSaundersonMscModel.hh"
//#include "G4WentzelVIModel.hh"
#include "G4CoulombScattering.hh"
//#include "G4eCoulombScatteringModel.hh"
//

#include "G4LossTableManager.hh"
#include "G4VAtomDeexcitation.hh"
#include "G4UAtomicDeexcitation.hh"

#include "G4RadioactiveDecay.hh"

// particles

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"
//#include "G4MuonPlus.hh"
//#include "G4MuonMinus.hh"
//#include "G4NeutrinoMu.hh"
//#include "G4AntiNeutrinoMu.hh"
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

//
#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"
#include "G4EmModelActivator.hh"

// factory
#include "G4PhysicsConstructorFactory.hh"


RadiationPhysics::RadiationPhysics( ) : G4VUserPhysicsList(){}


RadiationPhysics::~RadiationPhysics(){}


void RadiationPhysics::ConstructParticle(){

    // gamma
    G4Gamma::GammaDefinition();

    // leptons
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();

    /*
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();
    G4NeutrinoE::NeutrinoMuDefinition();
    G4AntiNeutrinoE::AntiNeutrinoMuDefinition();
    */

    // baryons
    G4Proton::ProtonDefinition();
    G4AntiProton::AntiProton();

    // ions
    G4Deuteron::DeuteronDefinition();
    G4Triton::TritonDefinition();
    G4He3::He3Definition();
    G4Alpha::AlphaDefinition();
    G4GenericIon::GenericIonDefinition();
}


void RadiationPhysics::ConstructProcess(){
  
    AddTransportation();

    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    G4LossTableManager* man = G4LossTableManager::Instance();

    auto iter=GetParticleIterator();
    iter->reset();
    while( (*iter)() ){

        G4ParticleDefinition* particle = iter->value();
        G4String particleName = particle->GetParticleName();

        if (!particle){
            continue;
        }
        if (particleName == "gamma") {

            //Photo-electric effect
            G4PhotoElectricEffect* ph_ele = new G4PhotoElectricEffect();
            ph_ele->SetEmModel( new G4PenelopePhotoElectricModel() );
            ph->RegisterProcess( ph_ele, particle );

            //Compton scattering
            G4ComptonScattering* cs = new G4ComptonScattering();
            cs->SetEmModel( new G4PenelopeComptonModel( ));
            ph->RegisterProcess( cs, particle);

            //Gamma conversion
            G4GammaConversion* gconv = new G4GammaConversion();
            gconv->SetEmModel( new G4PenelopeGammaConversionModel() );
            ph->RegisterProcess( gconv, particle);

            //Rayleigh scattering
            ph->RegisterProcess( new G4RayleighScattering(), particle);

        }
        else if (particleName == "e-" || particleName=="e+") {

            // multiple scattering
            G4eMultipleScattering* emsc = new G4eMultipleScattering;
            G4GoudsmitSaundersonMscModel* gs_msc = new G4GoudsmitSaundersonMscModel();
            emsc->SetEmModel( gs_msc );
            ph->RegisterProcess( emsc, particle);

            // Ionisation
            G4eIonisation* eioni = new G4eIonisation();
            eioni->AddEmModel( 0, new G4PenelopeIonisationModel(), new G4UniversalFluctuation());
            ph->RegisterProcess( eioni, particle);
  
            //Bremsstrahlung
            G4eBremsstrahlung* ebrem = new G4eBremsstrahlung();
            ebrem->SetEmModel( new G4PenelopeBremsstrahlungModel() );
            ph->RegisterProcess( ebrem, particle);

            // electron pair production by e-/e+
            //G4ePairProduction* ee = new G4ePairProduction();
            //ph->RegisterProcess( ee, particle);


            if (particleName == "e+") {
                G4eplusAnnihilation* anni = new G4eplusAnnihilation();
                anni->SetEmModel( new G4PenelopeAnnihilationModel() );
                ph->RegisterProcess(anni, particle);
            }
        }
        
        // Do not consider muon for the moment, because it can be complicated.
        /*
        else if( particleName == "mu+" || particleName == "mu-"){
            
            ph->RegisterProcess( G4MuIonisation(), particle);

            G4MuMultipleScattering* mumsc = new G4MuMultipleScattering();
            mumsc->SetEmModel(new G4WentzelVIModel());
            ph->RegisterProcess( mumsc, particle);

            ph->RegisterProcess( G4CoulombScattering(), particle);
            ph->RegisterProcess( G4MuBremsstrahlung(), particle);
            ph->RegisterProcess( G4MuPairProduction(), particle);
        }*/
        else if ( IsHadron( particleName ) ){
            ph->RegisterProcess( new G4hMultipleScattering(), particle);
            ph->RegisterProcess( new G4NuclearStopping(), particle);

            G4ionIonisation* ionIoni = new G4ionIonisation();
            ionIoni->SetEmModel( new G4IonParametrisedLossModel() );
            ionIoni->SetStepFunction( 0.1, 1*um);
            ph->RegisterProcess( ionIoni, particle);

            if( particleName == "proton" || particleName == "anti_proton"){
                ph->RegisterProcess( new G4hBremsstrahlung(), particle);
                ph->RegisterProcess( new G4hPairProduction(), particle);
                //ph->RegisterProcess( new G4CoulombScattering(), particle);
            }

            if( particleName == "GenericIon" || particleName == "triton" ){

                G4RadioactiveDecay* radiodecay = new G4RadioactiveDecay();
                radiodecay->SetHLThreshold( -1.*s );
                radiodecay->SetICM( true );                //Internal Conversion
                radiodecay->SetARM( true );               //Atomic Rearangement
                ph->RegisterProcess( radiodecay, particle);
            }
        }
    }
    
    // Deexcitation
    //
    G4VAtomDeexcitation* deex = new G4UAtomicDeexcitation();
    man->SetAtomDeexcitation( deex );
    deex->SetFluo(true);
    deex->SetAuger(true);
    deex->SetPIXE(true);
}


  
G4bool RadiationPhysics::IsHadron( G4String test){
    if( test=="proton" || test=="anti_proton" )
        return true;
    else if( test=="GenericIon" )
        return true;
    else if( test=="alpha" || test=="He3" || test=="triton" || test=="deuteron" )
        return true;
    return false;
}
      

