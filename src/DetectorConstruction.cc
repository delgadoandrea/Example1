#include "DetectorConstruction.hh"
#include "PMTSD.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4NistManager.hh"
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

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4Element *elH = new G4Element("Hydrogen","H",1., 1.01*g/mole);
  G4Element *elB = new G4Element("Boron","B",5., 10.81*g/mole);
  G4Element *elC = new G4Element("Carbon","C",6.,12.01*g/mole);
  G4Element *elO = new G4Element("Oxygen","O",8.,16.0*g/mole);
  G4Element *elNa = new G4Element("Sodium","Na",11.,22.99*g/mole);
  G4Element *elAl = new G4Element("Aluminium","Al",13.,26.98*g/mole);
  G4Element *elSi = new G4Element("Silicon","Si",14., 28.085*g/mole);
  G4Element *elK = new G4Element("Potassium","K",19., 39.098*g/mole);

  G4MaterialPropertiesTable* tpbMPT = new G4MaterialPropertiesTable();
  G4double tpb_energy[2] = {2.95*eV,9.68*eV};
  G4double tpb_rindex[2]={ 1.60, 1.60};
//  G4double tpb_abslength[2]={1.00*m, 0.0002*mm};
  G4double tpb_abslength[2]={1.00*m, 1.0*m};  
  G4double tpb_emission[2]={1.0, 0.0};
  tpbMPT->AddProperty("RINDEX", tpb_energy, tpb_rindex, 2);
  tpbMPT->AddProperty("WLSABSLENGTH", tpb_energy, tpb_abslength, 2);
  //tpbMPT->AddProperty("WLSCOMPONENT", tpb_energy, tpb_emission, 2);
  //tpbMPT->AddConstProperty("WLSTIMECONSTANT", 0.5*ns);

  G4MaterialPropertiesTable* larMPT = new G4MaterialPropertiesTable();
  //G4double lar_energy[2] = {2.95*eV,9.68*eV};
  //G4double lar_rindex[2]={ 1.24, 1.46};
  //G4double lar_abslength[2]={1.0*m, 1.0*m};
  //larMPT->AddProperty("RINDEX", lar_energy, lar_rindex, 2);
  //larMPT->AddProperty("ABSLENGTH", lar_energy, lar_abslength, 2);

  G4MaterialPropertiesTable* pmmaMPT = new G4MaterialPropertiesTable();
  //G4double pmma_energy[2] = {2.95*eV,9.68*eV};
  //G4double pmma_rindex[2]={ 1.49, 1.60};
  //G4double pmma_abslength[2]={1.00*m, 0.0*m};
  //pmmaMPT->AddProperty("RINDEX", pmma_energy, pmma_rindex, 2);
  //pmmaMPT->AddProperty("ABSLENGTH", pmma_energy, pmma_abslength, 2);

  G4MaterialPropertiesTable* bk7MPT = new G4MaterialPropertiesTable();
  G4double bk7_energy[2] = {2.95*eV,9.68*eV};
  G4double bk7_rindex[2]={ 1.53, 1.60};
  G4double bk7_abslength[2]={1.00*m, 0.0*m};
  bk7MPT->AddProperty("RINDEX", bk7_energy, bk7_rindex, 2);
  bk7MPT->AddProperty("ABSLENGTH", bk7_energy, bk7_abslength, 2);

  G4MaterialPropertiesTable* sapphireMPT = new G4MaterialPropertiesTable();
  G4double sapphire_energy[2] = {2.95*eV,9.68*eV};
  G4double sapphire_rindex[2]={ 1.80, 1.80};
  G4double sapphire_abslength[2]={1.00*m, 0.0*m};
  sapphireMPT->AddProperty("RINDEX", sapphire_energy, sapphire_rindex, 2);
  sapphireMPT->AddProperty("ABSLENGTH", sapphire_energy, sapphire_abslength, 2);

  G4Material *LiquidArgon =
    new G4Material( "LiquidArgon",  // name
                    18.,            // z
                    39.95*g/mole,   // a
                    1.4*g/cm3);     // density
  //LiquidArgon->SetMaterialPropertiesTable(larMPT);

  G4Material *ArgonGas =
    new G4Material( "ArgonGas",     // name
                    18.,            // Z
                    39.95*g/mole,   // a
                    0.002*g/cm3);   // density

  G4Material *TPB =
    new G4Material( "TPB",          // Name
                    1.079*g/cm3,     // density
                    2);             // number of elements
  TPB->AddElement(elH, 22);
  TPB->AddElement(elC, 12);
  //TPB->SetMaterialPropertiesTable(tpbMPT);

  G4Material *PMMA =
    new G4Material( "PMMA",      // Name
                    1.18*g/cm3,     // density
                    3);             // number of elements
  PMMA->AddElement(elH, 8);
  PMMA->AddElement(elC, 5);
  PMMA->AddElement(elO, 2);
  PMMA->SetMaterialPropertiesTable(pmmaMPT);

  G4Material *BK7 =
    new G4Material( "BK7",          // Name
                    2.51*g/cm3,     // density
                    6);             // number of elements
  BK7->AddElement(elB, 0.070449);
  BK7->AddElement(elO, 0.641095);
  BK7->AddElement(elNa, 0.023311);
  BK7->AddElement(elAl, 0.008204);
  BK7->AddElement(elSi, 0.255327);
  BK7->AddElement(elK, 0.001615);
  BK7->SetMaterialPropertiesTable(bk7MPT);

  G4Material *Sapphire =
    new G4Material( "Sapphire",     // Name
                    3.98*g/cm3,     // density
                    2);             // number of elements
  Sapphire->AddElement(elAl, 2);
  Sapphire->AddElement(elO, 3);
  Sapphire->SetMaterialPropertiesTable(sapphireMPT);


  G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);
  //
  // World
  //

  G4double world_sizeXY = 100*cm;
  G4double world_sizeZ  = 100*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       world_sizeXY, world_sizeXY, world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        LiquidArgon,         //its material
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

  G4double  radius  = 2.5*cm;           // Radius of PMT and wls disks
  G4double  det_disk_dist = 1.0*cm;     // Distance between detector and wls disk
  G4double  disk_thickness = 5*mm;      // Disk thickness
  G4double  tpb_thickness = 0.002*mm;   // TPB thickness

  G4double  cone_width = 0.2*mm;
  G4double  cone_height = 0.2*mm;
  G4double  cone_pitch = 0.2*mm;

  G4Tubs *det = new G4Tubs("Det",
              0.0*cm, // inner radius
              radius, // outer radius
              0.1*cm, // height
              0.0*deg, 360.0*deg); // segment angle

  G4LogicalVolume* detLV = new G4LogicalVolume(det, BK7, "Det");
  detLV->SetVisAttributes(G4Colour(1.0,0.0,0.0)); //Setting Det color to red

  G4double detZ = 0.05*cm + det_disk_dist + tpb_thickness + disk_thickness;

  //G4VPhysicalVolume* detPV =
    new G4PVPlacement(0,
                      G4ThreeVector(0., 0., detZ),
                      "Det",
                      detLV,
                      physWorld,
                      false,
                      0);


  //G4Box* box = new G4Box("box", 0.5*cm, 0.5*cm, 0.1*cm);
  //G4LogicalVolume* boxLV = new G4LogicalVolume(box, world_mat, "Box");
  //G4VPhysicalVolume* boxPV = new G4PVPlacement(0,G4ThreeVector(), boxLV,"Box", logicWorld,false, 0, checkOverlaps);

  G4Tubs *disk = new G4Tubs("disk",
              0.0*cm, // inner radius
              radius, // outer radius
              disk_thickness, // height
              0.0*deg, 360.0*deg); // segment angle

  G4LogicalVolume* diskLV =
    new G4LogicalVolume(disk,   //its solid
                        PMMA,    //its material
                        "disk");     //its name

  G4double diskZ = disk_thickness + tpb_thickness;

  diskLV->SetVisAttributes(G4Colour(0.0,1.0,0.0));

//  G4VPhysicalVolume* diskPV =
    new G4PVPlacement(0,                     //no rotation
      G4ThreeVector(0., 0., diskZ),          // at (x,y,z)
                      "disk",
                      diskLV,                //its logical volume                //its name
                      physWorld,            //its mother  volume
                      false,                 //no boolean operation
                      0);


  G4Tubs *tpb_coating = new G4Tubs("tpb_coating",
              0.0*cm,   // inner radius
              radius,   // outer radius
              tpb_thickness, // height
              0.0*deg, 360.0*deg); // segment angle

  G4LogicalVolume* tpbLV =
      new G4LogicalVolume(tpb_coating,          //its solid
                          TPB,    //its material
                          "disk");      //its name

  G4double tpbZ =  tpb_thickness;
  tpbLV->SetVisAttributes(G4Colour(0.0,0.0,1.0));


//  G4VPhysicalVolume* tpbPV =
      new G4PVPlacement(0,                     //no rotation
        G4ThreeVector(0., 0., tpbZ),           //at (x,y,z)
                        "tpb_coating",
                        tpbLV,                 //its logical volume
                        physWorld,
                        false,                 //no boolean operation
                        0);        //overlaps checking

if (false) {
  G4Cons *cone = new G4Cons("cone",
              0.0*mm, 0.0*mm, // inner & outer radius 1
              0.0*mm, 0.5*cone_width,         // inner & outer radius 2
              0.5*cone_height,            // height
              0.0*deg, 360.0*deg);    // segment angle

  G4LogicalVolume* coneLV =
      new G4LogicalVolume(cone,         //its solid
                          Sapphire,    //its material
                          "cone");      //its name


  // Make a row as an assembly of cells, then combine rows in a honeycomb
  // structure. This again works without any need to define rows as
  // "overlapping"


  G4int copyNo = 0;
  G4int fnX = (G4int)(radius/cone_pitch), fnY = (G4int)(radius/(cone_pitch*0.866));
  G4double xloc, yloc, rloc;
  //G4double zloc = 0.5*cone_height - 0.5*tpb_thickness - 5.0*cm;
  G4double zloc = -1.0*cm;
  G4String tName("Cone");

  G4cout << "Creating patterned surface: " << fnX << " x " << fnY << G4endl;

  //G4double dy = pitch*TMath::Cos(30.*TMath::DegToRad());
  //G4double dx = pitch*TMath::Sin(30.*TMath::DegToRad());;

  for (G4int j = 0; j < fnY; j++)
  {
    //    Double_t yrow = 0.5*(2*j+1)*dy;
    //    Double_t xrow = 0.5*dx;
    yloc = cone_pitch*0.866*(G4double)j;

    for (G4int i = 0; i < fnX; i++)
    {
        if ((j%2)==0) {xloc = cone_pitch*(G4double)i;}
        else {xloc = cone_pitch*(G4double)i + 0.5*cone_pitch;}

        // First row
        rloc = std::sqrt(std::pow(xloc+(cone_width*0.5), 2) + std::pow(yloc+(cone_width*0.5), 2));
        if (rloc < radius && yloc == 0)
        {
            new G4PVPlacement(0,
                              G4ThreeVector(xloc, yloc, zloc),
                              tName,coneLV,physWorld,false,copyNo++);
            new G4PVPlacement(0,
                              G4ThreeVector(-xloc, yloc, zloc),
                              tName,coneLV,physWorld,false,copyNo++);
        }

        // Subsequent rows
        if (rloc < radius && yloc != 0)
        {
            new G4PVPlacement(0,
                              G4ThreeVector(xloc, yloc, zloc),
                              tName,coneLV,physWorld,false,copyNo++);
            new G4PVPlacement(0,
                              G4ThreeVector(-xloc, yloc, zloc),
                              tName,coneLV,physWorld,false,copyNo++);
            new G4PVPlacement(0,
                              G4ThreeVector(xloc, -yloc, zloc),
                              tName,coneLV,physWorld,false,copyNo++);
            new G4PVPlacement(0,
                              G4ThreeVector(-xloc, -yloc, zloc),
                              tName,coneLV,physWorld,false,copyNo++);
        }
    }
  }
}
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

   SetSensitiveDetector("Det", fPmt_SD.Get(),true);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDefaults() {

  //----AD Add hard-coded values here if you want to use them throughout the entire simulation

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
