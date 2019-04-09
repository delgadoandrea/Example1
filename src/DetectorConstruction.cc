#include "DetectorConstruction.hh"
#include "PMTSD.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4SubtractionSolid.hh"
#include "G4Ellipsoid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
#include "G4OpticalSurface.hh"
#include "G4MaterialTable.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4UImanager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct(){   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);
  //     
  // World
  //

  G4double world_sizeXY = 30*cm;
  G4double world_sizeZ  = 30*cm;
  G4Material* world_mat  = G4Material::GetMaterial("G4_AIR");

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       world_sizeXY, world_sizeXY, world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4Box* box = new G4Box("box", 0.5*cm, 0.5*cm, 0.1*cm);
  G4LogicalVolume* boxLV = new G4LogicalVolume(box, world_mat, "Box");

  G4VPhysicalVolume* boxPV = new G4PVPlacement(0,G4ThreeVector(), boxLV,"Box", logicWorld,false, 0, checkOverlaps);
            
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField() {

  if (!fPmt_SD.Get()) {
     //Created here so it exists as pmts are being placed
     G4cout << "Constructing /Det/pmtSD" << G4endl;
     PMTSD* pmt_SD = new PMTSD("/Det/pmtSD");
     fPmt_SD.Put(pmt_SD);

   }
   G4SDManager::GetSDMpointer()->AddNewDetector(fPmt_SD.Get());
   //-----AD sensitive detector is not actually on the photocathode.
   //processHits gets done manually by the stepping action.
   //It is used to detect when photons hit and get absorbed&detected at the
   //boundary to the photocathode (which doesnt get done by attaching it to a
   //logical volume.
   //It does however need to be attached to something or else it doesnt get
   //reset at the begining of events

   SetSensitiveDetector("Box", fPmt_SD.Get(),true); 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDefaults() {

  //----AD Add hard-coded values here if you want to use them throughout the entire simulation

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......