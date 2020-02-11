#ifndef HistoManager_h
	#define HistoManager_h 1

#include <fstream>
#include <string>

#include "DetectorGeometry.hh"

#include "TrackInfo.hh"

using std::string;
using std::map;
using std::ofstream;

class HistoManager{

public:
  
	HistoManager( string name = "foo.txt" );

	~HistoManager();
   
    void SetGeometry(  TargetGeometry t ){ geom = t; }

    void SetRunID( int i ){ runID = i; }
    int GetRunID(){ return runID; }

    void SetEventID( int i ){ eventID = i; }
    int GetEventID(){ return eventID; }

	void write();

    void clear();
        // clears previous memory

    bool find( int a){
        return !(tracks.find(a)==tracks.end());
    }
        // used to tell if the given track ID has been registered yet.

    void update( TrackInfo, bool initial = false );
        // update existing data sets.
        // if the new track has time earlier than the existing ti, initial information will be updated.
        // likewise, if time is older, the final information will be updated.
        // if the track is not previously in the set, a new entry is created.
        // in either case, energy deposit will be added.

    void add_edep( int trac_kid, G4double energy_deposit, string detector_name);
        // add incrementally energy deposit due to particle of different tracks.
        // detector_name is either coating or target

private:

    string delim;
        // delimiter used to separate fields in output file.

	string filename;
    ofstream output;

    TargetGeometry geom;

    int runID;
        // runID is each of command /run/beamOn xxx
    int eventID;
        // eventID is each of xxx in the beamOn command

    map<int, TrackInfo> tracks;
        // use a map to fast access track information from track ID.
};

#endif
