#pragma once

#include <iostream>
#include <sstream>
#include <string>

using std::string;

class Sales_data_ch7_v4 {
private: 
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

public: 
// Constructors

    // Changed here compared to v3: move this constructor to top
    Sales_data_ch7_v4(const string s, const unsigned units_sold, const double price) :
        bookNo{ s },
        units_sold{ units_sold },
        revenue{ units_sold * price }
    {
        std::cout << "In body of the first constructor." << std::endl;
        std::cout << "    " << ToString() << std::endl;
    }
    
    // Change here: make default constructor delegating
    Sales_data_ch7_v4() : Sales_data_ch7_v4("def", 1, 1)
    {
        std::cout << "In body of the \"default\" constructor." << std::endl;
        std::cout << "    " << ToString() << std::endl;
    }

    // Change here: make this constructor delegating.
    explicit Sales_data_ch7_v4(const string s) : Sales_data_ch7_v4(s, 2, 2)
    {
        std::cout << "In body of the third constructor." << std::endl;
        std::cout << "    " << ToString() << std::endl;
    }

    string isbn() const { return bookNo; }

    Sales_data_ch7_v4& combine(const Sales_data_ch7_v4& other)
    {
        units_sold += other.units_sold;
        revenue += other.revenue;
        return *this;
    }

    double avg_price() const
    {
        if (units_sold > 0)
            return revenue / units_sold;
        return 0;
    }

    string ToString() const
    {
        std::stringstream result;
        result << "ISBN: " << this->isbn() << ", units_sold: " << this->units_sold << ", revenue: "
            << this->revenue << ", average price: " << this->avg_price();
        return result.str();
    }

};

