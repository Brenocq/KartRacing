//------------------------------------//
// Author: Breno Cunha Queiroz        //
// Date: 2020-11-17                   //
// SCC0650 - Computação Gráfica (2020)//
//------------------------------------//
#include <stdio.h>
#include "log.hpp"
#include "defines.hpp"

Log::Log()
{

}

Log::~Log()
{

}

void Log::verbose(std::string tag, std::string text, bool showTag)
{
	logging(tag, BOLDCYAN, CYAN, text, showTag);
}

void Log::debug(std::string tag, std::string text, bool showTag)
{
	logging(tag, BOLDGREEN, RESET, text, showTag);
}

void Log::success(std::string tag, std::string text, bool showTag)
{
	logging(tag, BOLDGREEN, GREEN, text, showTag);
}

void Log::info(std::string tag, std::string text, bool showTag)
{
	logging(tag, BOLDWHITE, RESET, text, showTag);
}

void Log::infoItem(std::string tag, std::string text)
{
	info(tag, std::string("- ")+text, false);
}

void Log::warning(std::string tag, std::string text, bool showTag)
{
	logging(tag, BOLDYELLOW, YELLOW, text, showTag);
}

void Log::error(std::string tag, std::string text, bool showTag)
{
	logging(tag, BOLDRED, RED, text, showTag);
}

void Log::logging(std::string tag, const char* tagColor, const char* textColor, std::string text, bool showTag)
{
	std::string tag_ = tag;
	if(!showTag)
		for(int i=0; i<(int)tag_.size();i++)
			tag_[i] = ' ';

	// Print tag
	if(showTag)
    	printf("%s[%s]%s %s\n%s", tagColor, tag_.c_str(), textColor, text.c_str(), RESET);
	else
    	printf("%s %s %s %s\n%s", tagColor, tag_.c_str(), textColor, text.c_str(), RESET);
}
