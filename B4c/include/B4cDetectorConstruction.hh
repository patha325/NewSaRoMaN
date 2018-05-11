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
// $Id: B4cDetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4cDetectorConstruction.hh
/// \brief Definition of the B4cDetectorConstruction class

#ifndef B4cDetectorConstruction_h
#define B4cDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include <G4GDMLParser.hh>
#include <G4FieldManager.hh>
#include <G4ChordFinder.hh>
#include <fstream>
#include "MindBarSD.h"
#include "MindFieldMapR.hh"


class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In ConstructSDandField() sensitive detectors of B4cCalorimeterSD type
/// are created and associated with the Absorber and Gap volumes.
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class B4cDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  B4cDetectorConstruction();
  virtual ~B4cDetectorConstruction();
  
public:
  virtual G4VPhysicalVolume* Construct();
  //virtual void ConstructSDandField();
  
private:
  // methods
  //
  void DefineMaterials();
  //G4VPhysicalVolume* DefineVolumes();
  void SetVolumeInformation(G4VPhysicalVolume* pbase, G4String detectorName);
  void SetAuxInformation(G4String basename, G4LogicalVolume* myvol,
			 const G4GDMLAuxListType auxlist);


  void SetNullField(G4LogicalVolume& detector_logic);
  void SetMagneticField(G4LogicalVolume& vol);
  
  G4GDMLParser _gdml;
  double _detectormass;
  std::map<G4String, std::vector<G4VPhysicalVolume*> > regions;
  std::map<G4String, std::vector<G4ThreeVector> > regionoffset;
  std::map<G4String, double> regionmass;
  std::ofstream _myfile;
  std::vector<MindBarSD*> sensDetList;
  
  // data members
  //
  static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
  // magnetic field messenger
  
  G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
  G4int   fNofLayers;     // number of layers
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

