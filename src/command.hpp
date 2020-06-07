#pragma once

class Command
{
	public:
		virtual ~Command();
		virtual void execute() = 0;
		//Graphics* init_graphics(const std::string& name, size_t width, size_t height);
	protected:
		Command();
};
