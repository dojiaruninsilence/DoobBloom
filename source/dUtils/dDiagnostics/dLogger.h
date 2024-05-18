#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace doob {

	// logging class
	class dLog {
	public:
		// initialize the logging system
		static void Init();

		// get the logging system
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }
		inline static std::shared_ptr<spdlog::logger>& GetLoggerQuiet() { return s_loggerQuiet; }

	private:
		// ptr to the logging system
		static std::shared_ptr<spdlog::logger> s_logger;
		static std::shared_ptr<spdlog::logger> s_loggerQuiet;
	};
}

// logging macros
#define DB_TRACE(...) ::doob::dLog::GetLogger()->trace(__VA_ARGS__)
#define DB_INFO(...) ::doob::dLog::GetLogger()->info(__VA_ARGS__)
#define DB_WARN(...) ::doob::dLog::GetLogger()->warn(__VA_ARGS__)
#define DB_ERROR(...) ::doob::dLog::GetLogger()->error(__VA_ARGS__)
#define DB_FATAL(...) ::doob::dLog::GetLogger()->critical(__VA_ARGS__)

#define DB_TRACE_QUIET(...) ::doob::dLog::GetLoggerQuiet()->trace(__VA_ARGS__)
#define DB_INFO_QUIET(...) ::doob::dLog::GetLoggerQuiet()->info(__VA_ARGS__)
#define DB_WARN_QUIET(...) ::doob::dLog::GetLoggerQuiet()->warn(__VA_ARGS__)
#define DB_ERROR_QUIET(...) ::doob::dLog::GetLoggerQuiet()->error(__VA_ARGS__)
#define DB_FATAL_QUIET(...) ::doob::dLog::GetLoggerQuiet()->critical(__VA_ARGS__)

