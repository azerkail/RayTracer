#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace RayTracer {
    std::shared_ptr<spdlog::logger> Log::s_logger;

    void RayTracer::Log::Initialise() {
        spdlog::set_pattern("%^[%H:%M:%S.%e][%n]: %v%$");

        s_logger = spdlog::stdout_color_mt(m_loggerName);
        s_logger->set_level(spdlog::level::trace);
    }

    const std::shared_ptr<spdlog::logger>& RayTracer::Log::Logger() {
        return s_logger;
    }
}
