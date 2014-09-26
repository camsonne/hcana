#ifndef ROOT_THcHodoscope
#define ROOT_THcHodoscope

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// THcHodoscope                                                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <vector>

#include "TClonesArray.h"
#include "THaNonTrackingDetector.h"
#include "THcHitList.h"
#include "THcRawHodoHit.h"
#include "THcScintillatorPlane.h"
#include "THcShower.h"

#include "THaTrackingDetector.h"
#include "THcHitList.h"
#include "THcRawDCHit.h"
#include "THcSpacePoint.h"
#include "THcDriftChamberPlane.h"
#include "THcDriftChamber.h"
#include "TMath.h"

#include "THaSubDetector.h"
#include "TClonesArray.h"
#include <iostream>
#include <fstream>


class THaScCalib;

class THcHodoscope : public THaNonTrackingDetector, public THcHitList {

public:
  THcHodoscope( const char* name, const char* description = "",
		   THaApparatus* a = NULL );
  virtual ~THcHodoscope();

  virtual Int_t      Decode( const THaEvData& );
  virtual EStatus    Init( const TDatime& run_time );
  
  virtual Int_t      CoarseProcess( TClonesArray& tracks );
  virtual Int_t      FineProcess( TClonesArray& tracks );
  
  virtual Int_t      ApplyCorrections( void );
  Double_t GetStartTime() const { return fStartTime; }
  Bool_t IsStartTimeGood() const {return fGoodStartTime;};
  Int_t GetNfptimes() const {return fNfptimes;};
  Int_t GetScinIndex(Int_t nPlane, Int_t nPaddle);
  Int_t GetScinIndex(Int_t nSide, Int_t nPlane, Int_t nPaddle);
  Double_t GetPathLengthCentral();
  Int_t GetNTracks() const { return fTrackProj->GetLast()+1; }
  Double_t GetTdcMin() const {return fScinTdcMin;}
  Double_t GetTdcMax() const {return fScinTdcMax;}
  Double_t GetTofTolerance() const {return fTofTolerance;}
  Double_t GetTdcToTime() const {return fScinTdcToTime;}
  Double_t GetHodoPosPhcCoeff(Int_t iii) const {return fHodoPosPhcCoeff[iii];}
  Double_t GetHodoNegPhcCoeff(Int_t iii) const {return fHodoNegPhcCoeff[iii];}
  Double_t GetHodoPosMinPh(Int_t iii) const {return fHodoPosMinPh[iii];}
  Double_t GetHodoNegMinPh(Int_t iii) const {return fHodoNegMinPh[iii];}
  Double_t GetHodoPosTimeOffset(Int_t iii) const {return fHodoPosTimeOffset[iii];}
  Double_t GetHodoNegTimeOffset(Int_t iii) const {return fHodoNegTimeOffset[iii];}
  Double_t GetHodoVelLight(Int_t iii) const {return fHodoVelLight[iii];}
  Double_t GetStartTimeCenter() const {return fStartTimeCenter;}
  Double_t GetStartTimeSlop() const {return fStartTimeSlop;}
  Double_t GetBetaNotrk() const {return fBetaNotrk;}

  Int_t GetGoodRawPad(Int_t iii){return fGoodRawPad[iii];}
  Double_t GetNScinHits(Int_t iii){return fNScinHits[iii];}

  Int_t GetNPaddles(Int_t iii) { return fNPaddle[iii];}
  Double_t GetPlaneCenter(Int_t iii) { return fPlaneCenter[iii];}
  Double_t GetPlaneSpacing(Int_t iii) { return fPlaneSpacing[iii];}

  //  Double_t GetBeta() const {return fBeta[];}

  Double_t GetBeta(Int_t iii) const {return fBeta[iii];} // Ahmed
  //  Int_t GetEvent(){ return fCheckEvent;}

  Double_t GetHodoPosSigma(Int_t iii) const {return fHodoPosSigma[iii];}
  Double_t GetHodoNegSigma(Int_t iii) const {return fNPmtHit[iii];}


  const TClonesArray* GetTrackHits() const { return fTrackProj; }

  friend class THaScCalib;

  THcHodoscope();  // for ROOT I/O
protected:

  //  std::vector<bool> myScinGoodTime;  // Ahmed

  Int_t fAnalyzePedestals;

  // Calibration

  // Per-event data
  Bool_t fGoodStartTime;
  Double_t fStartTime; 
  Int_t fNfptimes;

  //  Double_t fdEdX;

  Double_t fBetaNotrk;
  //  Double_t fBeta;  
  // Per-event data

  // Potential Hall C parameters.  Mostly here for demonstration
  Int_t fNPlanes,fMaxScinPerPlane,fMaxHodoScin; // number of planes; max number of scin/plane; product of the first two 
  Double_t fStartTimeCenter, fStartTimeSlop, fScinTdcToTime;
  Double_t fTofTolerance;
  Double_t fPathLengthCentral;
  Double_t fScinTdcMin, fScinTdcMax; // min and max TDC values
  char** fPlaneNames;
  Int_t* fNPaddle;		// Number of paddles per plane

  Double_t* fHodoVelLight;
  Double_t* fHodoPosSigma;
  Double_t* fHodoNegSigma;

  Double_t* fHodoPosMinPh;
  Double_t* fHodoNegMinPh;
  Double_t* fHodoPosPhcCoeff;
  Double_t* fHodoNegPhcCoeff;
  Double_t* fHodoPosTimeOffset;
  Double_t* fHodoNegTimeOffset;
  Int_t* fHodoPosPedLimit;
  Int_t* fHodoNegPedLimit;
  Int_t fTofUsingInvAdc;
  Double_t* fHodoPosInvAdcOffset;
  Double_t* fHodoNegInvAdcOffset;
  Double_t* fHodoPosInvAdcLinear;
  Double_t* fHodoNegInvAdcLinear;
  Double_t* fHodoPosInvAdcAdc;
  Double_t* fHodoNegInvAdcAdc;

  THcScintillatorPlane** fPlanes; // List of plane objects

  TClonesArray*  fTrackProj;  // projection of track onto scintillator plane
                              // and estimated match to TOF paddle

  //--------------------------   Ahmed   -----------------------------

  THcShower* fShower;

  //  Int_t        fCheckEvent;

  Int_t        fGoodTrack;
  Int_t        MAXHODHITS;

  Int_t        fSelNDegreesMin;
  Double_t     fSeldEdX1Min;
  Double_t     fSeldEdX1Max;
  Double_t     fSelBetaMin;
  Double_t     fSelBetaMax;
  Double_t     fSelEtMin;
  Double_t     fSelEtMax;
  Double_t     fScin2XZpos;
  Double_t     fScin2XdZpos;
  Double_t     fScin2YZpos;
  Double_t     fScin2YdZpos;

  Double_t     fChi2Min;
  Double_t*    fPlaneCenter;
  Double_t*    fPlaneSpacing;

  Double_t**   fdEdX;                   // [MAXHODHITS] Array
  Double_t**   fScinHit;                // [fNPlanes] Array
  Int_t*       fGoodRawPad;
  Double_t*    fBeta;                 // [MAXHODHITS] Array
  Double_t*    fBetaChisq;            // [MAXHODHITS] Array

  Double_t*    fFPTime;               // [fNPlanes] Array 


  Double_t* fScinSigma;
  Double_t* fGoodScinTime;
  Double_t* fScinTime;
  Double_t* fTime;
  Double_t* adcPh;                    // Correct it
  Double_t* fTimeAtFP;
  Double_t* fPath;
  Double_t* fTimePos;
  Double_t* fTimeNeg;
  Double_t* fScinTimefp;
  Double_t* fScinPosTime;
  Double_t* fScinNegTime;
  Double_t* fSumPlaneTime;

  Int_t* fHitPaddle;
  Int_t* fNScinHit;
  Int_t* fNScinHits;
  Int_t* fNPmtHit;
  Int_t* fTimeHist;
  Int_t* fNPlaneTime;

  Bool_t* fScinGoodTime;
  Bool_t* fKeepPos;
  Bool_t* fKeepNeg;
  Bool_t* fGoodPlaneTime;
  Bool_t* fGoodTDCPos;
  Bool_t* fGoodTDCNeg;

  Int_t fGoodTimeIndex;

  TClonesArray* scinPosADC;
  TClonesArray* scinNegADC;
  TClonesArray* scinPosTDC;
  TClonesArray* scinNegTDC;

  //test array
  Double_t test_arr[53];
  Double_t test_arr1[2];

  //----------------------------------------------------------------

  // Useful derived quantities
  // double tan_angle, sin_angle, cos_angle;
  
  //  static const char NDEST = 2;
  //  struct DataDest {
  //    Int_t*    nthit;
  //    Int_t*    nahit;
  //    Double_t*  tdc;
  //    Double_t*  tdc_c;
  //    Double_t*  adc;
  //    Double_t*  adc_p;
  //    Double_t*  adc_c;
  //    Double_t*  offset;
  //    Double_t*  ped;
  //    Double_t*  gain;
  //  } fDataDest[NDEST];     // Lookup table for decoder

  void           ClearEvent();
  void           DeleteArrays();
  virtual Int_t  ReadDatabase( const TDatime& date );
  virtual Int_t  DefineVariables( EMode mode = kDefine );
  Double_t DefineDoubleVariable(const char* fName);
  Int_t    DefineIntVariable(const char* fName);
  void DefineArray(const char* fName, const Int_t index, Double_t *myArray);
  void DefineArray(const char* fName, char** Suffix, const Int_t index, Double_t *myArray);
  void DefineArray(const char* fName, char** Suffix, const Int_t index, Int_t *myArray);
  enum ESide { kLeft = 0, kRight = 1 };
  
  virtual  Double_t TimeWalkCorrection(const Int_t& paddle,
					   const ESide side);
  void Setup(const char* name, const char* description);

  ClassDef(THcHodoscope,0)   // Hodoscope detector
};

////////////////////////////////////////////////////////////////////////////////

#endif
