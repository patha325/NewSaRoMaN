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


int main() {

  // init geometry and mag. field
  new TGeoManager("Geometry", "Geane geometry");
  TGeoManager::Import("MIND.gdml");
  genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());
  genfit::FieldManager::getInstance()->init(new genfit::ConstField(15.,0., 0.)); // 1.5 T units given in kGauss 1 kGauss = 0.1 T // Over full detector, need to implement field only in IRON and not uniform.

  //gGeoManager->GetListOfVolumes()->Print();
  
  // init event display
  genfit::EventDisplay* display = genfit::EventDisplay::getInstance();


  const int nIter = 20; // max number of iterations
  const double dPVal = 1.E-3; // convergence criterion
  const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToPredictionWire;

  
  // init fitter
  genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitterRefTrack(nIter,dPVal);

  fitter->setMaxIterations(nIter);

  fitter->setMultipleMeasurementHandling(mmHandling);
  

  // reading root
  TFile *f=new TFile("B4.root");
  TTree *tr=(TTree*)f->Get("B4");

  

  // need some initial guess, this is for simulation?
  
  // particle pdg code; pion hypothesis
  const int pdg = 13;

  // start values for the fit, e.g. from pattern recognition
  //TVector3 pos(0, 0, -2200);
  TVector3 pos(0, 0, -400);
  //TVector3 pos(0, 0, 100);
  TVector3 mom(0, 0, 3);


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
  double detectorResolution(3); // resolution of planar detectors
  TMatrixDSym hitCov(2);
  hitCov.UnitMatrix();
  hitCov *= detectorResolution*detectorResolution;

  // reading root
  std::vector<double> *vposX=0;
  std::vector<double> *vposY=0;
  std::vector<double> *vposZ=0;
  std::vector<int> *vPDG=0;
  

  tr->SetBranchAddress("positionX",&vposX);
  tr->SetBranchAddress("positionY",&vposY);
  tr->SetBranchAddress("positionZ",&vposZ);
  tr->SetBranchAddress("pdg",&vPDG);

  TVectorD hitCoords(2);
  genfit::PlanarMeasurement* measurement;
  
  int entries= tr->GetEntries();
  for (int i=0; i<entries; i++)
    {
      tr->GetEntry(i);
      for(unsigned int j=0; j<vposY->size(); j++)
	{
	  int pdgR = vPDG->at(j);
	  if(pdgR==13)
	    {
	      double posX = vposX->at(j);
	      double posY = vposY->at(j);
	      double posZ = vposZ->at(j);
	      std::cout<<"Coord="<<posY<<" "<<posZ<<std::endl;
	      
	      hitCoords[0] = posX/10.0;
	      hitCoords[1] = posY/10.0;
	      measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
	      measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0,0,posZ/10.0), TVector3(1,0,0), TVector3(0,1,0))), ++planeId);
	      fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));
	    }
	}  
    }
  
  // add some planar hits to track with coordinates I just made up
  /*
  TVectorD hitCoords(2);
  hitCoords[0] = 0;
  hitCoords[1] = 0;
  genfit::PlanarMeasurement* measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
  measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0,0,0), TVector3(1,0,0), TVector3(0,1,0))), ++planeId);
  fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

  hitCoords[0] = -0.15;
  hitCoords[1] = 0.15;
  measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
  measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0,0,100), TVector3(1,0,0), TVector3(0,1,0))), ++planeId);
  fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

  hitCoords[0] = -0.15;
  hitCoords[1] = 0.3;
  measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
  measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0,0,-100), TVector3(1,0,0), TVector3(0,1,0))), ++planeId);
  fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

  hitCoords[0] = -0.4;
  hitCoords[1] = 0.6;
  measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
  measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0,0,200), TVector3(1,0,0), TVector3(0,1,0))), ++planeId);
  fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

    hitCoords[0] = -0.4;
  hitCoords[1] = 0.8;
  measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
  measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0,0,-200), TVector3(1,0,0), TVector3(0,1,0))), ++planeId);
  fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));
  */

  //check
  fitTrack.checkConsistency();

  // do the fit
  fitter->processTrack(&fitTrack);

  std::cout<<"State?"<<std::endl;
  // print fit result
  fitTrack.getFittedState().Print();
  std::cout<<"End of state"<<std::endl;

  TVector3 pos2;
  TVector3 mom2;
  TMatrixDSym cov2;
  fitTrack.getFittedState().getPosMomCov(pos2,mom2,cov2);
  
  //const TVectorD& state = fitTrack.getFittedState();
  //std::cout<<"Momentum rec="<<1.0/state[0]<<std::endl;
  std::cout<<"Rec Momentum:"<<std::endl;
  std::cout<<mom2[0]<<" "<<mom2[1]<<" "<<mom2[2]<<std::endl;

  std::cout<<"True Momentum:"<<std::endl;
  std::cout<<mom[0]<<" "<<mom[1]<<" "<<mom[2]<<std::endl;
  
  
  //check
  fitTrack.checkConsistency();


  display->addEvent(&fitTrack);


  delete fitter;

  // open event display
  display->open();

}


