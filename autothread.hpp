#pragma once
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace autothread {

enum States { START, STOP, WAIT, BOOLWAIT };

struct Thread {

  // BOOL = 0 = thread.RUN

  bool AutoLoop = false; // If set to true your function thread will run on a
                         // loop untill told to stop

  States State = START;

  int WaitTime = 0; // Time stored in milliseconds

  bool IsWorking = false; // easy way to check if the 'work' function is compleated 

  //	virtual void Input();

  virtual void FunctionCallBack() { std::cout << "PLS OVERIDE" << std::endl; };

  inline void Manager(States S, int T = 0) {
    this->State = S;
    this->WaitTime = T;
  };
};

inline void Machine(Thread *T) {

  do {
    int tmp = T->WaitTime;
    switch (T->State) {

    case STOP: {

      // TO STOP
      T->AutoLoop = false;
    } break;

    case WAIT: {
      auto time = std::chrono::milliseconds(tmp);
      std::this_thread::sleep_for(time);
      // This sets the local tmp  value without effecting the wait time if
      // wanted for auto loop
      tmp = 0;

      // After this is passes over BOOLWAIT to START
    }

    case BOOLWAIT: {
      if (T->WaitTime == 0) {
        // Nothing to do besied move to START
      } else if (T->WaitTime == 1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        continue;
      } else {
        T->AutoLoop = STOP;
        std::cout << "ERROR STOPPING THREAD" << std::endl;
        break;
      }
    }

    case START: {
      T->IsWorking = true;
      T->FunctionCallBack();
      T->IsWorking = false;
    } break;
    };
  } while (T->AutoLoop);
};

inline void StartWork(Thread *T) {

  std::thread Worker(Machine, T);
  Worker.detach();
};

}; // namespace autothread
