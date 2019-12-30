#include  "pid.h"

STATUS PID_FACTOR__Init(PID_FACTOR * _myPIDFactor, float _kp, float _ki, float _kd)
{
	if (_myPIDFactor != NULL) {
		_myPIDFactor->kp = _kp;
		_myPIDFactor->ki = _ki;
		_myPIDFactor->kd = _kd;
		return _SUCCESS;
	}
	else {
		return _FAILED;
	}
	
}

PID_FACTOR * PID_FACTOR__Create(float _kp, float _ki, float _kd)
{
	PID_FACTOR* __result = (PID_FACTOR*)malloc(sizeof(PID_FACTOR));
	if (PID_FACTOR__Init(__result, _kp, _ki, _kd) == _SUCCESS) {
		return __result;
	}
	return NULL;
	
}

STATUS PID_OUT_LIMIT__Init(PID_OUT_LIMIT * _myLimit, double _min, double _max)
{
	if (_myLimit != NULL) {
		_myLimit->min = _min;
		_myLimit->max = _max;
		return _SUCCESS;
	}
	else {
		return _FAILED;
	}
}

PID_OUT_LIMIT * PID_OUT_LIMIT__Create(double _min, double _max) {
	PID_OUT_LIMIT * __result = (PID_OUT_LIMIT *)malloc(sizeof(PID_OUT_LIMIT));
	if (PID_OUT_LIMIT__Init(__result, _min, _max) == _SUCCESS) {
		return __result;
	}
	return NULL;
}

STATUS PID__Init(PID * _myPID, PID_FACTOR* _myFactors, unsigned int * _in, double * _out, double  _setPoint, PID_OUT_LIMIT _limit) {
	if(_myPID != NULL){
		_myPID->pidFactor = _myFactors;
		_myPID->in = _in;
		_myPID->out = _out;
		_myPID->setPoint = _setPoint;
		//setting default value is 0
		_myPID->err = 0;
		_myPID->sumErr = 0;
		_myPID->lastErr = 0;
		_myPID->isUseOutputLimit = NO;
		_myPID->outLimit = _limit;
		//
		return _SUCCESS;
	}
	else {
		return _FAILED;
	}
}

PID * PID__Create(PID_FACTOR* _myFactors, unsigned int * _in, double * _out, double  _setPoint, PID_OUT_LIMIT _limit)
{

	PID* __result = (PID*)malloc(sizeof(PID));
	
	PID__Init(__result, _myFactors, _in, _out, _setPoint,_limit);

	return __result;
}

void PID__Caculate(PID * _myPID) {
	//
	double in = (short)*_myPID->in;
	_myPID->err = _myPID->setPoint - in;
	//check first state
	if (_myPID->lastErr == 0) {
		_myPID->sumErr = 0;
	}
	else {
		_myPID->sumErr += _myPID->err*(double)PERIOD_UPDATE_PID +
						0.5*(_myPID->lastErr - _myPID->err)*(double)PERIOD_UPDATE_PID;
	}
	
	//caculate

	double __result =	_myPID->pidFactor->kp*_myPID->err +
						_myPID->pidFactor->ki*_myPID->sumErr +
						_myPID->pidFactor->kd*(_myPID->err - _myPID->lastErr) / (double)PERIOD_UPDATE_PID;
				 
	//
	if (_myPID->isUseOutputLimit == YES) {
		if (__result > _myPID->outLimit.max) {
			*_myPID->out = _myPID->outLimit.max;
		}
		else if (__result < _myPID->outLimit.min) {
			*_myPID->out = _myPID->outLimit.min;
		}
		else {
			*_myPID->out = __result;
		}
	}
	else {
		*_myPID->out = __result;
	}

	//backup variable
	_myPID->lastErr = _myPID->err;
}

void PID__SetTurning(PID * _myPID, float _kp, float _ki, float _kd) {
	PID_FACTOR__Init(_myPID->pidFactor, _kp, _ki, _kd);
}

void PID__OnOutputLimitFlag(PID * _myPID) {
	_myPID->isUseOutputLimit = YES;
}

void PID__OffOutputLimitFlag(PID * _myPID) {
	_myPID->isUseOutputLimit = NO;
}



void printClassPID(PID  _myPID) {
	printf("%s\n", "-----------------------------------");
	printClassPID_FACTOR(*_myPID.pidFactor);
	printf("%s%f\n", "Value of [in] : ", *_myPID.in);
	printf("%s%f\n", "Value of [out] : ", *_myPID.out);
	printf("%s%f\n", "Value of [setpoint] : ", _myPID.setPoint);
	printf("%s%d\n", "Value of [isTurnLimit] : ", _myPID.isUseOutputLimit);
	printf("%s%f\n", "Value of [err] : ", _myPID.err);
	printf("%s%f\n", "Value of [sum of err] : ", _myPID.sumErr);
	printf("%s%f\n", "Value of [last err] : ", _myPID.lastErr);
	printf("%s%f\n", "Value of [MIN OUT] : ", _myPID.outLimit.min);
	printf("%s%f\n", "Value of [MAX  OUT] : ", _myPID.outLimit.max);

}

void printClassPID_FACTOR(PID_FACTOR  _myFactors) {
	printf("%s%f\n", "Value of [Kp] : ", _myFactors.kp);
	printf("%s%f\n", "Value of [Ki] : ", _myFactors.ki);
	printf("%s%f\n", "Value of [Kd] : ", _myFactors.kd);
}

