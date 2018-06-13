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
// $Id: B4PrimaryGeneratorAction.cc 100946 2016-11-03 11:28:08Z gcosmo $
// 
/// \file B4PrimaryGeneratorAction.cc
/// \brief Implementation of the B4PrimaryGeneratorAction class

#include "B4PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4PrimaryGeneratorAction::B4PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr)
{
  // for neutrino mode

  _mcrec[0] = new NtpMCEventRecord();
  _mcrec[1] = new NtpMCEventRecord();

  
  G4String active_mat_file  = "genie_active.root";//config.GetSParam("active_material_data");
  _genieFiles[0] = new TFile( active_mat_file.data(), "read" );
  _genieData[0] = dynamic_cast <TTree *>( _genieFiles[0]->Get("gtree")  );
  _genieData[0]->SetBranchAddress("gmcrec", &_mcrec[0]);
  
  // Only get Iron target events if there is iron.
  G4String passive_mat_file = "genie_passive.root";//config.GetSParam("passive_material_data");
    _genieFiles[1] = new TFile( passive_mat_file.data(), "read" );
    _genieData[1] = dynamic_cast <TTree *>(_genieFiles[1]->Get("gtree")  );
    _genieData[1]->SetBranchAddress("gmcrec", &_mcrec[1]);
    
    
    //_fsl_select = config.PeekIParam("FSL_Select") ? config.GetIParam("FSL_Select") : 0;
    
    _evCount[0] = 0; _evCount[1] = 0;
    //if ( MindConfigService::Instance().Geometry().PeekIParam("TASD") )
    //_tasd = MindConfigService::Instance().Geometry().GetIParam("TASD");
    //else _tasd = false;
    _tasd = true;
    
    // _had4P = bhep::vdouble(4);
    //_fspdg = bhep::vdouble(6);
    //for(int i=0; i<6; i++) _fspdg[i] = 0;
  
  
  /*
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  
  auto particleDefinition 
    = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  //fParticleGun->SetParticleEnergy(3000.*MeV);
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4PrimaryGeneratorAction::~B4PrimaryGeneratorAction()
{
  //delete fParticleGun;

  // for neutrino mode
  
  delete _genieData[0];
  _genieFiles[0]->Close();
  delete _genieFiles[0];
  
  //if ( _genieFiles[1] ) {
  delete _genieData[1];
  _genieFiles[1]->Close();
  delete _genieFiles[1];
  //}
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume 
  // from G4LogicalVolumeStore
  //

  // for neutrino mode

  bool neutrinoMode = false;//true;

  // When not in neutrino mode, use fix energy or spectrum.
  
  bool energySpectrum = true;
  
  if(neutrinoMode)
  {
  
    G4String region_name = "TASD";//"WAGASCIDetectorMod";//"PASSIVE";//"ACTIVE","TASD"
    G4int region_code = region_name.contains("PASSIVE") ? 1 : 0;

    (void) _genieData[region_code]->GetEntry( _evCount[region_code] );
   _genieData[region_code]->Show(_evCount[region_code]);

   // find some vertex position for the volume. TASD, randomly inside. Passive, random module random pos inside. For now just 0. Ask the geometry for positions!

   B4cDetectorConstruction* detConstr = (B4cDetectorConstruction*) 
     G4RunManager::GetRunManager()->GetUserDetectorConstruction();
   
   G4ThreeVector position = detConstr->GetVertex( region_name );
   
   //G4ThreeVector position = G4ThreeVector(0,0,-2000);
   G4double time = 0.;
   
   G4PrimaryVertex* vertex = new G4PrimaryVertex(position, time);
   
   EventRecord & gEvent = *(_mcrec[region_code]->event);
   
   //Event information.
   //Interaction* gInt = gEvent.Summary();
   //GHepParticle* fsl = gEvent.FinalStatePrimaryLepton();

   TObjArrayIter iter(&gEvent);
   GHepParticle *part = dynamic_cast<GHepParticle *>(iter.Next());//0;
   int pStatus, pdg;// fslcount=0;

   while ( part != NULL ){
     //Get particle status.
     pStatus = part->Status();
     
     pdg = part->Pdg();
  
     if ( pStatus == 1 && pdg < 2000000000 ) { //stable final state.

       G4ParticleDefinition* particle_def = G4ParticleTable::GetParticleTable()->FindParticle( pdg );

       G4PrimaryParticle* particle =  new G4PrimaryParticle(particle_def, part->Px()*GeV, part->Py()*GeV, part->Pz()*GeV);
	 
	 particle->SetMass(particle_def->GetPDGMass());
       
       particle->SetCharge( part->Charge() );
       
       //if ( part == fsl ){
	 // G4cout<<part->Pdg()<<"\t"<<part->E()<<G4endl;
	 vertex->SetPrimary(particle);
	 //}
     }  
     
     part = dynamic_cast<GHepParticle *>(iter.Next());
   }//end of while

   anEvent->AddPrimaryVertex(vertex);
   
   _evCount[region_code]++;
   _mcrec[region_code]->Clear();
}
   
  // end of neutrino mode
  else{
    //G4double worldZHalfLength = 0.;
    //auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
    
    // Check that the world volume has box shape
    /*
      G4Box* worldBox = nullptr;
      if (  worldLV ) {
      worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
      }
      
      if ( worldBox ) {
      worldZHalfLength = worldBox->GetZHalfLength();  
      }
      else  {
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()",
    "MyCode0002", JustWarning, msg);
    } 
    */
    /*
      G4PrimaryVertex* vertex = new G4PrimaryVertex(G4ThreeVector(0.0,0.0,-.5*worldZHalfLength), 0.0);
    */
  // Set gun position
  //fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -.2*worldZHalfLength));
    
    G4int nofParticles = 1;
    
    fParticleGun = new G4ParticleGun(nofParticles);
    
    auto particleDefinition 
    = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particleDefinition);
    
    fParticleGun->SetParticleEnergy(0.0);
    
    G4double min = 200. *MeV;
    G4double max = 10000. *MeV;
    
    G4double momentum = 3000. * MeV;

    if(energySpectrum)
      momentum = (G4UniformRand() * (max - min) + min);

    
    fParticleGun->SetParticleMomentum(G4ThreeVector(0.,0.,momentum));
    
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -3000.0));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
  /*
    G4PrimaryParticle* particle = new G4PrimaryParticle(G4ParticleTable::GetParticleTable()->FindParticle("mu-"), 0.0,0.0,3000.0);
    
    particle->SetMass(G4ParticleTable::GetParticleTable()->FindParticle("mu-")->GetPDGMass());
    particle->SetCharge(G4ParticleTable::GetParticleTable()->FindParticle("mu-")->GetPDGCharge());
    particle->SetPolarization(0.,0.,0.);
    vertex->SetPrimary(particle);
    anEvent->AddPrimaryVertex(vertex);
  */
    delete fParticleGun;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

