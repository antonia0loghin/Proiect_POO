#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "cafe.h"
#include "time_manager.h"
#include "stats.h"

class Simulator {
private:
    Cafe m_cafe;
    TimeManager m_time;

public:
    void Run();
    void AdvanceTime(int seconds); 

};

#endif
