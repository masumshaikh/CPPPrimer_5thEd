// Chapter7_Section2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>

using std::string;

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.2, Access Control and Encapsulation
// p. 269
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.16
// What, if any, are the constraints on where and how often an access speciﬁer
// may appear inside a class deﬁnition ? What kinds of members should be deﬁned
// after a public speciﬁer ? What kinds should be private ?
//
// ANSWER
// There are no constraints on where or how often.
//
// Implementation details should be kept private. Interesting functionality can be made public.

// Exercise 7.17 : What, if any, are the differences between using class or struct?
// 
// ANSWER
// No difference, except that members are public by default in a `struct`, private by default in a `class`.

// Exercise 7.18 : What is encapsulation ? Why is it useful?
// 
// ANSWER
// Encapsulation is the practice of showing to the user only what they need to see.
// It is useful to prevent users from messing around with the state of your objects.
// Also, we can change the hidden implementation without breaking client code.

// Exercise 7.19 : Indicate which members of your Person class you would declare as
// public and which you would declare as private. Explain your choice.
//
// ANSWER
// There are two data members in the class, and nothing else. It is common practice to make them both private,
// and introduce public getters and setters.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.2.1, Friends
// p. 269
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.20: When are friends useful ? Discuss the pros and cons of using friends.
// 
// Friends are useful for writing functions which are part of the interface of a class, but not members of it.
// Their main disadvantage is that they break encapsulation, since they can access private members.

// Exercise 7.21 : Update your Sales_dataclass to hide its implementation. The programs 
// you’ve written to use Sales_data operations should still continue to work.
// Recompile those programs with your new class deﬁnition to verify that they still work.
//
// ANSWER: struct changed to class. Data members hidden. Constructors and other methods public.
class Sales_data_ch7_v3 {
private: // New: these members are now private.
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

public: // New: public methods remain public, but now have to be specified as such, as we have changed the class 
        // to a struct.
    // Constructors
    // Default
    Sales_data_ch7_v3() = default;

    // From string, using initialiser list
    // Takes ISBN as parameter; units_sold and revenue kept at default values above.
    Sales_data_ch7_v3(const string s) : bookNo{ s }
    {}

    // Initialise all three members, using initialiser list
    Sales_data_ch7_v3(const string s, const unsigned units_sold, const double price) :
        bookNo{ s },
        units_sold{ units_sold },
        revenue{ units_sold * price }
    {}

    // Initialise from istream
    Sales_data_ch7_v3(std::istream& cin)
    {
        std::cout << "Please input bookNo, units_sold, and price (separated by spaces), or 'null 0 0' to exit: ";
        double price = 0.0;
        cin >> this->bookNo >> this->units_sold >> price;
        this->revenue = price * this->units_sold;
    }

    string isbn() const { return bookNo; }

    Sales_data_ch7_v3& combine(const Sales_data_ch7_v3& other)
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

int ex_7_21()
{
    // This is a copy/paste of ex_7_11(), with the only change being _v2 to _v3.
    // It still works unchanged.
    auto sd1 = Sales_data_ch7_v3();
    auto sd2 = Sales_data_ch7_v3("978-0-99-702549-1");
    auto sd3 = Sales_data_ch7_v3("978-2-12-345680-3", 10, 1.30);
    auto sd4 = Sales_data_ch7_v3(std::cin);

    std::cout << sd1.ToString() << std::endl;
    std::cout << sd2.ToString() << std::endl;
    std::cout << sd3.ToString() << std::endl;
    std::cout << sd4.ToString() << std::endl;

    return 0;
}

// Exercise 7.22 : Update your Person class to hide its implementation.
//
// ANSWER
// The last version of Person, Person_v7_9 is already encapsulated.

int main()
{
    ex_7_21();
}
