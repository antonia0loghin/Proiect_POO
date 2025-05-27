#include "time_manager.h"
#include <iostream>

TimeManager::TimeManager() : m_time(0) {}

void TimeManager::AdvanceTime(int seconds) {
    m_time += seconds;
    std::cout << "Time advanced by " << seconds << " seconds.Current time : " << m_time << "\n";
}

int TimeManager::GetTime() const {
    return m_time;
}
