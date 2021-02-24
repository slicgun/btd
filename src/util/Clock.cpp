#include "Clock.h"

using namespace std::chrono;

Clock::Clock()
{
	m_startTime = steady_clock::now();
}

double Clock::getSeconds() const
{
	duration<double> time = steady_clock::now() - m_startTime;
	return time.count();
}

double Clock::getMilliseconds() const
{
	duration<double> time = steady_clock::now() - m_startTime;
	return time.count() * 1000.f;
}

void Clock::reset()
{
	m_startTime = steady_clock::now();
}
