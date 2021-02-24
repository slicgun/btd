#pragma once

#include<memory>
#include<spdlog/spdlog.h>
#include<spdlog/fmt/ostr.h>

class Log
{
public:
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

	Log(Log&&) = delete;
	Log& operator=(Log&&) = delete;

	static Log& get() { static Log r; return r; }

	template<typename... Ts>
	static void trace(Ts... args)
	{
		get().m_logger->trace(std::forward<Ts>(args)...);
	}

	template<typename... Ts>
	static void info(Ts... args)
	{
		get().m_logger->info(std::forward<Ts>(args)...);
	}

	template<typename... Ts>
	static void warn(Ts... args)
	{
		get().m_logger->warn(std::forward<Ts>(args)...);
	}

	template<typename... Ts>
	static void error(Ts... args)
	{
		get().m_logger->error(std::forward<Ts>(args)...);
	}

	template<typename... Ts>
	static void critical(Ts... args)
	{
		get().m_logger->critical(std::forward<Ts>(args)...);
	}
private:
	Log();

	std::shared_ptr<spdlog::logger> m_logger;
};