#include "OpticalPhysics.hh"
#include "G4OpticalPhoton.hh"
#include "G4ProcessManager.hh"
#include "G4OpAbsorption.hh"

OpticalPhysics::OpticalPhysics(G4bool toggle)
    : G4VPhysicsConstructor("Optical")
{

	fWLSProcess      = NULL;
	fScintProcess    = NULL;
	fCerenkovProcess = NULL;
	fBoundaryProcess = NULL;
	fAbsorptionProcess = NULL;
	fRayleighScattering = NULL;

	fAbsorptionOn = toggle;

}

OpticalPhysics::~OpticalPhysics() {}

void OpticalPhysics::ConstructParticle(){
	G4OpticalPhoton::OpticalPhotonDefinition();
}

void OpticalPhysics::ConstructProcess(){
	G4cout << "OpticalPhysics:: Add Optical Physics Processes" << G4endl;

	fWLSProcess = new G4OpWLS();
  	fScintProcess = new G4Scintillation();
  	fScintProcess->SetScintillationYieldFactor(1.);
  	fScintProcess->SetTrackSecondariesFirst(true);

  	fCerenkovProcess = new G4Cerenkov();
  	fCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  	fCerenkovProcess->SetTrackSecondariesFirst(true);

  	fAbsorptionProcess      = new G4OpAbsorption();
  	fRayleighScattering     = new G4OpRayleigh();
	fBoundaryProcess        = new G4OpBoundaryProcess();

  //fAbsorptionProcess->DumpPhysicsTable();
  fWLSProcess->SetVerboseLevel(1);




  	G4ProcessManager* pManager =
                G4OpticalPhoton::OpticalPhoton()->GetProcessManager();

    if (!pManager) {
    	std::ostringstream o;
     	o << "Optical Photon without a Process Manager";
     	G4Exception("OpticalPhysics::ConstructProcess()","",
                  FatalException,o.str().c_str());
  	}

  	if (fAbsorptionOn) pManager->AddDiscreteProcess(fAbsorptionProcess);

  	pManager->AddDiscreteProcess(fBoundaryProcess);
  	pManager->AddDiscreteProcess(fRayleighScattering);

  	fWLSProcess->UseTimeProfile("delta");

  	pManager->AddDiscreteProcess(fWLSProcess);

  	fScintProcess->SetScintillationYieldFactor(1.);
  	fScintProcess->SetScintillationExcitationRatio(0.0);
  	fScintProcess->SetTrackSecondariesFirst(true);

  	pManager->AddProcess(fScintProcess);

}