#ifndef SDDS_CustomerOrder_H
#define SDDS_CustomerOrder_H
#include <iostream>
#include "Station.h"
namespace sdds {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder {
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;
		static size_t m_widthField;
		void setEmpty();
	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& src);
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&& src)noexcept;
		CustomerOrder& operator=(CustomerOrder&& src)noexcept;
		virtual ~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !SDDS_CustomerOrder_H
