#include <exception>
#include <string>
#include <iostream>


class No_impact : public std::exception
{
private:
	std::string m_error;

public:
	No_impact(): 
		m_error(std::string("No collision on trajectory\n"))
	{}

	// return the std::string as a const C-style string
//	const char* what() const { return m_error.c_str(); } // pre-C++11 version
	const char* what() const noexcept { return m_error.c_str(); } // C++11 version
};