#include <ConstField.h>
#include <Exception.h>
#include <FieldManager.h>
#include <KalmanFitterRefTrack.h>
#include <StateOnPlane.h>
#include <Track.h>
#include <TrackCand.h>
#include <TrackPoint.h>

#include <MeasurementProducer.h>
#include <MeasurementFactory.h>

#include "mySpacepointDetectorHit.h"
#include "mySpacepointMeasurement.h"

#include <MaterialEffects.h>
#include <RKTrackRep.h>
#include <TGeoMaterialInterface.h>

#include <EventDisplay.h>

#include <HelixTrackModel.h>
#include <MeasurementCreator.h>

#include <TDatabasePDG.h>
#include <TEveManager.h>
#include <TGeoManager.h>
#include <TRandom.h>
#include <TVector3.h>
#include <vector>

#include "TDatabasePDG.h"
#include <TMath.h>

#include "TFile.h"
#include "TTree.h"
#include <fstream>


int main() {

gRandom->SetSeed(14);

  // init MeasurementCreator
  //genfit::MeasurementCreator measurementCreator;


  // init geometry and mag. field
  new TGeoManager("Geometry", "Geane geometry");
  //TGeoManager::Import("genfitGeom.root");
  TGeoManager::Import("MIND.gdml");
  //genfit::FieldManager::getInstance()->init(new genfit::ConstField(0.,0., 15.)); // 15 kGauss
  genfit::FieldManager::getInstance()->init(new genfit::ConstField(15.,0., 0.));
  genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());

  //genfit::MaterialEffects::getInstance()->setDebugLvl();
  //genfit::MaterialEffects::getInstance()->drawdEdx(13);

  //auto material =new genfit::TGeoMaterialInterface();

  //material->setDebugLvl(2);
  
  //genfit::MaterialEffects::getInstance()->init(material);

  //material->setDebugLvl(2);
  

  // init event display
  genfit::EventDisplay* display = genfit::EventDisplay::getInstance();


  // init fitter
  genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitterRefTrack();


  TClonesArray myDetectorHitArray("genfit::mySpacepointDetectorHit");

  // init the factory
  int myDetId(1);
  genfit::MeasurementFactory<genfit::AbsMeasurement> factory;
  genfit::MeasurementProducer<genfit::mySpacepointDetectorHit, genfit::mySpacepointMeasurement> myProducer(&myDetectorHitArray);
  factory.addProducer(myDetId, &myProducer);
  
  TFile *f=new TFile("B4.root");
  TTree *tr=(TTree*)f->Get("B4");
  
  std::ofstream myfile;
  myfile.open ("example2.txt");
  
  // main loop
  for (unsigned int iEvent=0; iEvent<1000; ++iEvent){

    std::cout<<"Event Num="<<iEvent<<std::endl;
    
    if(iEvent==483 || iEvent==666) continue; // Why does this one break??!?!?!
    // it has no hits with pdg 13 for some reason??
      
    std::vector<double> *vposX=0;
    std::vector<double> *vposY=0;
    std::vector<double> *vposZ=0;
    std::vector<int> *vPDG=0;
    int eventIDR = 0;
    tr->SetBranchAddress("positionX",&vposX);
    tr->SetBranchAddress("positionY",&vposY);
    tr->SetBranchAddress("positionZ",&vposZ);
    tr->SetBranchAddress("pdg",&vPDG);
    tr->SetBranchAddress("EventID",&eventIDR);
    
    tr->GetEntry(iEvent);

    myDetectorHitArray.Clear();
    
    //TrackCand
    genfit::TrackCand myCand;
    
    // true start values
    TVector3 pos(0, 0, -200);
    TVector3 mom(0,0,-3.0);
    //mom.SetPhi(gRandom->Uniform(0.,2*TMath::Pi()));
    //mom.SetTheta(gRandom->Uniform(0.4*TMath::Pi(),0.6*TMath::Pi()));
    //mom.SetMag(gRandom->Uniform(0.2, 1.));
    
    
    // helix track model
    const int pdg = 13;               // particle pdg code
    const double charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/(3.);
    //genfit::HelixTrackModel* helix = new genfit::HelixTrackModel(pos, mom, charge);
    //measurementCreator.setTrackModel(helix);
    
    
    unsigned int nMeasurements = gRandom->Uniform(5, 15);
    
    // covariance
    double resolution = 5.0;//0.01;
    TMatrixDSym cov(3);
    for (int i = 0; i < 3; ++i)
      cov(i,i) = resolution*resolution;

    //for(unsigned int i=0; i<vposY->size(); i++){
    for(unsigned int i=vposY->size()-1; i<-1; i--){
TVector3 currentPos;
  //for (unsigned int i=0; i<nMeasurements; ++i) {
      // "simulate" the detector
      //TVector3 currentPos = helix->getPos(i*2.);
/*
      currentPos.SetX(gRandom->Gaus(currentPos.X(), resolution));
      currentPos.SetY(gRandom->Gaus(currentPos.Y(), resolution));
      currentPos.SetZ(gRandom->Gaus(currentPos.Z(), resolution));
*/

 int pdgR = vPDG->at(i);
 double posX = vposX->at(i);
 double posY = vposY->at(i);
 double posZ = vposZ->at(i);
 if(pdgR==13 && posZ>-1800)
   {
     currentPos.SetX(posX/10.0);
     currentPos.SetY(posY/10.0);
     currentPos.SetZ(posZ/10.0);

      // Fill the TClonesArray and the TrackCand
      // In a real experiment, you detector code would deliver mySpacepointDetectorHits and fill the TClonesArray.
      // The patternRecognition would create the TrackCand.
      new(myDetectorHitArray[i]) genfit::mySpacepointDetectorHit(currentPos, cov);
      myCand.addHit(myDetId, i);
    }
}


    // smeared start values (would come from the pattern recognition)
    //const bool smearPosMom = true;   // init the Reps with smeared pos and mom
    //const double posSmear = 0.1;     // cm
    //const double momSmear = 3. /180.*TMath::Pi();     // rad
    //const double momMagSmear = 0.1;   // relative

    TVector3 posM(pos);
    TVector3 momM(mom);
    //TVector3 pos(0, 0, -200);
    //TVector3 mom(0,0,5.0);

    /*
    if (smearPosMom) {
      posM.SetX(gRandom->Gaus(posM.X(),posSmear));
      posM.SetY(gRandom->Gaus(posM.Y(),posSmear));
      posM.SetZ(gRandom->Gaus(posM.Z(),posSmear));

      momM.SetPhi(gRandom->Gaus(mom.Phi(),momSmear));
      momM.SetTheta(gRandom->Gaus(mom.Theta(),momSmear));
      momM.SetMag(gRandom->Gaus(mom.Mag(), momMagSmear*mom.Mag()));
    }
    */

    // initial guess for cov
    TMatrixDSym covSeed(6);
    for (int i = 0; i < 3; ++i)
      covSeed(i,i) = resolution*resolution;
    for (int i = 3; i < 6; ++i)
      covSeed(i,i) = pow(resolution / nMeasurements / sqrt(3), 2);


    // set start values and pdg to cand
    myCand.setPosMomSeedAndPdgCode(posM, momM, pdg);
    myCand.setCovSeed(covSeed);


    // create track
    genfit::Track fitTrack(myCand, factory, new genfit::RKTrackRep(pdg));


    // do the fit
    try{
      fitter->processTrack(&fitTrack);
    }
    catch(genfit::Exception& e){
      std::cerr << e.what();
      std::cerr << "Exception, next track" << std::endl;
      continue;
    }

    fitTrack.checkConsistency();

    TVector3 pos2;
    TVector3 mom2;
    TMatrixDSym cov2;

    //fitTrack.getFittedState().Print();
    /*
    for(unsigned counter = 0; counter<fitTrack.getNumPoints();counter++)
      {
    fitTrack.getFittedState(counter).getPosMomCov(pos2,mom2,cov2);
    myfile << mom2[2]<<"\t"<<fitTrack.getFittedState(counter).getCharge()<<"\t"<<mom2[2]<<"\t"<<pos2.Z()<<"\n";
      }
    */
    fitTrack.getFittedState().getPosMomCov(pos2,mom2,cov2);
    myfile << (fabs(mom2[2])-fabs(-3.0)) / sqrt(cov2[0][0])<<"\t"<<fitTrack.getFittedState().getCharge()<<"\t"<<mom2[2]<<"\t"<<sqrt(cov2[0][0])<<"\n";
     
    
    if (iEvent < 1000) {
      // add track to event display
      display->addEvent(&fitTrack);
    }


  }// end loop over events

  delete fitter;

  myfile.close();
  
  // open event display
  display->open();

}


