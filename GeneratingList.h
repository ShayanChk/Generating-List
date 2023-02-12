//Name: Shayan Chabook
//student ID: 159844208
//email:schabook@myseneca.ca
//7/23/2022
#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	template<typename T>
	class GeneratingList {

		std::vector<T> list;
	public:

		GeneratingList() {}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T& operator[](size_t i) const { return list[i]; }

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's
		bool Luhn(const std::string card)
		{
			int nDigits = card.length();

			int nSum = 0, isSecond = false;
			for (int i = nDigits - 1; i >= 0; i--) {

				int d = card[i] - '0';

				if (isSecond == true)
					d = d * 2;

				nSum += d / 10;
				nSum += d % 10;

				isSecond = !isSecond;
			}
			return (nSum % 10 == 0);

		}

		//TODO: Overload the += operator with a raw pointer
		// as a second operand.
		void operator+=(T* obj)
		{
			list.push_back(std::move(*obj));
		}

		void operator+=(std::shared_ptr<T> obj)
		{
			list.push_back(std::move(*obj));
		}

		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H