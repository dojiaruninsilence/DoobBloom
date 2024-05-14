#include "dLogger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace dDiagnostics {

	std::shared_ptr<spdlog::logger> dLog::s_logger;

	void dLog::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_logger = spdlog::stdout_color_mt("DB");
		s_logger->set_level(spdlog::level::trace);
	}
}
