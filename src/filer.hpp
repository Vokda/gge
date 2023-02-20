#pragma once
#include <string>
using namespace std;
// use C solution until switching to C++17
// Running C++17 now, but why change a working concept
// TODO unix only, change for portability
#include <sys/stat.h>

/*
 * handles files and paths
 * also contains directories for game 
 */

class Filer
{
	public:
		Filer(const char* game_dir);
		Filer() = delete;

		bool is_file(const string& file_path);
		bool is_dir(const string& dir_path);

		const string& get_game_root_dir() { return _game_root_dir; }
		string in_game_dir(const string& append_path);
		string in_game_dir(const char* append_path);
	private:
		struct stat stat_file(const string& game_dir);
		void init(const string& game_dir);

		string _game_root_dir;
		struct stat _file_stat;

};
