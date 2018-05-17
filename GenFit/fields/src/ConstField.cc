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
  
  TVector3 ConstField::get(const TVector3&) const {
    return field_;
  }
  
  void ConstField::get(const double& x, const double& y, const double& z, double& Bx, double& By, double& Bz) const {
    // Handling only field in iron.
    if(gGeoManager->FindNode(x,y,z)->GetName()[0]=='F')
      {
	//std::cout<<true<<std::endl;
	//std::cout<<gGeoManager->FindNode(x,y,z)->GetName()<<std::endl;
	Bx = field_.X();
	By = field_.Y();
	Bz = field_.Z();
      }
    else
      {
	Bx=0.0;
	By=0.0;
	Bz=0.0;
      }
    
  }
  /* End of namespace genfit */
}
