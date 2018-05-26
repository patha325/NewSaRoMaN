//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4cDetectorConstruction.cc 101905 2016-12-07 11:34:39Z gunter $
// 
/// \file B4cDetectorConstruction.cc
/// \brief Implementation of the B4cDetectorConstruction class

#include "B4cDetectorConstruction.hh"
#include "B4cCalorimeterSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* B4cDetectorConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorConstruction::B4cDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true),
   fNofLayers(-1)
{
  _myfile.open ("detectorFile.txt");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorConstruction::~B4cDetectorConstruction()
{
  _myfile.close();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4cDetectorConstruction::Construct()
{
  G4PVPlacement* world_physi;
  _gdml.Read("../../MIND.gdml",0);
  world_physi = dynamic_cast<G4PVPlacement*>(_gdml.GetWorldVolume());
  // SetNullField(*world_physi->GetLogicalVolume());
  regionmass["TASD"] = 0;
  regionmass["ACTIVE"] = 0;
  regionmass["PASSIVE"] = 0;
  G4String detectorName = "MIND/";
  _detectormass = world_physi->GetLogicalVolume()->GetMass();
  SetVolumeInformation(world_physi, detectorName);

  G4int volselect = 0;

  for ( int outerI = 0; outerI < world_physi->GetLogicalVolume()->GetNoDaughters(); outerI++ ) {
    
    G4int nDaughters = world_physi->GetLogicalVolume()->GetDaughter(outerI)->GetLogicalVolume()->GetNoDaughters();
    
    for ( int i = 0; i < nDaughters; i++ ) {
      G4VPhysicalVolume* daughter = world_physi->GetLogicalVolume()->GetDaughter(outerI)->GetLogicalVolume()->GetDaughter(i);
      
      G4LogicalVolume* myvol = daughter->GetLogicalVolume();
      G4Box* solidBox = (G4Box*) myvol->GetSolid();
      
      if(myvol->GetName() == "TASD")
	{// TASD in ND
	  _myfile<<myvol->GetName()<<" "
	    //<<myvol->GetMass()/solidBox->GetCubicVolume()<<" "
		 <<daughter->GetFrameTranslation()[0]<<" "
		 <<daughter->GetFrameTranslation()[1]<<" "
		 <<regionoffset[myvol->GetName()][volselect][2]<<" "
		 <<solidBox->GetXHalfLength()*2.0<<" "
		 <<solidBox->GetYHalfLength()*2.0<<" "
		 <<solidBox->GetZHalfLength()*2.0<<std::endl;
	volselect++;
	}
      else
	{
	  _myfile<<myvol->GetName()<<" "
	    //<<myvol->GetMass()/solidBox->GetCubicVolume()<<" "
		 <<daughter->GetFrameTranslation()[0]<<" "
		 <<daughter->GetFrameTranslation()[1]<<" "
	    //<<regionoffset[myvol->GetName()][0][2]<<" "
	    //<<daughter->GetFrameTranslation()[2]<<" "
		 <<daughter->GetFrameTranslation()[2]+regionoffset["Detector"][0][2]<<" "
	    //<<daughter->GetFrameTranslation()[2]<<" "
	    //<<regionoffset["Detector"][0][2]<< " "
		 <<solidBox->GetXHalfLength()*2.0<<" "
		 <<solidBox->GetYHalfLength()*2.0<<" "
		 <<solidBox->GetZHalfLength()*2.0<<std::endl;
	}
      
       }
    }
  
  /*
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
  */

  return world_physi;
  
}

void B4cDetectorConstruction::SetVolumeInformation(G4VPhysicalVolume* pbase, 
						    G4String detectorName) {

  G4LogicalVolume* base = pbase->GetLogicalVolume();
  // G4VPhysicalVolume* world = _parser.GetWorldVolume();
  G4int nDaughters = base->GetNoDaughters();
 
  for ( int i = 0; i < nDaughters; i++ ) {
    //cout<<"DetectorName="<<detectorName<<endl;
    //cout<<"pbase->GetFrameTranslation()"<<pbase->GetFrameTranslation()<<endl;


    G4VPhysicalVolume* daughter = base->GetDaughter(i);
    G4LogicalVolume* myvol = daughter->GetLogicalVolume();
    G4String volumename = detectorName;
    volumename += myvol->GetName();
    volumename += "/";
    // first check if there are auxiliary objects
    std::cout<<volumename.c_str()<<std::endl;
    //cout<<myvol->GetName().contains("TASD")<<endl;
    //cout<<myvol->GetName().contains("Detector")<<endl;
    // If this name corresponds to one of the three regions add them to the map.
    if (myvol->GetName().contains("TASD")){
      regions["TASD"].push_back(daughter);
      regionmass["TASD"] += myvol->GetMass();
      regionoffset["TASD"].push_back(pbase->GetFrameTranslation());
    } else if (myvol->GetName().contains("ACTIVE")){
      regions["ACTIVE"].push_back(daughter);
      regionmass["ACTIVE"] += myvol->GetMass();
      regionoffset["ACTIVE"].push_back(pbase->GetFrameTranslation());
    } else if (myvol->GetName().contains("PASSIVE")){
      regions["PASSIVE"].push_back(daughter);
      regionmass["PASSIVE"] += myvol->GetMass();
      regionoffset["PASSIVE"].push_back(pbase->GetFrameTranslation());
      //} else if (myvol->GetName().contains("Detector")){
      //regionoffset["Detector"].push_back(pbase->GetFrameTranslation());
      //cout<<"Here="<<pbase->GetFrameTranslation()<<endl;
    } //Ignore otherwise
  
    //For ND.
    if(detectorName == "MIND/Detector/") regionoffset["Detector"].push_back(pbase->GetFrameTranslation());


    
    const G4GDMLAuxListType auxlist = 
      _gdml.GetVolumeAuxiliaryInformation(myvol);

    // Squeak::mout(Squeak::info) << "Found volume " << myvol->GetName()
    // << " with "<< auxlist.size() <<" auxiliary elements." << std::endl;
    if (auxlist.size() > 0) {
      // Set auxiliary information
      SetAuxInformation(volumename, myvol, auxlist);
    }
    // 	 else {
    // 	 _detector->GetUserLimits().push_back(new G4UserLimits(_stepMax, _trackMax,
    // 	 _timeMax, _keThreshold));
    // 	 myvol->SetUserLimits(_detector->GetUserLimits().back());
    // 	 }
    if ( myvol->GetNoDaughters() > 0 ) {
      // Consider adding information to the daughter volumes
      SetVolumeInformation(daughter, volumename);
    }
  }
}

void B4cDetectorConstruction::SetAuxInformation(G4String basename, 
						 G4LogicalVolume* myvol, 
						 const G4GDMLAuxListType auxlist){
  G4String sensdetname = basename;
  G4GDMLAuxListType::const_iterator vit = auxlist.begin();
  G4SDManager* SDMgr = G4SDManager::GetSDMpointer();
  do {
    try {
      G4VSensitiveDetector* mydet;
      if ((*vit).type.contains("SD")){
          mydet = SDMgr->FindSensitiveDetector((*vit).value);
          if ( mydet ){
              myvol->SetSensitiveDetector(mydet);
          } else {
              G4cout << sensdetname << " detector not found. Defining detector." << G4endl;
              sensDetList.push_back( new MindBarSD((*vit).value) );
              SDMgr->AddNewDetector(sensDetList.back());
              mydet = SDMgr->FindSensitiveDetector(sensdetname);
              myvol->SetSensitiveDetector(mydet);
          }
    }
    else if((*vit).type.contains("Color")){
	if((*vit).value.contains("Red"))
	  myvol->SetVisAttributes(new G4VisAttributes(G4Color(1, 0, 0)));

	else if((*vit).value.contains("Orange"))
	  myvol->SetVisAttributes(new G4VisAttributes(G4Color(1, 0.65, 0)));

	else if((*vit).value.contains("Blue"))
	  myvol->SetVisAttributes(new G4VisAttributes(G4Color(0.2, 0.2, 1)));

	else if((*vit).value.contains("Brown"))
	  myvol->SetVisAttributes(new G4VisAttributes(G4Color(0.61, 0.4, 0.12)));
      }
      else if ((*vit).type.contains("Invisible")) {
	myvol->SetVisAttributes(new G4VisAttributes(false));
      }
      else if ((*vit).type.contains("EMField")) {
	if ((*vit).value.contains("MagMap")){
	  SetMagneticField(*myvol);
	} else if((*vit).value.contains("NULL")){
	  SetNullField(*myvol);
	  }
      }
    } catch (...) { 
      continue;
    }
    vit++;
  } while (vit != auxlist.end());	  
}

void B4cDetectorConstruction::SetMagneticField(G4LogicalVolume& vol) {
  
  G4FieldManager* fieldMgr = new G4FieldManager(); 
 
  double fieldScaling = +1.0;
  G4String Bmap = "CenterPlate.table";
  // Declaration of the magnetic field map object
  MindFieldMapR* magField = new MindFieldMapR(Bmap, fieldScaling, 30.0, 4, 30.0);
  // Now to embed the field in the detector geometry
  fieldMgr->SetDetectorField(magField);
  fieldMgr->CreateChordFinder(magField);
  fieldMgr->GetChordFinder()->SetDeltaChord(0.1*cm);
  vol.SetFieldManager( fieldMgr, true );
}

void B4cDetectorConstruction::SetNullField(G4LogicalVolume& detector_logic)
{
  // apply a global uniform magnetic field along Y axis
  //G4FieldManager* fieldMgr = new G4FieldManager();
  G4MagneticField* magField = 0;
  //G4Field* magField = 0;
  //fieldMgr->SetDetectorField(magField);
  //fieldMgr->CreateChordFinder(magField);
  //fieldMgr->GetChordFinder()->SetDeltaChord(0.1*cm);
  G4FieldManager* fieldMgr = new G4FieldManager(magField);
  
  detector_logic.SetFieldManager( fieldMgr, false );
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");
  
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
G4VPhysicalVolume* B4cDetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  fNofLayers = 10;
  G4double absoThickness = 10.*mm;
  G4double gapThickness =  5.*mm;
  G4double calorSizeXY  = 10.*cm;

  auto layerThickness = absoThickness + gapThickness;
  auto calorThickness = fNofLayers * layerThickness;
  auto worldSizeXY = 1.2 * calorSizeXY;
  auto worldSizeZ  = 1.2 * calorThickness; 
  
  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto absorberMaterial = G4Material::GetMaterial("G4_Pb");
  auto gapMaterial = G4Material::GetMaterial("liquidArgon");
  
  if ( ! defaultMaterial || ! absorberMaterial || ! gapMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("B4DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }  
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                               
  // Calorimeter
  //  
  auto calorimeterS
    = new G4Box("Calorimeter",     // its name
                 calorSizeXY/2, calorSizeXY/2, calorThickness/2); // its size
                         
  auto calorLV
    = new G4LogicalVolume(
                 calorimeterS,     // its solid
                 defaultMaterial,  // its material
                 "Calorimeter");   // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 calorLV,          // its logical volume                         
                 "Calorimeter",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
   
  //                                 
  // Layer
  //
  auto layerS 
    = new G4Box("Layer",           // its name
                 calorSizeXY/2, calorSizeXY/2, layerThickness/2); //its size
                         
  auto layerLV
    = new G4LogicalVolume(
                 layerS,           // its solid
                 defaultMaterial,  // its material
                 "Layer");         // its name

  new G4PVReplica(
                 "Layer",          // its name
                 layerLV,          // its logical volume
                 calorLV,          // its mother
                 kZAxis,           // axis of replication
                 fNofLayers,        // number of replica
                 layerThickness);  // witdth of replica
  
  //                               
  // Absorber
  //
  auto absorberS 
    = new G4Box("Abso",            // its name
                 calorSizeXY/2, calorSizeXY/2, absoThickness/2); // its size
                         
  auto absorberLV
    = new G4LogicalVolume(
                 absorberS,        // its solid
                 absorberMaterial, // its material
                 "AbsoLV");        // its name
                                   
   new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -gapThickness/2), // its position
                 absorberLV,       // its logical volume                         
                 "Abso",           // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // Gap
  //
  auto gapS 
    = new G4Box("Gap",             // its name
                 calorSizeXY/2, calorSizeXY/2, gapThickness/2); // its size
                         
  auto gapLV
    = new G4LogicalVolume(
                 gapS,             // its solid
                 gapMaterial,      // its material
                 "GapLV");         // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., absoThickness/2), // its position
                 gapLV,            // its logical volume                         
                 "Gap",            // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
 
  //
  // print parameters
  //
  G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    << "---> The calorimeter is " << fNofLayers << " layers of: [ "
    << absoThickness/mm << "mm of " << absorberMaterial->GetName() 
    << " + "
    << gapThickness/mm << "mm of " << gapMaterial->GetName() << " ] " << G4endl
    << "------------------------------------------------------------" << G4endl;
  
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  calorLV->SetVisAttributes(simpleBoxVisAtt);

  //
  // Always return the physical World
  //
  return worldPV;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void B4cDetectorConstruction::ConstructSDandField()
{
  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  // 
  // Sensitive detectors
  //
  auto absoSD 
    = new B4cCalorimeterSD("AbsorberSD", "AbsorberHitsCollection", fNofLayers);
  G4SDManager::GetSDMpointer()->AddNewDetector(absoSD);
  SetSensitiveDetector("AbsoLV",absoSD);

  auto gapSD 
    = new B4cCalorimeterSD("GapSD", "GapHitsCollection", fNofLayers);
  G4SDManager::GetSDMpointer()->AddNewDetector(gapSD);
  SetSensitiveDetector("GapLV",gapSD);

  // 
  // Magnetic field
  //
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
