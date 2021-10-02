// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-05
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
namespace sdds {
	class Utilities {
		size_t m_widthField = 1;
		static char m_delimeter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
	
}
#endif // !SDDS_UTILITIES_H

