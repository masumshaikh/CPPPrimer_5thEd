// Chapter7_Section4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Sales_data_ch7_v4.h"

using std::string;

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.4, Class Scope
// p. 283
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.33: What would happen if we gave Screen a size member deﬁned as
// follows (in line [1])? Fix any problems you identify.
//
// ANSWER
// A much cut-down version of the screen class is given below
// and the mistake in line [1] corrected underneath it. 
class Screen_v7_33
{
    typedef int pos;
    pos size() const;
    pos height, width;
};

// pos ToyScreen::size() const //               [1]
Screen_v7_33::pos Screen_v7_33::size() const
{
    return height * width;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.4.1, Name lookup and class scope
// p. 287
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.34: What would happen if we put the typedef of `pos` in the `Screen` class
// on page 285 as the last line in the class ?

// ANSWER
// There would be an error,
// because `pos` would not yet have been seen in the other two lines for `setHeight()` and `height`.
class Screen_v7_34
{
public:
    typedef std::string::size_type pos;
    void setHeight(pos); // when the line above is moved to the end of the class, pos is unknown here.
    pos height = 0;
};

Screen_v7_34::pos verify(Screen_v7_34::pos var) { return var; } // Dummy body added for compilation.

void Screen_v7_34::setHeight(pos var) {
    // var: refers to the parameter
    // height: refers to the class member
    // verify: refers to the global function
    height = verify(var);
}

// Exercise 7.35 : Explain the following code, indicating which deﬁnition of Type or
// initValis used for each use of those names. Say how you would ﬁx any errors.
typedef string Type;                            // global scope
Type initVal() { return "init"; }               // global scope  

class Exercise
{
public:
    typedef double Type;                        // class scope
    Type setVal(Type);                          // class scope [2]
    Type initVal() { return 0; }                // class scope

private:
    int val;
};

// In line [3] below, the first `Type` is the global one.
// But in line [2], `setVal(...)` is declared as taking the class-scope Type as a parameter.
// So the compiler thinks that we are trying to redeclare `setVal()` here. Hence the error:
// "member function Exercise::setVal may not be redeclared outside its class".
//
// Type Exercise::setVal(Type param)            // [3]
//
// The corrected version is below. The first `Type` needs to be scoped properly.
// But by the time we get to the second `Type`, the scope `Exercise::` has been seen, so it is correctly scoped.
// 
// Of course, it would be better to be explicit and write:
// Exercise::Type Exercise::setVal(Exercise::Type parm)
// 
// And the best thing, of course, is to just not have names that hide each other like this.
Exercise::Type Exercise::setVal(Type parm)
{
    val = parm + initVal();
    return val;
}

// To prove that the second Type is a double (the class scope version) and not a string (the global scope)
int ex_7_35()
{
    auto ex = Exercise();

    ex.setVal(0.0);         // this works.
    // ex.setVal("set");    // this doesn't: Exercise::setVal(...) will only accept `double` values
                            // (ie., it only takes Exercise::Type and not global::Type values).
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.5.1, Constructor Initialiser List
// p. 291
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.36: The following initializer is in error. Identify and ﬁx the problem.
//
// ANSWER
// The error is this: `rem` is declared before `base` in line [4], so it is initialised first
// ** even though it is the second item in the constructor initialiser list **.
// This is undefined behaviour, because `base` hasn't been initialised yet.
struct X_7_36 {
    X_7_36(int i, int j) : base(i), rem(base% j) { }
    int rem, base;                                          // [4]
};

// Test the above:
int ex_7_36()
{
    auto x = X_7_36(1, 2);
    std::cout << x.rem  // This may NOT print 1 % 2 = 0, because `base` may not yet been set to 1,
                        // (depending on the compiler).
        << x.base       // This will print 2, but it was initialised too late to be used to initialise `rem`.
        << std::endl;

    return 0;
}

// Exercise 7.37: Using the version of Sales_data from this section, determine which
// constructor is used to initialize each of the following variables and list the values of the
// data members in each object.
class Sales_data_v7_37 {
private:
    string bookNo;
    unsigned units_sold;
    double revenue;

    // definition added to allow compilation and run.
    void read(std::istream& is, Sales_data_v7_37 sd)
    {
        std::cout << "(7.37) Please input bookNo, units_sold, and price (separated by spaces), or 'null 0 0' to exit: ";
        double price = 0.0;
        is >> sd.bookNo >> sd.units_sold >> price;
        sd.revenue = price * sd.units_sold;
    }

public:
    // deﬁnes the default constructor as well as one that takes a string argument
    Sales_data_v7_37(std::string s = "") : bookNo(s) { }

    // remaining constructors unchanged
    Sales_data_v7_37(std::string s, unsigned cnt, double rev) :
        bookNo(s), units_sold(cnt), revenue(rev* cnt) { }

    Sales_data_v7_37(std::istream& is) { read(is, *this); }
    // remaining members as before
};

// Sales_data_v7_37 first_item(std::cin);       // third constructor used.
int ex_7_37()
{
    Sales_data_v7_37 next;                      // first constructor used with default argument empty string,
    Sales_data_v7_37 last("9-999-99999-9");     // first constructor used.
    return 0;
}

// Exercise 7.38: We might want to supply cin as a default argument to the constructor
// that takes an istream &. Write the constructor declaration that uses cin as a default
// argument.
//
// ANSWER
// Sales_data_v7_37(std::istream& is = std::cin) { read(is, *this); }
//
// But we can't put this in the class, because it clashes with the first constructor: 
// see next question.

// Exercise 7.39 : Would it be legal for both the constructor that takes a string and the
// one that takes an istream& to have default arguments ? If not, why not?
//
// ANSWER
// No, because then `Sales_data_v7_37()` would be ambiguous.

// Exercise 7.40 : Choose one of the following abstractions (or an abstraction of your
//     own choosing). Determine what data are needed in the class. Provide an appropriate
//     set of constructors. Explain your decisions.
//     (a) Book (b) Date (c) Employee
//     (d) Vehicle (e) Object (f) Tree
//
// ANSWER
// Not going to do it. This question is too vague.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.5.2, Delegating Constructors
// p. 292
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.41: Rewrite your own version of the Sales_data class to use delegating
// constructors. Add a statement to the body of each of the constructors that prints a
// message whenever it is executed. Write declarations to construct a Sales_data object
// in every way possible. Study the output until you are certain you understand the order
// of execution among delegating constructors.
//
// The class is in Sales_data_ch7_v4.h. Test harness below.
int ex_7_41()
{
    auto s2 = Sales_data_ch7_v4("X101231222", 1, 9.71);
    std::cout << "First constructor ... " << s2.ToString() << std::endl << std::endl;
    
    s2 = Sales_data_ch7_v4();
    std::cout << "Default constructor ... " << s2.ToString() << std::endl << std::endl;

    s2 = Sales_data_ch7_v4("StringOnly");
    std::cout << "String only constructor  ... " << s2.ToString() << std::endl << std::endl;

    return 0;
}

// Exercise 7.42 : For the class you wrote for exercise 7.40 in § 7.5.1 (p. 291), decide
// whether any of the constructors might use delegation.If so, write the delegating con -
// structor(s) for your class.If not, look at the list of abstractions and choose one that you
// think would use a delegating constructor.Write the class deﬁnition for that abstraction.
//
// ANSWER
// Didn't do 7.40, so can't do this.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.5.3, The Role of the Default Constructor
// p. 294
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.43: Assume we have a class named NoDefault that has a constructor that
// takes an int, but has no default constructor. Deﬁne a class C that has a member of
// type NoDefault. Deﬁne the default constructor for C.
class NoDefault
{
private:
    int fInt;
public:
    NoDefault(int i) { fInt = i; }

    // ToString() added just for debugging.
    string ToString()
    {
        std::stringstream sb;
        sb << fInt;
        return sb.str();
    }
};

class C
{
    NoDefault fNoDef;

public:
    // Note that this attempt doesn't work; it fails with error, "No default constructor for NoDefault".
    // C() default-initialises all its members before getting to the body of the initialiser.
    // But it can't default initialise `fNoDef` because the `NoDefault` class doesn't have a default constructor.
    // This is the first attempt:
    // 
    // C() { fNoDef = NoDefault{ 0 }; }

    // The next line does work.
    C() : fNoDef{ 0 } // Both fNoDef{0} and fNoDef(0) with round brackets work.
    {}

    // ToString() added just for debugging.
    string ToString()
    {
        std::stringstream sb;
        sb << fNoDef.ToString();
        return sb.str();
    }
};

int ex_7_43()
{
    C c;
    std::cout << c.ToString() << std::endl;
    return 0;
}

// Exercise 7.44: Is the following declaration legal? If not, why not?
int ex_7_44()
{
    // std::vector<NoDefault> vec(10); // Error: NoDefault has no appropriate default constructor available.
    return 0;
}

// Exercise 7.45: What if we deﬁned the vector in the previous execercise to hold objects of type C?
int ex_7_45()
{
    std::vector<C> vec(10); // Is fine.
    return 0;
}

// Exercise 7.46: Which, if any, of the following statements are untrue? Why?
// (a) A class must provide at least one constructor.
// 
// Not true. If no constructors are given, then the compiler will generate a default constructor.
// 
// (b) A default constructor is a constructor with an empty parameter list.
// 
// Usually but not necessarily.
// A default constructor is also defined if a constructor is provided for which all parameters have default values.
// 
// (c) If there are no meaningful default values for a class, the class should not provide a default constructor.
// 
// Not true. I think. I'm not sure, but I'm going off the tip in the book that:
// "In practice, it is almost always right to provide a default constructor if other constructors are being deﬁned."
// 
// (d) If a class does not deﬁne a default constructor, the compiler generates one that
// initializes each data member to the default value of its associated type.
// 
// True, if all data members that are not of an inbuilt type are of types that have a default constructor.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.5.4, Implicit Class-Type Conversions
// p. 
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.47: Explain whether the Sales_data constructor that takes a string
// should be explicit. What are the beneﬁts of making the constructor explicit?
// What are the drawbacks?
// 
// ANSWER
// Converting constructors should only be made explicit if there is one unambiguous way that it can be converted.

// Exercise 7.48: Assuming the Sales_data constructors are not explicit, what operations
// happen during the following deﬁnitions
int ex_7_48()
{
     string null_isbn("9-999-99999-9");             
     Sales_data_ch7_v4 item1(null_isbn);
     Sales_data_ch7_v4 item2("9-999-99999-9");

     return 0;
}
// What happens if the Sales_data constructors are explicit?

// Exercise 7.49: For each of the three following declarations of combine, explain what
// happens if we call i.combine(s), where iis a Sales_dataand sis a string:
// (a) Sales_data &combine(Sales_data);
// (b) Sales_data &combine(Sales_data&);
// (c) Sales_data &combine(const Sales_data&) const;

// Exercise 7.50: Determine whether any of your Person class constructors should be
// explicit.

// Exercise 7.51: Why do you think vectordeﬁnes its single-argument constructor as
// explicit, but stringdoes not?

int main()
{
    ex_7_43();
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 
// p. 
// --------------------------------------------------------------------------------------------------------------------
