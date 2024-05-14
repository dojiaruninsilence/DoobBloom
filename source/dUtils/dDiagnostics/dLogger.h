#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace dDiagnostics {

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
#define DB_TRACE(...) ::dDiagnostics::dLog::GetLogger()->trace(__VA_ARGS__)
#define DB_INFO(...) ::dDiagnostics::dLog::GetLogger()->info(__VA_ARGS__)
#define DB_WARN(...) ::dDiagnostics::dLog::GetLogger()->warn(__VA_ARGS__)
#define DB_ERROR(...) ::dDiagnostics::dLog::GetLogger()->error(__VA_ARGS__)
#define DB_FATAL(...) ::dDiagnostics::dLog::GetLogger()->critical(__VA_ARGS__)

#define DB_TRACE_QUIET(...) ::dDiagnostics::dLog::GetLoggerQuiet()->trace(__VA_ARGS__)
#define DB_INFO_QUIET(...) ::dDiagnostics::dLog::GetLoggerQuiet()->info(__VA_ARGS__)
#define DB_WARN_QUIET(...) ::dDiagnostics::dLog::GetLoggerQuiet()->warn(__VA_ARGS__)
#define DB_ERROR_QUIET(...) ::dDiagnostics::dLog::GetLoggerQuiet()->error(__VA_ARGS__)
#define DB_FATAL_QUIET(...) ::dDiagnostics::dLog::GetLoggerQuiet()->critical(__VA_ARGS__)

