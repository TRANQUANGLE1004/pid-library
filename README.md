# pid-library
this library implement pid control.
## Introduction
you can use my library for arduino or stm32 project.
## Advantages
+) my code update integral algorithm
  ```C
  _myPID->sumErr += _myPID->err*(double)PERIOD_UPDATE_PID + 0.5*(_myPID->lastErr - _myPID->err)*(double)PERIOD_UPDATE_PID;
  ```


