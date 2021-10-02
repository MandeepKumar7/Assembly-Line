// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-15
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <iostream>
#include <vector>
#include "Workstation.h"
using namespace std;
namespace sdds {
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;
	Workstation::Workstation(const std::string& str) :Station(str)
	{

	}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool out = true;
		if (m_orders.empty())
		{
			out = false;
		}
		else {
			if (m_orders.front().isItemFilled(Station::getItemName())) {
				if (m_orders.front().isFilled()) {
					completed.push_back(std::move(m_orders.front()));
					m_orders.pop_front();
				}
				else if (m_pNextStation != nullptr) {
					*m_pNextStation += std::move(m_orders.front());
					m_orders.pop_front();
				}
				else {
					out = false;
				}
			}
			else if (Station::getQuantity() == 0) {
				incomplete.push_back(std::move(m_orders.front()));
				m_orders.pop_front();
			}
		}
		return out;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}
	const Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
		}
		else {
			os << getItemName() << " --> End of Line" << endl;
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}
}