#include "Log.h"

#include<spdlog/sinks/stdout_color_sinks.h>

Log::Log()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	m_logger = spdlog::stdout_color_mt("Log");
	m_logger->set_level(spdlog::level::trace);
}
