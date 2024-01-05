// Chapter7_Section3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Screen_v7_27.h"
#include "Screen_v7_32.h"

using std::string;

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.3.1
// p. 275
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.23: Write your own version of the Screen class.
// Exercise 7.24 : Give your Screen class three constructors : a default constructor; a constructor
// that takes values for height and width and initializes the contents to hold the
// given number of blanks; and a constructor that takes values for height, width, and a
// character to use as the contents of the screen.
//
// ANSWER to exercise 7.23 below; answer to exercise 7.24 is inside it.
class Screen_v7_23
{
public:
    // We could use int or some other integral data type here, but 
    // It is a type that is big enough to represent the size of a string, no matter how big that string is.
    // 
    // Remember, can also accomplish the below using:
    // using pos = string::size_type;
    //
    // Second note: I like to put private members before public ones, and usually, it doesn't matter:
    // usually, you can use an ordinary member before it appears in the class.
    // However, typedefs MUST appear before they are used, so they usually appear at the top of the class.
    typedef string::size_type pos;

private:
    pos fCursor = 0; // [1] in-class initialiser for fCursor: see below.
    pos fHeight = 0, fWidth = 0;
    string fContents;

public:
    // ANSWER to exercise 7.24: the three constructors.
    Screen_v7_23() = default;
    Screen_v7_23(pos ht, pos wd) :
        fHeight{ ht },
        fWidth{ wd }
    {
        fContents = string(ht * wd, ' ');
    }

    Screen_v7_23(pos ht, pos wd, char c):
        fHeight{ht},
        fWidth{wd},
        // contents{ ht * wd, c }   // invalid narrowing conversion from `unsigned long long` to `char`:
                                    // it looks like we're trying to use the string(const char*, size_t) constructor
        fContents( ht * wd, c )
    {
        // Comment about the initialisation syntax: As usual, we prefer to use list initialisation
        // -- ie, height{ht}  with curly brackets -- but we were not allowed to use it for `contents{ht * wd, c}`
        // because list initialisation doesn't allow narrowing.
        //
        // Always prefer list initialisation when it is allowed.
        //
        // Also note that fCursor isn't in the initialisation list: it impolictly uses the in-class initialiser [1].
    }

    char get() const
    {
        return fContents[fCursor];          // [2] implicitly inline, as the body is given inside the class.
    }

    inline char get(pos ht, pos wd) const;  // [3] explicitly inline.
    Screen_v7_23 &move(pos r, pos c);       // [4] can be made inline later.
};

// dummy function to show inlinification [4]
inline Screen_v7_23& Screen_v7_23::move(pos r, pos c)
{
    Screen_v7_23 s = Screen_v7_23();
    return s;
}

int ex_7_23()
{
    // We'll just check we can use the constructors; won't check internals.
    auto s1 = Screen_v7_23();
    auto s2 = Screen_v7_23(12, 10);
    auto s3 = Screen_v7_23(12, 10, 'c');

    return 0;
}

// Exercise 7.25: Can Screen safely rely on the default versions of copy and assignment ?
// If so, why ? If not, why not?
// 
// ANSWER
// Yes, it can. None of the members are naked pointers and all its data members have copy/assignment
// constructors.

// Exercise 7.26 : Deﬁne Sales_data::avg_priceas an inline function.
//
// ANSWER
// Can't be bothered to copy and paste the whole class. General rules: 
// - [2] (see above) If you define the method inside the class, it's inline.
// - [3] If you declare it inside the class but define it outside, you can make it inline by declaring it as inline.
// - [4] If you don't declare it inline inside the class, you can specify `inline` when you define it outside.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.3.2, Functions that return `*this`
// p. 278
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.27: Add the move, set, and display operations to your version of Screen.
// Test your class by executing the code at [test code] below.
int ex_7_27()
{
    // [test code]
    Screen_v7_27 myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";

    return 0;
}

// Exercise 7.28: What would happen in the previous exercise if the return type of move,
// set, and displaywas Screen rather than Screen& ?
//
// ANSWER
// Then `.move()` and `.set()` would return copies of myScreen, and the second `display()` call would be all X's 
// (ie., unchanged).

// Exercise 7.29 : Revise your Screen class so that move, set, and display functions
// return Screen and check your prediction from the previous exercise.
// 
// ANSWER
// Confirmed (and the class reverted to the more functional version in ex 7.23).

// Exercise 7.30 : It is legal but redundant to refer to members through the this pointer.
// Discuss the pros and cons of explicitly using the thispointer to access members.
//
// ANSWER:
// Con: makes the class more difficult to read in terms of clutter.
// Pro: function definitions easier to read, as you can easily distinguish between local variables vs class members.
//      Workaround: adopt a style that distinguishes class members. For example, fBlah and _blah are both common.


// ---------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.3.3, Class Types
// p. 279
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.31: Deﬁne a pair of classes X and Y, in which X has a pointer to Y, and Y has
// an object of type X.
class Y; // forward declaration.
class X { Y* yp; };
class Y { X x; }; // definition.
int ex_7_31() { X(); Y(); return 0; } // Dummy function to check this compiles and runs.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 7.3.4, Friendship Revisited
// p. 282
// --------------------------------------------------------------------------------------------------------------------

// Exercise 7.32: Deﬁne your own versions of `Screen` and `Window_mgr` in which
// `clear` is a member of `Window_mgr` and a friend of `Screen`.
//
// ANSWER
// See the class defined in Screen_v7_32.h.
// I think the required order of declarations and definitions given in the book on p 281
// omits the forward declaration of Screen at the beginning of the list.
//
// Below is a small function to check that everything behaves as expected.
int ex_7_32()
{
    ToyWindowManager wm = ToyWindowManager();
    std::cout << wm.fScreenPtr->ToString() << std::endl; // Check wm has a screen with contents of 100.

    wm.clear(); // This only works because of the friend declaration.
    std::cout << wm.fScreenPtr->ToString() << std::endl; // Check wm has a screen with contents of 0.

    return 0;
}

int main()
{
    ex_7_32();
}