#include <ConstField.h>
#include <Exception.h>
#include <FieldManager.h>
#include <KalmanFitterRefTrack.h>
#include <StateOnPlane.h>
#include <Track.h>
#include <TrackPoint.h>

#include <MaterialEffects.h>
#include <RKTrackRep.h>
#include <TGeoMaterialInterface.h>

#include <EventDisplay.h>

#include <PlanarMeasurement.h>

#include <TEveManager.h>
#include <TGeoManager.h>
#include <TVector3.h>
#include <vector>

#include "TDatabasePDG.h"
#include <TMath.h>

#include "TFile.h"
#include "TTree.h"
#include <vector>
#include "TH1.h"
#include "TCanvas.h"
#include <fstream>
#include <GFGbl.h>

int main() {

  // init geometry and mag. field
  new TGeoManager("Geometry", "Geane geometry");
  TGeoManager::Import("MIND.gdml");
  genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());
  genfit::FieldManager::getInstance()->init(new genfit::ConstField(15.,0., 0.)); // 1.5 T units given in kGauss 1 kGauss = 0.1 T // Over full detector, need to implement field only in IRON and not uniform. Has been done in a bad way by changing ConstField.

  //gGeoManager->GetListOfVolumes()->Print();
  
  // init event display
  genfit::EventDisplay* display = genfit::EventDisplay::getInstance();


  const int nIter = 100; // max number of iterations
  const double dPVal = 1.E-3; // convergence criterion
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToPredictionWire;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::weightedAverage;

  const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToPrediction;

  std::ofstream myfile;
  myfile.open ("example.txt");

  
  
  // init fitter
  genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitterRefTrack(nIter,dPVal);

  //genfit::GFGbl* fitter = new genfit::GFGbl();

  fitter->setMaxIterations(nIter);

  fitter->setMultipleMeasurementHandling(mmHandling);
  

  // reading root
  //TFile *f=new TFile("B4.root","update");
  TFile *f=new TFile("B4.root");
  TTree *tr=(TTree*)f->Get("B4");

  //TCanvas *c1 = new TCanvas("c1","The HSUM example",200,10,600,400);
  
  //TH1F* main_histo = new TH1F("main_histo","Main contributor",100,-10,10);


  //std::vector<double> recMom;
  // need some initial guess, this is for simulation?
  
  // particle pdg code; pion hypothesis
  const int pdg = 13;

  //for (unsigned int iEvent=0; iEvent<300; ++iEvent)
  for (unsigned int iEvent=0; iEvent<1000; ++iEvent)
    {
      std::cout<<"Event Num="<<iEvent<<std::endl;

      if(iEvent==483 || iEvent==666) continue; // Why does this one break??!?!?!
      // it has no hits with pdg 13 for some reason??
      
      // start values for the fit, e.g. from pattern recognition
      TVector3 pos(0, 0, -200); // change of units, in cm here
      //TVector3 pos(0, 0, -400);
      //TVector3 pos(0, 0, 100);
      TVector3 mom(0, 0, 10);
      
      // need better rep, helix.
      
      // trackrep
      genfit::AbsTrackRep* rep = new genfit::RKTrackRep(pdg);
      
      // create track
      genfit::Track fitTrack(rep, pos, mom);
      
      // need to initialize a track?
      
      // read in hits from root and implement these planar hits.
      // check other examples to see if this is also done.
      
      
      const int detId(0); // detector ID
      int planeId(0); // detector plane ID
      int hitId(0); // hit ID
      
      //double detectorResolution(0.001); // resolution of planar detectors
      double detectorResolution(0.01); // resolution of planar detectors
      TMatrixDSym hitCov(2);
      hitCov.UnitMatrix();
      hitCov *= detectorResolution*detectorResolution;
      
      // reading root
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
      
      TVectorD hitCoords(2);
      genfit::PlanarMeasurement* measurement;

      //std::cout<<"Here "<<tr->GetEntries()<<std::endl;
      
      double lastZ = -999.9;

      //int i = iEvent;
       
      //int entries= tr->GetEntries();
      //for (int i=0; i<entries; i++)
      //{
      tr->GetEntry(iEvent);
	  //std::cout<<"Here "<<eventIDR<<" "<<iEvent<<std::endl;
	  //std::cout<<vposY->size()<<std::endl;
	  
	  //if(eventIDR==iEvent && check>0)
	  //{
	      //std::cout<<"Here2"<<std::endl;
	      for(unsigned int j=0; j<vposY->size(); j++)
		{
		  //std::cout<<"Here3"<<std::endl;
		  int pdgR = vPDG->at(j);
		  if(pdgR==13)
		    {
		      //std::cout<<pdgR<<std::endl;
		      //std::cout<<"Here4"<<std::endl;
		      double posX = vposX->at(j);
		      double posY = vposY->at(j);
		      double posZ = vposZ->at(j);
		      //std::cout<<"Coord="<<posY<<" "<<posZ<<std::endl;
		      
		      //if(posZ>-1800 && fabs(lastZ-posZ)>50)
		      //if(fabs(lastZ-posZ)>50)
		      //{
			  lastZ = posZ;
			  
			  hitCoords[0] = 0.0;//posX/10.0;
			  hitCoords[1] = posY/10.0;
			  measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
			  measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0,0,posZ/10.0), TVector3(1,0,0), TVector3(0,1,0))), ++planeId);
			  fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));
			  //}
		    }
		}  
	      //}
	      //}
  
      
      //check
      fitTrack.checkConsistency();
      
      // do the fit
      fitter->processTrack(&fitTrack);

      if (! fitTrack.getFitStatus(rep)->isFitConverged()) {
        std::cout << "Track could not be fitted successfully! Fit is not converged! \n";
      }
      
      //fitTrack.sort();
      
      //std::cout<<"State?"<<std::endl;

      //for(unsigned counter = 0; counter<fitTrack.getNumPoints();counter++)
	//fitTrack.getFittedState(counter).Print();
	
      // print fit result
      //fitTrack.getFittedState().Print();
      //std::cout<<"End of state"<<std::endl;
      //fitTrack.getFittedState(9).Print();
      TVector3 pos2;
      TVector3 mom2;
      TMatrixDSym cov2;
      fitTrack.getFittedState().getPosMomCov(pos2,mom2,cov2);
       /*
      //const TVectorD& state = fitTrack.getFittedState();
      //std::cout<<"Momentum rec="<<1.0/state[0]<<std::endl;
      std::cout<<"Rec Momentum:"<<std::endl;
      std::cout<<mom2[0]<<" "<<mom2[1]<<" "<<mom2[2]<<std::endl;
      
      std::cout<<"True Momentum:"<<std::endl;
      std::cout<<mom[0]<<" "<<mom[1]<<" "<<mom[2]<<std::endl;
       */

      myfile << (mom2[2]-3.0) / sqrt(cov2[0][0])<<"\t"<<fitTrack.getFittedState().getCharge()<<"\t"<<mom2[2]<<"\t"<<sqrt(cov2[0][0])<<"\n";
      /*
      std::cout<<"track info"<<std::endl;
      std::cout<<fitTrack.hasFitStatus()<<std::endl;
      std::cout<<fitTrack.getNumPoints()<<std::endl;
      std::cout<<fitTrack.getNumPointsWithMeasurement()<<std::endl;
      std::cout<<fitTrack.getNumReps()<<std::endl;
      std::cout<<fitTrack.getTrackLen()<<std::endl; //in cm!
      */
      //main_histo->Fill(mom2[2]);
      //std::cout<<"Here"<<std::endl;
      /*
      float pt;
      TBranch *bpt = tr->Branch("rec_mom",&pt,"pt/F");
      pt = mom2[2];
      bpt->Fill();
      tr->Write();
      */
      //T->SetBranchAddress("px",&px);
      //T->SetBranchAddress("py",&py);
      //Long64_t nentries = T->GetEntries();
      /*for (Long64_t i=0;i<nentries;i++)
	{
	  T->GetEntry(i);
	  pt = TMath::Sqrt(px*px+py*py);
	  bpt->Fill();
	}
      T->Print();
      T->Write();
      delete f; 
      */
      
      //check
      fitTrack.checkConsistency();
      display->addEvent(&fitTrack);

      //recMom.push_back(mom2[2]);
      //std::cout<<mom2[2]<<"=="<<recMom.back()<<std::endl;
      
    } // end loop over events
  
  delete fitter;

  /*
  TBranch *bpt = tr->Branch("rec_mom",&recMom,"pt/F");
  bpt->Fill();
  tr->Write();
  */
  delete f;

  //main_histo->Draw();

  myfile.close();
  
  // open event display
  display->open();

}


