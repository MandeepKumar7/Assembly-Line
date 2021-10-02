// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-05
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace sdds {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;
	Station::Station(const std::string str)
	{
		Utilities util;
		bool more = true;
		size_t next_pos = 0;
		id_generator++;
		m_id = id_generator;
		m_name = more ? util.extractToken(str, next_pos, more) : "";
		m_nextSerial = more ? stoi(util.extractToken(str, next_pos, more)) : 0;
		m_noOfItems = more?stoi(util.extractToken(str, next_pos, more)):0;
		m_widthField = (util.getFieldWidth() > m_widthField) ? util.getFieldWidth() : m_widthField;
		m_desc = more ? util.extractToken(str, next_pos, more) : "";	
	}
	const std::string& Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_nextSerial++;
	}
	size_t Station::getQuantity() const
	{
		return m_noOfItems;
	}
	void Station::updateQuantity()
	{
		if (m_noOfItems > 0) m_noOfItems--;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << "[";
		os << right << setw(3) << setfill('0') << m_id;
		os << "] Item: ";
		os << left << setw(m_widthField) << setfill(' ') << m_name;
		os << " [";
		os << right << setw(6) << setfill('0') << m_nextSerial;
		os << "]";
		if (full == false) {
			os << endl;
		}
		else {
			os << " Quantity: ";
			os << left << setw(m_widthField) << setfill(' ') << m_noOfItems;
			os << " Description: " << m_desc << endl;
		}
	}

	Station::~Station()
	{

	}

}