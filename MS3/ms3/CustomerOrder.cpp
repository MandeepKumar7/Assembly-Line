// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-10
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include"Utilities.h"
#include"Station.h"
using namespace std;
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	void CustomerOrder::setEmpty()
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder()
	{
		setEmpty();
	}

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities util;
		string s_str;
		bool more = false;
		size_t next_pos = 0;
		if (str=="") {
			setEmpty();
		}
		else {
			m_name = util.extractToken(str, next_pos, more);
			m_product = more ? util.extractToken(str, next_pos, more) : "";
			s_str = str.substr(next_pos, str.length() - next_pos);
			m_cntItem = count(s_str.begin(), s_str.end(), util.getDelimiter());
			m_cntItem++;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				if (more) {
					m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
				}
				else {
					i = m_cntItem;
				}
			}
			m_widthField = m_widthField < util.getFieldWidth() ? util.getFieldWidth() : m_widthField;
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw"ERROR";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		m_cntItem = 0;
		m_lstItem = nullptr;
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src) {
			m_name = src.m_name;
			m_product = src.m_product;
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[]m_lstItem;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.setEmpty();
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[]m_lstItem;
	}

	bool CustomerOrder::isFilled() const
	{
		bool out = true;
		for (size_t i = 0; i < m_cntItem && out; i++) {
			out = m_lstItem[i]->m_isFilled;
		}
		return out;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool out = true;
		for (size_t i = 0; i < m_cntItem && out; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				out = m_lstItem[i]->m_isFilled;
			}
		}
		return out;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() >= 1) {
					m_lstItem[i]->m_serialNumber =
						station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else {
					os << " Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}

	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << right << setw(6) << setfill('0') <<
				m_lstItem[i]->m_serialNumber << "] ";
			os << left << setw(m_widthField) << setfill(' ') <<
				m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED" << endl;
			}
			else {
				os << "TO BE FILLED" << endl;
			}
		}

	}

}