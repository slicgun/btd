#pragma once

#include<chrono>

class Clock
{
public:
	Clock();

	double getSeconds() const;
	double getMilliseconds() const;
	void reset();
private:
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};