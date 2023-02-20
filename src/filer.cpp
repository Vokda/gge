#include "filer.hpp"
#include <errno.h>
#include <string.h>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

Filer::Filer(const char* game_dir)
{
	_game_root_dir = string(game_dir);

	stat_file(_game_root_dir);

	if(!is_dir(_game_root_dir))
	{
		stringstream ss;
		ss << "Scripter: '" << game_dir << "' not a directory!" << _file_stat.st_mode << endl;
		throw runtime_error(ss.str());
	}
}

bool Filer::is_file(const string& file_path)
{
	stat_file(file_path.c_str());
	return S_ISREG(_file_stat.st_mode);
}

bool Filer::is_dir(const string& file_path)
{
	stat_file(file_path.c_str());
	return S_ISLNK(_file_stat.st_mode) || S_ISDIR(_file_stat.st_mode);
}

string Filer::in_game_dir(const string& append_path)
{
	string out = _game_root_dir;
	out += "/" + append_path;
	return out;
}

string Filer::in_game_dir(const char* ap)
{
	string s(ap);
	return in_game_dir(s);
}

struct stat Filer::stat_file(const string& path)
{
	if(stat(path.c_str(), &_file_stat) == -1)
	{
		stringstream ss;
		ss << "cannot stat file " << path << ": " << errno << endl;
		throw runtime_error(ss.str());
	}
	else
		return _file_stat;
}
