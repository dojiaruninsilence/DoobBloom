#include "dLogger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// super temp
#include <vector>

namespace dDiagnostics {

	std::shared_ptr<spdlog::logger> dLog::s_logger;
	std::shared_ptr<spdlog::logger> dLog::s_loggerQuiet;

	void dLog::Init() {
		// set the logging pattern
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// specify the path and filename for the log file
		std::string logFilePath = "../logs/logfile.log";

		// create a stdout color sink for console logging
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

		// create a file sink for file logging
		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, true);

		// create a logger with both console and file sinks
		std::vector<spdlog::sink_ptr> sinks = { console_sink, file_sink };
		s_logger = std::make_shared<spdlog::logger>("DB", begin(sinks), end(sinks));

		// create a logger with only a file sink
		s_loggerQuiet = std::make_shared<spdlog::logger>("DBQ", file_sink);

		// set the log level
		s_logger->set_level(spdlog::level::trace);
		s_loggerQuiet->set_level(spdlog::level::trace);

		// register the loggers with spdlog
		spdlog::register_logger(s_logger);
		spdlog::register_logger(s_loggerQuiet);
	}
}
