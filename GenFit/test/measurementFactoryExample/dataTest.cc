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
#include <cstdlib>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#include <KalmanFittedStateOnPlane.h>
#include <KalmanFitterInfo.h>
#include <AbsKalmanFitter.h>
#include <KalmanFitter.h>
#include <DAF.h>

//Declaring global jmp_buf variable to be used by both main and signal handler
jmp_buf buf;

struct sortByZ
{
    inline bool operator() (const TVector3& struct1, const TVector3& struct2)
    {
        return (struct1[2] < struct2[2]);
    }
};

void magic_handler(int s)
{
    switch(s)
    {
        case SIGSEGV:
        printf("\nSegmentation fault signal caught! Attempting recovery..");
        longjmp(buf, 1);
        break;
    }
}

int main(int argc, char* argv[]) {

  //std::cout << argv[0] << std::endl;
  //std::cout << argv[1] << std::endl;

int lowerEventNum = atoi(argv[1]);
int higherEventNum = atoi(argv[2]);
  
gRandom->SetSeed(14);

  // init MeasurementCreator
  //genfit::MeasurementCreator measurementCreator;


  // init geometry and mag. field
  new TGeoManager("Geometry", "Geane geometry");
  //TGeoManager::Import("genfitGeom.root");
  TGeoManager::Import("../../../MIND.gdml");
  //genfit::FieldManager::getInstance()->init(new genfit::ConstField(0.,0., 15.)); // 15 kGauss
  //genfit::FieldManager::getInstance()->init(new genfit::ConstField(-15.,0., 0.)); //1.5 Tesla.
  genfit::FieldManager::getInstance()->init(new genfit::ConstField(15.,0., 0.)); //1.5 Tesla.
  genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());

  genfit::MaterialEffects::getInstance()->setMscModel("Highland");

  //genfit::EventDisplay* display = genfit::EventDisplay::getInstance();
  
  genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitter();//new genfit::KalmanFitterRefTrack();
  fitter->setMaxIterations(10);
  fitter->setMinIterations(8);

  const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToPrediction;
  fitter->setMultipleMeasurementHandling(mmHandling);

  TClonesArray myDetectorHitArray("genfit::mySpacepointDetectorHit");

  // init the factory
  int myDetId(1);
  genfit::MeasurementFactory<genfit::AbsMeasurement> factory;
  genfit::MeasurementProducer<genfit::mySpacepointDetectorHit, genfit::mySpacepointMeasurement> myProducer(&myDetectorHitArray);
  factory.addProducer(myDetId, &myProducer);
  
  //TFile *inFile=new TFile("data.root","READONLY");
  //TFile *inFile=new TFile("/root/NewSaRoMaN/neutrinoData/Event_31_May_1.root","READONLY");
  //TFile *inFile=new TFile("/root/NewSaRoMaN/neutrinoData/Event_30_May_6.root","READONLY");
  //TFile *inFile=new TFile("/root/NewSaRoMaN/neutrinoData/Event_28_May_1.root","READONLY");
  TFile *inFile=new TFile("/root/NewSaRoMaN/neutrinoData/Event_31_May_1.root","READONLY");

  /*
24 2,3,5
25 1,3
27 1
28 1 
29 1
30 1,2,3,4,5,6
31 1


   */
  
  TTree *tr=(TTree*)inFile->Get("events");

  // Create the out root file and fix all branches
  TFile outFile("out.root","recreate");
  TTree* tree = new TTree("tree","A ROOT TREE");

  double o_mctr_mom = 0.0;
  double o_mctr_charge = 0.0;
  double o_mctr_eng = 0.0;
  int o_event = 0;
  int o_first = 0;
  int o_second = 0;
  int o_third = 0;
  int o_forth = 0;
  int o_charge = 0;
  double o_mom = 0.0;
  double o_mom_range = 0.0;
  double o_cov = 0.0;
  double o_track_len = 0.0;
  double o_true_track_len = 0.0;
  std::vector<double> *o_vposX=0;
  std::vector<double> *o_vposY=0;
  std::vector<double> *o_vposZ=0;
  std::vector<double> *o_vmomZ=0;
  std::vector<double> *o_recvposX=0;
  std::vector<double> *o_recvposY=0;
  std::vector<double> *o_recvposZ=0;
  std::vector<int> *o_vPDG=0;
  std::vector<double> *o_mom_pos=0;
  int o_fitted = 0;
  double o_chi2=0.0;
  double o_ndf =0.0;
  int o_converged=0;
  int o_failedPoints=0;
  double o_pval=0.0;
  double o_rec_angle=0.0;
  double o_mc_angle=0.0;
  int o_failCode = 0;

  tree->Branch("MC_positionX",&o_vposX);
  tree->Branch("MC_positionY",&o_vposY);
  tree->Branch("MC_positionZ",&o_vposZ);
  tree->Branch("MC_momentumZ",&o_vmomZ);
  tree->Branch("pdg",&o_vPDG);
  tree->Branch("MCtr_Mom",&o_mctr_mom);
  tree->Branch("MCtr_Charge",&o_mctr_charge);
  tree->Branch("MCtr_Energy",&o_mctr_eng);
  tree->Branch("Event",&o_event);
  tree->Branch("Rec_Charge",&o_charge);
  tree->Branch("Rec_mom",&o_mom);
  tree->Branch("Rec_mom_pos",&o_mom_pos);
  tree->Branch("Rec_mom_range",&o_mom_range);
  tree->Branch("Rec_cov",&o_cov);
  tree->Branch("Rec_track_len",&o_track_len);
  tree->Branch("MC_track_len",&o_true_track_len);
  tree->Branch("Rec_positionX",&o_recvposX);
  tree->Branch("Rec_positionY",&o_recvposY);
  tree->Branch("Rec_positionZ",&o_recvposZ);
  tree->Branch("Fitted",&o_fitted);
  tree->Branch("Chi2",&o_chi2);
  tree->Branch("NDF",&o_ndf);
  tree->Branch("Converged",&o_converged);
  tree->Branch("failedPoints",&o_failedPoints);
  tree->Branch("Pval",&o_pval);
  tree->Branch("MC_angle",&o_mc_angle);
  tree->Branch("Rec_angle",&o_rec_angle);
  tree->Branch("FailCode",&o_failCode);
  tree->Branch("First",&o_first);
  tree->Branch("Second",&o_second);
  tree->Branch("Third",&o_third);
  tree->Branch("Forth",&o_forth);
  
  //std::ofstream myfile;
  //myfile.open ("example2.txt",std::ofstream::out | std::ofstream::app);

  // the data file is read in once, providing all of the event data.

  std::vector<double> *vposX=0;
  std::vector<double> *vposY=0;
  std::vector<double> *vposZ=0;
  std::vector<double> *vEventNum=0;

  tr->SetBranchAddress("_PosX",&vposX);
  tr->SetBranchAddress("_PosY",&vposY);
  tr->SetBranchAddress("_PosZ",&vposZ);
  tr->SetBranchAddress("_EventNum",&vEventNum);
  
  tr->GetEntry(0);
  
  // main loop
  for (int iEvent=lowerEventNum; iEvent<higherEventNum; ++iEvent){
    std::cout<<"Event Num="<<iEvent<<std::endl;

    o_event = iEvent;
    o_vposX->clear();
    o_vposY->clear();
    o_vposZ->clear();
 
    std::vector<TVector3> eventHits;

    o_first=0;
    o_second=0;
    o_third=0;
    o_forth=0;

    //Fill the out root file with simulation parameters.
    /*
    o_vposX=vposX;
    o_vposY=vposY;
    o_vposZ=vposZ;
    o_vmomZ=vmomZ;
    o_vPDG=vPDG;
    o_mctr_mom=mctr_mom;
    o_mctr_eng=mctr_eng;
    o_mctr_charge=mctr_charge;
    */
    myDetectorHitArray.Clear();
    
    //TrackCand
    genfit::TrackCand myCand;
    
    // Provide the fitter with an initial guess.
    TVector3 pos(0, 0, -300); //cm random low number
    TVector3 mom(0,0,2.0); // GeV random number

    double maxZ = - 9000; //random small
    double minZ = 9000; // random large
    
    
    // track model
    const int pdg = -13;// particle pdg code
    const int refcharge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/3.0;
    
    // covariance
    double resolution = 1.0;//0.01; //cm
    TMatrixDSym cov(3);
    for (int i = 0; i < 3; ++i)
      cov(i,i) = resolution*resolution;

    for(unsigned int i=0; i<vposY->size(); i++){
      TVector3 currentPos;
      
      //std::cout<<i<<std::endl;
      double posX = vposX->at(i);
      double posY = vposY->at(i);
      double posZ = vposZ->at(i);
      double eventNum = vEventNum->at(i);
      //std::cout<<"passed"<<std::endl;

      // split proton and muon tracks? Need the angle... Use angle from muon assuming neutrino straight in.
      // same way as before, find track in MIND and find best hits that fit in track?

      //instead of pattern rec, just artificially use only muon hits. (Not perfect)
      // For us, enough with cuts on energy dep, checking that hit lines up with track parts.
      
      if(eventNum==iEvent)
	  {
	    //mapping
	    if(posZ==-40)
	      {
		posZ= -1627;
		o_first = 1;
	      }
	    else if(posZ==183)
	      {
		posZ= -1376.6;
		o_second = 1;
	      }
	    else if(posZ==387)
	      {
		posZ= -1207.3;
		o_third = 1;
	      }
	    else if(posZ==497)
	      {
		posZ= -1101.5;
		o_forth = 1;
	      }
	    else if(posZ==607) posZ= -989.6;
	    else if(posZ==849) posZ= -902.3;
	    else if(posZ==1027) posZ= -725.2;
	    else if(posZ==1342) posZ= -555;
	    else if(posZ==1521) posZ= -381;
	    else if(posZ==1828) posZ= -214.25;
	    else if(posZ==2121) posZ= 49.3;
	    else if(posZ==2327) posZ= 369.3;
	    else if(posZ==2551) posZ= 424.3;
	    else if(posZ==2755) posZ= 719.5;
	    else if(posZ==3200) posZ= 763;
	    else if(posZ==3520) posZ= 1068;
	    else if(posZ==3944) posZ= 1430.5;
	    else if(posZ==4044) posZ= 1568;


	    o_vposX->push_back(posX);
	    o_vposY->push_back(posY);
	    o_vposZ->push_back(posZ);
	    
	  currentPos.SetX(posX/10.0);
	  currentPos.SetY(posY/10.0);
	  currentPos.SetZ(posZ/10.0);

	  if(posZ>maxZ) maxZ = posZ;

	  if(posZ<minZ) minZ = posZ;

	  eventHits.push_back(currentPos);

	  std::cout<<posX<<"\t"<<posY<<"\t"<<posZ<<std::endl;
	  
	  
	  // Fill the TClonesArray and the TrackCand
	  // In a real experiment, you detector code would deliver mySpacepointDetectorHits and fill the TClonesArray.
	  // The patternRecognition would create the TrackCand.
	  new(myDetectorHitArray[i]) genfit::mySpacepointDetectorHit(currentPos, cov);
	  myCand.addHit(myDetId, i);

	  }
    } // End of for loop
    if(myCand.getNHits()<2)
      {
	o_fitted = 0;
	o_failCode = 1;
	tree->Fill();
	continue;
      }
    else
      {
	std::sort(eventHits.begin(),eventHits.end(),sortByZ());
	
	TVector3 diff = eventHits[1]-eventHits[0];
	
	// Angle from initial neutrino
	TVector3 neutrino(0,0,1);
	
	o_mc_angle = diff.Angle(neutrino);
	    
      }


    o_true_track_len = maxZ-minZ;
    
    //std::cout<<"end for"<<std::endl;


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
      covSeed(i,i) = pow(resolution / 18 / sqrt(3), 2);

    // set start values and pdg to cand
    myCand.setPosMomSeedAndPdgCode(posM, momM, pdg);
    myCand.setCovSeed(covSeed);

    //std::cout<<"before track"<<std::endl;
    genfit::AbsTrackRep* rep = new genfit::RKTrackRep(pdg);
    // create track
    //genfit::Track fitTrack(myCand, factory,new genfit::RKTrackRep(pdg));
    genfit::Track fitTrack(myCand, factory,rep);
    //fitTrack.reverseTrackPoints(); //provides better fit.
    
    //std::cout<<"trying to fit"<<std::endl;
    //std::cout<<myCand.getNHits()<<std::endl;

    signal(SIGSEGV, magic_handler); // prepare segfault handler

    if(!setjmp(buf)) // handle the strange segfault error.
      {
    
    // do the fit
    try{
      TVector3 pos2;
      TVector3 mom2;
      TMatrixDSym cov2;
      fitter->processTrack(&fitTrack);
      fitTrack.checkConsistency();
      fitTrack.getFittedState().getPosMomCov(pos2,mom2,cov2);
      /*
      genfit::TrackPoint* tp = fitTrack.getPointWithMeasurementAndFitterInfo(fitTrack.getNumPoints()-1, rep);
      genfit::KalmanFittedStateOnPlane kfsop(*(static_cast<genfit::KalmanFitterInfo*>(tp->getFitterInfo(rep))->getBackwardUpdate()));
      rep->extrapolateToPlane(kfsop, fitTrack.getFittedState().getPlane());
      const TVectorD& state = kfsop.getState();
      */
      //fitTrack.getCardinalRep()->getPosMomCov(fitTrack.getFittedState(),pos2,mom2,cov2);
      //fitTrack.getFittedState(fitTrack.getNumPoints()-1).getPosMomCov(pos2,mom2,cov2);
      //int reccharge = refcharge*fitTrack.getFittedState().getCharge();
      //charge comes back as a true/false value. True given pdg assumption.
      
      double length = fitTrack.getTrackLen()*10;
      genfit::FitStatus* status = fitTrack.getFitStatus();

      //std::cout<<refcharge<<"\t"<<status->getCharge()<<std::endl;
      
      //if(fitTrack.getFittedState().getCharge())
      /*
      if(status->getCharge()==1)
	{
	  o_charge = refcharge;
	}
      else
	{
	  o_charge = -refcharge;
	}
      */
      
      o_charge = status->getCharge();
      o_chi2 = status->getChi2();
      o_ndf = status->getNdf();
      o_fitted = status->isFitted(); //fitter->isTrackFitted(track, rep);
      o_converged = status->isFitConvergedFully();
      o_failedPoints = status->getNFailedPoints();
      o_pval = status->getPVal();

      //Fill the out root file with rec parameters.
      //o_event = iEvent;
      //o_charge = reccharge;
      //o_mom = 1000.0/state[0];//
      o_mom = mom2[2]*1000.0;
      o_cov = sqrt(cov2[0][0])*1000;
      o_track_len = length;

      // Formula from fitting true length to Momentum
      o_mom_range = 49.4328 + 0.5473 * length;

      o_recvposX->clear();
      o_recvposY->clear();
      o_recvposZ->clear();
      o_mom_pos->clear();

      for(unsigned counter = 0; counter<fitTrack.getNumPoints();counter++)
	{
	  fitTrack.getFittedState(counter).getPosMomCov(pos2,mom2,cov2);
	  o_recvposX->push_back(pos2[0]*10.0);
	  o_recvposY->push_back(pos2[1]*10.0);
	  o_recvposZ->push_back(pos2[2]*10.0);
	  o_mom_pos->push_back(mom2[2]*1000.0);
	  //std::cout<<pos2[2]*10.0<<std::endl;
	  
	  //myfile << mom2[2]<<"\t"<<fitTrack.getFittedState(counter).getCharge()<<"\t"<<mom2[2]<<"\t"<<pos2.Z()<<"\n";
	}

      // Angle calculation
      //fitTrack.reverseTrackPoints();// Back to normal order

      if(fitTrack.getNumPoints()>1)
	{
	  // Angle from muon track
	  TVector3 pos0;
	  TVector3 pos1;
	  TVector3 dummyV;
	  TMatrixDSym dummyM;
	  fitTrack.getFittedState(0).getPosMomCov(pos0,dummyV,dummyM);
	  //fitTrack.getFittedState(fitTrack.getNumPoints()-1).getPosMomCov(pos0,dummyV,dummyM);
	  //fitTrack.getFittedState(fitTrack.getNumPoints()-2).getPosMomCov(pos1,dummyV,dummyM);
	  fitTrack.getFittedState(1).getPosMomCov(pos1,dummyV,dummyM);

	  TVector3 diff = pos1-pos0;

	// Angle from initial neutrino
	  TVector3 neutrino(0,0,1);

	  o_rec_angle = diff.Angle(neutrino);

	  //std::cout<<angle<<std::endl;
	}
      

      
      //myfile << iEvent <<"\t"<< mctr_mom/1000.0 <<"\t"<<reccharge<<"\t"<<mom2[2]<<"\t"<<sqrt(cov2[0][0])<<"\t"<<length<<"\n";
    }
    catch(genfit::Exception& e){
      //cerr ->cout
      std::cout << e.what();
      std::cout << "Exception, next track" << std::endl;
      //myfile << iEvent <<"\t"<< mctr_mom/1000.0 <<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\n";
      o_fitted = 0;
      o_failCode = 2;
      tree->Fill();
      continue;
    }
    catch(...){
      std::cout << "Exception, next track" << std::endl;
      //myfile << iEvent <<"\t"<< mctr_mom/1000.0 <<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\n";
      o_fitted = 0;
      o_failCode = 3;
      tree->Fill();
      continue;
    }

      }
    else
      {
	printf("\nSuccessfully recovered! Welcome back in main!!\n\n");
	o_fitted = 0;
	o_failCode = 4;
	tree->Fill();
	continue;
      }

    //std::cout<<"after fit"<<std::endl;

    //fitTrack.checkConsistency();

    /* did not work?
    std::cout<<"before"<<std::endl;
    std::cout<<fitTrack.hasFitStatus()<<std::endl;
    std::cout<<fitTrack.hasFitStatus(rep)<<std::endl;
    if(!fitTrack.hasFitStatus())
      {
	//delete fitter;
	continue;
      }
    */
    //std::cout<<"after"<<std::endl;
    /*
    TVector3 pos2;
    TVector3 mom2;
    TMatrixDSym cov2;
    */
    //fitTrack.getFittedState().Print();
    /*
    for(unsigned counter = 0; counter<fitTrack.getNumPoints();counter++)
      {
    fitTrack.getFittedState(counter).getPosMomCov(pos2,mom2,cov2);
    myfile << mom2[2]<<"\t"<<fitTrack.getFittedState(counter).getCharge()<<"\t"<<mom2[2]<<"\t"<<pos2.Z()<<"\n";
      }
    */
    //std::cout<<"before file write"<<std::endl;
    /*
    fitTrack.getFittedState().getPosMomCov(pos2,mom2,cov2);
    myfile << iEvent <<"\t"<< mctr_mom/1000.0 <<"\t"<<fitTrack.getFittedState().getCharge()<<"\t"<<mom2[2]<<"\t"<<sqrt(cov2[0][0])<<fitTrack.getTrackLen()*10<<"\n";
    */
    //std::cout<<"display event"<<std::endl;
    /*
    if (iEvent < 1000) {
      // add track to event display
      display->addEvent(&fitTrack);
    }
    */
    //std::cout<<"ended loop of event"<<std::endl;

    o_failCode = 0;
    tree->Fill();
    
  }// end loop over events

  delete fitter;

  //tree->Write();
  outFile.Write();
  //outFile.close();
  
  //myfile.close();
  
  // open event display
  //display->open();

  return 0;
}


