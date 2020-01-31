#pragma once
#ifndef PORTAL_ERROR_HPP
#define PORTAL_ERROR_HPP

// portal_error.hpp
// Check if a sf::FloatRect collides with the right or left side of the hitbox
// Contains the No_Impact class


#include <exception>
#include <string>
#include <iostream>

// Class for throwing std::strings as errors
class No_Impact : public std::exception
{
private:
	std::string m_error;

public:
	// Constructor
	No_Impact(): 
		m_error(std::string("No collision on trajectory\n"))
	{}

	// Return the std::string as a const C-style string
	// const char* what() const { return m_error.c_str(); } // pre-C++11 version
	const char* what() const noexcept { return m_error.c_str(); } // C++11 version
};


#endif