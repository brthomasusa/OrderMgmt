#pragma once
#include <string_view>
#include <mutex>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

using namespace std;

namespace CommonUtilities {

    class Logger
    {
    public:
        static Logger& instance();

        // Remove copy ctor and assignment operator
        Logger(const Logger&) = delete;
        Logger& operator=(Logger&) = delete;

        void LogTrace(string_view message);
        void LogDebug(string_view message);
        void LogInfo(string_view message);
        void LogWarning(string_view message);
        void LogError(string_view message);

    private:
        Logger();
        ~Logger() = default;

        void boostLoggingInit();

        static Logger _instance;
        std::mutex _lock;
        boost::log::sources::severity_logger<boost::log::trivial::severity_level> _logger;
    };
}

