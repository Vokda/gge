/*
 * Reads and parses configuration file (gge.cfg)
 */

#pragma once
class GGE_API;
class Filer;
#include <string>
#include <stdexcept>
#include <vector>
#include "script_handling/scripter.hpp"
#include <libconfig.h++>
class Logger; 

class Configurer
{
	public:
		Configurer(const Filer& f, GGE_API&);

		const libconfig::Config& get_configuration() const;

		template<typename T>
		T read_value(const std::string& name) 
		{
			T value;
			try
			{
				_config.lookupValue(name.c_str(), value);
			}
			catch(const libconfig::SettingNotFoundException& e)
			{
				_log.error("Configuration setting not found: %s", name.c_str());
				throw std::runtime_error(e.what());
			}
			catch(const libconfig::SettingTypeException& e)
			{
				_log.error("Configuration setting has wrong type: %s", name.c_str());
				throw std::runtime_error(e.what());
			}
			return value;
		};

	private:
		void read_config(const std::string&);
		void store_config(const string& command, const vector<string>& args);
		void apply_config();

		GGE_API& _gge_api;
		libconfig::Config& _config;
        Logger::Log& _log;
};
