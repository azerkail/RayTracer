#ifndef RAYTRACER_LOG_H
#define RAYTRACER_LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace RayTracer {

    class Log {
    public:
        static void Initialise();
        static const std::shared_ptr<spdlog::logger>& Logger();
    private:
        inline static const std::string& m_loggerName = "RayTracer";
        static std::shared_ptr<spdlog::logger> s_logger;
    };

// Macros for usability and stripping.
#define AS_CRITICAL(...) ::RayTracer::Log::Logger()->critical(__VA_ARGS__)
#define AS_ERROR(...) ::RayTracer::Log::Logger()->error(__VA_ARGS__)
#define AS_WARNING(...) ::RayTracer::Log::Logger()->warn(__VA_ARGS__)
#define AS_INFO(...) ::RayTracer::Log::Logger()->info(__VA_ARGS__)
#define AS_TRACE(...) ::RayTracer::Log::Logger()->trace(__VA_ARGS__)

}

#endif //RAYTRACER_LOG_H
