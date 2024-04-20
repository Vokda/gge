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
namespace log4cpp
{
    class PatternLayout;
}

class Logger
{
	enum Log_amount {NONE, DEBUG, SPAM};
	public:
        typedef log4cpp::Category Log;

        static Logger& get_instance() 
        {
            static Logger instance; // This instance is created only once.
            return instance;
        }

        // Prevent copying or assignment.
        Logger(Logger const&) = delete;
        void operator=(Logger const&) = delete;

        // log stuff
        void log(const string& category, log4cpp::Priority::Value p, const std::string& message); 
        void log(const std::string& message); 
        void info(const std::string& message); 
		void debug(const string& s);
        void fatal(const string& s);
        inline void spam(const string& s);

		log4cpp::Category& add_category(const string& s);
		log4cpp::Category& add_category(const string& s, const log4cpp::Priority::Value p);

        void set_category(const string& s);

		// save up
		//void operator<<(const string &s);
		//void operator<<(const basic_ostream& o);
		void flush(); // and pop category*/
	private:
		Logger(); 
        ~Logger() {};

		unique_ptr<Appender> _appender;
		stringstream buffer;
		Log_amount _log_amount;
		log4cpp::Category& _root;
        log4cpp::Category* _current_category = &_root;
        shared_ptr<PatternLayout> _pattern_layout;
};
