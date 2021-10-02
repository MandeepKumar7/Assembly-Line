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
		size_t next_pos = 0;
		bool more = false;
		string s_str;
		if (str.empty()) {
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
			out = m_lstItem[i]->m_itemName == itemName ? m_lstItem[i]->m_isFilled : true;
		}
		return out;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() >= 1) {
					m_lstItem[i]->m_serialNumber =
						station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					os << "    Filled " << m_name;
					os << ", " << m_product;
					os << " [" << m_lstItem[i]->m_itemName;
					os << "]" << std::endl;
				}
				else {
					os << " Unable to fill " << m_name;
					os << ", " << m_product;
					os << " [" << m_lstItem[i]->m_itemName;
					os << "]" << std::endl;
				}
			}
		}

	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << std::right <<
				m_lstItem[i]->m_serialNumber << "] ";
			os << std::setfill(' ') << std::setw(m_widthField) << std::left <<
				m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << std::endl;
		}

	}

}