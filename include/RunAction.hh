#include "G4UserRunAction.hh"

#ifndef RunAction_h
#define RunAction_h 1

class Run;
class HistoManager;
class G4Run;

class RunAction : public G4UserRunAction
{
  public:

    RunAction();
    virtual ~RunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

  private:

    Run*          fRun;
    HistoManager* fHistoManager;
};

#endif