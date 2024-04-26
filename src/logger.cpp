#include "logger.hpp"
using namespace std;
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
using namespace log4cpp;

Logger::Logger():
	_root(log4cpp::Category::getRoot())
{
    // TODO read log amount from config or make file
	_log_amount = DEBUG;

    // TODO only append to ostream atm
	_appender = make_unique<OstreamAppender>("console", &std::cout);

    _pattern_layout = make_shared<PatternLayout>();
    _pattern_layout->setConversionPattern("%d{%Y-%m-%dT%H:%M:%S} - %c %p: %m\n");
    _appender->setLayout(_pattern_layout.get());
    //_appender->setLayout(new BasicLayout());

    _root.setPriority(log4cpp::Priority::INFO);
    _root.addAppender(*_appender);
    _logger_info = &add_category("Logger", log4cpp::Priority::INFO);

    _root.info("log4cpp setup complete");
}

log4cpp::Category& Logger::add_category(const string& s, const log4cpp::Priority::Value p)
{
    if(auto cat = Category::exists(s))
    {
        _logger_info->info("Category '" + s + "' already exists!");
        return *cat;
    }
    else
    {
        log4cpp::Category& instance = Category::getInstance(s);
        //instance.addAppender(*_appender);
        instance.setPriority(p);
        return instance;
    }
}

log4cpp::Category& Logger::add_category(const string& s)
{
    return add_category(s, log4cpp::Priority::INFO);
}

Logger::Log& Logger::get_category(const string& s)
{
    if(auto cat = Category::exists(s))
       return *cat;
    else 
        throw(runtime_error("Category " + s + " does not exist!"));
}

Logger::Log& Logger::get_category(const string& s, const log4cpp::Priority::Value p)
{
    if(auto cat = Category::exists(s))
    {
       return *cat;
    }
    else 
    {
        _logger_info->info("Category '" + s + "' does not exist. Creating new category '" + s + "'");
        return add_category(s, p);
    }
}

Logger::Log_stream Logger::get_category_stream(const string& category_name, const Priority::Value priority)
{
    Log& category = get_category(category_name, priority);
    return category.getStream(priority);
}

void Logger::log(const string& s, log4cpp::Priority::Value p, const std::string& message)
{
    if(auto cat = Category::exists(s))
    {
        cat->log(p, message);
    }
    else
    {
        _root.warn("Category " + s + " does not exist! Printing as root:\n" + message);
    }
}

void Logger::log_buffer(const string& category, log4cpp::Priority::Value p)
{
    Log& log = get_category("category");
    log.log(p, _buffer.str());
    _buffer.flush();
}
