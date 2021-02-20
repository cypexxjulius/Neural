#include "nlpch.h"
#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Neural {
	std::shared_ptr<spdlog::logger> Logging::m_CoreLogger;
	std::shared_ptr<spdlog::logger> Logging::m_ClientLogger;

	void Logging::init() {
		spdlog::set_pattern("%^[ + ] %n: %v%$");
		m_CoreLogger = spdlog::stdout_color_mt("Neural");
		m_CoreLogger->set_level(spdlog::level::trace);
		
		m_ClientLogger = spdlog::stdout_color_mt("APP");
		m_ClientLogger->set_level(spdlog::level::trace);
	}
}