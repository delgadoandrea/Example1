#ifndef EventAction_h
#define EventAction_h 1

#include "EventMessenger.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4Event;
class DetectorConstruction;

class EventAction : public G4UserEventAction
{
  public:

    EventAction(const DetectorConstruction*);
    virtual ~EventAction();

  public:

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void SetEventVerbose(G4int v){fVerbose=v;}

    void SetForceDrawPhotons(G4bool b){fForcedrawphotons=b;}
    void SetForceDrawNoPhotons(G4bool b){fForcenophotons=b;}

    void IncEDep(G4double dep){fTotE+=dep;}
    void IncAbsorption(){fAbsorptionCount++;}
    void IncBoundaryAbsorption(){fBoundaryAbsorptionCount++;}
    void IncHitCount(G4int i=1){fHitCount+=i;}

    void SetEWeightPos(const G4ThreeVector& p){fEWeightPos=p;}
    void SetReconPos(const G4ThreeVector& p){fReconPos=p;}
    void SetConvPos(const G4ThreeVector& p){fConvPos=p;fConvPosSet=true;}
    void SetPosMax(const G4ThreeVector& p,G4double edep) {
      fPosMax = p;
      fEdepMax = edep;
    }

    G4int GetHitCount()const {return fHitCount;}
    G4double GetEDep()const {return fTotE;}
    G4int GetAbsorptionCount()const {return fAbsorptionCount;}
    G4int GetBoundaryAbsorptionCount() const {return fBoundaryAbsorptionCount;}

    G4ThreeVector GetEWeightPos(){return fEWeightPos;}
    G4ThreeVector GetReconPos(){return fReconPos;}
    G4ThreeVector GetConvPos(){return fConvPos;}
    G4ThreeVector GetPosMax(){return fPosMax;}
    G4double GetEDepMax(){return fEdepMax;}
    G4double IsConvPosSet(){return fConvPosSet;}

    //Gets the total photon count produced

  private:

    EventMessenger* fEventMessenger;
    const DetectorConstruction* fDetector;

    G4int fPMTCollID;

    G4int fVerbose;

    G4bool fForcedrawphotons;
    G4bool fForcenophotons;

    G4int fHitCount;
    G4int fAbsorptionCount;
    G4int fBoundaryAbsorptionCount;

    G4double fTotE;

    //These only have meaning if totE > 0
    //If totE = 0 then these wont be set by EndOfEventAction
    G4ThreeVector fEWeightPos;
    G4ThreeVector fReconPos; //Also relies on hitCount>0
    G4ThreeVector fConvPos;//true (initial) converstion position
    G4bool fConvPosSet;
    G4ThreeVector fPosMax;
    G4double fEdepMax;
};

#endif