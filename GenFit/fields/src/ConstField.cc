/* Copyright 2008-2010, Technische Universitaet Muenchen,
   Authors: Christian Hoeppner & Sebastian Neubert & Johannes Rauch

   This file is part of GENFIT.

   GENFIT is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GENFIT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with GENFIT.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ConstField.h"
#include <TGeoManager.h>
//#include <iostream>

namespace genfit {
  
  TVector3 ConstField::get(const TVector3& in) const {
    TVector3 tmp(0,0,0);

    if(gGeoManager->FindNode(in[0],in[1],in[2]))
      {
	if(gGeoManager->FindNode(in[0],in[1],in[2])->GetName()[0]=='F')
	  {
	    if(fabs(in[1])>50)
	      tmp[0] = -field_.X();
	    else
	      tmp[0] = field_.X();
	    
	    tmp[1] = field_.Y();
	    tmp[2] = field_.Z();
	  }
      }

    return tmp;
    //return field_;
  }
  
  void ConstField::get(const double& x, const double& y, const double& z, double& Bx, double& By, double& Bz) const {
    // Handling only field in iron. Baby MIND field model.

    Bx=0.0;//0.01*field_.X();
    By=0.0;//0.01*field_.Y();
    Bz=0.0;//0.01*field_.Z();
    
    if(gGeoManager->FindNode(x,y,z))
      {
	if(gGeoManager->FindNode(x,y,z)->GetName()[0]=='F')
	  {
	    /*
	    Bx = field_.X();
	    By = field_.Y();
	    Bz = field_.Z();
	    */
	    
	    if(fabs(y)>50)
	      Bx = -field_.X();
	    else
	      Bx = field_.X();
	    //Bx = field_.X();
	    By = field_.Y();
	    Bz = field_.Z();
	    
	  }
      }
  }
  /* End of namespace genfit */
}
