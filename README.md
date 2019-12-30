# pid-library
this library implement pid control.
## Introduction
you can use my library for arduino or stm32 project.
## Advantages
- my code can reuseable. It can add many PID in your project.
- my code update integral algorithm
  ```C
  _myPID->sumErr += _myPID->err*(double)PERIOD_UPDATE_PID + 0.5*(_myPID->lastErr - _myPID->err)*(double)PERIOD_UPDATE_PID;
  ```
  instead of:
  ```C
  _myPID->sumErr += _myPID->err*(double)PERIOD_UPDATE_PID;
  ```
## Getting start
- First you need create PID_FACTOR about (Kp, Ki and Kd). My struct are 2 ways to declar.
  - Way 1:
    ```C
    PID_FACTOR* myPIDFactor = PID_FACTOR__Create(10, 20, 0.01);
    ```
  - Way 2:
    ```C
    PID_FACTOR myPIDFactor;
    //...
    //...
    PID_FACTOR__Init(&myPIDFactor, 10, 20, 0.01);
    ```
- Now you can create PID. You can use one of two way to do it.
  - Way 1:
    ```C
    STATUS PID__Init(PID* _myPID, PID_FACTOR* _myFactors,unsigned int* _in,double* _out,double _setPoint, PID_OUT_LIMIT _limit);				 
    ```
    STATUS can return FAILED when you doesn't init _myPID @@.
  - Way 2:
    ```C
    PID* PID__Create(PID_FACTOR* _myFactors, unsigned int* _in, double* _out, double _setPoint, PID_OUT_LIMIT _limit);  								
    ```
- Why i use pointer PID_FACTOR, input and output?.You can change your PID_FACTOR anytime.Input and Output can change anytime, you can't use a timer for update it.
