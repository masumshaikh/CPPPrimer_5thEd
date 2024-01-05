// Chapter7_Section4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

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

Screen_v7_34::pos verify(Screen_v7_34::pos);

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

int main()
{
    ex_7_35();
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 
// p. 
// --------------------------------------------------------------------------------------------------------------------
