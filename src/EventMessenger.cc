#include "EventMessenger.hh"
#include "EventAction.hh"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventMessenger::EventMessenger(EventAction* event)
 : fEvent(event)
{
  fVerboseCmd = new G4UIcmdWithAnInteger("/Example/eventVerbose",this);
  fVerboseCmd->SetGuidance("Set the verbosity of event data.");
  fVerboseCmd->SetParameterName("verbose",true);
  fVerboseCmd->SetDefaultValue(1);

  fForceDrawPhotonsCmd=new G4UIcmdWithABool("/Example/forceDrawPhotons",this);
  fForceDrawPhotonsCmd->SetGuidance("Force drawing of photons.");
  fForceDrawPhotonsCmd
    ->SetGuidance("(Higher priority than /Example/forceDrawNoPhotons)");

  fForceDrawNoPhotonsCmd=new G4UIcmdWithABool("/Example/forceDrawNoPhotons",this);
  fForceDrawNoPhotonsCmd->SetGuidance("Force no drawing of photons.");
  fForceDrawNoPhotonsCmd
    ->SetGuidance("(Lower priority than /Example/forceDrawPhotons)");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventMessenger::~EventMessenger(){
  delete fVerboseCmd;
  delete fForceDrawPhotonsCmd;
  delete fForceDrawNoPhotonsCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventMessenger::SetNewValue(G4UIcommand* command, G4String newValue){
  if( command == fVerboseCmd ){
    fEvent->SetEventVerbose(fVerboseCmd->GetNewIntValue(newValue));
  }
  else if(command == fForceDrawPhotonsCmd){
    fEvent->SetForceDrawPhotons(fForceDrawPhotonsCmd
                                  ->GetNewBoolValue(newValue));
  }
  else if(command == fForceDrawNoPhotonsCmd){
    fEvent->SetForceDrawNoPhotons(fForceDrawNoPhotonsCmd
                                  ->GetNewBoolValue(newValue));
  }
}