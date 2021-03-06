#ifndef OpticalPhysics_h
#define OpticalPhysics_h 1

#include "globals.hh"

#include "G4OpWLS.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpRayleigh.hh"
#include "G4OpAbsorption.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4VPhysicsConstructor.hh"

class OpticalPhysics : public G4VPhysicsConstructor
{
  public:

    OpticalPhysics(G4bool toggle=true);
    virtual ~OpticalPhysics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

    G4OpWLS* GetWLSProcess() {return fWLSProcess;}
    G4Cerenkov* GetCerenkovProcess() {return fCerenkovProcess;}
    G4Scintillation* GetScintillationProcess() {return fScintProcess;}
    G4OpAbsorption* GetAbsorptionProcess() {return fAbsorptionProcess;}
    G4OpRayleigh* GetRayleighScatteringProcess() {return fRayleighScattering;}
    G4OpBoundaryProcess* GetBoundaryProcess() { return fBoundaryProcess;}

private:

    G4OpWLS*             fWLSProcess;
    G4Cerenkov*          fCerenkovProcess;
    G4Scintillation*     fScintProcess;
    G4OpAbsorption*      fAbsorptionProcess;
    G4OpRayleigh*        fRayleighScattering;
    G4OpBoundaryProcess* fBoundaryProcess;
 
    G4bool fAbsorptionOn;

};
#endif
