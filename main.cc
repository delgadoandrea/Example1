//Initialize all your classes here

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Types.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4String.hh"

#include "FTFP_BERT.hh"
#include "OpticalPhysics.hh"
//#include "G4OpWLS.hh"
#include "G4EmStandardPhysics_option4.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4VPhysicsConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  //detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  if (argc == 1) { ui = new G4UIExecutive(argc,argv); }

  G4RunManager * runManager = new G4RunManager;

  DetectorConstruction* det = new DetectorConstruction();
  runManager->SetUserInitialization(det);

  G4VModularPhysicsList* physicsList = new FTFP_BERT; 
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  OpticalPhysics* opticalPhysics = new OpticalPhysics(true);
  //G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();  
  //G4OpWLS* wlsPhys = new G4OpWLS();
  //opticalPhysics->SetWLSTimeProfile("delta");
  //opticalPhysics->SetScintillationYieldFactor(1.0);
  //opticalPhysics->SetScintillationExcitationRatio(0.0);
  //opticalPhysics->SetMaxNumPhotonsPerStep(100);
  //opticalPhysics->SetMaxBetaChangePerStep(10.0);
  //opticalPhysics->SetTrackSecondariesFirst(kCerenkov, true);
  //opticalPhysics->SetTrackSecondariesFirst(kScintillation, true);
  physicsList->RegisterPhysics(opticalPhysics);

  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new ActionInitialization(det));

  //initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  //get the pointer to the User Interface manager 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui) {
    //interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    //if (ui->IsGUI()) {
    //  UImanager->ApplyCommand("/control/execute gui.mac");
    //}
    ui->SessionStart();
    delete ui;
  } else {
    //batch mode  
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  // job termination
  delete visManager;
  delete runManager;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......