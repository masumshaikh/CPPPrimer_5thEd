// Chapter4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// iostream
using std::cin;
using std::cout;
using std::endl; 

using std::string;

using std::vector;


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.1.2, Precedence and Associativity
// p137.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.1: What is the value returned by 5 + 10 * 20 / 2 ?
int ex_4_1()
{
    // 105
    std::cout << 5 + 10 * 20 / 2 << std::endl;
    return 0;
}

// Exercise 4.2 : Using Table 4.12 (p. 166), parenthesize the following expressions 
// to indicate the order in which the operands are grouped :
// (a)*vec.begin() (b)* vec.begin() + 1
int ex_4_2()
{
    // Create a vector to check our answers.
    vector<int> vec{ 4, 20, 3 };

    // (a) *vec.begin() 
    // Operator precedence:
    //      `.` member selector and `()` function call, left to right, then
    //      `*` dereference
    // The answer is:
    //      *((vec).begin()) 
    cout << *vec.begin() << " " << *((vec).begin()) << endl; // 4, as expected.

    // (b) * vec.begin() + 1
    // Operator precedence:
    //      `.` member selector and `()` function call, left to right, then
    //      `*` dereference, then
    //      `+` add
    cout << * vec.begin() + 1 << " " << (*((vec).begin())) + 1; // 5, as expected.

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.1.3, Order of Evaluation
// p139.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.3: Order of evaluation for most of the binary operators is left undefined
// to give the compiler opportunities for optimization.This strategy presents a trade - off
// between efficient code generation and potential pitfalls in the use of the language by
// the programmer.Do you consider that an acceptable trade - off ? Why or why not?
//
// ANSWER
// Yes. to take the example given in the book, if any of the functions f() .. j() do anything sneaky with state,
// then the programmer can always decide for themselves which bits to do first, and split up the expression accordingly.
// 
// So it's better to leave this up to them and for the compiler to have the flexibility to optimize where it can.
//
// Example. Define f(), a function that changes state: v is passed in by reference, and then its length modified.
int f(vector<int>& v)
{
    v.pop_back();        // changes the length of v.
    return v.size();
}

// Define g(), h(), and j(). These do not change state.
int g() { return 3; }
int h() { return 5; }
int j(vector<int> v) { return v.size(); }

int ex_4_3()
{
    vector<int> v{ 1, 2, 3 };

    // Visual Studio, in this instance, calculates f(), then g(), then h(), then j().
    // f() reduces the length of v, then j() returns the length of the shorter vector.
    //         2 +   3 *   5 +   2 = 19
    cout << f(v) + g() * h() + j(v) << endl;
    
    // Restore original v.
    v.push_back(3);

    // If we want to force our program to calculate j() first, we can always do:
    int result_j = j(v); // 3

    //         2 +   3 *   5 +        3 = 20
    cout << f(v) + g() * h() + result_j << endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.2 Aritmetic Operators
// p141.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.4: Parenthesize the following expression to show how it is evaluated.Test
// your answer by compiling the expression(without parentheses) and printing its result.
// 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2
int ex_4_4()
{
    cout << ((12 / 3) * 4) + (5 * 15) + (24 % 4) / 2 << endl;
    cout << 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2 << endl;
    return 0;
}

// Exercise 4.5 : Determine the result of the following expressions.
// (a)-30 * 3 + 21 / 5 (b)-30 + 3 * 21 / 5
// (c)30 / 3 * 21 % 5 (d)-30 / 3 * 21 % 4
int ex_4_5()
{
    // (a)
    cout << "(a)" << endl;
    cout << -30 * 3 + 21 / 5 << endl;
    cout << (-30 * 3) + (21 / 5) << endl;   // multiply and divide precede addition.
    cout << (-90) + (4) << endl;            // 21 and 5 are both ints, so the fractional part is discarded.
    cout << -86 << endl << endl;
        
        
    // (b)
    cout << "(b)" << endl;
    cout << -30 + 3 * 21 / 5 << endl;
    cout << -30 + 63 / 5 << endl;           // times and divide have same precedence, so left-to-right.
    cout << -30 + 12 << endl;               // integer division: fractional part discarded.
    cout << -18 << endl << endl;
    
    // (c)
    cout << "(c)" << endl;
    cout << 30 / 3 * 21 % 5 << endl;        // All operators have same precedence: left-to-right.
    cout << 10 * 21 % 5 << endl;
    cout << 210 % 5 << endl;
    cout << 0 << endl << endl;
        
    // (d)
    cout << "(d)" << endl;
    cout << -30 / 3 * 21 % 4 << endl;       // Pedantic note: -30 isn't a literal. 30 is a literal, 
                                            // then unary - operates on it.
    cout << -10 * 21 % 4 << endl;
    cout << -210 % 4 << endl;
    cout << -2 << endl;                     // (-m) % n = -(m % n)
                                            // Also note that m % (-n) == m % n.

    return 0;
}

// Exercise 4.6 : Write an expression to determine whether an int value is even or odd.
int ex_4_6()
{
    int i;
    cout << "Please enter an integer: ";
    cin >> i;
    
    cout << i << " is " << (i % 2 == 0 ? "even" : "odd") << "." << endl;
    return 0;
}

// Exercise 4.7 : What does overflow mean ? Show three expressions that will overflow
int ex_4_7()
{
    // ANSWER: when the value you try to put into a variable is too big for that type.
    // Uncomment any of the below to get a run-time overflow error.
    short short_value = 32767;
    short short_overflow = short_value + 1;
    cout << short_overflow << endl;  // Silent error: the value -32767 is printed without warning. We have wraparound.

    char char_value = 255;
    char char_overflow = char_value + 1;
    cout << char_overflow << endl;  // Silent error: it looks like nothing has printed, and we have no explanation.
                                    // Debugging, it turns out that a char value of 256
                                    // corresponds to the null terminator. But this behaviour is not guaranteed,
                                    // as whatever happens is undefined.

    unsigned int i = 0;
    unsigned int unsigned_underflow = i - 1;
    cout << unsigned_underflow << endl; // 4294967295 printed. We have nuclear Gandhi! (Again, not guaranteed).

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.3, Logical and Relationship Operators
// p145.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.8: Explain when operands are evaluated in the logical AND, logical OR, and
// equality operators.
//
// ANSWER.
// Left side evaluated first. Right side only evaluated if needed.
// So right side of AND not evaluated if left side gives false,
// and right side or OR not evaulated if left side gives true.

// Exercise 4.9 : Explain the behavior of the condition in the following if :
int ex_4_9()
{
    const char* cp = "Hello World";

    // cp is not a null pointer, *cp is not an empty or null string.
    // Both sides of the logical AND evaluate to true.
    if (cp && *cp)
        cout << "Ta-dah!" << endl; // Ta-dah is printed.
    return 0;
}

// Exercise 4.10: Write the condition for a while loop that would read ints from the
// standard input and stop when the value read is equal to 42.
int ex_4_10()
{
    int i;
    while (cin >> i && i != 42);

    return 0;
}

// Exercise 4.11 : Write an expression that tests four values, a, b, c, and d, and ensures
// that a is greater than b, which is greater than c, which is greater than d.
int ex_4_11()
{
    int a, b, c, d;
    cin >> a; cin >> b; cin >> c; cin >> d;

    if ((a > b) && (b > c) && (c > d))
        cout << "All three conditions are satisfied!" << endl;
    else
        cout << "All three conditions are not satisfied :-(" << endl;
    return 0;
}

// Exercise 4.12 : Assuming i, j, and k are all ints, explain what i != j < k means.
// `i != j` is a bool, which will get cast to 0 (if false) or 1 (if true) when comparing to the int k.
// The result will be a bool, as per whether or not (0 or 1, as appropriate) < k.
int ex_4_12()
{
    // ANSWER.
    // != has lower precedence than <.
    // So `i != j < k` means `i != (j < k)`
    // 
    // i is an int, so the bool `j < k` is cast to either 0 (false) or 1 (true) for the != comparison.
    // So we'll have `i != 0` or `i != 1`, depending on the result of `j < k`.
    // 
    // The result of this comparison will also be cast to 0 or 1 when streamed to cout. 
    // 
    int i, j, k;

    // Case 1, i != 1, j < k. 
    // (j < k) is true --> cast to 1.
    // i != 1 --> true.
    i = 83; j = 23; k = 100;
    cout << "Case 1. Expect: 1, result: " << (i != j < k) << endl;

    // Case 2, i == 1, j < k. 
    // (j < k) is true --> cast to 1.
    // i != 1 --> false.
    i = 1; j = 23; k = 100;
    cout << "Case 2. Expect: 0, result: " << (i != j < k) << endl;

    // Case 3, i != 1, j > k. 
    // (j < k) is false --> cast to 0.
    // i != 0 --> true.
    i = 83; j = 100; k = 24;
    cout << "Case 3. Expect: 1, result: " << (i != j < k) << endl;

    // Case 2, i == 1, j > k.
    // (j < k) is false --> cast to 0.
    // i != 0 --> false.
    i = 0; j = 100; k = 24;
    cout << "Case 2. Expect: 0, result: " << (i != j < k) << endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.4, Assignment Operators
// p147.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.13: What are the values of i and d after each assignment ?
// int i; double d;
// 
int ex_4_13()
{
    int i;
    double d;

    // (a)
    cout << "(a)" << endl;
    d = i = 3.5;    // ANSWER: d = 3.0, i = 3.
                    // i = 3.5 is an operator that (1st) puts 3.5 into i, and (2nd) returns the value that was put in.
                    // If you put 3.5 into i, i becomes 3, and that's the value that the assignment operator returns.
                    // So what's left is d = 3, so d contains the double value 3.0 after this assignment.
    
    cout << "d: expected = 3.0, result = " << d << endl;
    cout << "i: expected = 3, result = " << i << endl;

    // (b)
    i = d = 3.5;    // ANSWER: d = 3.5, i = 3.
                    // Following the same logic as above, 3.5 is put into d without any truncation, 
                    // and then gets truncated when it is put into i.
    
    cout << "d: expected = 3.5, result = " << d << endl;
    cout << "i: expected = 3, result = " << i << endl;
    return 0;
}

// Exercise 4.14: Explain what happens in each of the if tests :
//     if (42 = i) // ...
//      if (i = 42) // ...
int ex_4_14()
{
    int i = 0;
    // if (42 = i); // Not allowed: 42 cannot be assigned a value.
    
    if (i = 42);    // This will evaluate to true. 
                    // The assignment operator, as well doing the assignment, also returns the value that was assigned,
                    // which in this case is 42.
                    // So the condition is `if (42)`, which is `if (true)`.

    // Other notes. Working through the same steps shows that if (i = 0) is a failed test, btw.
    // So this looks like it should print something, even though it doesn't.
    i = 0;
    if (i = 0)      // We probably meant ==
        cout << "Hello World!" << endl;     // Does not print.

    return 0;
}

// Exercise 4.15 : The following assignment is illegal. Why ? How would you correct it ?
// double dval; int ival; int* pi;
// dval = ival = pi = 0;  
int ex_4_15()
{
    double dval; int ival; int* pi;
    
    // dval = ival = pi = 0;    // Does not compile. Assignment is right-associative, which means its the same thing as:
    // dval = (ival = (pi = 0)) 
    
    // In the above chain, first ...
    pi = 0; // ... is done, which sets pi to be the null pointer, and returns the null pointer
    // to be used in the next assignment in the chain.
    // 
    // So the next assignment becomes 
    // ival = null pointer, which of course can't be done, 
    // because you can't assign a pointer (even the null pointer) to an int.
    //
    // Compiler error: An entity of type int* (the null pointer) cannot be assigned to an entity of type int (ival).

    return 0;
}

// Exercise 4.16: Although the following are legal, they probably do not behave as the
// programmer expects.Why ? Rewrite the expressions as you think they should be.
// 
// (a) if (p = getPtr() != 0)
//      ANSWER. The intention here is a null check. The programmer wants to:
//      - get a pointer, 
//      - assign it to p (so p must be a pointer.), and then#
//      - check p is not null.
// 
//      But != has a higher precedence than =, so what they've written actually means:
// 
//      if (p = (getPtr() != 0)) ... so what we're doing is:
// 
//      - get a pointer,
//      - check it's not null, which gives a bool
//      - assign that bool to p, which as we noted earlier, is a pointer.
//      - We can't assign a bool to a pointer, so this line won't compile.
// 
//      Correction:
// 
//      if ((p = getPtr()) != 0) 
// 
//      
// (b) if (i = 1024)
//      ANSWER. Obviously we want if (i == 1024) here.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.5, Increment and Decrement Operators
// p150.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.17: Explain the difference between prefix and postfix increment.
int ex_4_17()
{
    int a, b;

    cout << "Postfix operator." << endl;
    a = 0;
    b = a++;    // a++ increases the value of a, so a is now 1.
                // It then returns the original value of a, so b is now 0.
    cout << "a: expected = 1, result = " << a << endl;
    cout << "b: expected = 0, result = " << b << endl << endl ;

    cout << "Prefix operator." << endl;
    a = 0;
    b = ++a;    // ++a increases the value of a, so a is now 1.
                // It then returns the new value of a, so b is now 1.
    cout << "a: expected = 1, result = " << a << endl;
    cout << "b: expected = 1, result = " << b << endl << endl;

    return 0;
}

// Exercise 4.18 : What would happen if the while loop on page 148 
// that prints the elements from a vector used the prefix increment operator ?
int ex_4_18()
{
    // We would have *++beg. The * and prefix ++ operators have the same precedence and are right-associative,
    // so that's equivalent to *(++beg).
    // So every time we go through the cout statement, we increase the iterator, 
    // then dereference the increased iterator. 
    // 
    // Effects: we're going to:
    // - skip the first (zero-th) element.
    // - print the first negative value if one exists. The original loop doesn't print it.
    // - get a runtime error if we try to dereference the off-the-end iterator (which happens.

    // Check
    vector<int> v1{ 3, 2, 65, -1, 5, 2 };
    vector<int> v2{ 3, 2, 65, 11, 5, 2 }; // no negative values.
    
    // Original loop.
    cout << "Original loop............" << endl;
    auto pbeg = v1.begin();

    // Prints "3 2 65" as expected
    while (pbeg != v1.end() && *pbeg >= 0)
        cout << *pbeg++ << " " ; 
    cout << endl;

    // Prints "3 2 65 11 5 2" as expected.
    pbeg = v2.begin();
    while (pbeg != v2.end() && *pbeg >= 0)
        cout << *pbeg++ << " " ;
    cout << endl;

    // Prefix loop
    cout << endl << "Prefix loop............" << endl;
    pbeg = v1.begin();

    // Prints "2 65 -1" : first element skipped, first negative int included.
    while (pbeg != v1.end() && *pbeg >= 0)
        cout << *++pbeg << " ";
    cout << endl;

    // Prints "2 65 11 5 2", so first element skipped, and then get a runtime out-of-bounds error.
    pbeg = v2.begin();
    while (pbeg != v2.end() && *pbeg >= 0)
        cout << *++pbeg << " ";
    cout << endl;

    return 0;
}

// Exercise 4.19 : Given that ptr points to an int, that vec is a vector<int>, and that
// ival is an int, explain the behavior of each of these expressions. Which, if any, are
// likely to be incorrect ? Why ? How might each be corrected ?
// (a) ptr != 0 && *ptr++
// (b) ival++ && ival
// (c) vec[ival++] <= vec[ival]
int ex_4_19()
{
    int ival = 0;
    int* ptr = &ival;
    vector<int> vec{ 5, 2, 1 };


    // (a)
    ptr != 0 && *ptr++;     // What this actually means, is: (ptr != 0) && (*(ptr++))
                            // If ptr is a null pointer, then the other term of the && is not evaluated.
                            // (It's short-cicuited)
                            // If it is not a null pointer, then we incrememt ptr and dereference the original location.
                            // But now ptr is pointing somewhere else.
                            // If it's an element of an array, then it could be pointing past the end.
                            // If it's not, then it's definitely pointing somewhere we don't want.
                            // We likely meant to dereference ptr and then increase the dereferenced value.
    
    ptr != 0 && (*ptr)++;   // Corrected version.
    (ptr != 0) && (*ptr)++; // Clearer.
    if (ptr != 0)           // Even more explicit.
        (*ptr)++;

    // (b)
    ival++ && ival;         // What this actually means is: (ival++) && (ival)
                            // In algebraic notation, if ival = x to start,
                            // ival++ sets ival to (x + 1) and returns x, so the expression becomes
                            // x AND (x + 1)
                            // ... which is 0 if x = -1 or x = 0, and 1 otherwise.
                            // 
                            // I have no idea what the intention might be here, so I can't correct it!
    // Check:
    ival = 0;
    cout << "ival = 0:  " << (ival++ && ival) << endl;

    ival = -1;
    cout << "ival = -1: " << (ival++ && ival) << endl;

    ival = 1;
    cout << "ival = 1:  " << (ival++ && ival) << endl;

    vec[ival++] <= vec[ival];   // We don't know which side will be evaluated first.
                                // Suppose initial value of ival is x.
                                // If LHS evaluated first, ival++ returns x, and ival becomes x + 1,
                                // so the comparison is vec[x] <= vec[x + 1].
                                //
                                // If the RHS is evaluated first, the comparison is:
                                // vec[x] <= vec[x], and ival is now x + 1.
                                // 
                                // See exercise 4.3, and the warning at the top of p138:
                                // For operators that do not specify evaluation order, 
                                // it is an error for an expression to refer to and change the same object
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.6, The Member Access Operators
// p150.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.20: Assuming that iter is a vector<string>::iterator, indicate
// which, if any, of the following expressions are legal.Explain the behavior of the legal expressions
// and why those that aren’t legal are in error.
int ex_4_20()
{
    vector<string> v{ "ab", "cd" };
    auto iter = v.begin();
    string diag_str;
    bool diag_bool;

    // (a) *iter++;
    // Equivalent to *(iter++). Increment iter, then dereference original value.
    // Will compile.
    // Will run as long as iter is not pointing to the last element or the off-the-end position in the vector.
    // Run-time out-of-bounds error in those last two cases.
    diag_str = *iter++;
    cout << endl << "(a)" << endl;
    cout << "diag, expected value = 'ab', result = " << diag_str << endl;
    cout << "iter, expected to now point at 'cd', result = " << *iter << endl;

    diag_str = *iter++;     // Now equal to "cd", iter now points to off-the-end position.
    // diag_str = *iter++;  // Run-time error if uncommented.

    // (b) (*iter)++;
    // Dereferencing iter gives a string. Postfix ++ is not defined for strings.
    // Will not compile.
    // Compiler error: No operator ++ matches these operands. 
    // (*iter)++;

    // (c) *iter.empty()
    // Equivalent to *(iter.empty())
    // iter does not have a member called empty().
    // Will not compile.
    // Compiler error: Class <full name of string iterator> has no member "empty()".
    // *iter.empty();

    // (d) iter->empty();
    // Equivalent to (*iter).empty(). Dereference iter to get a string, check if the string is empty.
    // Will compile.
    // Will run as long as iter is not pointing to the last element or the off-the-end position in the vector.
    // Run-time out-of-bounds error in those last two cases.
    iter = v.begin(); 
    diag_bool = iter->empty();
    cout << endl << "(d)" << endl;
    cout << "diag, expected value = false (cout as '0'), result = " << diag_bool << endl;
    cout << "iter, expected to now point at 'ab', result = " << *iter << endl;

    // (e) ++*iter;
    // Prefex ++ and dereference * have same priority, and are right-to-left associative.
    // So this is equivalent to ++(*iter);
    // Dereference iter to get a string, then try to increment it, but you can't increment a string.
    // Will not compile.
    // Compiler error: No operator ++ matches these operands. 
    // ++*iter;

    // (f) iter++->empty();
    // Equivalent to (iter++)->empty().
    // Increment iter, then do ->empty() on original value: dereference original value and check it's empty.
    // Will compile, and run as long as iter is not v.end();
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.7, The Conditional Operator
// p152.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.21: Write a program to use a conditional operator to find the elements in a
// vector<int> that have odd value and double the value of each such element.
int ex_4_21()
{
    vector<int> v;
    int i;

    // Get some ints to form a vector.
    cout << "Please enter some integers, or ^Z to complete entry." << endl;
    while (cin >> i)
        v.push_back(i);

    for (int& elem : v) // Jas be a reference, because we want to change it in place.
        elem = (elem % 2 == 1) ? 2 * elem : elem;
    
    // Check
    for (const int& elem : v) // const to promise we won't change it (just printing).
        cout << elem << " ";
    cout << endl;

    return 0;
}

// Exercise 4.22 : Extend the program that assigned high pass, pass, and fail grades to
// also assign low pass for grades between 60 and 75 inclusive.Write two versions : One
// version that uses only conditional operators; the other should use one or more if
// statements.Which version do you think is easier to understand and why ?
int ex_4_22()
{
    int grade;
    string finalgrade, finalgrade2="";

    cin >> grade;
    
    // Tenary operators.
    finalgrade = (grade > 90)   ? "high pass"
                                : (grade < 60)  ? "fail" 
                                                : (60 <= grade && grade <= 75) ? "low pass" : "pass";
    // If statement.
    if (grade > 90)
        finalgrade2 = "high pass";
    else if (grade < 60)
        finalgrade2 = "fail";
    else if (60 <= grade && grade <= 75)
        finalgrade2 = "low pass";
    else
        finalgrade2 = "pass";

    cout << finalgrade << " " << finalgrade2 << endl;

    return 0;
}

// Exercise 4.23 : The following expression fails to compile due to operator precedence.
// Using Table 4.12 (p. 166), explain why it fails. How would you fix it ?
// string s = "word";
// string pl = s + s[s.size() - 1] == ’s’ ? "" : "s";
int ex_4_23()
{
    string s = "word"; // No problem here.

    // ANSWER: Operator precedence is:
    // +
    // ==
    // = and ?:
    // So what we've written is equivalent to:
    // string pl = ((s + s[s.size() - 1]) == 's') ? "" : "s"
    s + s[s.size() - 1];            // This is a string.
    // s + s[s.size() - 1] == 's';  // Here we are trying to compare a string to a char, which does not compile.
                                    // Compiler error: no operator == matches these operands. (string, char)

    // To fix it:
    // realise that we probably want to add an 's' at the end of the string if it doesn't already end in one.
    string pl = s + (s[s.size() - 1] == 's' ? "" : "s");

    return 0;
}

// Exercise 4.24: Our program that distinguished between high pass, pass, and fail depended on the fact 
// that the conditional operator is right associative. Describe how that
// operator would be evaluated if the operator were left associative
//
// ANSWER.  I do not engage with hypotheticals. Especially not this one, because there is only one ternary operator,
//          and it's right-associative, so there's no point figuring out what a left-associative one would look like.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.8,  The Bitwise Operators
// p156.
// --------------------------------------------------------------------------------------------------------------------

// Not going to do these, because I do not currently plan to re-write Quake III.
// The important bit in this section is that "Shift Operators (aka IO Operators) Are Left Associative".
// Specifically, that `cout << 10 < 42;` is interpreted as `(cout << 10) < 42;` due to operator precedence,
// which is not valid.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.9,  The `sizeof` Operator
// p158.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.28: Write a program to print the size of each of the built - in types.
int ex_4_28()
{
    cout << std::setw(20) << endl;
    cout << std::setw(20) << "bool " << sizeof(bool) << endl;
    cout << std::setw(20) << "char " << sizeof(char) << endl;
    cout << std::setw(20) << "signed char " << sizeof(signed char) << endl;
    cout << std::setw(20) << "unsigned char " << sizeof(unsigned char) << endl;
    cout << std::setw(20) << "wchar_t " << sizeof(wchar_t) << endl;
    cout << std::setw(20) << "float " << sizeof(float) << endl;
    cout << std::setw(20) << "double " << sizeof(double) << endl;
    cout << std::setw(20) << "long double " << sizeof(long double) << endl;
    cout << std::setw(20) << "short " << sizeof(short) << endl;
    cout << std::setw(20) << "unsigned short " << sizeof(unsigned short) << endl;
    cout << std::setw(20) << "int " << sizeof(int) << endl;
    cout << std::setw(20) << "unsigned int " << sizeof(unsigned int) << endl;
    cout << std::setw(20) << "long " << sizeof(long) << endl;
    cout << std::setw(20) << "unsigned long " << sizeof(unsigned long) << endl;
    cout << std::setw(20) << "long long " << sizeof(long long) << endl;
    cout << std::setw(20) << "unsigned long long " << sizeof(unsigned long long) << endl;

    return 0;
}

// Exercise 4.29 : Predict the output of the following code and explain your reasoning.
// Now run the program.Is the output what you expected ? If not, figure out why.
// int x[10]; int* p = x;
// cout << sizeof(x) / sizeof(*x) << endl;
// cout << sizeof(p) / sizeof(*p) << endl;
int ex_4_29()
{
    // sizeof(x)
    //      returns the size of the array. It has 10 elements of ints, which are size 4.
    //      So this returns 40.
    // sizeof(*x)
    //      *x dereferences the pointer to the first element of array,
    //      so this expression returns the sizeof the first element, ie., sizeof(int) = 4.
    // sizeof(p)
    //      p is a pointer ie., an address in memory, so sizeof it is machine-dependent.
    // sizeof(*p)
    //      int *p = x is the same as int *p = &x[0], see Section 3.5.3.
    //      So this returns sizeof(int), as x[0] is an int. 
    
    int x[10]; int* p = x;
    cout << "Expected: 40 / 4 = 10, result " << sizeof(x) / sizeof(*x) << endl << endl;
    cout << "Expected: dunno; this is not a sensible division, result " << sizeof(p) / sizeof(*p) << endl;
    cout << "Indeed, Visual Studio gives the warning under `sizeof(p)`:" << endl;
    cout << "'Dividing size of a pointer by another value', to indicate that this is not sensible." << endl;
    return 0;
}

// Exercise 4.30: Using Table 4.12 (p. 166), parenthesize the following expressions to
// match the default evaluation :
// (a) sizeof x + y
// (b) sizeof p->mem
// (c) sizeof a < b 
// (d) sizeof f()
int ff() { return 0; } // We already used f() in a previous exercise.
int ex_4_30()
{
    char x = 6; // size 1
    int y = 42; // value 42; don't need its size.
    vector<string> v{ "hello" };
    auto p = v.begin();

    
    // (a) sizeof is higher than +
    // Could also paranthesize as `sizeof(x) + y`.
    cout << "These should both be equal to 1 + 42: (" << (sizeof x + y) << ", " << (sizeof x) + y << ")." << endl;

    // (b) -> is higher than sizeof. Do the dereference and evaluate the member function, then get size of the result.
    // In our setup, *p is a string, and we will assume that .mem() is .empty()
    cout << "These should both be equal to the size of a bool, ie., 1: (" 
        << sizeof p->empty() << ", " 
        << sizeof(p->empty()) << ")." << endl;

    // (c) sizeof is higher than <
    // Could also paranthesize as `sizeof(a) < b`.
    auto a = x; // size 1
    auto b = y; // value 42; don't need its size.
    cout << std::boolalpha 
        << "These should both be true (1 < 42): (" << (sizeof a < b) << ", " << ((sizeof a) < b) << ")." << endl;

    // (d) Function call () is higher than sizeof.
    cout << "These should both be 4 (ff() returns int): (" << sizeof ff() << ", " << sizeof (ff()) << ")." << endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.10, Comma Operator
// p158.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.31: The program in this section used the prefix increment and decrement
// operators. Explain why we used prefix and not postfix. What changes would have to
// be made to use the postfix versions ? Rewrite the program using postfix operators.
int ex_4_31_orig_code()
{
    vector<int> ivec(10);
    vector<int>::size_type cnt = ivec.size();



    return 0;
}
int ex_4_31()
{
    vector<int> ivec(10);
    vector<int>::size_type cnt = ivec.size();

    // Original loop: prints out "10 9 8 7 6 5 4 3 2 1".
    for (vector<int>::size_type ix = 0; ix != ivec.size(); ++ix, --cnt)
    {
        ivec[ix] = cnt;
        cout << ivec[ix] << " ";
    }
    cout << endl;

    // Modified loop: also prints out "10 9 8 7 6 5 4 3 2 1".
    cnt = ivec.size();
    for (vector<int>::size_type ix = 0; ix != ivec.size(); ix++, cnt--)
    {
        ivec[ix] = cnt;
        cout << ivec[ix] << " ";

    }
    cout << endl;

    // No functional difference, but the advice is to always use prefix operators unless it's not possible,
    // to avoid unnecessary copying. (See p148).
    return 0;
}

// Exercise 4.32 : Explain the following loop.
// constexpr int size = 5;
// int ia[size] = { 1,2,3,4,5 };
// for (int* ptr = ia, ix = 0;
//     ix != size && ptr != ia + size;
//     ++ix, ++ptr) { /* ... */
// }
//
// ANSWER: the program loops over the array, increasing 
// the subscript ix and the pointer ptr as it goes.

// Exercise 4.33: Using Table 4.12 (p. 166) explain what the following expression does :
// someValue ? ++x, ++y : --x, --y;
int ex_4_33()
{
    int x = 43, y = 27;
    // someValue ? ++x, ++y : --x, --y;
    // 
    // This is a trap! It looks like `someValue ? (++x, ++y) : (--x, --y)`
    // 
    // But if you carefully follow the rules of operator precedence, what you actually get is:
    // 
    // (someValue ? ++x, ++y : --x), --y;
    // 
    // Case 1: someValue is true. The expression simplifies to `(++x, ++y), --y`.
    // Evaluation of the bracket:
    // x is incremented (to 44) and the value discarded.
    // y is incremented (to 28) and the value returned.
    // 
    // The second comma operator discards that value and evaluates --y:
    // y is decremented, and the new value of y (27) is returned.
    // x and y now hold 44 and 27.
    // Check:
    bool someValue = true;
    cout << "someValue == true" << endl;
    cout << "Evaluate expression. Expect 27, result " << (someValue ? ++x, ++y : --x, --y) << endl;
    cout << "x after evaluation. Expect 44, result " << x << endl;
    cout << "y after evaluation. expect 27, result " << y << endl;
    
    // Case 2: someValue is false. Expression simplifies to `--x, --y`.
    // x is decremented to 42 and the value discarded.
    // y is decremented to 26 and the value returned.
    x = 43, y = 27;
    someValue = false;
    cout << endl << "someValue == false" << endl;
    cout << "Evaluate expression. Expect 26, result " << (someValue ? ++x, ++y : --x, --y) << endl;
    cout << "x after evaluation. Expect 42, result " << x << endl;
    cout << "y after evaluation. expect 26, result " << y << endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 4.11.1, The Arithmetic Conversions
// p161.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 4.34: Given the variable definitions in this section, explain what conversions
// take place in the following expressions :
// 
// (a) if (fval)
// (b) dval = fval + ival;
// (c) dval + ival * cval;
// 
// Remember that you may need to consider the associativity of the operators.
//
// ANSWER.
// (a) if (fval)
// In conditions, numeric types are converted to false if equal to 0, and 1 otherwise.
//
// (b) dval = fval + ival;
// ival converted to float, then added to fval, result converted to double to put in dval.
//
// (c) dval + ival * cval;
// The multiplication is formed first. The char is promoted to int. That int is multiplied by the int ival,
// which returns an int. That int is converted to a double for addition to dval.


// Exercise 4.35: Given the following definitions,
// char cval; int ival; unsigned int ui;
// float fval; double dval;
// identify the implicit type conversions, if any, taking place :
int ex_4_35()
{
    char cval;
    float fval;
    double dval;
    unsigned int ui;
    int ival;
    
    // (a) cval = 'a' + 3;      
    // 'a' promoted to int (which gives 97 on my machine), then 3 is added. 
    // Since it's a char, the answer is cout as 'd'.
    cval = 'a' + 3;
    cout << "(a) " << cval << endl;
    
    // (b) fval = ui - ival * 1.0;  
    // See https://learn.microsoft.com/en-us/cpp/cpp/standard-conversions?view=msvc-170#arithmetic-conversions 
    // The rules start: [1] if either operand is a long double, the other one gets converted to a long double.
    // [2] If last rule not met, if either operand is a double, the other is converted to a double.
    //
    // By these rules:
    // ui - ival * 1.0          ... has types:
    // unsigned - int * double  ... This simplifies to:
    // unsigned - double        ... Use rule [2] on the multiplication. This then simplifies further to:
    // double                   ... Use rule [2] again.
    //
    // Finally, the resulting double is truncated to float to fit into fval.
    //
    // Proof that (unsigned - double) is converted to (double - double) and not (unsigned - unsigned).    
    ui = 10;
    ival = 3; // ival * 1.5 gives the double 4.5

    // If ival * 1.5 is converted to unsigned, the 0.5 will get truncated and 
    // ui - (ival * 1.5) will become ui - 4, which simplifies to 10 - 4 = 6.
    //
    // But, if ui is converted to double, then the 0.5 in 4.5 will not get truncated, and 
    // ui - (ival * 1.5) will become 10.0 - 4.5 = 5.5.
    fval = ui - ival * 1.5;     
    cout << "(b) " << fval << endl; // We get 5.5.

    // (c) dval = ui * fval; 
    // Use rule [3] at the above link: if rule [1] and rule [2] both not met, then 
    // if either operand is a float, convert the other one to a float. 
    // ui will be converted to a float, then multiplied by fval,
    // then the result converted to a double and put into dval.
    ui = 1;
    fval = 1.5;
    dval = ui * fval; // 1.0 * 1.5 if ui converted to float, but 1 * 1 if fval converted to unsigned.
    cout << "(c) " << dval << endl; // prints 1.5.
    
    // (d) cval = ival + fval + dval;
    // Addition is left-to-right, so first bit that gets done is (ival + fval). Then the result is added to dval.
    // Use rule 3: ival is converted to float so this addition yields a float.
    // Adding a float to a dval: use rule 2, which says that the float is converted to a double.
    // So we have double + double, which gives double.
    // 
    // Another way to think of it is to write it all out in terms of types from the beginning:
    // 
    // int    + flaot  + double. 
    // (int   + float) + double       <-- Associatibity rules
    // (float + float) + double       <-- int converted to float by Rule 3
    //      float      + double
    //      double     + double       <-- float converted to double by Rule 2
    //            double
    // The fractional part is truncated to put into cval. Also there might be overflow errors here.
    ival = 0;
    fval = 97.5;
    dval = 3.7;
    cval = ival + fval + dval;          // This will be 101.2 ('e') if I am right in my logic above.
                                        // But if the floating parts are truncted, then the answer will be 100 ('d').
    cout << "(d) " << cval << endl;     // Prints 'e'.

    ival = 188;
    cval = ival + fval + dval;          // Overflow. Undefined behaviour. In Visual Studio, gives silent wraparound.
    cout << "(d) " << cval << endl;     // Prints '!', which is ASCII character 33 = int(188 + 97.5 + 3.7) - 256.

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
//EXERCISES SECTION 4.11.3, Explicit Conversions
// p165.
// --------------------------------------------------------------------------------------------------------------------

//Exercise 4.36: Assuming i is an int and d is a double write the expression i *= d so
//that it does integral, rather than floating - point, multiplication.
int ex_4_36()
{
    int i = 3;
    double d = 2.9;

    cout << (i *= d) << endl; // Prints 8: first converts i to a double, then does 3.0 * 2.9, then truncates that.

    i = 3; d = 2.9;
    cout << (i *= static_cast<int>(d)) << endl; // prints 6: casts d to an int, giving 2. Then multiplies by i, which is 3.
    return 0;
}

//Exercise 4.37 : Rewrite each of the following old - style casts to use a named cast :
int ex_4_37()
{
    string s = "hello";
    char c = 'c';
    int i; double d; const string* ps = &s; char* pc = &c; void* pv;

    // (a) 
    pv = (void*)ps; 
    //pv = static_cast<void*>(ps);                      // This doesn't work. pv is a non-const (pointer), whereas ps is a const (pointer to string).
                                                        // Need to cast away the const (const_cast) and then cast to a different type (static_cast).
    pv = const_cast<string*>(ps);                       // This seems to work, although I don't know why.
    pv = static_cast<void*>(const_cast<string*>(ps));

    // (b) 
    i = int(*pc);
    i = static_cast<int>(*pc);
    
    // (c) 
    pv = &d;
    pv = static_cast<void*>(&d);
    
    // (d) 
    pc = (char*)pv;
    pc = static_cast<char*>(pv);

    return 0;
}

//Exercise 4.38: Explain the following expression :
int ex_4_38()
{
    // ANSWER: the integers are divided using integer addition, and the result is then cast to double.
    // For the values below, we'll get int(5/2) = 2, NOT 2.5.
    int i = 2, j = 5;

    double slope = static_cast<double>(j / i);
    cout << "Expect slope to be 2, result is " << slope << "." << endl;
    return 0;
}


int main()
{
    return ex_4_38();
}
