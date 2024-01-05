// Chapter2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.1.2, Type conversions.
// p38.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.3.
// What output will the following code produce ?
int ex_2_3()
{
    unsigned u = 10, u2 = 42;
    std::cout << u2 - u << std::endl; // 42 - 10 = 32
    std::cout << u - u2 << std::endl; // 10 - 42 = -32, which then wraps around to MAX_INT - 32
    
    int i = 10, i2 = 42;
    std::cout << i2 - i << std::endl; // 32. Normal signed integer arithmetic within the limits
    std::cout << i - i2 << std::endl; // -32. Normal signed integer arithmetic within the limits
    
    std::cout << i - u << std::endl; // signed(1) - cast_to_signed(unsigned(10) = signed(10) - signed(10) = 0
    std::cout << u - i << std::endl; // unsigned(10) - cast_to_unsigned(10) = unsigned(10) - unsigned(10) = 0

    return 0;
}

// Exercise 2.4.
// Write a program to check whether your predictions were
// correct. If not, study this section until you understand what the problem is.
int ex_2_4()
{
    // All correct.
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.1.3, Literals.
// p41.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.5.
// Determine the type of each of the following literals.
// Explain the differences among the literals in each of the four examples :
int ex_2_5()
{
    // (a)
    'a';    // char
    L'a';   // wchar_t
    "a";    // is a string -- array of char
    L"a";   // is a wide character string -- array of wchar_t
    
    // (b)
    10;     // int
    10u;    // uint
    10L;    // long
    10uL;   // unsigned long
    012;    // int, octal literal
    0xC;    // int, hex literal

    // (c)
    3.14;   // double
    3.14f;  // float
    3.14L;  // long double

    // (d)
    10;     // int
    10u;    // unsigned int
    10.;    // double
    10e-2;  // double

    return 0;
}

// Exercise 2.6.
// What, if any, are the differences between the following
// definitions :
int ex_2_6()
{
    int month = 9, day = 7;     // These are normal ints in base 10
    // int month = 09, day = 07;   // These would have been int literals in base 8, but month is not valid. 
    return 0;
}

// Exercise 2.7.
// What values do these literals represent ? What type does each
// have ?
int ex_2_7()
{
    // (a) string of char with two octal escape sequences.
    // \145 in oct is equal to 101 in decimal, which is character 'e'.
    // \012 in oct is 10, which is the newline character.
    std::cout << "Who goes with F\145rgus?\012" << std::endl;
    
    // (b) long double, value 31.4
    std::cout << 3.14e1L << std::endl;
    
    // (c) Must be an error in the textbook:
    // does not complile unless amended to 1024.f
    // ... in which case it's a float
    // std::cout << 1024f << std::endl;

    // (d) long double
    std::cout << 3.14L << std::endl;

    return 0;
}

// Exercise 2.8.
// Using escape sequences, write a program to print 2M followed
// by a newline. Modify the program to print 2, then a tab, then an M, followed
// by a newline.
int ex_2_8()
{
    std::cout << "2M\n";
    std::cout << "2\tM\n";
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.2.1, Variable Definitions.
// p44.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.9: Explain the following definitions. For those that are illegal,
// explain what’s wrong and how to correct it.
int ex_2_9()
{
    // (a) Does not work: have to define first.
    // std::cin >> int input_value;
    int input_value;
    std::cin >> input_value;

    // (b) Does not compile: loss of data isn't allowed with list initialisation.
    // int i = { 3.14 };
    
    // (c) Does not work, wage not declared.
    // double salary = wage = 9999.99;
    double salary, wage;
    salary = wage = 9999.99;
    
    // (d) Compiles and runs, but truncates.
    int j = 3.14;

    return 0;
}

// Exercise 2.10: What are the initial values, if any, of each of the following variables?
// Assume that the entire body of the function is all standalone code and nothing is uncommented.
std::string global_str; // defined outside any function body: initialised to empty string.
int global_int;         // defined outside any function body: initialised to zero.
int ex_2_10()
{
    // General rules:
    // - Variables defined outside any function body are initialized to zero.
    // 
    // - With one exception, (covered later), variables of built - in type
    //    defined inside a function are uninitialized.
    // 
    // - Uninitialized objects of built-in type defined inside a function body have
    //    undefined value.
    // 
    // - Objects of class type that we do not explicitly initialize have
    //      a value that is defined by the class.


    // int main()
    {
        int local_int;      // Defined inside a function: unitialised.
        std::string local_str;  // Defined inside a function, but still iitialised to empty string.
                                // string is a class, whereas int is a primitive type.
    }
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.2.2, Varialbe Declarations and Definitions.
// p46.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.11: Explain whether each of the following is a declaration or a definition :
extern int ix = 1024;   // definition: assignment overrides the extern keyword.
int iy;                 // definition.
extern int iz;          // declaration.
int ex_2_11()
{
    // extern int ix_infunc = 1024; // Not allowed to assign to extern inside a function.
    int iy;                 // definition.
    extern int iz;          // declaration.

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.2.3, Identifiers.
// p47.
// --------------------------------------------------------------------------------------------------------------------

//Exercise 2.12: Which, if any, of the following names are invalid ?
int ex_2_12()
{
    // (a) Error: `double` is a keyword.
    // int double = 3.14;
    
    // (b) Allowed.
    int _;
    
    // (c) Error: `catch` is a keyword.
    // int catch - 22;
    
    // (d) Error: identifiers cannot start with a digit.
    // int 1_or_2 = 1;
    
    // (e) Allowed: `Double` is different to `double`, and the former is not a keyword.
    double Double = 3.14;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.2.4, Scope of a Name.
// p49.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.13: What is the value of j in the following program ?
// int i = 42;
// int main()
// {
//     int i = 100; int j = i;
// }
//
// Answer: 100. Local scope takes precedence.

// Exercise 2.14: Is the following program legal ? If so, what values are printed?
void ex_2_14()
{
    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
        sum += i;
    std::cout << i << std::endl;    // Prints 100. 
                                    // The `i` in the for loop has gone out of scope.
    std::cout << sum << std::endl;  // Printgs 45.
                                    // The `for` looped ignored the outer `i`. 
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.3.1, References.
// p51.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.15: Which of the following definitions, if any, are invalid? Why?
int ex_2_15()
{
    // (a)
    int ival = 1.01;    // Valid. 
    
#   // (b)
    // int& rval1 = 1.01;// Not valid. A reference cannot be bound to a literal.
    
    // (c)
    int& rval2 = ival;  // Valid.
    
    // (d)
    // int& rval3;      // Not valid: A reference has be bound when declared.

    return 0;
}


// Exercise 2.16: Which, if any, of the following assignments are invalid ? 
// If they are valid, explain what they do.
int ex_2_16()
{
    int i = 0, & r1 = i;
    double d = 0, & r2 = d;
    
    // (a)
    r2 = 3.14159;       // Valid, changes value of d to 3.14159. 
    
    // (b)
    r2 = r1;            // Valid, equivalent to d = i.
    
    // (c)
    i = r2;             // Valid, equivalent to i = d.
    
    // (d)
    r1 = d;             // Valid, equivalent to i = d.

    return 0;
}

// Exercise 2.17: What does the following code print ?
int ex_2_17()
{
    int i, & ri = i;
    i = 5;
    ri = 10; // Equivalent to i = 10.
    std::cout << i << " " << ri << std::endl; // `i` prints 10, as does `ri`.

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.3.2, Pointers.
// p56.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.18: Write code to change the value of a pointer.
// Write code to change the value to which the pointer points.
int ex_2_18()
{
    int rval1 = 4, rval2 = 5,  *p = &rval1;

    p = &rval2;  // Change the value of a pointer.
    rval2 = 6;   // Change the value to which a pointer points.
    return 0;
}

// Exercise 2.19 : Explain the key differences between pointers and references.
//
// Pointers can be declared without initialising. References need to be bound when declared.
// Pointers need to be dereferenced to get the value, references do not.
// You can't have a reference to a reference but you can have a pointer to a pointer.
// You can't have a pointer to a reference but you can have a reference to a pointer.

// Exercise 2.20 : What does the following program do ?
int ex_2_20()
{
    int i = 42;         // Declare an int.
    int* p1 = &i;       // Declare a pointer to an int that holds the value of i.
    *p1 = *p1 * *p1;    // The value of where pi points is changed to that value^2
                        // i now contains the value 42*42.

    std::cout << i << std::endl;
    return 0;
}

// Exercise 2.21: Explain each of the following definitions.
// Indicate whether any are illegal and, if so, why.
int ex_2_21()
{
    int i = 0;
    // (a)
    // double* dp = &i; // Not valid. A pointer to a double can't hold the address of an int.
    
    // (b)
    // int* ip = i;     // Not valid: a pointer to an int holds the address of an int, not an int itself.
    
    // (c)
    int* p = &i;        // Valid.

    return 0;
}

// Exercise 2.22: Assuming p is a pointer to int, explain the following code :
int ex_2_22()
{
    int i, * p = &i;
    if (p)  {}  // Do something if p is not a null pointer.
    if (*p) {}  // Do something if the value to which p points is not zero.

    return 0;
}

// Exercise 2.23 : Given a pointer p, can you determine whether p points to a
// valid object ? If so, how ? If not, why not?
//
// Answer: https://stackoverflow.com/questions/17202570/c-is-it-possible-to-determine-whether-a-pointer-points-to-a-valid-object/17202622#17202622

// Exercise 2.24 : Why is the initialization of p legal but that of lp illegal ?
int ex_2_24()
{
    int i = 42;
    void* p = &i;   // void* can hold the address of any data pointer type.
    // long* lp = &i;  // a long pointer cannot hold the address of an int.

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.3.3, Understanding Compound Type Declarations.
// p59.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.25: Determine the types and values of each of the following variables.
int ex_2_25()
{
    //(a)
    // int* ip, & r = ip;   // ip is a pointer to an int.
                            // r would be a reference to an int, not an int*, hence error.
    
    // (b)
    {
        int i, * ip = 0;    // i is an unitialised  int, ip is a null pointer (to an int).
                            // if this line was outside any function then i would've been 0.
        i = 1;              // Code added by me because otherwise the std::cout << i doesn't work.
                            // If this line is ommitted, i remains unitialised so cannot be used.
        std::cout << "(b)" << std::endl;
        std::cout << "i " << i << std::endl;
        std::cout << "ip " << ip << std::endl;
    }

    // (c)
    {
        int* ip, ip2;       // ip is an unitialised pointer to an int, ip2 is an unitialised int.
        ip2 = 0; ip = &ip2; // Code added by me for same reason as above.
        std::cout << "(c)" << std::endl;
        std::cout << "ip " << ip << std::endl;
        std::cout << "ip2 " << ip2 << std::endl;
    }

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.4, `const` Qualifier.
// p60.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.26: Which of the following are legal ? For those that are illegal,
// explain why.
int ex_2_26()
{
    // (a)
    // const int buf;   // not valid: a const must be given a value when declared.
    
    // (b)
    int cnt = 0;        // Obviously fine.

    // (c)
    const int sz = cnt; // Also fine: we can bind a reference to const to:
                        // - a non-const object,
                        // a literal, 
                        // or a more general expression that can be converted to the type of the reference.
    
    // (d)
    ++cnt;              // Fine: cnt is just a normal int.
    // ++sz;            // Not fine: sz is a const, so can't be changed after initialisation.

    // (bonus)
    const int& r2 = 42;
    // int& r4 = r2*2;  // This is not fine, even though it looks like int& r4 = 84.
                        // The LHS is a non-const reference, whereas the RHS is derived from a const.
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.4.2, Pointers and `const`.
// p64.
// --------------------------------------------------------------------------------------------------------------------

// General rules, taken from https://stackoverflow.com/questions/14779776/use-a-const-int-const-pointer-to-point-to-an-int
int ex_section_2_4_2()
{
    int const constVar = 42;  // this defines a top-level constant
    int variable = 11;

    int* const constPointer1 = &variable;

    // int* const constPointer2 = &constVar; // not allowed because you can change constant using it

    const int* const constPointer3 = &constVar; // perfectly ok. here you can't change constVar by any mean. it is a low level constant.

    const int* const constPointer4 = &variable; // also ok, because it says you can't change the value using this pointer, but you can change value like variable=15 .

    // *constPointer4 = 5; //you get error assignment of readonly location, because that pointer is constant and pointing to read only memory location.

    return 0;
}

// Exercise 2.27: Which of the following initializations are legal ? Explain why.
int ex_2_27()
{
    // (a)
    {
        // int i = -1, & r = 0; // Second part not valid: cannot assign literal values to non-const references.
    }

    // (b)
    {
        int i2 = 1;             // Added this line to allow the code to compile.
                                // Without this line, you just get the trivial error that i2 is not defined.
        int* const p2 = &i2;    // Valid after above line is added.
                                // p2 is const pointer to a non-const int.
        i2 = 4;                 // ... so this is valid ...
        *p2 = 3;                // ... and even this ...
        
        int i3 = 3;
        // p2 = &i3;            // ... but this isn't. p2 is holiding a memory address
                                // and that's the thing that can't change.
                                // The data that is in that memory address can be changed.
    }

    // (c)
    {
        const int i = -1, & r = 0;  // OK. Note that the `const` applies to the rest of the line, just like the `int`.

        // We can check that r is a const reference with the following experiment:
        const int j1 = 1, &r2 = j1; // Same structure as the code in this exercise.
        const int j2 = 2;
        // r2 = j2;                 // Does not compile.

        // Simpler check that const applies to rest of the line:
        const int k1 = 1, k2 = 2;
        // k2 = 3;                  // Does not compile, showing that k2 is a const.
    }

    // (d)
    {
        // const int i2 = 0;        // Adding this line will obviously allow the code to compile.
        int i2 = 0;                 // This works, too!
        const int* const p3 = &i2;  // Is fine, even if i2 is non-const.
                                    // See https://stackoverflow.com/questions/14779776/use-a-const-int-const-pointer-to-point-to-an-int
        // *p3 = 5;                 // This won't work, because p3 is a pointer to a const, ie., you can't change what's in p3 via *p3.
        i2 = 4;                     // But if otherwise allowed, you can change what's in p3 via other means.
    }

    // (e)
    {
        // const int i2 = 0;        // Adding this line will obviously allow the code to compile.
        int i2 = 0;                 // This works, too!
        const int* p1 = &i2;        // Same situation as (d).
    }

    // (f)
    {
        // const int& const r2;     // Not allowed: need to initialise r2.

        int i2 = 9;                 // Can be const or non-const.
        const int& const r2 = i2;
    }
    // (g) 
    {
        int i = 0;                  // Added to to define i. Can be const or non-const.
        const int i2 = i, & r = i;  // Both allowed, as per above.
    }

    return 0;
}

// Exercise 2.28: Explain the following definitions.Identify any that are illegal.
int ex_2_28()
{
    // (a)
    // int i, * const cp;           // Not valid: const pointer is not initialised.
    
    // (b)
    // int* p1, * const p2;         // Not valid: const pointer is not initialised.
    
    // (c)
    // const int ic, & r = ic;      // Not valid: const int is not initialised.
    
    // (d)
    // const int* const p3;         // Not valid: const pointer is not initialised.
    
    // (e)
    const int* p;                   // Fine.
    return 0;
}

// Exercise 2.29: Uing the variables in the previous exercise, which of the
// following assignments are legal ? Explain why.
int ex_2_29()
{
    // Note: added these definitions to get useful compiler errors (as opposed to "variable not defined".
    int i = 0;
    const int ic = 9;
    int* p1 = &i;
    int* const p2 = &i;
    const int* const p3 = &i;

    // (a)
    i = ic;         // Fine. ic is copied by value into i. i can be changed, but ic will not change.

    // (b)
    // p1 = p3;     // Not fine:    p3 is a (const) pointer to a const int
                    //              p1 is pointer to an int.
                    // A pointer to a non-const int cannot be assigned a pointer to a const int.
                    // Compiler error: a value of type const int* cannot be assigned to an entity of type int*.
    
    // (c)
    // p1 = &ic;    //  Not fine:   &ic is a pointer to a const int
                    //              p1 is a pointer to an int. Same situation as the last one.
                    // Same compiler error.
                    
    
    // (d)
    // p3 = &ic;   //  Not fine:  p3 is a const pointer (to a const int). A const cannot be reassigned.
                    // Compiler error: expression must be a modifiable value.
    
    // (e)
    // p2 = p1;    //  Not fine:   p2 is a const pointer (to a non-const int). A const cannot be reassigned.
                    // Same compiler error.

    // (f)
    // ic = *p3;    //  Not fine:   ic is a const. A const cannot be reassigned.
                    // Same compiler error.
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.4.3, Top-level `const`.
// p65.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.30: For each of the following declarations indicate whether the
// object being declared has top - level or low - level const.
int ex_2_30()
{
    const int v2 = 0; int v1 = v2;  // v2: top-level. An object itself is const.
    // Hence, can be ignored when copying to v1.

    int* p1 = &v1, & r1 = v1;       // Nothing is const!

    int i = 0; // Added to compile the line below.
    const int* p2 = &v2, * const p3 = &i, & r2 = v2;
    // p2 is low-level const.
    // - The pointer itself is not const, but rather the object to which it pointing.
    // 
    // p3 is both top- and low-level const.
    // 
    // r2 is a low-level const.
    // - References do not have top-level const-ness,
    // - since they are not objects.
    // - Rather, the object to r2 is referring is const. Hence, low-level.

// Handy table, from https://grant6899.github.io/2018/01/07/Top-level-const-and-Low-level-const/
    {
        int i = 0;
        int* const p1 = &i;         // p1 has top-level const, &i has no const
        const int ci = 42;          // we cannot change ci; const is top-level const
        const int* p2 = &ci;        // p2 has low-level const, &ci has low-level const
        const int* const p3 = p2;   // right-most const is top-level, left-most is low-level
        const int& rc = ci;         // const in reference types is always low-level
    }

    return 0;
}

// Exercise 2.31: Given the declarations in the previous exercise
// determine whether the following assignments are legal.
// Explain how the top - level or low-level const applies in each case.
int ex_2_31()
{
    /* Variable     Type                Top-level const     Low-level const
    i	         int	             non-const  	     N / A
    ci	         int	             const	             N / A
    p	         int*                non-const	         non-const
    p1	         int* const          const	             non-const
    p2	         const int*          non-const	         const
    p3	         const int* const    const	             const
    r	         int&                N / A	             non-const
    rc	         const int&          N / A	             const
    */

    // When we copy an object, both objects must have either:
    //      the same low-level const qualification, OR
    //      LHS has more strict constness than RHS
    //          (In other words, there must be a conversion between the types of the two objects.
    //          In general, we can convert a nonconst to const but not the other way round).
    //  
    // Another way to say the same thing:
    //      The assignment can add but not lose the low-level `const` qualifier.
    //      The assignment will ignore top-level `const` qualifier.

    const int v2 = 0; int v1 = v2;  
    int* p1 = &v1, & r1 = v1;  
    int i = 0; // Added to compile the line below.
    const int* p2 = &v2, * const p3 = &i, & r2 = v2;
    
    r1 = v2;        // r1 is not const. v2 is top-level const, so it is ignored and we can copy. 
    
    // p1 = p2;     // p1 is not const. p2 is low-level const. LHS is less const-strict than RHS. We cannot copy.
                    // Compiler error: a value of type const int* cannot be assigned to an entity of type int*.
    
    p2 = p1;        // p2 is low-level const. p1 is not const. LHS is more const-strict than RHS. We can copy.
    
    // p1 = p3;     // p1 is not const. p3 is both top- and low-level const. LHS is less const-strict than RHS. 
                    // We cannot copy.
                    // Compiler error: a value of type const int* cannot be assigned to an entity of type int*.
    
    p2 = p3;        // p2 is low-level const. p3 is both top- and low-level const. Ignore top-level const-ness.
                    // Then we have same const-strictness on both sides, so we can copy.

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.4.4, `constexpr` and Constant Expressions.
// p67.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.32: Is the following code legal or not? If not, how might you make it legal ?
int intThatRemainsAtAFixedAddress = 1;
int ex_2_32()
{
    // int null = 0, * p = null;    // Not OK.
                                    // null is an int.
                                    // p is an int*: pointer to an int.
                                    // You can't assign an int to an int*.
                                    // Compiler error: a value of type int cannot be assigned to an entity of type int*.
    
    int null = 0, * p = &null;      // Now OK, but I don't think this is what the code is trying to get at.

    // I think we're trying to define p as a null pointer. These are the two obvious ways.
    { int* p = nullptr; }
    { int* p = NULL; }

    // Also this section is about constexpr, so not that we can initialize a constexpr pointer from the nullptr literal ... 
    { constexpr int* p = nullptr; }
    { constexpr int* p = NULL; }

    // ... or the literal (i.e., constant expression) 0, so this works:
    { constexpr int* p = 0; }

    // But not this:
    {
        constexpr int i = 0;
        // constexpr int* p = i;
    }

    // Finally, We can also point to (or bind to) an object that remains at a fixed address.
    // objectThatRemainsAtAFixedAddress has a fixed address because it is outside any function.
    constexpr int* p_to_fixed_address = &intThatRemainsAtAFixedAddress;

    // As a counterexample, we define an int in this function. It's inside function so has no fixed address.
    // Compiler error: A pointer or reference to variable <...> cannot be used as a constant.
    int intThatHasNoFixedAddress = 2;
    // constexpr int* p_to_local_int = &intThatHasNoFixedAddress; 

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.5.2, The `auto` Type Specifier.
// p70.
// --------------------------------------------------------------------------------------------------------------------

// Understanding typedef and const
int code_examples_2_5_1()
{
    typedef char* pstring;  // pstring is an alias for "pointer to char".
    const pstring cstr = 0; // cstr is a const "pointer to char". It is obvious when you put it like this.
    
    const pstring* ps;      // ps is a pointer to 'const pstring', ie., a pointer to a 'const "pointer to char"'. 

    // The following is a WRONG way to think about it, that will give you the WRONG type:
    // const <pstring> cstr -> const <char *> cstr ... this is a pointer to a const char, which is wrong.
    // *** TYPEDEFS ARE NOT MACROS ***  

    return 0;
}

// The `auto` type specifier. It's basically like `var` in C#.
int code_examples_2_5_2()
{
    // Introduction to auto
    {
        int i = 0, & r = i; // i is an int, r is an alias for i. 

        // Changing r will change i.
        r = 2;
        std::cout << "After setting `r=2`, i is now " << i << std::endl;

        // Now introduce an auto.
        auto a = r; // a is an int, NOT a reference to an int.

        // Changing a will not change r or i.
        a = 3;
        std::cout << "After setting `a=3`, r and i are still " << r << " and " << i << std::endl;

        // Aside: you can have a ref to a ref; what you get is effectively just a ref to the original underlying.
        // As the book puts it: "when we use a reference as an initializer, the initializer is the corresponding object".
        int& r2 = r;
        r2 = 4;
        std::cout << "After setting `r2=4`, r and i are now " << r << " and " << i << std::endl;
    }

    // Understanding const and auto.
    {
        int i = 0;
        const int ci = i;       // ci is a top-level const. 
        const int & cr = ci;    // cr is a low-level const. Can't be top-level const because it's not really an object.
        
        auto b = ci;            // ci is a (top-level) const int. So it's like we're saying
                                // 
                                // `const int b = ci` ...
                                // 
                                // ... but auto ignores top-level const-ness. So we end up with:
                                // 
                                // int b = ci;
        b = 4;                  // And indeed, we can change the value of b.
                                
        auto c = cr;            // "When we use a reference as an initializer, the initializer is the corresponding object".
                                // The "corresponding object" that cr is referencing, is ci.
                                // We repeat the logic above, to come to the same conclusion.
        c = 4;                  // And again, we can change the value of c.
                                
        auto d = &i;            // i is a non-const int. &i is a pointer to a non-const int.
                                //
                                // We don't have to worry about const-ness, so d is just int*.
                                //
                                // int * d = &i;
                                
        auto e = &ci;           // ci is a const int. &ci is a pointer to a const-int.
                                // 
                                // This is low-level const-ness. Low level const is respected.
                                // Hence e is a (non-const) pointer to a const int.
                                //  
                                // const int * e = &ci;
                                
        const auto f = ci;      // ci: const int -- it's a top-level const-ness, which we ignore.
                                // So it's like initialising f with an int. That is, auto is deduced to be int.
                                // 
                                // const int f = ci;
        // f = 4;               // Won't work.

        auto& g = ci;           // ci: const int. Top level const-ness, which we ignore.
                                // Initialising g with an int.
                                // But note, it's a reference. So auto deduced as reference to int.
                                // 
                                // int& g = ci;

        // auto& h = 42;        // Can't bind reference to a literal.

        const auto& j = 42;     // But we CAN bind a const reference to a literal.

        auto k = ci, & l = i;   // Is good, because we can say:
                                // 
                                // int k = ci, &l = i

        // In the examples below, we have `auto&`, not `auto`.
        // The rule about top-level const-ness being ignored doesn't apply for `auto&`, so don't try to use it!
        auto& m = ci, * p = &ci;    // ci is a const int. So m is a reference to a const int.
                                    //
                                    // const int& m = ci
                                    //
                                    // Thus auto is deduced to be const int.
                                    // Moving on, &ci is a pointer to a const int.
                                    // Can we have the following, using the just-deduced auto?
                                    //
                                    // const int * p = &ci
                                    //
                                    // Yes we can! So this is a good line of code.

        // auto& n = i, * p2 = &ci; // Can't deduce auto:
                                    // int& n = i, *p2 = &ci; ... if it worked, would have to be the same as:
                                    // 
                                    // int& n = i;      <-- auto is deduced to be int.     
                                    // int * p2 = &ci;  <-- And this is the line that fails. 
                                    //                      &ci is a pointer to a const int.
    }

    return 0;
}


// Exercise 2.33: Using the variable definitions from this section, determine what happens in each of these assignments:
int ex_2_33() {
    int i = 0, &r = i;
    const int ci = i;
    const int& cr = ci;

    auto a = r;
    auto b = ci;
    auto c = cr;
    auto d = &i;
    auto e = &ci;
    const auto f = ci;
    auto& g = ci;

    // Answers
    a = 42;     // Legal:- a (and r) get changed to 42.
    b = 42;     // Legal:- b is an int, not a const int (top-level const in definition of ci is ignored).
    c = 42;     // Legal:- c is an int. cr is a reference to a const int.
                //       - Initialising with a reference is the same as initialising with the underlying.
                //       - Initialising an int with a const int copies the value but not the const-ness.
    // d = 42;  // Won't work: d is a pointer to an int, whereas 42 is an int.
    // e = 42;  // Won't work for the same reason.
    // g = 42;  // Won't work: g is a reference to a const int, so you can't change its (ie, ci's) value.

    return 0;
}

// Exercise 2.35: Determine the types deduced in each of the following
// definitions.Once you’ve figured out the types, write a program to see
// whether you were correct.
int ex_2_35()
{
    const int i = 42;           // i is const int.
    auto j = i;                 // j is a (non-const) int. Top-level const-ness of i is ignored.
    const auto& k = i;          // From `auto&`, we know that k is a reference.
                                // From `i`, we know that k is a reference to an int. So the line is deduced to be:
                                // 
                                // const int& k = i;
    // k = 3;                   // Check: and indeed this does not compile.

    auto* p = &i;               // &i is a pointer to a const int -- ie., const int*.
                                // Thus, auto deduced to be const int.
                                // 
                                // const int* p = &i

    const auto j2 = i, & k2 = i;// k2 is a reference to whatever type i is (ie., int).
                                // auto must be int. So we have:
                                //  
                                // const int j2 = i, & k2 = i;
                                // 
                                // The const and int both "distribute" over all the definitions on the line, giving ...
                                // 
                                // const int j2 = i; const int & k2 = i;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.5.2, The `decltype` Type Specifier.
// p72.
// --------------------------------------------------------------------------------------------------------------------

// I think I will skip these for now because StackOverflow says it's an advanced topic.
// I will come back to it when I do templates.


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.6.1, Defining the `Sales_data` Type.
// p74.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.39: Compile the following program to see what happens when
// you forget the semicolon after a class definition.Remember the message for future reference.
struct Foo { /* empty */ }; // If the semi-colon is omitted, you get two compiler errors:
                            // Foo followed by `int` is illegal (did you forget a `;`?)
                            // `return`: cannot convert from `int` to `Foo`. 

// Exercise 2.40: Write your own version of the Sales_data class.
// No answer: not sure what is expected here, as Sales_data is just a struct.
//
// Here's the code for Sales_data, from p73.
struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
}; // <--------------------------- Do not forget the semicolon after the closing curly of a struct or class!


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.6.2, Using the `Sales_data` Class.
// p76.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 2.41: Use your Sales_data class to rewrite the exercises in §
// 1.5.1 (p. 22), § 1.5.2 (p. 24), and § 1.6 (p. 25). For now, you should define
// your Sales_data class in the same file as your main function.

// Section 1.5.1, Exercise 1.21.
// Write a program that reads two Sales_item objects that have the same ISBN and produces their sum.
int ex_2_41_121()
{
    /// Code to read data1 and data2. Triple /// means a comment given in the book, on p114.
    Sales_data data1, data2;
    std::string bookNo = "";
    unsigned int units_sold = 0;
    double revenue = 0.0;

    std::cin >> bookNo >> units_sold;
    data1.bookNo = bookNo;
    data1.units_sold = units_sold;
    data1.revenue = revenue;

    // We should factor this out into a function, but the book hasn't covered how to return 
    // a Sales_data object from a function, so we'll just write it twice.
    std::cin >> bookNo >> units_sold;   
    data2.bookNo = bookNo;
    data2.units_sold = units_sold;
    data2.revenue = revenue;

    /// Code to check whether data1 and data2 have the same ISBN
    /// ... and if so, print the sum of data1 and data2.
    if (data1.bookNo == data2.bookNo)
        std::cout   << data1.bookNo << " " 
                    << data1.units_sold + data2.units_sold << " "
                    << data1.revenue + data2.revenue << std::endl;
    else
    {
        std::cerr << "The two Sales_data items must have the same ISBN.";
        return -1;
    }

    return 0;
}

// Section 1.5.1, Exercise 1.22.
// Write a program that reads several transactions for the same ISBN.
// Write the sum of all the transactions that were read.
//
// I won't be doing the rest of these, as it seems rather pointless.
int ex_2_41_122()
{
    return 0;
}

int ex_2_41_152()
{
    return 0;
}

int ex_2_41_16()
{
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 2.6.3, Writing our own header files.
// p77.
// --------------------------------------------------------------------------------------------------------------------

// Not going to do this exercise, as it is a simplified version of what happens in real life.
// The section in the book says to put the entire class in the header file, but this is not usually done.
// Usually, most classes are split between a header file and one or more class files.

int temp()
{

    return 0;
}


int main()
{
    return ex_2_41_122();
};
