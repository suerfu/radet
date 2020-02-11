
#include "HistoManager.hh"
#include <ctime>

using std::endl;

HistoManager::HistoManager( string name ): filename(name){

    delim = ", ";

	filename = name;

    if( filename!="" ){

        output.open( filename );

        time_t tm( time(0) );
        output << "# " << asctime( localtime( &tm ) ) << endl << endl;

        output << "# --- Format --- " << endl;
        output << "# runID" << delim;   // run ID
        output << "eventID" << delim; // event ID

        output << "trackID" << delim;    // particle ID
        output << "parentID" << delim;  // parent information, 0 if primary
        output << "PID" << delim;

        output << "init x" << delim << "y" << delim << "z" << delim;
        output << "theta" << delim << "phi" << delim;
        output << "Ei" << delim;

        output << "fin x" << delim << "y" << delim << "z" << delim;
        output << "theta" << delim << "phi" << delim;
        output << "Ef" << delim;

        output << "Edep_coating" << delim;
        output << "Edep_target" << endl << endl;

        output << "# units: all positions in cm, angles in degree, and energy in MeV" << endl << endl;
    }

}


HistoManager::~HistoManager(){
    if( output.good() )
        output.close();
}


void HistoManager::clear(){
    tracks.clear();
}


void HistoManager::write(){ 

    if( !output.good() )
        return;

    for( map<int, TrackInfo>::iterator itr = tracks.begin(); itr!=tracks.end(); itr++){

        output << runID << delim;   // run ID
        output << eventID << delim; // event ID

        output << (itr->second).ID << delim;    // particle ID
        output << (itr->second).parentID << delim;  // parent information, 0 if primary
        output << (itr->second).pid << delim;

        // initial state
        output << (itr->second).ri.x()/cm << delim << (itr->second).ri.y()/cm << delim << (itr->second).ri.z()/cm << delim;
            // initial position
        output << (itr->second).pi.theta()/degree << delim << (itr->second).pi.phi()/degree << delim;// << (itr->second).pi.z() << delim;
            // initial momentum
        output << (itr->second).Ei << delim;
            // initial energy

        // final state
        output << (itr->second).rf.x()/cm << delim << (itr->second).rf.y()/cm << delim << (itr->second).rf.z()/cm << delim;
            // final position
        output << (itr->second).pf.theta()/degree << delim << (itr->second).pf.phi()/degree << delim;// << (itr->second).pf.z() << delim;
            // final momentum
        output << (itr->second).Ef/MeV << delim;
            // final energy

        output << (itr->second).edep_coating/MeV << delim;
        output << (itr->second).edep_target/MeV << endl;
    }
}



void HistoManager::update( TrackInfo input, bool initial){

    if ( tracks.find( input.ID )==tracks.end() ){
        // if track with the ID has not been registered yet.
        tracks[input.ID] = input;
        //G4cout << "registering track with ID " << input.ID << ", E = " << input.Ei << endl;
    }
    else{
        // otherwise update the existing information based on the time.
        TrackInfo* p = &tracks[input.ID];
        if( initial ){
            //G4cout << "Updating initial information of track " << p->ID << ", E = " << input.Ei << G4endl;
            p->ri = input.ri;
            p->pi = input.pi;
            p->Ei = input.Ei;
            p->ti = input.ti;
        }
        else if( input.tf > p->tf ){
            //G4cout << "Updating final information of track " << p->ID << ", E = " << input.Ef << G4endl;
            p->rf = input.rf;
            p->pf = input.pf;
            p->Ef = input.Ef;
            p->tf = input.tf;
        }
    }
}


void HistoManager::add_edep( int id, G4double e, string name){
    if( name == "coating" )
        tracks[id].edep_coating += e;
    else if( name == "target" )
        tracks[id].edep_target += e;
}

