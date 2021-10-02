// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-05
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
namespace sdds {
	class Station {
		int m_id;
		std::string m_name;
		std::string m_desc;
		unsigned int m_nextSerial;
		unsigned int m_noOfItems;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station(const std::string str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
		virtual ~Station();
	};
}
#endif // !SDDS_STATION_H

