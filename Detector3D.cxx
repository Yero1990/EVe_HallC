///////////////////////////////////////
/*  Detector3D.h  7/17/14
    
    Ben Davis-Purcell

    Class that joins all detectors in 3D view
    and handles 3D full and partial tracks

*/
///////////////////////////////////////

#include "Detector3D.h"
#include "TMath.h"
#include <cstring>
#include <cstdio>
#include <iostream>
#include <sstream>
#include "TGeoSphere.h"
#include "TWire3D.h"
#include "GetVariables.h"
#include "TGeoMatrix.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

Detector3D::Detector3D()
{
   
      mgr = new TGeoManager("Geom", "Composite shape example");
      TGeoMedium *medium = 0;
      mgr->SetVisOption(1);
      mgr->SetVisLevel(6);
      top = mgr->MakeBox("TOP",medium,600,300,300);
      mgr->SetTopVolume(top); 

    string PN[6]={"x", "y", "u", "v", "yp", "xp"};
    vector<string> PlaneNames(&PN[0],&PN[0]+6);
    // First MWDC
     MWDC1 = new WireChamber3D((char*) "MWDC1",  PlaneNames, top, mgr);

     //MWDC1-> LeftWall-> InvisibleAll(kFALSE);
     //MWDC1-> UpperWall->InvisibleAll(kTRUE);

    // Second MWDC
     MWDC2 = new WireChamber3D((char*) "MWDC2",  PlaneNames, top, mgr);


      // s1x - Scintillation Plane     
      s1xplane = new ScintPlane3D((char*)"s1x",top);

      // s1y - Scintillation Plane  
      s1yplane = new ScintPlane3D((char*)"s1y",top);
      
      //s2x Scint Plane
      s2xplane = new ScintPlane3D((char*)"s2x",top);

      //s2y Scint Plane
      // changed volume size to 60
      s2yplane = new ScintPlane3D((char*)"s2y",top);    

      // There will be 10 tracks for any fixed number of tracks in this code,
      // The reason for it is after you call CloseGeometry() function, you cannot dynamically change number of TGeoVolume in root.
      for(int i=0; i<10; i++){
	TrackList.push_back(new Trajectory3D(top,mgr,i));}

       mgr->CloseGeometry();
       //top->Raytrace();
       top->Draw("ogl");
       cout<<"Detector Created!"<<endl;
}


Detector3D::~Detector3D()
{

}


void Detector3D::ClearTracks()
{
  for (int i=0; i<TrackList.size(); i++) {
    TrackList[i]->Disable();
  }
}
