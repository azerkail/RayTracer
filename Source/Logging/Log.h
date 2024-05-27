#ifndef RAYTRACER_LOG_H
#define RAYTRACER_LOG_H

#include "spdlog/spdlog.h"

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
#define LOG_CRITICAL(...) ::RayTracer::Log::Logger()->critical(__VA_ARGS__)
#define LOG_ERROR(...) ::RayTracer::Log::Logger()->error(__VA_ARGS__)
#define LOG_WARNING(...) ::RayTracer::Log::Logger()->warn(__VA_ARGS__)
#define LOG_INFO(...) ::RayTracer::Log::Logger()->info(__VA_ARGS__)
#define Log_TRACE(...) ::RayTracer::Log::Logger()->trace(__VA_ARGS__)

}

#endif //RAYTRACER_LOG_H
