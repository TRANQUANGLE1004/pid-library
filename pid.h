
/* ==========================================================================
; Title:  PID FOR ROBOCON 2020
; Author: Kuro - SPK FIRE-PHOENIX 
; Date:   12 Dec 2019
; Use for STM32
; ===========================================================================
*/

/* Desciption XOXO


 */
#ifndef _PID_H_

#define  _PID_H_

//**********************************************/
#include <stdio.h>
#include "STATE.h"
//**********************************************/


// modify by user
#define		FREQUENCY_UPDATE_PID	1000.0  // (unit: Hz)
#define		PID_OUTPUT_MAX			700
#define		PID_OUTPUT_MIN			0
//*******************************NOT MODIFY*******************************
#define		PERIOD_UPDATE_PID		1.0/FREQUENCY_UPDATE_PID
//************************************************************************



typedef enum BOOLs {
	YES = 1,
	NO = 0
}BOOL;



typedef struct PID_FACTORs {
	float kp; 							// (P)roportional
	float ki; 							// (I)ntegral
	float kd; 							// (D)erivative
}PID_FACTOR;

STATUS PID_FACTOR__Init(PID_FACTOR* _myPIDFactor, float _kp, float _ki, float _kd); // use Init and Change Value
PID_FACTOR* PID_FACTOR__Create(float _kp,float _ki, float _kd);							
/*------------------------------MANUAL----------------------------------
User declar 2 ways: 
1)
PID_FACTOR* myPIDFactor = PID_FACTOR__Create(10, 20, 0.01);
2)
PID_FACTOR myPIDFactor;
PID_FACTOR__Init(&myPIDFactor, 10, 20, 0.01);

------------------------------------Have Fun--------------------------------
*/

typedef struct PID_OUT_LIMITs {
	double min;
	double max;
}PID_OUT_LIMIT
;

STATUS PID_OUT_LIMIT__Init(PID_OUT_LIMIT* _myLimit,double _min,double _max);
PID_OUT_LIMIT* PID_OUT_LIMIT__Create(double _min, double _max);

typedef struct PIDs {
		
		// declare variable
		PID_FACTOR*  pidFactor;				// Kp Ki and Kd
		double* out; 						// this is address of output variable
		unsigned int* in; 						// this is address of input variable
		double setPoint; 					// this is the value system want to achieve 

		// this is private variable 

		double err;							// this is error = setpoint - current value(in)
		double sumErr;						// this is SUM of err use in integral
		//backup value
		double lastErr;						// this is last err
		//
		PID_OUT_LIMIT outLimit;				// MIN<------out------>MAX
		// status variable
		BOOL isUseOutputLimit;				// default is 0 (Not use)
}PID
;

// there are 2 way to create PID
STATUS PID__Init(PID* _myPID, PID_FACTOR* _myFactors,unsigned int* _in,double* _out,double _setPoint, PID_OUT_LIMIT _limit);				// Init value PID
PID* PID__Create(PID_FACTOR* _myFactors, unsigned int* _in, double* _out, double _setPoint, PID_OUT_LIMIT _limit);  												// Create a new PID


// this function will be call in Timer_Vector()
void PID__Caculate(PID* _myPID);														//	caculate value of output 
void PID__SetTurning(PID* _myPID,float _kp,float _ki,float _kd);						//  this function update PID_FACTOR

void PID__OnOutputLimitFlag(PID* _myPID);
void PID__OffOutputLimitFlag(PID* _myPID);
																												//

// ---------------------------------------------------DEGUB FUNCTION ---------------------------------------------

void printClassPID(PID _myPID);
void printClassPID_FACTOR(PID_FACTOR _myFactors);

#endif // !_PID_H_
