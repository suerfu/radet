#include "DetectorHit.hh"

//G4Allocator<DetectorHit> DetectorHitAllocator;
// Above line not compatible with multi-threading mode.

G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator=0;


DetectorHit::DetectorHit(){}

DetectorHit::~DetectorHit(){}

DetectorHit::DetectorHit( const DetectorHit& right):G4VHit(){
    trackID = right.trackID;
    parentID = right.parentID;
    pid = right.pid;
	r = right.r;
	p = right.p;
    t = right.t;
	edep = right.edep;
    ekin = right.ekin;
}

const DetectorHit& DetectorHit::operator =( const DetectorHit& right){
    trackID = right.trackID;
    parentID = right.parentID;
    pid = right.pid;
	r = right.r;
	p = right.p;
    t = right.t;
	edep = right.edep;
    ekin = right.ekin;
	return *this;
}

int DetectorHit::operator==( const DetectorHit& right) const{
	return (this==&right) ? 1 : 0;
}

void DetectorHit::Draw(){

	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

	if(pVVisManager){
		G4Circle circle(r);
		circle.SetScreenSize(0.04);
		circle.SetFillStyle(G4Circle::filled);
		G4Colour colour(1.,0.,0.);
		G4VisAttributes attribs(colour);
		circle.SetVisAttributes(attribs);
		pVVisManager->Draw(circle);
	}

}

void DetectorHit::Print(){}
