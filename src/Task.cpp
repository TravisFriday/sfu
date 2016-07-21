#include "Task.h"

Task::Task(uint16_t timeout, uint32_t Interval, funcPtr setFn){
  timeOut = timeout;
  lastRun = 0;
  runStart = 0;
  interval = Interval;
  pointedFunc =  setFn; // pointedFunc(nullptr)
  module = NULL;
}

Task::Task(uint16_t timeout, uint32_t Interval, Module *_module) {
  timeOut = timeout;
  lastRun = 0;
  runStart = 0;
  interval = Interval;
  pointedFunc = NULL;
  module = _module;
}


void Task::setLastRun(uint32_t lastrun){
  lastRun = lastrun;
}

void Task::setRunStart(uint32_t runstart){
  runStart = runstart;
}


void Task::setFunc( funcPtr f ) {
  pointedFunc = f;
}

void Task::runTask(uint32_t systemTick){
  setRunStart(systemTick);
  lastRun = systemTick;
  if (systemTick != lastRun){  // prevents double running of functions
    // put watchdog things here
    if(pointedFunc == NULL) {
      module->tick();
    } else {
      (*pointedFunc)(); // run the function from the poitner
    }
  }
}

scheduling_freq Task::onStateChanged(const SystemState &state) {
  if(module == NULL) {
    scheduling_freq ret;
    ret.valid = false;
    return ret;
  } else {
    return module->onStateChanged(state);
  }
}