#ifndef SteppingAction_H
#define SteppingACtion_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

#include "G4OpBoundaryProcess.hh"

class EventAction;
class TrackingAction;
class SteppingMessenger;

class SteppingAction : public G4UserSteppingAction
{
  public:

    SteppingAction(EventAction*);
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);

    void SetOneStepPrimaries(G4bool b){fOneStepPrimaries=b;}
    G4bool GetOneStepPrimaries(){return fOneStepPrimaries;}
 
  private:

    G4bool fOneStepPrimaries;
    SteppingMessenger* fSteppingMessenger;
    EventAction*       fEventAction;

    G4OpBoundaryProcessStatus fExpectedNextStatus;
};

#endif