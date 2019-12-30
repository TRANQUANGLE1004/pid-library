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
- Next step is delar PID_OUT_LIMIT
  - You can init similar declar PID_FACTOR.
    ```C
    PID_OUT_LIMIT myLimit;
    //...
    //...
    PID_OUT_LIMIT__Init(myLimit,double _min,double _max);
    ```
    Or you cannot declar it, and you use (PID_OUT_LIMIT){ -500, 500 } add to PID declar:
    ```C
    PID__Init(&myPID, &myPIDFactor, myEncoder.pulse, &pidOut,50, (PID_OUT_LIMIT){ -500, 500 });			 
    ```
- After you turn on flag isUseOutputLimit if you want limit your output.
    ```C
    PID__OnOutputLimitFlag(&myPID);
    ```
   Default PID don't use limit output. But i want use it to protect system. Output high can damaged hardware.  
- IMPORTANCE: 
  - You must change FREQUENCY_UPDATE_PID in pid.h. This is frequency i caculate out and update value.

- Now you can create PID. You can use one of two way to do it.
  - Way 1:
    ```C
    PID myPID;
    //...
    //...
    PID__Init(&myPID, &myPIDFactor, myEncoder.pulse, &pidOut,50, (PID_OUT_LIMIT){ -500, 500 });			 
    ```

  - Way 2:
    ```C
    PID* myPID = PID__Create(&myPIDFactor, myEncoder.pulse, &pidOut,50, (PID_OUT_LIMIT){ -500, 500 });								
    ```
- Why i use pointer PID_FACTOR, input and output? You can change your PID_FACTOR anytime.Input and Output can change anytime, you can't use a timer for update it.

## Update in future
- I want implement a low pass filter for sensor(input) because noise can make wrong ouput. Exemple i use 1000Hz update and caculate output but noise can make a high frequency => derivite so high and Wrong. So i research in future.
- You can implement low pass filter by electrical in [low pass filter](https://www.electronics-tutorials.ws/filter/filter_2.html)
- I want to make a auto turning.
## Reference
- [PID controler Matlab Techtak](https://www.youtube.com/watch?v=wkfEZmsQqiA&t=72s)
- [Arduino-PID-Library](https://github.com/br3ttb/Arduino-PID-Library/)
## Thank you !!! 
