#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class DetectorConstruction;

/// Action initialization class.
///

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(const DetectorConstruction* det);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:

    const DetectorConstruction* fDetector;
};

#endif