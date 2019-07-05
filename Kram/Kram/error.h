#pragma once

#include <exception>
#include <string>

class kram_error : public std::exception
{
public:
	kram_error(const std::string& message = "") :
		exception{ message.c_str() }
	{}
};

#define DECLARE_ERROR_TYPE(identifier) class identifier : public kram_error
