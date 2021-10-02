// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-15
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds {
    class LineManager
    {
        std::vector<Workstation*> activeLine;
        size_t m_cntCustomerOrder = 0;
        Workstation* m_firstStation=nullptr;
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void linkStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif // !SDDS_LINEMANAGER_H

