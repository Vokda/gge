#pragma once

#define LOG4CPP_FIX_ERROR_COLLISION 1
#include <memory>
#include <map>
#include <stack>
#include <sstream>
using namespace std;

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
using namespace log4cpp;

#include "gge_modules/registered_gge_modules.hpp"
#include "sdl_helper.hpp"

namespace log4cpp
{
    class PatternLayout;
}

class Logger
{
	enum Log_amount {NONE, DEBUG, SPAM};
	public:
        typedef log4cpp::Category Log;
        typedef log4cpp::CategoryStream Log_stream;

        static Logger& get_instance() 
        {
            static Logger instance; // This instance is created only once.
            return instance;
        }

        //static Log& get_category(const string& category_name = "");

        // Prevent copying or assignment.
        Logger(Logger const&) = delete;
        void operator=(Logger const&) = delete;

        template<typename T>
        stringstream& operator<<(const T& value)
        {
            _buffer << value;
            return _buffer;
        }

        stringstream& get_buffer() {return _buffer;}

        // log stuff
        void log(const string& category, log4cpp::Priority::Value p, const std::string& message); 

        void log_buffer(const string& category, log4cpp::Priority::Value p); 

		log4cpp::Category& add_category(const string& s);
		log4cpp::Category& add_category(const string& s, const log4cpp::Priority::Value p);
        Log& get_category(const string& s = "");
        Log& get_category(const string& s, const log4cpp::Priority::Value p);

        Log_stream get_category_stream(const string& category_name, const Priority::Value priority);

	private:
		Logger(); 
        ~Logger() {};

		unique_ptr<Appender> _appender;
		stringstream _buffer;
		Log_amount _log_amount;
		log4cpp::Category& _root;
        Log* _logger_info;
        shared_ptr<PatternLayout> _pattern_layout;
};
