// Chapter7_Ex_7_2to3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <sstream>

using std::string;

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.1.1, Designing the `Sales_data` class
// p. 256
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.1: Write a version of the transaction-processing program from § 1.6 
// (p. 25, EXERCISES SECTION 1.6, The Bookstore Program, ex_1_25())
// using the Sales_data class you deﬁned for the exercises in § 2.6.1 (p. 72).
// 
// Ignored for now: it makes much more sense to rewrite the transaction processing program
// in exercise 7.7 (in section 7.1.3).


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.1.2, Defining The Revised `Sales_data` class
// p. 260
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.2
// Add the combine and isbn members to the Sales_data class you
// wrote for the exercises in § 2.6.2 (p. 76).
struct Sales_data_ch7 {
    // data members are unchanged from  § 2.6.1 (p. 72)
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    // ** Answer to Exercise 7.2 **
    // 
    // By default, `this` is a `const` pointer to the non-`const` version of the class type.
    // So by default, we cannot bind `this` to a `const` object (§ 2.4.2, p. 62). 
    // So we cannot call an ordinary member function on a `const` object.
    // If `isbn()` were a normal function and `this` were an ordinary pointer, we would declare `this` thus:
    // `const Sales_data* const this` -- this shows that `this` is a `const` pointer to a Sales_data `const`.
    // But we're NOT allowed to declare `this`, so instead
    // the language allows you to put `const` after the parameter list. 
    // 
    // This is called a `const` member function.
    // It may read but not write to the data members of the object on which it is called.
    std::string isbn() const { return bookNo; }

    // ** Answer to Exercise 7.2, continued **
    // 
    // This is an interesting function, as it returns the `this` object.
    Sales_data_ch7& combine(const Sales_data_ch7 &other)
    {
        // When the user calls something like `total.combine(trans)`, the address of `total` is bound to the implicit
        // `this` parameter and `other` is bound to `trans`. That's how the next two lines work.
        units_sold += other.units_sold;
        revenue += other.revenue;

        // The interesting bit. We declared this funtion to return a reference.
        // This was a stylistic choice, and we did it because we wanted to mimic the `+=` operator, which returns its
        // left-hand operand as an l-value (§ 4.4, p. 144).
        // To return an lvalue, our combinefunction must return a reference(§ 6.3.2, p. 226).
        // However, `this` is a pointer, so we have to deference `this` in the `return` statement.
        return *this;
    }
    
    // Define a member function outside the class just to show how: first, define the stub inside the class.
    double avg_price() const;
};

// Define a member function outside the class just to show how: write the function body outside the class,
// but include NameOfClass:: in the definition.
double Sales_data_ch7::avg_price() const
{
    if (units_sold > 0)
        return revenue / units_sold;
    return 0;
}

// Exercise 7.3
// Revise your transaction - processing program from § 7.1.1 (p. 256) to use
// these members.
//
// Another one will do later, after the class is complete.

// Exercise 7.4
// Write a class named Person that represents the name and address of
// a person. Use a string to hold each of these elements. Subsequent exercises will
// incrementally add features to this class.
class Person_v7_4
{
public :
    string fName;
    string fAddress;
};

// Exercise 7.5
// Provide operations in your Person class to return the name and address.
// Should these functions be const? Explain your choice.
//
// Answer to second part: yes they should be const member functions,
// because they don't change the object.
class Person_v7_5
{
    // The members have been made private for reasons explained below.
private:
    string fName;
    string fAddress;

public:
    // IIRC, constructors haven't been covered yet, but I'm putting one in here 
    // for this convoluted chain of reasoning: 
    // - the question basically asks us to write getter functions.
    // - for getters to make sense, the members should be private.
    // - But if they're private, then we have to have a way to set them.
    // - A constructor saves the hassle of writing setters or overloading >>.
    Person_v7_5(string name, string address) : fName{ name }, fAddress{ address }
    {}

    string GetName() const
    {
        return fName;
    }

    string GetAddress() const
    {
        return fAddress;
    }
};
 

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.1.3, Defining non-member class-related functions
// p. 262
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.6
// Deﬁne your own versions of the add, read, and print functions.
Sales_data_ch7 add(const Sales_data_ch7& lhs, const Sales_data_ch7& rhs)
{
    Sales_data_ch7 sum = lhs;
    sum.combine(rhs);
    return sum;
}

void print(std::ostream& cout, const Sales_data_ch7 item)
{
    cout << "ISBN: " << item.isbn() << ", units_sold: " << item.units_sold << ", revenue: "
        << item.revenue << ", average price: " << item.avg_price();
}

// Unlike `print`, this function can't be void because we want to 
// say things like `if(read(blah))`, which only works if `read` returns an `istream`.
std::istream& read(std::istream& cin, Sales_data_ch7& item)
{
    std::cout << "Please input bookNo, units_sold, and price (separated by spaces): ";
    double price = 0.0;
    cin >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;

    return cin;
}

int ex_7_6()
{
    Sales_data_ch7 item;
    read(std::cin, item);
    print(std::cout, item);

    return 0;
}

// Exercise 7.7
// Rewrite the transaction-processing program you wrote for the
// Exercises in § 7.1.2 (p. 260) to use these new functions.
//
// ANSWER: we finally write this program!
int ex_7_7()
{
    Sales_data_ch7 total; // variable to hold data for the next transaction

    // read the first transaction and ensure that there are data to process
    if (read(std::cin, total))
    {
        Sales_data_ch7 trans; // variable to hold the running sum

        // read and process the remaining transactions
        while (read(std::cin, trans))
        {
            // if we're still processing the same book
            if (total.isbn() == trans.isbn())
                total.combine(trans); // update the running total
            else
            {
                // print results for the previous book
                print(std::cout, total);
                std::cout << std::endl;
                total = trans; // total now refers to the next book
            }
        }
        print(std::cout, total);
       std::cout << std::endl; // print the last transaction
    }
    else
    {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1; // indicate failure
    }
    return 0;
}

// Exercise 7.8
// Why does `read` deﬁne its Sales_data parameter as a plain reference
// and `print` deﬁne its parameter as a reference to const?
// 
// ANSWER: `read` needs to modify the parameter `item`, but `print` doesn't.

// Exercise 7.9
// Add operations to read and print Person objects to the code you wrote
// for the Exercises in § 7.1.2 (p. 260).
class Person_v7_9
{
private:
    string fName;
    string fAddress;

public:
    Person_v7_9(string name, string address) : fName{ name }, fAddress{ address }
    {}

    string GetName() const
    {
        return fName;
    }

    string GetAddress() const
    {
        return fAddress;
    }

    void print(std::ostream& cout) const
    {
        cout << this->fName << ", lives at: " << this->fAddress << std::endl;
    }

    void read(std::istream& cin)
    {
        std::cout << "Please enter name: ";
        std::getline(cin, this->fName);
        std::cout << "Please enter address: ";
        std::getline(cin, this->fAddress);
    }
};

int ex_7_9()
{
    std::cout << "Testing the Person print() functionality:" << std::endl;
    auto p = Person_v7_9("Masum", "65 Westview Drive");
    p.print(std::cout);

    std::cout << "And now to test the Person read() method: " << std::endl;
    p.read(std::cin);
    p.print(std::cout);

    return 0;
}

// Exercise 7.10
// What does the condition in the following if statement do ?
// if (read(read(cin, data1), data2))
//
// ANSWER: the inner `read` call reads `data1` and returns `cin`,
//      which is used to read `data2`. 
int ex_7_10()
{
    Sales_data_ch7 data1;
    Sales_data_ch7 data2;

    if (read(read(std::cin, data1), data2))
    {
        std::cout << "True!" << std::endl;

        print(std::cout, data1);
        std::cout << std::endl;
        print(std::cout, data2);
        return 0;
    }

    // Will never get here, unless something really bad happens.
    std::cout << "False!" << std::endl;
    return -1;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION, 7.1.4
// p. 266
// --------------------------------------------------------------------------------------------------------------------

// Exercise  7.11
// Add constructors to your Sales_data class and write a program to
// use each of the constructors.
struct Sales_data_ch7_v2 {
    // Default values.
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    // ANSWER TO 7.11: FOUR CONSTRUCTORS
    // Default
    Sales_data_ch7_v2() = default;

    // From string, using initialiser list
    // Takes ISBN as parameter; units_sold and revenue kept at default values above.
    Sales_data_ch7_v2(const string s) : bookNo{ s }
    {}

    // Initialise all three members, using initialiser list
    Sales_data_ch7_v2(const string s, const unsigned units_sold, const double price) :
        bookNo{ s },
        units_sold{ units_sold },
        revenue{ units_sold * price }
    {}

    // Initialise from istream, much like the old `read` function.
    // Except that we can't return cin from the constructor.
    Sales_data_ch7_v2(std::istream& cin)
    {
        std::cout << "Please input bookNo, units_sold, and price (separated by spaces), or 'null 0 0' to exit: ";
        double price = 0.0;
        cin >> this->bookNo >> this->units_sold >> price;
        this->revenue = price * this->units_sold;
    }

    // END ANSWERS TO 7.11: rest of class unchanged, apart from the very last method, ToString.
    string isbn() const { return bookNo; }

    Sales_data_ch7_v2& combine(const Sales_data_ch7_v2& other)
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

    // Not going to implement a `print` method like we did before.
    // Seems cleaner to define a ToString() method that lives in the class.
    // Can send the result to any ostream we want.
    string ToString() const
    {
        std::stringstream result;
        result << "ISBN: " << this->isbn() << ", units_sold: " << this->units_sold << ", revenue: "
            << this->revenue << ", average price: " << this->avg_price();
        return result.str();
    }
};

int ex_7_11()
{
    auto sd1 = Sales_data_ch7_v2();
    auto sd2 = Sales_data_ch7_v2("978-0-99-702549-1");
    auto sd3 = Sales_data_ch7_v2("978-2-12-345680-3", 10, 1.30);
    auto sd4 = Sales_data_ch7_v2(std::cin);
    
    std::cout << sd1.ToString() << std::endl;
    std::cout << sd2.ToString() << std::endl;
    std::cout << sd3.ToString() << std::endl;
    std::cout << sd4.ToString() << std::endl;

    return 0;
}

// Exercise  7.12 
// Move the deﬁnition of the Sales_data constructor that takes an
// istream into the body of the Sales_dataclass.
//
// ANSWER: already done.

// Exercise  7.13 
// Rewrite the program from page 255 to use the istream constructor.
int ex_7_13()
{
    // Read in first sales datum.
    Sales_data_ch7_v2 total(std::cin); 

    // If the first one is valid, then read in more. 
    if (total.isbn() != "null")
    {
        // read and process the remaining transactions
        while (true)
        {
            Sales_data_ch7_v2 trans(std::cin); // variable to hold the running sum
            
            // If user entered null, we break the loop and exit the program
            if (trans.isbn() == "null")
                break;

            // if we're still processing the same book
            if (total.isbn() == trans.isbn())
                total.combine(trans); // update the running total
            else
            {
                // print results for the previous book
                std::cout << total.ToString() << std::endl;
                total = trans; // total now refers to the next book
            }
        }
        std::cout << total.ToString() << std::endl; // print the last transaction
    }
    else
    {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1; // indicate failure
    }
    return 0;
}

// Exercise  7.14 
// Write a version of the default constructor that explicitly initializes the
// members to the values we have provided as in-class initializers.
//
// ANSWER: toy class below demonstrates.
class Ex_7_14
{
    // Members
    int a;
    int b;

    // Correct way to write default constructor
    // Ex_7_14() = default;

    // Old, long way to write it
    Ex_7_14()
    {
        this->a = 0;
        this->b = 0;
    }
};

// Exercise  7.15 
// Add appropriate constructors to your Person class.
//
// ANSWER: I already put them in.

int main()
{
    return ex_7_13();
}