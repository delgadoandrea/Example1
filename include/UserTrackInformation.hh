#include "G4VUserTrackInformation.hh"
#include "globals.hh"

#ifndef UserTrackInformation_h
#define UserTrackInformation_h 1

enum TrackStatus { active=1, hitPMT=2, absorbed=4, boundaryAbsorbed=8,
                      hitSphere=16, inactive=14};

/*TrackStatus:
  active: still being tracked
  hitPMT: stopped by being detected in a PMT
  absorbed: stopped by being absorbed with G4OpAbsorbtion
  boundaryAbsorbed: stopped by being aborbed with G4OpAbsorbtion
  inactive: track is stopped for some reason
   -This is the sum of all stopped flags so can be used to remove stopped flags
 
*/

class UserTrackInformation : public G4VUserTrackInformation
{
  public:

    UserTrackInformation();
    virtual ~UserTrackInformation();

    void SetTrackStatusFlags(int s){fStatus=s;}

    void AddTrackStatusFlag(int s);
 
    int GetTrackStatus()const {return fStatus;}
 
    void IncReflections(){fReflections++;}
    G4int GetReflectionCount()const {return fReflections;}

    void SetForceDrawTrajectory(G4bool b){fForcedraw=b;}
    G4bool GetForceDrawTrajectory(){return fForcedraw;}

    inline virtual void Print() const{};

  private:

    int fStatus;
    G4int fReflections;
    G4bool fForcedraw;
};

#endif