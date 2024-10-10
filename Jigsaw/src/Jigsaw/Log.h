#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Jigsaw {

	class JIGSAW_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define JS_CORE_FATAL(...)	::Jigsaw::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define JS_CORE_ERROR(...)	::Jigsaw::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JS_CORE_WARN(...)	::Jigsaw::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JS_CORE_INFO(...)	::Jigsaw::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JS_CORE_TRACE(...)	::Jigsaw::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define JS_FATAL(...)		::Jigsaw::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define JS_ERROR(...)		::Jigsaw::Log::GetClientLogger()->error(__VA_ARGS__)
#define JS_WARN(...)		::Jigsaw::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JS_INFO(...)		::Jigsaw::Log::GetClientLogger()->info(__VA_ARGS__)
#define JS_TRACE(...)		::Jigsaw::Log::GetClientLogger()->trace(__VA_ARGS__)