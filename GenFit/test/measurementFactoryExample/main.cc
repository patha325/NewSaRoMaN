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


struct Hit
{
  Hit() {};
  ~Hit() {};
  Hit(TVector3 inpos,int inpdg,double inmom,double inedep,double intime,
      double inbarPT,double inbarPZ,int inbarO,
      int inbarN,bool inTASD)
  {
    tposition=inpos;
    tpdg=inpdg;
    tmom=inmom;
    edep=inedep;
    time=intime;
    barPositionL=inbarPT;
    barPositionZ=inbarPZ;
    barOrientation=inbarO;
    barNumber=inbarN;
    TASD=inTASD;    
  };
  TVector3 tposition;
  int tpdg;
  double tmom;
  double edep;
  double time;
  double barPositionL;
  double barPositionZ;
  int barOrientation; // 1 is bars providing Y-position (Small bars) 0 is x bars.
  int barNumber;
  bool TASD;
  
};

struct ClusteredHit
{
  ClusteredHit() {};
  ~ClusteredHit() {};
  TVector3 clusteredPosition;
  double time;
  double combinedEdep;

  std::vector<Hit*> hitList;
};

struct Plane
{
  Plane() {};
  ~Plane() {};
  Plane(Hit* inHit )
  {
    hitList.push_back(inHit);
    combinedPositionZ=inHit->barPositionZ;
  };
  std::vector<Hit*> hitList;
  std::vector<ClusteredHit*> clusterHitList; 
  double combinedPositionZ;
};

//Declaring global jmp_buf variable to be used by both main and signal handler
jmp_buf buf;


struct sortByZ
{
  inline bool operator() (const TVector3& struct1, const TVector3& struct2)
    {
      return (struct1[2] < struct2[2]);
    }
  inline bool operator() (const Hit* struct1, const Hit* struct2)
  {
    return (struct1->barPositionZ < struct2->barPositionZ);
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
  genfit::FieldManager::getInstance()->init(new genfit::ConstField(-15.,0., 0.)); //1.5 Tesla.
  //genfit::FieldManager::getInstance()->init(new genfit::ConstField(15.,0., 0.)); //1.5 Tesla.
  genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());

  genfit::MaterialEffects::getInstance()->setMscModel("Highland");
  
  //genfit::MaterialEffects::getInstance()->setDebugLvl();
  //genfit::MaterialEffects::getInstance()->drawdEdx(13);

  //auto material =new genfit::TGeoMaterialInterface();

  //material->setDebugLvl(2);
  
  //genfit::MaterialEffects::getInstance()->init(material);

  //material->setDebugLvl(2);
  

  // init event display
  //genfit::EventDisplay* display = genfit::EventDisplay::getInstance();

  //const int nIter = 100; // max number of iterations // randomly chosen number.
  //const double dPVal = 1.E-6; // convergence criterion // random low number

  // init fitter
  //genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitterRefTrack(nIter,dPVal);
  //genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitterRefTrack();

  genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitter();//new genfit::KalmanFitterRefTrack();
  fitter->setMaxIterations(8); //10
  fitter->setMinIterations(4); //8

  const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToPrediction;
  fitter->setMultipleMeasurementHandling(mmHandling);


  TClonesArray myDetectorHitArray("genfit::mySpacepointDetectorHit");

  // init the factory
  int myDetId(1);
  genfit::MeasurementFactory<genfit::AbsMeasurement> factory;
  genfit::MeasurementProducer<genfit::mySpacepointDetectorHit, genfit::mySpacepointMeasurement> myProducer(&myDetectorHitArray);
  factory.addProducer(myDetId, &myProducer);
  
  TFile *inFile=new TFile("in.root","READONLY");
  TTree *tr=(TTree*)inFile->Get("B4");

  // Create the out root file and fix all branches
  TFile outFile("out.root","recreate");
  TTree* tree = new TTree("tree","A ROOT TREE");

  double o_mctr_mom = 0.0;
  double o_mctr_momX = 0.0;
  double o_mctr_momY = 0.0;
  double o_mctr_momZ = 0.0;
  double o_mctr_weight = 0.0;
  double o_mctr_charge = 0.0;
  double o_mctr_eng = 0.0;
  double o_vertPosX = 0.0;
  double o_vertPosY = 0.0;
  double o_vertPosZ = 0.0;
  int o_event = 0;
  int o_charge = 0;
  double o_mom = 0.0;
  double o_momX = 0.0;
  double o_momY = 0.0;
  double o_momZ = 0.0;
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
  int o_numHits = 0;
  int o_numPlanes = 0;
  double o_avrHitsPlanes = 0;
  std::vector<double> *o_plane_zpos=0;

  tree->Branch("MC_positionX",&o_vposX);
  tree->Branch("MC_positionY",&o_vposY);
  tree->Branch("MC_positionZ",&o_vposZ);
  tree->Branch("MC_VertexX",&o_vertPosX);
  tree->Branch("MC_VertexY",&o_vertPosY);
  tree->Branch("MC_VertexZ",&o_vertPosZ);
  tree->Branch("MC_momentumZ",&o_vmomZ);
  tree->Branch("pdg",&o_vPDG);
  tree->Branch("MCtr_Mom",&o_mctr_mom);
  tree->Branch("MCtr_MomX",&o_mctr_momX);
  tree->Branch("MCtr_MomY",&o_mctr_momY);
  tree->Branch("MCtr_MomZ",&o_mctr_momZ);
  tree->Branch("MCtr_Weight",&o_mctr_weight);
  tree->Branch("MCtr_Charge",&o_mctr_charge);
  tree->Branch("MCtr_Energy",&o_mctr_eng);
  tree->Branch("Event",&o_event);
  tree->Branch("Rec_Charge",&o_charge);
  tree->Branch("Rec_Mom",&o_mom);
  tree->Branch("Rec_MomX",&o_momX);
  tree->Branch("Rec_MomY",&o_momY);
  tree->Branch("Rec_MomZ",&o_momZ);
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
  tree->Branch("NumberofHits",&o_numHits);
  tree->Branch("NumberofPlanes",&o_numPlanes);
  tree->Branch("AvrHitsPerPlane",&o_avrHitsPlanes);
  tree->Branch("PlanesZPos",&o_plane_zpos);
  
  //std::ofstream myfile;
  //myfile.open ("example2.txt",std::ofstream::out | std::ofstream::app);


  // main loop
  for (int iEvent=lowerEventNum; iEvent<higherEventNum; ++iEvent){
  //for (unsigned int iEvent=0; iEvent<10; ++iEvent){
  //for (unsigned int iEvent=55655; iEvent<100000; ++iEvent){
    std::cout<<"Event Num="<<iEvent<<std::endl;
    
    //if(iEvent==34 || iEvent==666) continue; // Why does this one break??!?!?!
    // it has no hits with pdg 13 for some reason??

    std::vector<TVector3> eventHits;
    std::vector<Hit*> eventHitsV;
    std::vector<double> *vposX=0;
    std::vector<double> *vposY=0;
    std::vector<double> *vposZ=0;
    std::vector<double> *vmomZ=0;
    std::vector<int> *vPDG=0;
    std::vector<int> *vhedep=0;
    std::vector<int> *vhtime=0;
    std::vector<int> *vhbaror=0;
    std::vector<int> *vhtransbarpos=0;
    std::vector<int> *vhlongbarpos=0;
    std::vector<int> *vhbarnum=0;
    std::vector<int> *vTASD=0;
    //int eventIDR = 0;
    double mctr_mom =0.0;
    double mctr_momX =0.0;
    double mctr_momY =0.0;
    double mctr_momZ =0.0;
    double mctr_charge =0.0;
    double mctr_weight =0.0;
    double mctr_eng =0.0;
    double vert_X =0.0;
    double vert_Y =0.0;
    double vert_Z =0.0;
    
    tr->SetBranchAddress("positionX",&vposX);
    tr->SetBranchAddress("positionY",&vposY);
    tr->SetBranchAddress("positionZ",&vposZ);
    tr->SetBranchAddress("momentumZ",&vmomZ);
    tr->SetBranchAddress("pdg",&vPDG);
    //tr->SetBranchAddress("EventID",&eventIDR);
    tr->SetBranchAddress("MCtr_Mom",&mctr_mom);
    tr->SetBranchAddress("MCtr_MomX",&mctr_momX);
    tr->SetBranchAddress("MCtr_MomY",&mctr_momY);
    tr->SetBranchAddress("MCtr_MomZ",&mctr_momZ);
    tr->SetBranchAddress("MCtr_Weight",&mctr_weight);
    tr->SetBranchAddress("MCtr_Charge",&mctr_charge);
    tr->SetBranchAddress("MCtr_Energy",&mctr_eng);
    tr->SetBranchAddress("MCtr_VertexX",&vert_X);
    tr->SetBranchAddress("MCtr_VertexY",&vert_Y);
    tr->SetBranchAddress("MCtr_VertexZ",&vert_Z); 
    tr->SetBranchAddress("hitEdep",&vhedep);
    tr->SetBranchAddress("hitTime",&vhtime);
    tr->SetBranchAddress("barOrientation",&vhbaror);
    tr->SetBranchAddress("transBarPos",&vhtransbarpos);
    tr->SetBranchAddress("longBarPos",&vhlongbarpos);
    tr->SetBranchAddress("barNumber",&vhbarnum);
    tr->SetBranchAddress("TASD",&vTASD);
    
    tr->GetEntry(iEvent);

    //Fill the out root file with simulation parameters.
    o_vposX=vposX;
    o_vposY=vposY;
    o_vposZ=vposZ;
    o_vmomZ=vmomZ;
    o_vPDG=vPDG;
    o_mctr_mom=mctr_mom;
    o_mctr_momX=mctr_momX;
    o_mctr_momY=mctr_momY;
    o_mctr_momZ=mctr_momZ;
    o_mctr_weight=mctr_weight;
    o_mctr_eng=mctr_eng;
    o_mctr_charge=mctr_charge;
    o_vertPosX=vert_X;
    o_vertPosY=vert_Y;
    o_vertPosZ=vert_Z;
    
    myDetectorHitArray.Clear();
    
    //TrackCand
    genfit::TrackCand myCand;
    
    // Provide the fitter with an initial guess.
    TVector3 pos(0, 0, -300); //cm random low number
    TVector3 mom(0,0,2.0); // GeV random number
    //mom.SetPhi(gRandom->Uniform(0.,2*TMath::Pi()));
    //mom.SetTheta(gRandom->Uniform(0.4*TMath::Pi(),0.6*TMath::Pi()));
    //mom.SetMag(gRandom->Uniform(0.2, 1.));

    double maxZ = - 9000; //random small
    double minZ = 9000; // random large
    
    // track model
    const int pdg = -13;// particle pdg code
    const int refcharge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/3.0;
    //genfit::HelixTrackModel* helix = new genfit::HelixTrackModel(pos, mom, charge);
    //measurementCreator.setTrackModel(helix);
    
    //unsigned int nMeasurements = gRandom->Uniform(5, 15);
    
    // covariance
    double resolution = 1.0;//0.01; //cm
    TMatrixDSym cov(3);
    for (int i = 0; i < 3; ++i)
      cov(i,i) = resolution*resolution;

    for(unsigned int i=0; i<vposY->size(); i++){
    //for(unsigned int i=vposY->size()-1; i>0; i--){
      TVector3 currentPos;
      //for (unsigned int i=0; i<nMeasurements; ++i) {
      // "simulate" the detector
      //TVector3 currentPos = helix->getPos(i*2.);
      /*
	currentPos.SetX(gRandom->Gaus(currentPos.X(), resolution));
	currentPos.SetY(gRandom->Gaus(currentPos.Y(), resolution));
	currentPos.SetZ(gRandom->Gaus(currentPos.Z(), resolution));
      */
      //std::cout<<i<<std::endl;
      int pdgR = vPDG->at(i);
      double posX = vposX->at(i);
      double posY = vposY->at(i);
      double posZ = vposZ->at(i);
      //std::cout<<"passed"<<std::endl;

      // split proton and muon tracks? Need the angle... Use angle from muon assuming neutrino straight in.
      // same way as before, find track in MIND and find best hits that fit in track?

      //instead of pattern rec, just artificially use only muon hits. (Not perfect)
      // For us, enough with cuts on energy dep, checking that hit lines up with track parts.
      
      if((pdgR==pdg || pdgR==-pdg))// && posZ>-2400)// && fabs(mctr_mom) >500.0)
	  {
	  currentPos.SetX(posX/10.0);
	  currentPos.SetY(posY/10.0);
	  currentPos.SetZ(posZ/10.0);

	  if(posZ>maxZ) maxZ = posZ;

	  if(posZ<minZ) minZ = posZ;

	  eventHits.push_back(currentPos);

	  // This should be filled with all hits and used for the patternrec.
	  eventHitsV.push_back(new Hit(currentPos,pdgR,vmomZ->at(i),vhedep->at(i),
				       vhtime->at(i),vhtransbarpos->at(i)/10.0,
				       vhlongbarpos->at(i)/10.0,vhbaror->at(i),
				       vhbarnum->at(i),vTASD->at(i)));

	  // 
	  
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

    o_numHits = eventHitsV.size();
    std::sort(eventHitsV.begin(),eventHitsV.end(),sortByZ());

    //combine all bars at most 7.5mm from eachother. (Center to center)

    // debug, take a large size

    double barDiffZ = 15.2/10.0;//7.5; // mm
    std::vector<Plane*> hitPlanes;
    int jmp = 1;
    o_avrHitsPlanes = 0;
    o_plane_zpos->clear();

    for(unsigned int hitCounter = 0; hitCounter<eventHitsV.size(); hitCounter+=jmp)
      {
	jmp=1;
	hitPlanes.push_back(new Plane(eventHitsV[hitCounter]));

	//std::cout<<"plane pos initial="<<hitPlanes.back()->hitList.back()->barPositionZ<<std::endl;
	
	for(unsigned int hitCounterIn = hitCounter+1; hitCounterIn<eventHitsV.size(); hitCounterIn++)
	  {
	    //std::cout<<"Wanting to add ="<<eventHitsV[hitCounterIn]->barPositionZ<<std::endl;

	    //std::cout<<"Diff="<<eventHitsV[hitCounterIn]->barPositionZ-
	    //hitPlanes.back()->hitList.back()->barPositionZ<<std::endl;
	    
	    if(eventHitsV[hitCounterIn]->barPositionZ-
	       hitPlanes.back()->hitList.back()->barPositionZ
	       < barDiffZ)
	      {
		hitPlanes.back()->hitList.push_back(eventHitsV[hitCounterIn]); 
		jmp++;
		
		//std::cout<<"Added"<<std::endl;
	      }
	    else
	      {
		//std::cout<<"Not added, break"<<std::endl;
		break;
	      }
	  }
	//std::cout<<"Hits in plane="<<hitPlanes.back()->hitList.size()<<std::endl;
			  
	double Z = 0;
	//o_plane_zpos->clear();
	//o_avrHitsPlanes = 0;
	for(unsigned int planeCounter = 0; planeCounter<hitPlanes.back()->hitList.size(); planeCounter++)
	  {
	    //std::cout<<"Pos="<<hitPlanes.back()->hitList[planeCounter]->barPositionZ<<std::endl;
	    Z+= hitPlanes.back()->hitList[planeCounter]->barPositionZ;
	  }

	//std::cout<<"Z="<<Z<<std::endl;
	//std::cout<<"Size="<<hitPlanes.back()->hitList.size()<<std::endl;
	//std::cout<<"plane pos="<<hitPlanes.back()->combinedPositionZ<<std::endl;
	
	hitPlanes.back()->combinedPositionZ = Z / hitPlanes.back()->hitList.size();

	o_avrHitsPlanes += hitPlanes.back()->hitList.size();

		   o_plane_zpos->push_back(hitPlanes.back()->combinedPositionZ * 10.0); //cm to mm
      }
  
    //std::cout<<hitPlanes.size()<<std::endl;
    o_numPlanes = hitPlanes.size();

    //std::cout<<"tot hits planes="<<o_avrHitsPlanes<<std::endl;

    o_avrHitsPlanes/=o_numPlanes;

    //std::cout<<"avr hits planes="<<o_avrHitsPlanes<<std::endl;

    //for(unsigned int planesCounter = 0; planesCounter.)
    //{

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
      o_event = iEvent;
      //o_charge = reccharge;
      //o_mom = 1000.0/state[0];//
      o_mom = mom2.Mag()*1000.0;
      o_momX = mom2[0]*1000.0;
      o_momY = mom2[1]*1000.0;
      o_momZ = mom2[2]*1000.0;
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


