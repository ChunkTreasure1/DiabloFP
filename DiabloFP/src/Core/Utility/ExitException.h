#pragma once

#include <exception>

namespace Diablo
{
	struct ExitException: public std::exception
	{
		const char* what() const throw()
		{
			return "Exit Application";
		}
	};
}