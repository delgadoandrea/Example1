#ifndef EventMessenger_h
#define EventMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class EventAction;
class PrimaryGeneratorMessenger;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

class EventMessenger: public G4UImessenger
{
  public:

    EventMessenger(EventAction*);
    virtual ~EventMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:

    EventAction*      fEvent;
    PrimaryGeneratorMessenger* fPrimaryGenerator; 
    G4UIcmdWithAnInteger*  fVerboseCmd;
    G4UIcmdWithABool*      fForceDrawPhotonsCmd;
    G4UIcmdWithABool*      fForceDrawNoPhotonsCmd;
};

#endif