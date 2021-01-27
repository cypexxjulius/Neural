#include "nlpch.h"
#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Neural {
	std::shared_ptr<spdlog::logger> Logging::c_CoreLogger;
	std::shared_ptr<spdlog::logger> Logging::c_ClientLogger;

	void Logging::init() {
		spdlog::set_pattern("%^[ + ] %n: %v%$");
		c_CoreLogger = spdlog::stdout_color_mt("Neural");
		c_CoreLogger->set_level(spdlog::level::trace);
		
		c_ClientLogger = spdlog::stdout_color_mt("APP");
		c_ClientLogger->set_level(spdlog::level::trace);
	}
}