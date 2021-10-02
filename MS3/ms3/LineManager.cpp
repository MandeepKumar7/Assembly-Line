// Name: Mandeep Kumar
// Seneca Student ID: 157972183
// Seneca email: mkumar62@myseneca.ca
// Date of completion: 2021-04-15
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include<string>
#include <set>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;
namespace sdds {

	LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations)
	{
        ifstream fin(filename);
        if (!fin.is_open()) {
            throw "File could not be opened";
        }
        Utilities util;
        util.setDelimiter('|');
        while (!fin.eof()) {
            bool more = true;
            string str;
            size_t next_pos = 0;
            getline(fin, str);
            str.erase(str.find_last_not_of("\r") + 1);
            string beginning = util.extractToken(str, next_pos, more);
            auto first = *find_if(
                stations.begin(),
                stations.end(),
                [&](Workstation* station) {
                    return station->getItemName() == beginning;
                });
            activeLine.push_back(first);
            if (!more) {
                continue;
            }
            string end = util.extractToken(str, next_pos, more);
            auto last = *find_if(
                stations.begin(),
                stations.end(),
                [&](Workstation* station) {
                    return station->getItemName() == end;
                });
            first->setNextStation(last);
        }
        Workstation* current = nullptr;
        for_each(
            stations.begin(),
            stations.end(),
            [&](Workstation* workstation) {
                current = *find_if(
                    stations.begin(),
                    stations.end(),
                    [&](Workstation* station) {
                        return station->getNextStation() == current;
                    });
            });
        m_firstStation = current;

	}
	void LineManager::linkStations()
	{
        const Workstation* current = m_firstStation;
        size_t i = 0;
        while (current != nullptr) {
            activeLine[i++] = const_cast<Workstation*>(current);
            current = current->getNextStation();
        }

	}
	bool LineManager::run(std::ostream& os)
	{

        static size_t count = 1;
        os << "Line Manager Iteration: " << count << endl;
        count++;
        if (!pending.empty()) {
            *m_firstStation += move(pending.front());
            pending.pop_front();
            m_cntCustomerOrder++;
        }
        for (auto& station : activeLine) {
            station->fill(os);
        }
        for (auto& station : activeLine) {
            station->attemptToMoveOrder();
        }
        return completed.size() + incomplete.size() == m_cntCustomerOrder;

	}
	void LineManager::display(std::ostream& os) const
	{

        for (auto& station : activeLine) {
            if (station != nullptr) {
                station->display(os);
            }
        }

	}
}