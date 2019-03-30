#pragma once
#include <string>
#include <mutex>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

using namespace std;

namespace ServiceLayer {

    class Logger
    {
    public:
        static Logger& instance();

        // Remove copy ctor and assignment operator
        Logger(const Logger&) = delete;
        Logger& operator=(Logger&) = delete;

        void LogTrace(const string& message);
        void LogDebug(const string& message);
        void LogInfo(const string& message);
        void LogWarning(const string& message);
        void LogError(const string& message);

    private:
        Logger();
        ~Logger() = default;

        void boostLoggingInit();

        static Logger _instance;
        std::mutex _lock;
        boost::log::sources::severity_logger<boost::log::trivial::severity_level> _logger;
    };
}

