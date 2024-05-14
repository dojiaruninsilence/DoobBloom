#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace dDiagnostics {

	// logging class
	class dLog {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_logger;
	};
}

// logging macros
#define DB_TRACE(...) ::dDiagnostics::dLog::GetLogger()->trace(__VA_ARGS__)
#define DB_INFO(...) ::dDiagnostics::dLog::GetLogger()->info(__VA_ARGS__)
#define DB_WARN(...) ::dDiagnostics::dLog::GetLogger()->warn(__VA_ARGS__)
#define DB_ERROR(...) ::dDiagnostics::dLog::GetLogger()->error(__VA_ARGS__)
#define DB_FATAL(...) ::dDiagnostics::dLog::GetLogger()->critical(__VA_ARGS__)

