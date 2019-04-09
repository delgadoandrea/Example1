#ifndef PMTSD_h
#define PMTSD_h 1

#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VProcess.hh"
#include "PMTHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class PMTSD : public G4VSensitiveDetector
{

  public:

    PMTSD(G4String name);
    virtual ~PMTSD();
 
    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
 
    //A version of processHits that keeps aStep constant
    G4bool ProcessHits_constStep(const G4Step* ,
                                 G4TouchableHistory* );
    virtual void EndOfEvent(G4HCofThisEvent* );
    virtual void clear();
    void DrawAll();
    void PrintAll();

  private:

    PMTHitsCollection* fPMTHitCollection;
};

#endif