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
// $Id: B4cEventAction.cc 100946 2016-11-03 11:28:08Z gcosmo $
// 
/// \file B4cEventAction.cc
/// \brief Implementation of the B4cEventAction class

#include "B4cEventAction.hh"
#include "B4cCalorimeterSD.hh"
#include "B4cCalorHit.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cEventAction::B4cEventAction()
 : G4UserEventAction(),
   fAbsHCID(-1),
   fGapHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cEventAction::~B4cEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cCalorHitsCollection* 
B4cEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection 
    = static_cast<B4cCalorHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::PrintEventStatistics(
                              G4double absoEdep, G4double absoTrackLength,
                              G4double gapEdep, G4double gapTrackLength) const
{
  // print event statistics
  G4cout
     << "   Absorber: total energy: " 
     << std::setw(7) << G4BestUnit(absoEdep, "Energy")
     << "       total track length: " 
     << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
     << G4endl
     << "        Gap: total energy: " 
     << std::setw(7) << G4BestUnit(gapEdep, "Energy")
     << "       total track length: " 
     << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::EndOfEventAction(const G4Event* event)
{  
  // Get hits collections IDs (only once)
  /*
  if ( fAbsHCID == -1 ) {
    fAbsHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("AbsorberHitsCollection");
    fGapHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("GapHitsCollection");
  */
  G4int collection_id = G4SDManager::GetSDMpointer()->GetCollectionID("MindCollection");

  //std::cout<<"collection_id="<<collection_id<<std::endl;
  
  //G4int collection_id = SDman->GetCollectionID("MindCollection");
  //(MindBarHitsCollection*)(HCE->GetHC(collection_id));
  //auto hitsCollection 
  //= static_cast<B4cCalorHitsCollection*>(
  //    event->GetHCofThisEvent()->GetHC(hcID));

  // Get hits collections
  //auto absoHC = GetHitsCollection(fAbsHCID, event);
  //auto gapHC = GetHitsCollection(fGapHCID, event);
  auto collection = static_cast<MindBarHitsCollection*>(event->GetHCofThisEvent()->GetHC(collection_id));

  //std::cout<<"collection="<<collection<<std::endl;
  
  // Get hit with total values
  //auto absoHit = (*absoHC)[absoHC->entries()-1];
  //auto gapHit = (*gapHC)[gapHC->entries()-1];

  auto collectionHit = (*collection)[collection->entries()-1];
  
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     
/*
    PrintEventStatistics(
      absoHit->GetEdep(), absoHit->GetTrackLength(),
      gapHit->GetEdep(), gapHit->GetTrackLength());
*/

  }  
  
  // Fill histograms, ntuple
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  /*
    int GetTrackID
    G4ThreeVector GetPosition
    double GetEnergyDeposit
    double GetHitTime
    G4ThreeVector GetBarTranslation
    string GetModule
    int GetBarOrientation
    int GetTASD
    int GetBarNumber
    G4ThreeVector GetMomentum
   */
  // fill histograms
  //analysisManager->FillH1(0, collectionHit->GetEnergyDeposit());
  //analysisManager->FillH1(1, collectionHit->GetModule());
  //analysisManager->FillH1(2, collectionHit->GetBarNumber());
  //analysisManager->FillH1(3, collectionHit->GetHitTime());
  
  // fill ntuple
  analysisManager->FillNtupleIColumn(0, collectionHit->GetTrackID());
  //std::cout<<collectionHit->GetTrackID()<<std::endl;

  //aStep->GetTrack()->GetDefinition()->GetParticleName()
  
  //std::cout<<"Here"<<std::endl;
  //if(collectionHit && collectionHit->GetTrackID()){
    //std::cout<<collectionHit->GetTrackID()<<std::endl;
  //std::cout<<"entries="<<collection->entries()<<std::endl;
  
   for (G4int i=0;i<collection->entries();i++) 
  {
    G4ThreeVector position = (*collection)[i]->GetPosition();
    G4ThreeVector momentum = (*collection)[i]->GetMomentum();
    analysisManager->FillNtupleDColumn(1,position.x());
    analysisManager->FillNtupleDColumn(2,position.y());
    analysisManager->FillNtupleDColumn(3,position.z());
    //std::cout<<"PosZ="<<position.z()<<std::endl;
    analysisManager->FillNtupleDColumn(4, (*collection)[i]->GetEnergyDeposit());
    analysisManager->FillNtupleDColumn(5, (*collection)[i]->GetHitTime());
    analysisManager->FillNtupleIColumn(6, (*collection)[i]->GetBarOrientation());
    
    G4double transbarpos = (*collection)[i]->GetBarOrientation()==1 ?
      (*collection)[i]->GetBarTranslation().y() : (*collection)[i]->GetBarTranslation().x();
    analysisManager->FillNtupleDColumn(7,transbarpos);
    
    G4double longbarpos = (*collection)[i]->GetBarTranslation().z();
    analysisManager->FillNtupleDColumn(8,longbarpos);
    
    analysisManager->FillNtupleIColumn(9, (*collection)[i]->GetTASD());
    analysisManager->FillNtupleIColumn(10, (*collection)[i]->GetBarNumber());
    analysisManager->FillNtupleDColumn(11,momentum.x());
    analysisManager->FillNtupleDColumn(12,momentum.y());
    analysisManager->FillNtupleDColumn(13,momentum.z());
    analysisManager->FillNtupleIColumn(14,(*collection)[i]->GetPDG());
    analysisManager->AddNtupleRow(); 
  } 
   //}
  
   //analysisManager->AddNtupleRow(); 
  
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
