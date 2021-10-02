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
		size_t next_pos = 0;
		bool more = true;
		m_name = more ? util.extractToken(str, next_pos, more) : "";
		m_nextSerial = more ? stoi(util.extractToken(str, next_pos, more)) : 0;
		m_noOfItems = more?stoi(util.extractToken(str, next_pos, more)):0;
		m_widthField = (util.getFieldWidth() > m_widthField) ? util.getFieldWidth() : m_widthField;
		m_desc = more ? util.extractToken(str, next_pos, more) : "";
		id_generator++;
		m_id = id_generator;
		
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
		os << setw(3) << right << setfill('0') << m_id << "] Item: ";
		os << left << setw(m_widthField) << setfill(' ') << m_name << " [";
		os << setw(6) << right << setfill('0') << m_nextSerial << "]";
		if (full == false) {
			os << endl;
		}
		else {
			os << " Quantity: ";
			os << setw(m_widthField) << left << setfill(' ') << m_noOfItems << " Description: " << m_desc << endl;
		}
	}

	Station::~Station()
	{

	}

}