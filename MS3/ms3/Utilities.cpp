// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-05
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <sstream>
#include "Utilities.h"
using namespace std;
namespace sdds {
	char Utilities::m_delimeter = ',';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string token;
		string::size_type beginning = next_pos;
		string::size_type end;
		end = str.find(m_delimeter, beginning);
		string::size_type size = end - beginning;
  		if (end >= str.length()) {
			end = str.length();
			size = str.length()-beginning;
			token = str.substr(beginning);
			more = false;
		}
		else {
			token = str.substr(beginning, size);
			more = true;
		}		
		if (token != "") {
			end++;
			next_pos = end;
			if (getFieldWidth() < size) {
				setFieldWidth(size);
			}
		}
		else {
			more = false;
			throw"ERROR: No token.";
		}
		
		return token;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimeter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimeter;
	}

}