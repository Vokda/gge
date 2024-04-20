#include "logger.hpp"
using namespace std;
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
using namespace log4cpp;

Logger::Logger():
	_root(log4cpp::Category::getRoot())
    //_current_category(_root)
{
    // TODO read log amount from config or make file
	_log_amount = DEBUG;

    // TODO only append to ostream atm
	_appender = make_unique<OstreamAppender>("console", &std::cout);

    _pattern_layout = make_shared<PatternLayout>();
    _pattern_layout->setConversionPattern("%d{%Y-%m-%dT%H:%M:%S} @ %c %p: %m\n");
	_appender->setLayout(_pattern_layout.get());
	//_appender->setLayout(new BasicLayout());
	_root.setPriority(log4cpp::Priority::INFO);
	_root.addAppender(*_appender);
}

log4cpp::Category& Logger::add_category(const string& s, const log4cpp::Priority::Value p)
{
    log4cpp::Category& instance = Category::getInstance(s);
	instance.addAppender(*_appender);
	instance.setPriority(p);
    return instance;
}

log4cpp::Category& Logger::add_category(const string& s)
{
    return add_category(s, log4cpp::Priority::INFO);
}

void Logger::set_category(const string& s)
{
    if(auto cat = Category::exists(s))
    {
        _current_category = cat;
    }
    else
        _root.warn("Category " + s + " does not exist!");
} 

void Logger::debug(const string& s)
{
    _current_category->debug(s);
}

void Logger::info(const string& s)
{
    _current_category->info(s);
}

void Logger::fatal(const string& s)
{
    _current_category->fatal(s);
}

void Logger::log(const string& s, log4cpp::Priority::Value p, const std::string& message)
{
    if(auto cat = Category::exists(s))
    {
        cat->log(p, message);
    }
    else
    {
        _root.warn("Category " + s + " does not exist!");
    }
}

void Logger::log(const std::string& message)
{
    _current_category->log(_current_category->getPriority(), message);
}
