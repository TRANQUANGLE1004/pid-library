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
- first you need create PID_FACTOR about (Kp, Ki and Kd). My struct are 2 ways to declar.
  - 1:
    ```C
    PID_FACTOR* myPIDFactor = PID_FACTOR__Create(10, 20, 0.01);
    ```
  - 2:
    ```C
    PID_FACTOR myPIDFactor;
    //...
    //...
    PID_FACTOR__Init(&myPIDFactor, 10, 20, 0.01);
    ```


