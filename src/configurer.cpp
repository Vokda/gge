#include "configurer.hpp"
#include "filer.hpp"
#include "logger.hpp"
#include "script_handling/gge_api.hpp"
using namespace std;
using namespace libconfig;

Configurer::Configurer(const Filer& f, GGE_API& ga):
	_gge_api(ga), _config(*new Config()), _log(Logger::make_category("Configurer"))
{
	string cfg = f.in_game_dir("gge.cfg");
    _log.info("Expecting configuration file name: %s", cfg.c_str());
	read_config(cfg);
	//apply_config();
}

void Configurer::read_config(const std::string& config_path)
{
	_log.info("Reading configuration file: %s", config_path.c_str());
	try 
	{
		_config.readFile(config_path.c_str());
	}
	catch(const FileIOException& e)
	{
		_log.error("I/O error while reading configuration file: %s", e.what());
		throw runtime_error(e.what());
	}
	catch(const libconfig::ParseException& e)
	{
		_log.error("Error parsing configuration file: %s", e.what());
		throw runtime_error(e.what());
	}
	
	_log.info("Configuration file read successfully.");
}

const libconfig::Config& Configurer::get_configuration() const
{
	return _config;
}

void Configurer::apply_config()
{
	// modules
	const Setting& root = _config.getRoot();
	if(root.exists("modules"))
	{
		_log.debug("Applying configuration for modules...");
		const Setting& modules = root["modules"];
		// TODO make this more dynamic
		if (modules.exists("graphics"))
		{
			_log.debug("Applying configuration for graphics module...");
			const Setting& graphics_config = modules["graphics"];
			_log.debug("calling api to initialize graphics module...");
			string window_title; 
			int window_width, window_height;
			graphics_config.lookupValue("window_title", window_title);
			graphics_config.lookupValue("window_width", window_width);
			graphics_config.lookupValue("window_height", window_height);
			_gge_api.init_graphics(
				window_title,
				window_width,
				window_height);
		}
		if (modules.exists("events"))
		{
			_gge_api.init_events();
		}
		if (modules.exists("gui"))
		{
			_gge_api.init_gui();
		}
	}

	bool debug_mode = read_value<bool>("debug_mode");
	_gge_api.debug(debug_mode);
	
}