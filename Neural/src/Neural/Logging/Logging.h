#pragma once

#include "Neural/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <stdio.h>

namespace Neural {
	class Logging {
	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return m_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return m_ClientLogger;
		}

	};
}


// Core log Macros
#define NL_CORE_ERROR(...) ::Neural::Logging::GetCoreLogger()->error(__VA_ARGS__)
#define NL_CORE_WARN(...) ::Neural::Logging::GetCoreLogger()->warn(__VA_ARGS__)
#define NL_CORE_INFO(...) ::Neural::Logging::GetCoreLogger()->info(__VA_ARGS__)
#define NL_CORE_TRACE(...) ::Neural::Logging::GetCoreLogger()->trace(__VA_ARGS__)
#define NL_CORE_FATAL(...) ::Neural::Logging::GetCoreLogger()->critical(__VA_ARGS__)

#define NL_ERROR(...) ::Neural::Logging::GetClientLogger()->error(__VA_ARGS__)
#define NL_WARN(...) ::Neural::Logging::GetClientLogger()->warn(__VA_ARGS__)
#define NL_INFO(...) ::Neural::Logging::GetClientLogger()->info(__VA_ARGS__)
#define NL_TRACE(...) ::Neural::Logging::GetClientLogger()->trace(__VA_ARGS__)
#define NL_FATAL(...) ::Neural::Logging::GetClientLogger()->critical(__VA_ARGS__)