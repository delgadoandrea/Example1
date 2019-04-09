#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Run : public G4Run
{
  public:
    Run();
    ~Run();

    void IncEDep(G4double dep) {
      fTotE  += dep;
      fTotE2 += dep*dep;
    }
    void IncAbsorption(G4int count) {
      fAbsorptionCount  += count;
      fAbsorptionCount2 += count*count;
    }
    void IncBoundaryAbsorption(G4int count) {
      fBoundaryAbsorptionCount  += count;
      fBoundaryAbsorptionCount2 += count*count;
    }
    void IncHitCount(G4int count) {
      fHitCount  += count;
      fHitCount2 += count*count;
    }

    virtual void Merge(const G4Run* run);

    void EndOfRun();


  private:
    G4int fHitCount, fHitCount2;
    G4int fAbsorptionCount, fAbsorptionCount2;
    G4int fBoundaryAbsorptionCount, fBoundaryAbsorptionCount2;

    G4double fTotE, fTotE2;
};

#endif