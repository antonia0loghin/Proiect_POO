#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

class TimeManager {
private:
    int m_time;

public:
    TimeManager();
    void AdvanceTime(int seconds);
    int GetTime() const;
};

#endif
