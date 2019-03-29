#include "Logger.h"
#include <iostream>
#include <memory>
#include <utility>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

namespace logging = boost::log;
using namespace logging::trivial;

namespace CommonUtilities {

    Logger Logger::_instance;

    Logger& Logger::instance()
    {
        return _instance;
    }

    Logger::Logger()
    {
        boostLoggingInit();
        logging::add_common_attributes();
    }

    void Logger::LogTrace(string_view message)
    {
        lock_guard<mutex> guard(_lock);
        BOOST_LOG_SEV(_logger, trace) << message;
    }

    void Logger::LogDebug(string_view message)
    {
        lock_guard<mutex> guard(_lock);
        BOOST_LOG_SEV(_logger, debug) << message;
    }

    void Logger::LogInfo(string_view message)
    {
        lock_guard<mutex> guard(_lock);
        BOOST_LOG_SEV(_logger, info) << message;
    }

    void Logger::LogWarning(string_view message)
    {
        lock_guard<mutex> guard(_lock);
        BOOST_LOG_SEV(_logger, warning) << message;
    }

    void Logger::LogError(string_view message)
    {
        lock_guard<mutex> guard(_lock);
        BOOST_LOG_SEV(_logger, error) << message;
    }

    void Logger::boostLoggingInit()
    {
        logging::add_file_log
                (
                        boost::log::keywords::file_name = "/home/bthomas/Projects/cplus/OciLibTest/logs/OciLibTest-%N.log",
                        boost::log::keywords::open_mode = std::ios_base::app,
                        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
                        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
                        boost::log::keywords::format = "[%TimeStamp%]: %Message%",
                        boost::log::keywords::auto_flush = true
                );

        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::trace);
                                        
        logging::add_common_attributes();
    }

}

