#include "Run.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::Run() : G4Run()
{
  fHitCount                = fHitCount2                = 0;
  fAbsorptionCount         = fAbsorptionCount2         = 0;
  fBoundaryAbsorptionCount = fBoundaryAbsorptionCount2 = 0;

  fTotE = fTotE2 = 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::~Run()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::Merge(const G4Run* run)
{
  const Run* localRun = static_cast<const Run*>(run);

  fHitCount                 += localRun->fHitCount;
  fHitCount2                += localRun->fHitCount2;
  fAbsorptionCount          += localRun->fAbsorptionCount;
  fAbsorptionCount2         += localRun->fAbsorptionCount2;
  fBoundaryAbsorptionCount  += localRun->fBoundaryAbsorptionCount;
  fBoundaryAbsorptionCount2 += localRun->fBoundaryAbsorptionCount2;
  fTotE                     += localRun->fTotE;
  fTotE2                    += localRun->fTotE2;

  G4Run::Merge(run);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::EndOfRun()
{
  G4cout << "\n ======================== run summary ======================\n";

  G4int prec = G4cout.precision();

  G4int n_evt = numberOfEvent;
  G4cout << "The run was " << n_evt << " events." << G4endl;
 
  G4cout.precision(4);
  G4double hits = G4double(fHitCount)/n_evt;
  G4double hits2 = G4double(fHitCount2)/n_evt;
  G4double rms_hits = hits2 - hits*hits;
  if (rms_hits > 0.) rms_hits = std::sqrt(rms_hits/n_evt);
  else rms_hits = 0.;
  G4cout << "Number of hits per event:\t " << hits << " +- " << rms_hits 
         << G4endl;
  G4double absorb = G4double(fAbsorptionCount)/n_evt;
  G4double absorb2 = G4double(fAbsorptionCount2)/n_evt;
  G4double rms_absorb = absorb2 - absorb*absorb;
  if (rms_absorb > 0.) rms_absorb = std::sqrt(rms_absorb/n_evt);
  else rms_absorb = 0.;

  G4cout << "Number of absorbed photons per event :\t " << absorb << " +- " 
         << rms_absorb << G4endl;

  G4double bdry = G4double(fBoundaryAbsorptionCount)/n_evt;
  G4double bdry2 = G4double(fBoundaryAbsorptionCount2)/n_evt;
  G4double rms_bdry = bdry2 - bdry*bdry;
  if (rms_bdry > 0.) rms_bdry = std::sqrt(rms_bdry/n_evt);
  else rms_bdry = 0.;

  G4cout << "Number of photons absorbed at boundary per event:\t " << bdry 
         << " +- " << rms_bdry << G4endl;
  //G4cout << "Number of unaccounted for photons: " << G4endl;

  G4double en = fTotE/n_evt;
  G4double en2 = fTotE2/n_evt;
  G4double rms_en = en2 - en*en;
  if (rms_en > 0.) rms_en = std::sqrt(rms_en/n_evt);
  else rms_en = 0.;

  G4cout << "Total energy deposition in scintillator per event:\t " << en/keV 
         << " +- " << rms_en/keV << " keV." << G4endl;

  G4cout << G4endl;
  G4cout.precision(prec);
}