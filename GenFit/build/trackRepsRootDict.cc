// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIrootdINewSaRoMaNdIGenFitdIbuilddItrackRepsRootDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/root/NewSaRoMaN/GenFit/trackReps/include/RKTrackRep.h"

// Header files passed via #pragma extra_include

namespace genfit {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *genfit_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("genfit", 0 /*version*/, "AbsFinitePlane.h", 35,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &genfit_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *genfit_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void *new_genfitcLcLRKTrackRep(void *p = 0);
   static void *newArray_genfitcLcLRKTrackRep(Long_t size, void *p);
   static void delete_genfitcLcLRKTrackRep(void *p);
   static void deleteArray_genfitcLcLRKTrackRep(void *p);
   static void destruct_genfitcLcLRKTrackRep(void *p);
   static void streamer_genfitcLcLRKTrackRep(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::genfit::RKTrackRep*)
   {
      ::genfit::RKTrackRep *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::genfit::RKTrackRep >(0);
      static ::ROOT::TGenericClassInfo 
         instance("genfit::RKTrackRep", ::genfit::RKTrackRep::Class_Version(), "", 77,
                  typeid(::genfit::RKTrackRep), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::genfit::RKTrackRep::Dictionary, isa_proxy, 17,
                  sizeof(::genfit::RKTrackRep) );
      instance.SetNew(&new_genfitcLcLRKTrackRep);
      instance.SetNewArray(&newArray_genfitcLcLRKTrackRep);
      instance.SetDelete(&delete_genfitcLcLRKTrackRep);
      instance.SetDeleteArray(&deleteArray_genfitcLcLRKTrackRep);
      instance.SetDestructor(&destruct_genfitcLcLRKTrackRep);
      instance.SetStreamerFunc(&streamer_genfitcLcLRKTrackRep);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::genfit::RKTrackRep*)
   {
      return GenerateInitInstanceLocal((::genfit::RKTrackRep*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::genfit::RKTrackRep*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace genfit {
//______________________________________________________________________________
atomic_TClass_ptr RKTrackRep::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RKTrackRep::Class_Name()
{
   return "genfit::RKTrackRep";
}

//______________________________________________________________________________
const char *RKTrackRep::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::genfit::RKTrackRep*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RKTrackRep::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::genfit::RKTrackRep*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RKTrackRep::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::genfit::RKTrackRep*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RKTrackRep::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::genfit::RKTrackRep*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace genfit
namespace ROOT {
   // Wrappers around operator new
   static void *new_genfitcLcLRKTrackRep(void *p) {
      return  p ? new(p) ::genfit::RKTrackRep : new ::genfit::RKTrackRep;
   }
   static void *newArray_genfitcLcLRKTrackRep(Long_t nElements, void *p) {
      return p ? new(p) ::genfit::RKTrackRep[nElements] : new ::genfit::RKTrackRep[nElements];
   }
   // Wrapper around operator delete
   static void delete_genfitcLcLRKTrackRep(void *p) {
      delete ((::genfit::RKTrackRep*)p);
   }
   static void deleteArray_genfitcLcLRKTrackRep(void *p) {
      delete [] ((::genfit::RKTrackRep*)p);
   }
   static void destruct_genfitcLcLRKTrackRep(void *p) {
      typedef ::genfit::RKTrackRep current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_genfitcLcLRKTrackRep(TBuffer &buf, void *obj) {
      ((::genfit::RKTrackRep*)obj)->::genfit::RKTrackRep::Streamer(buf);
   }
} // end of namespace ROOT for class ::genfit::RKTrackRep

namespace {
  void TriggerDictionaryInitialization_trackRepsRootDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/root/NewSaRoMaN/GenFit/core/include",
"/root/NewSaRoMaN/GenFit/trackReps/include",
"/root/root-build/include",
"/root/NewSaRoMaN/GenFit/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "trackRepsRootDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace genfit{class RKTrackRep;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "trackRepsRootDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
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

/** @addtogroup RKTrackRep
 * @{
 */

#ifndef genfit_RKTrackRep_h
#define genfit_RKTrackRep_h

#include "AbsTrackRep.h"
#include "StateOnPlane.h"
#include "RKTools.h"
#include "StepLimits.h"
#include "Material.h"

#include <algorithm>

namespace genfit {

/**
 * @brief Helper for RKTrackRep
 */
struct RKStep {
  MatStep matStep_; // material properties and stepsize
  M1x7 state7_; // 7D state vector
  StepLimits limits_;

  RKStep() {
    std::fill(state7_.begin(), state7_.end(), 0);
  }
};


/**
 * @brief Helper for RKTrackRep
 */
struct ExtrapStep {
  M7x7 jac7_; // 5D jacobian of transport
  M7x7 noise7_; // 5D noise matrix

  ExtrapStep() {
    std::fill(jac7_.begin(), jac7_.end(), 0);
    std::fill(noise7_.begin(), noise7_.end(), 0);
  }
};


/**
 * @brief AbsTrackRep with 5D track parameterization in plane coordinates: (q/p, u', v', u, v)
 *
 * q/p is charge over momentum.
 * u' and v' are direction tangents.
 * u and v are positions on a DetPlane.
 */
class RKTrackRep : public AbsTrackRep {
    friend class RKTrackRepTests_momMag_Test;
    friend class RKTrackRepTests_calcForwardJacobianAndNoise_Test;
    friend class RKTrackRepTests_getState7_Test;
    friend class RKTrackRepTests_getState5_Test;

 public:

  RKTrackRep();
  RKTrackRep(int pdgCode, char propDir = 0);

  virtual ~RKTrackRep();

  virtual AbsTrackRep* clone() const {return new RKTrackRep(*this);}

  virtual double extrapolateToPlane(StateOnPlane& state,
      const SharedPlanePtr& plane,
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const;

  using AbsTrackRep::extrapolateToLine;

  virtual double extrapolateToLine(StateOnPlane& state,
      const TVector3& linePoint,
      const TVector3& lineDirection,
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const;

  virtual double extrapolateToPoint(StateOnPlane& state,
      const TVector3& point,
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const {
    return extrapToPoint(state, point, nullptr, stopAtBoundary, calcJacobianNoise);
  }

  virtual double extrapolateToPoint(StateOnPlane& state,
      const TVector3& point,
      const TMatrixDSym& G, // weight matrix (metric)
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const {
    return extrapToPoint(state, point, &G, stopAtBoundary, calcJacobianNoise);
  }

  virtual double extrapolateToCylinder(StateOnPlane& state,
      double radius,
      const TVector3& linePoint = TVector3(0.,0.,0.),
      const TVector3& lineDirection = TVector3(0.,0.,1.),
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const;

  
  virtual double extrapolateToCone(StateOnPlane& state,
      double radius,
      const TVector3& linePoint = TVector3(0.,0.,0.),
      const TVector3& lineDirection = TVector3(0.,0.,1.),
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const;

  virtual double extrapolateToSphere(StateOnPlane& state,
      double radius,
      const TVector3& point = TVector3(0.,0.,0.),
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const;

  virtual double extrapolateBy(StateOnPlane& state,
      double step,
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const;


  unsigned int getDim() const {return 5;}

  virtual TVector3 getPos(const StateOnPlane& state) const;

  virtual TVector3 getMom(const StateOnPlane& state) const;
  virtual void getPosMom(const StateOnPlane& state, TVector3& pos, TVector3& mom) const;

  virtual double getMomMag(const StateOnPlane& state) const;
  virtual double getMomVar(const MeasuredStateOnPlane& state) const;

  virtual TMatrixDSym get6DCov(const MeasuredStateOnPlane& state) const;
  virtual void getPosMomCov(const MeasuredStateOnPlane& state, TVector3& pos, TVector3& mom, TMatrixDSym& cov) const;
  virtual double getCharge(const StateOnPlane& state) const;
  virtual double getQop(const StateOnPlane& state) const {return state.getState()(0);}
  double getSpu(const StateOnPlane& state) const;
  double getTime(const StateOnPlane& state) const;

  virtual void getForwardJacobianAndNoise(TMatrixD& jacobian, TMatrixDSym& noise, TVectorD& deltaState) const;

  virtual void getBackwardJacobianAndNoise(TMatrixD& jacobian, TMatrixDSym& noise, TVectorD& deltaState) const;

  std::vector<genfit::MatStep> getSteps() const;

  virtual double getRadiationLenght() const;

  virtual void setPosMom(StateOnPlane& state, const TVector3& pos, const TVector3& mom) const;
  virtual void setPosMom(StateOnPlane& state, const TVectorD& state6) const;
  virtual void setPosMomErr(MeasuredStateOnPlane& state, const TVector3& pos, const TVector3& mom, const TVector3& posErr, const TVector3& momErr) const;
  virtual void setPosMomCov(MeasuredStateOnPlane& state, const TVector3& pos, const TVector3& mom, const TMatrixDSym& cov6x6) const;
  virtual void setPosMomCov(MeasuredStateOnPlane& state, const TVectorD& state6, const TMatrixDSym& cov6x6) const;

  virtual void setChargeSign(StateOnPlane& state, double charge) const;
  virtual void setQop(StateOnPlane& state, double qop) const {state.getState()(0) = qop;}

  void setSpu(StateOnPlane& state, double spu) const;
  void setTime(StateOnPlane& state, double time) const;

  //! The actual Runge Kutta propagation
  /** propagate state7 with step S. Fills SA (Start directions derivatives dA/S).
   *  This is a single Runge-Kutta step.
   *  If jacobian is nullptr, only the state is propagated,
   *  otherwise also the 7x7 jacobian is calculated.
   *  If varField is false, the magnetic field will only be evaluated at the starting position.
   *  The return value is an estimation on how good the extrapolation is, and it is usually fine if it is > 1.
   *  It gives a suggestion how you must scale S so that the quality will be sufficient.
   */
  double RKPropagate(M1x7& state7,
                     M7x7* jacobian,
                     M1x3& SA,
                     double S,
                     bool varField = true,
                     bool calcOnlyLastRowOfJ = false) const;

  virtual bool isSameType(const AbsTrackRep* other);
  virtual bool isSame(const AbsTrackRep* other);

 private:

  void initArrays() const;

  virtual double extrapToPoint(StateOnPlane& state,
      const TVector3& point,
      const TMatrixDSym* G = nullptr, // weight matrix (metric)
      bool stopAtBoundary = false,
      bool calcJacobianNoise = false) const;

  void getState7(const StateOnPlane& state, M1x7& state7) const;
  void getState5(StateOnPlane& state, const M1x7& state7) const; // state7 must already lie on plane of state!

  void calcJ_pM_5x7(M5x7& J_pM, const TVector3& U, const TVector3& V, const M1x3& pTilde, double spu) const;

  void transformPM6(const MeasuredStateOnPlane& state,
                    M6x6& out6x6) const;

  void calcJ_Mp_7x5(M7x5& J_Mp, const TVector3& U, const TVector3& V, const TVector3& W, const M1x3& A) const;

  void calcForwardJacobianAndNoise(const M1x7& startState7, const DetPlane& startPlane,
				   const M1x7& destState7, const DetPlane& destPlane) const;

  void transformM6P(const M6x6& in6x6,
                    const M1x7& state7,
                    MeasuredStateOnPlane& state) const; // plane and charge must already be set!

  //! Propagates the particle through the magnetic field.
  /** If the propagation is successful and the plane is reached, the function returns true.
    * Propagated state and the jacobian of the extrapolation are written to state7 and jacobianT.
    * The jacobian is only calculated if jacobianT != nullptr.
    * In the main loop of the Runge Kutta algorithm, the estimateStep() is called
    * and may reduce the estimated stepsize so that a maximum momentum loss will not be exceeded,
    * and stop at material boundaries.
    * If this is the case, RKutta() will only propagate the reduced distance and then return. This is to ensure that
    * material effects, which are calculated after the propagation, are taken into account properly.
    */
  bool RKutta(const M1x4& SU,
              const DetPlane& plane,
              double charge,
              double mass,
              M1x7& state7,
              M7x7* jacobianT,
              M1x7* J_MMT_unprojected_lastRow,
              double& coveredDistance, // signed
              double& flightTime,
              bool& checkJacProj,
              M7x7& noiseProjection,
              StepLimits& limits,
              bool onlyOneStep = false,
              bool calcOnlyLastRowOfJ = false) const;

  double estimateStep(const M1x7& state7,
                      const M1x4& SU,
                      const DetPlane& plane,
                      const double& charge,
                      double& relMomLoss,
                      StepLimits& limits) const;

  TVector3 pocaOnLine(const TVector3& linePoint,
                     const TVector3& lineDirection,
                     const TVector3& point) const;

  //! Handles propagation and material effects
  /** #extrapolateToPlane(), #extrapolateToPoint() and #extrapolateToLine() etc. call this function.
    * #Extrap() needs a plane as an argument, hence #extrapolateToPoint() and #extrapolateToLine() create virtual detector planes.
    * In this function, #RKutta() is called and the resulting points and point paths are filtered
    * so that the direction doesn't change and tiny steps are filtered out.
    * After the propagation the material effects are called via the MaterialEffects singleton.
    * #Extrap() will loop until the plane is reached, unless the propagation fails or the maximum number of
    * iterations is exceeded.
    */
  double Extrap(const DetPlane& startPlane, // plane where Extrap starts
                const DetPlane& destPlane, // plane where Extrap has to extrapolate to
                double charge,
                double mass,
                bool& isAtBoundary,
                M1x7& state7,
                double& flightTime,
                bool fillExtrapSteps,
                TMatrixDSym* cov = nullptr,
                bool onlyOneStep = false,
                bool stopAtBoundary = false,
                double maxStep = 1.E99) const;

  void checkCache(const StateOnPlane& state, const SharedPlanePtr* plane) const;

  double momMag(const M1x7& state7) const;


  mutable StateOnPlane lastStartState_; //! state where the last extrapolation has started
  mutable StateOnPlane lastEndState_; //! state where the last extrapolation has ended
  mutable std::vector<RKStep> RKSteps_; //! RungeKutta steps made in the last extrapolation
  mutable int RKStepsFXStart_; //!
  mutable int RKStepsFXStop_; //!
  mutable std::vector<ExtrapStep> ExtrapSteps_; //! steps made in Extrap during last extrapolation

  mutable TMatrixD fJacobian_; //!
  mutable TMatrixDSym fNoise_; //!

  mutable bool useCache_; //! use cached RKSteps_ for extrapolation
  mutable unsigned int cachePos_; //!

  // auxiliary variables and arrays
  // needed in Extrap()
  mutable StepLimits limits_; //!
  mutable M7x7 noiseArray_; //! noise matrix of the last extrapolation
  mutable M7x7 noiseProjection_; //!
  mutable M7x7 J_MMT_; //!

 public:

  ClassDef(RKTrackRep, 1)

};

} /* End of namespace genfit */
/** @} */

#endif // genfit_RKTrackRep_h

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"genfit::RKTrackRep", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("trackRepsRootDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_trackRepsRootDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_trackRepsRootDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_trackRepsRootDict() {
  TriggerDictionaryInitialization_trackRepsRootDict_Impl();
}
