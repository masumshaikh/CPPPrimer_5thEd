// Chapter6.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <cassert>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// iomanip
using std::boolalpha;

// iostream
using std::cin;
using std::cout;
using std::endl;

// stdexcept
using std::invalid_argument;

// string
using std::string;

// vector
using std::vector;

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.1, Function Basics
// p205.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.1: What is the difference between a parameter and an argument ?
// 
// ANSWER: 
// -    Parameter: the variable we use inside the function.
// -    Argument:  the variable we use to call the function. The arguemnt(s) are used to initialise the parameters(s).
// 
// Exercise 6.2 : Indicate which of the following functions are in error and why.
// Suggest how you might correct the problems.
// (a) 
int f() {
    string s;
    // . . .
    // return s;               // Does not compile: `s` is a string but the function is declared to return int.
    return 0;                  // Correction to allow compilation.
 }
// (b)
// f2(int i) { /* . . . */ }    // f2 does not specify a return type.

// (c)
// int calc(int v1, int v1) /* . . . */ }   // Two things wrong with this: v1 is duplicated, and no opening `{`.

// (d)
// double square(double x) return x * x;    // No braces around the body of the function.


// Exercise 6.3: Write and test your own version of fact.
int ex_6_3_fact(int n)
{
    try
    {
        if (n < 0)
            throw std::invalid_argument("Can only calculate factorials of non-negative integers.");
        if (n == 0 || n == 1)
            return 1;
        else
            return n * ex_6_3_fact(n - 1);
    }
    catch (std::invalid_argument err)
    {
        throw;
    }
}
 
// Exercise 6.4 : Write a function that interacts with the user, asking for a number and
// generating the factorial of that number.Call this function from main.
int ex_6_4()
{
    int i;
    cout << "Please enter a non-negative integer, or 'x' to quit." << endl;
    while (cin >> i) // Exits ungracefully if you enter a decimal number, but that's cin's fault.
    {
        try
        {
            cout << i << "! is: " << ex_6_3_fact(i) << endl;
            cout << endl << "Please enter a non-negative integer, or 'x' to quit." << endl;
        }
        catch (std::invalid_argument err)
        {
            cout << err.what() << endl;
            cout << endl << "Please enter a non-negative integer, or 'x' to quit." << endl;
        }
    }

    return 0;
}
 
// Exercise 6.5 : Write a function to return the absolute value of its argument.
double ex_6_5_abs(double x)
{
     return (x < 0) ? -x : x;
 }

int ex_6_5()
{
    double x;
    cout << "Please enter a double, or 'x' to quit." << endl;
    while (cin >> x)
    {
        cout << "|" << x << "| is: " << ex_6_5_abs(x) << endl;
        cout << endl << "Please enter a double, or 'x' to quit." << endl;
    }

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.1.1, Local Objects
// p206.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.6: Explain the differences between a parameter, a local variable, and a local
// staticvariable.Give an example of a function in which each might be useful.
int ex_6_6(int i) // i is a parameter
{
    int j = 0;          // j is a local variable. It will be initialised to 0 every time the code goes through here.
    
    static int k = 0;   // k is a local static variable.
                        // It will be initialised to 0 the first time this function is called.
                        // But on subsequent calls, it won't be re-initialised.
    ++k;                // The new value of k will persist for the life of the program.

    // Upon function exit, `j` is destroyed, but `k` lives on.
    return 0;
}

// Exercise 6.7 : Write a function that returns 0 when it is ﬁrst called and then generates
// numbers in sequence each time it is called again.
int ex_6_7_answer()
{
    static int k = 0;      
    return k++;
}
int ex_6_7()
{
    cout << ex_6_7_answer() << endl;
    cout << ex_6_7_answer() << endl;
    cout << ex_6_7_answer() << endl;
    cout << ex_6_7_answer() << endl; // Prints 0, 1, 2, 3
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.2.1, Passing Arguments by Value
// p210.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.10: Using pointers, write a function to swap the values of two ints.
// Test the function by calling it and printing the swapped values.
void ex_6_10_swap(int* p, int* q)
{
    int temp = *p;      // Value pointed to by p copied to temp.

    *p = *q;            // Value pointed to by q copied to value pointed to by p.
    *q = temp;          // Value previously stored copied to value pointed to by q.
}
int ex_6_10()
{
    int m = 8, n = 3;
    ex_6_10_swap(&m, &n);

    cout << "Expect m to be 3, m = " << m << endl;
    cout << "Expect n to be 8, n = " << n << endl;

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.2.2, Passng Arguments as References
// p212.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.11: Write and test your own version of reset that takes a reference.
void ex_6_11_reset(int& j) { j = 0; }
int ex_6_11()
{
    int k = 9;
    ex_6_11_reset(k);
    cout << "k is now " << k;
    return 0;
}

// Exercise 6.12 : Rewrite the program from exercise 6.10 in § 6.2.1 (p. 210) to use refer -
// ences instead of pointers to swap the value of two ints. Which version do you think
// would be easier to use and why ?
//
// Answer: they are equally easy to use, as long as the API is documented correctly.
void ex_6_12_swap(int&i, int&j)
{
    int temp = i;
    i = j;
    j = temp;
}
int ex_6_12()
{
    int m = 8, n = 3;
    ex_6_12_swap(m, n);

    cout << "Expect m to be 3, m = " << m << endl;
    cout << "Expect n to be 8, n = " << n << endl;

    return 0;
}

// Exercise 6.13 : Assuming T is the name of a type, explain the difference between a
// function declared as `void f(T)` and `void f(T&)`.
//
// ANSWER: 
// void f(T)
//      The parameter is copied when passing to the function.
//
// void f(T&) 
//      The parameter is passed as a reference: no need to copy.

// Exercise 6.14 : Give an example of when a parameter should be a reference type.
// Give an example of when a parameter should not be a reference.
//
// ANSWER: A parameter should be a reference type when:
// -    the function needs to change it.
// -    If it is expensive to copy (and in this case, if you don't need to change it in the function, 
//      you should pass it as a const ref).
// -    If you want the function to return multiple values (return one main value
//      and send out the other ones out by modifying references passed in.
//
// A parameter should not be a reference if you don't want changes to the parameter made in the function
// to affect the argument passed in. For example, solving the matrix equation Ax = b. Typically solved by
// Gaussian elimination, which changes the rows of A. Don't pass in A by reference if you want it intact after
// finding x.

// PAGE 213. Understanding the code about const and parameter passing.
int reset(int* p) { return 0; }
int reset(int& p) { return 0; }
string::size_type find_char(const string s, char c,  string::size_type& occurs) // Also used in Exercise 6.15
{
    auto ret = s.size(); // position of the ﬁrst occurrence, if any
    occurs = 0; // set the occurrence count parameter
    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
                ret = i; // remember the ﬁrst occurrence of c
            ++occurs; // increment the occurrence count
        }
    }
    return ret; // count is returned implicitly in occurs
}

int code_example_p213()
{
    int i = 0;
    const int ci = i;
    string::size_type ctr = 0;

    reset(&i);          // Fine.
    
    // reset(&ci);      // Doesn't compile. &ci is a reference to a const int. References can only low-level const.
                        // When we go into the function, we initialise `p` by basically doing:
                        // int* p = &ci;
                        // ... and this line doesn't compile either.
                        // Compiler error: "const int* cannot be used to initialise int*".
                        // &ci is a low-level const ref (refs can only have low-level const: see ex_2_31().
                        // Cannot lose low-level const when assigning.  

    reset(i);           // Calls reset(int&).
    
    // reset(42);       // Doesn't compile: equivalent to `int* p = 42;`,
                        // and 42 is a literal and so doesn't have a memory address.

    // reset(ctr);      // Doesn't compile; type mismatch. size_t is not compatible with either int* or int&.

    find_char("Hello World!", 'o', ctr);    // This is OK. See ex_6_15()
    return 0;
}

// Exercise 6.15 : Explain the rationale for the type of each of find_char’s parameters
// In particular, why is `s` a reference to const, but `occurs` is a plain reference ? Why are
// these parameters references, but the `char` parameter `c` is not? What would happen if
// we made `s` a plain reference ? What if we made `occurs` a reference to const ?
int ex_6_15()
{
    string::size_type ctr = 0;
    find_char("Hello World!", 'o', ctr);

    // Work through each of the parameter initialisations :
    const string& s = "Hello World!";       // Initialising a reference to const string using a string literal: OK.
    char c = 'o';                           // Obviously allowed.
    string::size_type& occurs = ctr;        // Fine: no const involved. occurs is an alias for ctr inside the function.

    // Q:   Why is `s` a reference to const, but `occurs` is a plain reference?
    // A:   We won't be changing `s`, but we will be changing `occurs`.

    // Q:   Why are these parameters references, but the `char` parameter `c` is not? 
    // A:   `s` is a reference because strings can be very large, so we don't want to copy it unless we have to.
    //          But we did make it const to show that we're not going to change it.
    //      `occurs` is a reference because we want to change it inside the function as a way of returning additional
    //          information from the function. (Section Using Reference Parameters to Return Additional Information).
    //      'c' is not a reference because it's only a char so copying it is negligible. Not sure why it's not const.
    //          Note that if we wanted to make it a reference, it would have to be a const reference. See the comment
    //          against `reset(&ci);` in code_example_p213().
    // 
    // Q:   What would happen if we made `s` a plain reference ?
    // A:   No functional difference, but someone else reading the function
    //          might think we could change it inside the function.
    // 
    // Q:   What if we made `occurs` a reference to const ?
    // A    We wouldn't be able to change its value,
    //          and so wouldn't be able to use it to return the information we want.
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.2.3, `const` Parameters and Arguments
// p215.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.16: The following function, although legal, is less useful than it might be.
// Identify and correct the limitation on this function :
bool is_empty(string& s) { return s.empty(); }
int ex_6_16()
{
    // ANSWER: because `s` is passed as a plain reference, it can't accept string literals or const strings.
    //          Neither of the below compile.

    // Compiler error: reference of type string& (non-const) cannot be initalised with const char[].
    // is_empty("This literally won't work!"); 

    // Compiler error: Qualifiers dropped in binding reference of type string& to initialiser of type const string.
    // Translated: can't bind reference to non-const string to a const string.
    const string const_s = "Nor will this :-(";
    // is_empty(const_s);
    return 0;
}

// Exercise 6.17 : Write a function to determine whether a string contains any capital
// letters. Write a function to change a string to all lowercase. Do the parameters you
// used in these functions have the same type ? If so, why ? If not, why not?
bool ex_6_17_contains_caps(const string& s) // [1] Remove the const to see that ex_6_17() won't work if s is non-const.
{
    bool does_contain = false;
    for (const char& c : s)         // Could use auto, but explicitly typed for practice.
        if (isupper(c))
        {
            does_contain = true;
            break;
        }
    return does_contain;
}
void ex_6_17_to_lower(string& s)
{
    for (char& c : s)
        c = toupper(c);
}
int ex_6_17()
{
    string s = "hello";
    const string sc = "What's up, Doc?";

    // Works with strings, const strings, and string literals.
    cout << boolalpha << ex_6_17_contains_caps(s) << endl; // Expect false.
    cout << boolalpha << ex_6_17_contains_caps(sc) << endl; // Expect true. Won't compile if we remove const in [1].
    cout << boolalpha << ex_6_17_contains_caps("Hello") << endl; // Expect true. Also won't compile if remove const.

    cout << endl;
    // Works with strings only.
    ex_6_17_to_lower(s);
    cout << s << endl; // Expect "HELLO".

    return 0;
}

// Exercise 6.18 : Write declarations for each of the following functions. When you write
// these declarations, use the name of the function to indicate what the function does.
// (a)  A function named `compare` that returns a `bool` and has two parameters that
//      are references to a class named `matrix`.
// (b)  A function named `change_val` that returns a `vector<int>` iterator and
//      takes two parameters : One is an `int` and the other is an iterator for a `vector<int>`.
//
// ANSWER below. Note: can omit parameter names in declarations. Kept for clarity.
class matrix {};
bool ex_6_18_compare(const matrix& m1, const matrix& m2);
vector<int>::iterator ex_6_18_change_val(vector<int>::iterator position, int new_val);


// Exercise 6.19 : Given the following declarations, determine which calls are legal and
// which are illegal.For those that are illegal, explain why.
// double calc(double);
// int count(const string&, char);
// int sum(vector<int>::iterator, vector<int>::iterator, int);
// vector<int> vec(10);
// (a)calc(23.4, 55.1); (b)count("abcda", ’a’);
// (c)calc(66); (d)sum(vec.begin(), vec.end(), 3.8);
double ex_6_19_calc(double) { return 0.0; }                                          // Fine
int ex_6_19_count(const string&, char) { return 0; }                                 // Fine
int ex_6_19_sum(vector<int>::iterator, vector<int>::iterator, int) { return 0; }     // Fine
int ex_6_19()
{
    // (a)
    // ex_6_19_calc(23.4, 55.1);    // Doesn't compile: calc only takes double.
    
    // (b)
    ex_6_19_count("abcda", 'a');    // Fine.
    
    // (c)
    ex_6_19_calc(66);               // Fine.
    
    // (d)
    vector<int> vec{ 1, 2, 5 };
    ex_6_19_sum(vec.begin(), vec.end(), 3.8);   // Fine. 3.8 will get truncated to int when passed to the function.
                                                // See section 4.11, Type Conversions.
    return 0;
}

// Exercise 6.20: When should reference parameters be references to const ? What happens
// if we make a parameter a plain reference when it could be a reference to const ?
//
// ANSWER: Reference parameters should always be const if they are not being changed by the function.
// If you make a reference parameter a plain reference then it won't be as useful, because it won't be able to 
// accept const or literal arguments.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.2.4, Array Parameters
// p219
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.21: Write a function that takes an `int` and a pointer to an `int` and returns
// the larger of the `int` value or the value to which the pointer points. What type should
// you use for the pointer ?
int ex_6_21_compare(const int i, const int* p)
{
    // Remove the consts above to see what happens.
    // p needs to be const, otherwise you can't pass in const pointers.
    // However, i doesn't need to be const and you can still pass in const ints.
    // Why the difference?
    // Assume the consts have been removed.
    // Then when the execution path comes into the function from ex_t_21(), the following initialisations are done:
    // int i = j;   // This is allowed because j is a top level const, which is ignored.
    // int* p = q   // q is a pointer to a const int. q itself is not const: this is low-level const.
                    // You cannot lose a low-level const in an initialisation, so this is not allowed.
    return i > *p ? i : *p;
}
int ex_6_21()
{
    const int j = 3;
    const int k = 4;
    const int* const q = &j;
    cout << ex_6_21_compare(j, q) << endl;
    return 0;
}

// Exercise 6.22 : Write a function to swap two `int` pointers.
// ANSWER: we want to swap the pointers, not the values to which they are pointing. So we copy from ex_10_swap(), with
//      an extra layer of indirection.
void ex_6_22_swap(int** p1, int** p2)
{
    int* temp = *p1;    // Pointer pointed to by p1 copied to temp.

    *p1 = *p2;          // Pointer pointed to by p2 copied to pointer pointed to by p1.
    *p2 = temp;         // Pointer previously stored copied to pointer pointed to by p2.
}
int ex_6_22()
{
    int i = 3, j = 4;
    int* p1 = &i, * p2 = &j;

    // i is storing the value 3, j is storing the value 4.
    // pi is currently holding the address of i, pj holding the address of j.
    cout << "Before, i and j: " << i << ", " << j << endl;          // Expect 3, 4
    cout << "Before, pi and pj: " << *p1 << ", " << *p2 << endl;    // Expect 3, 4
    
    cout << endl;
    ex_6_22_swap(&p1, &p2);

    // i is still storing the value 3, j still is storing the value 4.
    // But pi is now holding the address of j, and pj is now holding the address of i.
    cout << "After , i and j: " << i << ", " << j << endl;          // Expect 3, 4
    cout << "After , pi and pj: " << *p1 << ", " << *p2 << endl;    // Expect 4, 3

    return 0;
}

// Exercise 6.23 : Write your own versions of each of the print functions presented in
// this section. Call each of these functions to print iand j deﬁned as follows :
// int i = 0, j[2] = { 0, 1 };
//
// ANSWER: the functions are too simple to write your "own version".

// Exercise 6.24: Explain the behavior of the following function. If there are problems in
// the code, explain what they are and how you might ﬁx them.
void ex_6_24_print(const int ia[10])
{
    for (size_t i = 0; i != 10; ++i)
        cout << ia[i] << endl;
}
int ex_6_24()
{
    // QUESTION: Explain the behavior of the following function.
    // ANSWER:   The function takes an array of length 10 (and only 10), and prints them out.
    int ia[10]{ 200, 32, 4, 134, 32, 3, 4, 5, 3 ,0 };
    ex_6_24_print(ia);
    cout << endl;

    // QUESTION: Explain any problems and how you might ﬁx them..
    // ANSWER: The code only takes in arrays of length exactly 10. The following will compile ...
    int ja[3]{ 200, 32, 0 };
    ex_6_24_print(ja);      // ... but it prints garbage values after the end of ja.
                            // Similarly an array longer than 10 would only print the first 10 elements.

    // QUESTION: how you might ﬁx them.
    // ANSWER:   Pass in pointers to the beginning and off-the-end elements (p216), or the size (p217).

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.2.5, `main`: Handling Command-Line Options
// p220.
// --------------------------------------------------------------------------------------------------------------------
// Exercise 6.25: Write a mainfunction that takes two arguments.Concatenate the sup -
// plied arguments and print the resulting string.
//
// Exercise 6.26 : Write a program that accepts the options presented in this section.Print
// the values of the arguments passed to main.
// 
// ANSWERS: will come back to these when I need to write a command line program that needs to accept arguments.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.2.6
// p
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.27: Write a function that takes an initializer_list<int> and produces 
// the sum of the elements in the list.
int ex_6_2_27_sum(std::initializer_list<int> lst)
{
    int sum = 0;
    for (const int& i : lst)
        sum += i;
    return sum;
}

int ex_6_27()
{
    cout << ex_6_2_27_sum({ 1, 2, 3 }) << endl; // expect 6.
    return 0;
}
// Exercise 6.28 : In the second version of error_msgthat has an `ErrCode` parameter,
// what is the type of `elem` in the forloop ?
//
// ANSWER: `const string&`.

// Exercise 6.29 : When you use an initializer_listin a range `for` would you ever
// use a reference as the loop control variable ? If so, why ? If not, why not?
//
// ANSWER: I would use a reference, to avoid copying. (The reference would have to be const, since the elements of
//          `initializer_list`s are const.



// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.3.2, Functions That Return a Value
// p228.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.30: Compile the version of `str_subrange` as presented on page 223 to see
// what your compiler does with the indicated errors.

//bool str_subrange(const string& str1, const string& str2)
//{
//    // same sizes: return normal equality test
//    if (str1.size() == str2.size())
//        return str1 == str2; // ok: ==returns bool
//    // ﬁnd the size of the smaller string; conditional operator, see § 4.7 (p. 151)
//    auto size = (str1.size() < str2.size())
//        ? str1.size() : str2.size();
//    // look at each element up to the size of the smaller string
//    for (decltype(size) i = 0; i != size; ++i) {
//        if (str1[i] != str2[i])
//            return; // error #1: no return value; compiler should detect this error
//    }
//    // error #2: control might ﬂow off the end of the function without a return
//    // the compiler might not detect this error
//
//}
// ANSWER: Compiler error: function must return a value.

// Exercise 6.31 : When is it valid to return a reference ? A reference to const ?
//
// It is valid to return a reference to a non-local variable. (§ Never Return a Reference or Pointer to a Local Object)
// You should return a reference to a const if you don't want to return an lvalue (something that can be assigned to).

// Exercise 6.32 : Indicate whether the following function is legal. If so, explain what it
// does; if not, correct any errors and then explain it.

int& ex_6_32_get(int* arry, int index) { return arry[index]; }

// int main() changed to int ex_6_32()
int ex_6_32()
{
    int ia[10];
    for (int i = 0; i != 10; ++i)
        ex_6_32_get(ia, i) = i;

    // ANSWER: get(ia, 1) returns a reference to the i-th element of the array.
    //          This is then assigned the value of i.
    //          The code changes the array to [0,1 , ... , 9]
    // Check:
    for (const int& i : ia)
        cout << i << " ";
    return 0;
}

// Exercise 6.33: Write a recursive function to print the contents of a vector.
void ex_6_33_print(vector<int>::iterator bg, vector<int>::iterator ed)
{
    if (bg == ed)
        return;
    cout << *bg << " ";
    ex_6_33_print(bg + 1, ed);
}
void ex_6_33_print(vector<int> v)
{
    ex_6_33_print(v.begin(), v.end());
}
int ex_6_33()
{
    vector<int> v{ 0, 3, 2 };
    ex_6_33_print(v);

    cout << endl;
    
    vector<int> w;
    ex_6_33_print(w);   // No runtime error for empty vectors either.

    return 0;
}

// Exercise 6.34 : What would happen if the stopping condition in `factorial` were
// if (val != 0)
// ANSWER: the code in question:
int ex_6_34_factorial(int val)
{
    if (val > 1)        // Original. Use this to experiment with [1] and [2] below.
    // if (val != 0)    // Proposed change.
        return ex_6_34_factorial(val - 1) * val;
        // return ex_6_34_factorial(val--) * val;      // [1] ... used in ex_6_35()
        // return ex_6_34_factorial(--val) * val;      // [2] ... used in ex_6_35()

    return 1;
}
// if we change the base condition to if (val != 0), then we get an infinite recursion for -ve numbers,
// whereas the original code returns 1.
int ex_6_34()
{
    cout << ex_6_34_factorial(5) << endl;       // Same as original code for positive integers.
    cout << ex_6_34_factorial(0) << endl;       // And indeed for 0.

    // cout << ex_6_34_factorial(-1) << endl;   // Infinite loop for numbers < 0.

    return 0;
}

// Exercise 6.35 : In the call to factorial, why did we pass `val - 1` rather than `val--` ?
//
// ANSWER: Two points to note:
// - `val--` decreases `val` but returns the original value of `val` to be passed to the recursive call.
// - The multiply operator does not guarantee what order the two sides are calculated.
// 
// Suppose we are at val = 5, and are about to calculate `factorial(val--) * val`.
// 
// If we do factorial(val--) first:
//      `val` now = 4, but the previous value, 5, is passed to the recursive call.
//      So we are evaluating factorial(5) * 4. Infinite loop! We are trying to calculate 5! to calculate 5!.
// 
// If we do v first:
//      We evaluate the right-hand operator to get 5, then to calcualte the left-hand operand,
//      decrease `val` but pass the original value of it to the recursive call.
//      So are evaluating factorial(5) * 5.
//
// TL;DR: two problems: (1) the fact that the order of execution of the two sides of the '*' operator is not guaranteed
//      makes the expression ambiguous. And (2) no matter which of the two possible interpretations the compiler does,
//      we run into an infinite loop.


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION  6.3.3, Returning a Pointer to an Array
// p230.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.36: Write the declaration for a function that returns a reference to an array
// of ten strings, without using either a trailing return, decltype, or a type alias.
//
//          ex_6_36()            // We are writing the declaration for a function, the brackets signify this.
//         &ex_6_36()            // It returns a reference.
//        (&ex_6_36())[10]       // [1] To an array of 10 ...
//  string(&ex_6_36())[10];      // ... strings. If you uncomment this line, you'll compile but it won't link.
//
// ANSWER: ^^
// 
// PS. Why do we need the extra brackets at [1]?
// string  ex_6_3()[10];        // This looks like a function returning an array of 10 strings, see notes on ex_3_43().
                                // And functions can't return arrays.
// string& ex_6_3()[10];        // This looks like a function returning an array of 10 references to strings,
                                // and again, we can't return arrays.
                                // Compiler error: function returning array is not allowed.

// Exercise 6.37 : Write three additional declarations for the function in the previous exercise.
// One should use a type alias, one should use a trailing return, and the third
// should use decltype.Which form do you prefer and why ?
//
// ANSWERS
// - type alias.
using str_array = string[10];
// str_array* ex_3_37_typedef();       // Uncomment to see that it compiles but won't link without a function body.

// - decltype
string s[10]{ "", "" , "", "", "", "", "", "", "", "" };
// decltype(s&) ex_3_37_decltype();     // Uncomment to see that it compiles but won't link without a function body.

// - trailing return
// auto ex_3_37_trailing_return() -> string(&)[10];    // Ditto re. uncomment.

// Exercise 6.38 : Revise the arrPtrfunction on to return a reference to the array.
//
// ANSWER. 
int odd[] = { 1,3,5,7,9 };
int even[] = { 0,2,4,6,8 };

// decltype(odd)* arrPtr(int i)         // original code.
decltype(odd)& ex_6_38_arrPtr(int i)
{
    // return (i % 2) ? &odd : &even;    // Original code.
    return (i % 2) ? odd : even;        // Neturns a reference to the appropriate array
}



// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.4, Overloaded Functions
// p234.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.39: Explain the effect of the second declaration in each one of the following
// sets of declarations.Indicate which, if any, are illegal.
// (a) int calc(int, int);
// int calc(const int, const int);
// (b) int get();
// double get();
// (c) int* reset(int*);
// double* reset(double*);
//
// ANSWERS
// (a)  This pair is not legal. We could pass in a non-const int to either one, so there is no way to distinguish which 
//      one to call when we are passing in non-const ints.
//      Compiler error: function already has a body.
int ex_6_39_calc(int, int) { return 0; }
// int ex_6_39_calc(const int, const int) { return 0; }
//
// (b)  This pair is not legal. There is no way to decide which one to pick when get() is called.
//      Compiler error: overloaded function differs only by return type.
int ex_6_39_get() { return 0; }
// double ex_6_39_get() { return 0.0; };

// (c)  This pair is legal: you either pass an int or a double, and there is no confusion which one is meant.
//      (The methods have different signatures).
int* ex_6_39_reset(int*) { return nullptr; }
double* ex_6_39_reset(double*) { return nullptr; }
;

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.5.1, Default Arguments
// p236.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.40: Which, if either, of the following declarations are errors ? Why ?
// (a) This is fine. The default parameters are all at the end.
int ff(int a, int b = 0, int c = 0) { return 0; }

// (b) This is not fine: a parameter with a default occures before parameters without.
// char* init(int ht = 24, int wd, char bckgrnd) { return nullptr; }


// Exercise 6.41: Which, if any, of the following calls are illegal ? Why ? Which, if any, are
// legal but unlikely to match the programmer’s intent ? Why ?
char* ex_6_41_init(int ht, int wd = 80, char bckgrnd = ' ') { return &bckgrnd; }
int ex_6_41()
{
    // (a) Not fine: ht doesn't have a default and no value is supplied for it.
    // ex_6_41_init();

    // (b) Fine. ht = 24, wd = 10, bckgrnd = ' '.
    ex_6_41_init(24, 10);

    // (c) This is legal, but it looks like the programmer intended:
    //      ht = 14, wd = 80 (the default), bckgrnd = '*',  whereas actually char is promoted to int:
    //      ht = 14, wd = 42 ('*' promoted to int), bckgrnd = ' ' (the default).
    ex_6_41_init(14, '*');

    // Check:
    char* pchar = ex_6_41_init(14, '*');
    cout << *pchar << endl; // prints a space, not a *.

    return 0;
}

// Exercise 6.42: Give the second parameter of make_plural (§ 6.3.2, p. 224) a default
// argument of ’s’.Test your program by printing singular and plural versions of the
// words successand failure.
//
// ANSWER: ="s" added.
string ex_6_42_make_plural(size_t ctr, const string& word, const string& ending = "s")
{
    return (ctr > 1) ? word + ending : word;
}
int ex_6_42()
{
    cout << "The plural of success is " << ex_6_42_make_plural(2, "success", "es") << endl;
    cout << "The plural of failure is " << ex_6_42_make_plural(2, "failure") << endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.5.2, Inline and `constexpr` Functions
// p240.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.43: Which one of the following declarations and deﬁnitions would you put
// in a header ? In a source ﬁle ? Explain why.
// (a) inline bool eq(const BigInt&, const BigInt&) { ... }
// (b) void putValues(int* arr, int size);
// 
// ANSWERS.
// (a)
// p239 says that: "`inline` and `constexpr` functions normally are deﬁned in headers." So the entire body of `eq()` needs
// to go in a header file, not just the declaration.
// 
// (b)
// This function is not `inline`d (and doesn't immediately look like a good candidate for it), so it should be declared
// in a header file if it will be used across multiple files, and actually defined (given a body) in a source file.
//

// Exercise 6.44: Rewrite the `isShorter` function from § 6.2.2 (p. 211) to be inline.
//
// ANSWER: `inline` added.
inline int ex_6_4_isShorter(const string& s1, const string& s2) 
{
    return s1.size() < s2.size();
}

// Exercise 6.45 : Review the programs you’ve written for the earlier exercises and decide
// whether they should be deﬁned as inline. If so, do so. If not, explain why they
// should not be inline.
//
// ANSWER. This seems like a lot of work.


// Exercise 6.46 : Would it be possible to deﬁne `isShorter` as a `constexpr` ? If so, do so. If not, explain why not.
// 
// ANSWER. `string` is not a literal type, so you can't have constexpr strings: the code below will not compile:
//      constexpr string s{ "hello" };
//      
//      A function can only be constexpr if it takes constexpr arguments, so as long as it takes strings as arguments,
//      `is_shorter()` cannot be `constexpr`. (If you changed it to accept `char[]` parameters, then the function could be
//      `constexpr`, as `char` arrays can be `constexpr`.
//


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.5.3, Aids for Debugging
// p243.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.47: Revise the program you wrote in the exercises in § 6.3.2 (p. 228) that
// used recursion to print the contents of a vector to conditionally print information
// about its execution. For example, you might print the size of the vector on each call.
// Compile and run the program with debugging turned on and again with it turned off.
void ex_6_47_print(vector<int>::iterator bg, vector<int>::iterator ed)
{
    // The code in the preprocessor block below does not execute if the solution is built in Release mode,
    // but does in Debug mode.
#ifndef NDEBUG
    cout << "------ Vector size is " << ed - bg << " -------------";
#endif
    if (bg == ed)
        return;
    cout << *bg << " ";

    // Another NDEBUG block, only put in to make the Debug output look good.
#ifndef NDEBUG
    cout << endl;
#endif

    ex_6_47_print(bg + 1, ed);
}
int ex_6_47()
{
    vector<int> v{ 1, 4, 2, 6, 3 };
    ex_6_47_print(v.begin(), v.end());
    return 0;
}



// Exercise 6.48 : Explain what this loop does and whether it is a good use of assert :
// string s;
// while (cin >> s && s != sought) {} // empty body
// assert(cin);
//
// ANSWER. assert(cin) terminates the program if `cin` is false, ie., if it's not in a valid state.
//          If this is something to be worried about, it seems better to do this in a try-catch block:
//          The try-catch block will work in Release build and allow graceful handling,
//          whereas assert(cin) will only work in Debug mode, so end-users will see an ugly runtime crash.
int ex_6_48()
{
    assert(false); // This will only do something if building in Debug mode. (And what it does isn't pretty).
    cout << "They WERE on a break!" << endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.6, Function Matching
// p245.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.49: What is a candidate function ? What is a viable function ?
//
// ANSWERS.
// - Candidate function: a (possibly overloaded) function with the same name as the one being called, 
//      that is visible at the time of call. Method signatures don't have to match.
// - Viable function: a candidate function with a signature that matches, or could be made to match with the available
//      type conversions, the signature of the call. 

// Exercise 6.50 : Given the declarations for `f` from page 242, list the viable functions, if
// any for each of the following calls. Indicate which function is the best match, or if the
// call is illegal whether there is no match or why the call is ambiguous.
// (a) f(2.56, 42)
// (b) f(42)
// (c) f(42, 0)
// (d) f(2.56, 3.14)
//
// ANSWER. The functions `f`:
void ex_6_50_f() { cout << "f()"; }
void ex_6_50_f(int) { cout << "f(int)"; }
void ex_6_50_f(int, int) { cout << "f(int, int)"; }
void ex_6_50_f(double, double = 3.14) { cout << "f(double, double)"; }
int ex_6_50()
{
    // (a) f(2.56, 42)
    //      - We definitely can't call the f() or f(int) overloads.
    //      - But which of the last two overloads will we call?
    //      - We could call it as either f(2, 46) or f(2.56, 42.0).
    // 
    //      - NOTE. I originally thought that this meant that the answer was that f(double, double),
    //      - as f(2, 46) requires requires a truncation, whereas the latter doesn't. 
    //      - This is incorrect reasoning, as the compiler treats all conversions the same: it doesn't take into acout
    //      - whether or not a conversion truncated precision.
    // 
    //      - The correct answer: we create the following table.
    //      - 
    //      - parameter                             42          2.56
    //      - when passed to f(int, int)            exact       converted
    //      - when passed to f(double, double)      converted   exact
    //      - 
    //      - There would be a winner if either of rows 2 or 3 was least as good as the other one.
    //      - (If there was one row that weakly dominated the other). But there isn't, so this call is ambiguous.
    // 
    cout << "(a): Commentd out; ambiguous call. " << endl;
    // ex_6_50_f(2.56, 42);
    // cout << "." << endl;


    // (b) f(43)
    //      - First viable overload is f(int), which does not require any type conversions.
    //      - Also viable, is f(double, double) with a default value for the second parameter.
    //          But that requires converting the int literal 43 to a double.
    //      - Choose the one that doesn't require any conversions.
    cout << "(b): Expect to call f(int), actually called: "; 
    ex_6_50_f(43);
    cout << "." << endl;

    // (c) f(42, 0)
    //      - Viable functions are either f(int, int) or f(double, double).
    //      - f(int, int) is an exact match whereas the other one requires conversion.
    //      - f(int, int) is the answer.
    cout << "(c): Expect to call f(int, int), actually called: ";
    ex_6_50_f(42, 0);
    cout << "." << endl;

    // (d) f(2.56, 3.14)
    //      - Viable functions are either f(int, int) or f(double, double).
    //      - f(double, double) is an exact match whereas the other one requires conversion.
    //      - f(double, double) is the answer.
    cout << "(d): Expect to call f(double, double), actually called: ";
    ex_6_50_f(2.56, 3.14);
    cout << "." << endl;
    
    return 0;
}

// Exercise 6.51 : Write all four versions of `f`. Each function should print a
// distinguishing message. Check your answers for the previous exercise. If your answers were
// incorrect, study this section until you understand why your answers were wrong.
//
// ANSWER.
// Already did this to check my answers to the last question.



// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.6.1, Argument Type Conversions
// p247.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 6.52: Given the following declarations,
// void manip(int, int);
// double dobj;
// what is the rank(§ 6.6.1, p. 245) of each conversion in the following calls ?
// (a) manip('a', 'z');
// (b) manip(55.4, dobj);
//
// ANSWERS.
// (a) manip('a', 'z')
//      Rank 3: Arguments are char, hence promoted to int and manip(int, int) called. 
//
// (b) manip(55.4, dobj);
//      Rank 4: arithmetic conversion (truncation on both parameters).


// Exercise 6.53: Explain the effect of the second declaration in each one of the following
// sets of declarations. Indicate which, if any, are illegal.
// 
// (a) 
int ex_6_53_calc_a(int&, int&) { cout << "calc_a(int&, int&)";  return 0; }
int ex_6_53_calc_a(const int&, const int&) { cout << "calc_a(const int&, const int&)"; return 0; }
// 
// ANSWER: These compile together and define valid overloads that do not clash. See ex_6_53() for explanation.
// 
// (b) 
int ex_6_53_calc_b(char*, char*) { cout << "calc_b(char*, char*)"; return 0; }
int ex_6_53_calc_b(const char*, const char*) { cout << "calc_b(const char*, const char*)"; return 0; }
// 
// ANSWER: These compile together and define valid overloads that do not clash. See ex_6_53() for explanation.
// 
// (c)  
// int ex_6_53_calc_c(char*, char*) { cout << "calc_c(char*, char*)"; return 0; }
int ex_6_53_calc_c(char* const, char* const) { cout << "calc_b(const char*, const char*)"; return 0; }
//
// ANSWER: These do NOT compile together as these valid overloads clash. See ex_6_53() for explanation.

int ex_6_53()
{
    // Set-up used in explanations.
    int i = 4;
    int& ri = i;
    const int& cri = i;         // [1]
    // int& bad_ref = cri;      // [2] Compiler rror: "Const qualifier dropped in binding reference of type int& to
                                //      initialiser of type cosnt int." 
                                //      (I feel like the types are the wrong way round in this message.)
    // int& bad_ref2 = 3;       // [3] Compiler error: "Initial value of reference to non-const must be an l-value."

    char c = 'c';
    char* pc = &c;
    const char* pcc = &c;       // pointer to a const char: *pcc cannot be changed (but `c` can, in this set-up).

    const char* pdc = pc;       // [4] Reading this as pointer to d as a const is helpful.
                                // Also, note that we are initialising a pointer to const from a pointer to non-const.
                                // We are adding a low-level const, which is allowed. See ex_2_31().
    // char* bad_ptr = pdc;     // [5] Not allowed: we are losing a low-level const. Or, to put it another way,
                                // pdc is a pointer to a const char, so we can't change *pdc. But by assigning it to 
                                // bad_ptr, which is NOT a pointer to a const char, we're sneakily trying to
                                // give ourselves the ability to change *bad_ptr.

    char* const cpc = &c;       // const ptr to `c`. (`*c` can be changed, but `c` can't be repointed.)
                                // Note that this is a top-level const, so it can be used to define both 
                                // `char*` (pointer to char) and `const char*` (pointer to const char).
                                // So both of the following are good:
    char* top_level_const_dropped = cpc;    // [6]
    const char* top_level_const_kept = cpc; // [7]

    // Explanation of (a)
    {
        // We will look all the possibilities for what we can pass in to calc_a and see if the choice of
        // overload is unambiguous in every case. We will pass in:
        // -    two references to const ints
        // -    two non-const ints
        // -    two references to plain ints
        // -    two int literals.
        
        // Passing in two references to const ints.
        // In the call on the next line of code, we pass in two const `int&`'s. Let's consider the first one `cri`.
        // When passing this to the first overload, we initialise the first parameter with a statement of the form
        //
        // "int& = const int&", but this is never allowed; see the commented out line [2].
        //
        // When passing this to the second overload, the initialisation of the first parameter is of the form:
        //
        // "const int& = const int&", which is allowed, so this one is called.
        //
        // Output: const int&, const int&
        ex_6_53_calc_a(cri, cri);
        cout << endl;

        // Passing in two ints.
        // In the call on the next line of code, we pass in two non-const `int`s. Let's  consider the first one `i`.
        // If we tried to pass this in to calc(const int& prm_i, cosnt int& prm_j), then effectively,
        // prm_i is initialised with the statement `const int & prm_i = i`, which is of the form:
        // 
        // "const int & = int" ... This is allowed (we did it in [1] above).
        // 
        // On the other hand, if we tried to pass it in to calc(int& prm_i,int& prm_j), prm_i is initalised with:
        // `int& prm_i = i`, which is of the form;
        //
        // "int & = int" ... Which is not only allowed, it is a better match compared to [2]. So we call this one.
        //
        // Output: int&, int&
        ex_6_53_calc_a(i, i);
        cout << endl;

        // Passing in two references to ints.
        // In the next call, the same logic applies as previously.
        //
        // Output: int&, int&
        ex_6_53_calc_a(ri, ri);
        cout << endl;

        // Passing in two int literals. The initialisations are of the form:
        //
        // "int& = literal" ... for the first overload, but this is not allowed: see [3] above.
        // "const int& = literal" for the second overload, which is allowed. So the second overload is called.
        //
        // Output: const int&, const int&
        ex_6_53_calc_a(4, 5);
        cout << endl;
    }

    // Explanation of (b)
    {
        // For (b) we will pass in:
        // -    two pointers to non-const `char`s. 
        // -    two pointers to const `char`s.
        // The other two permutations that we tried for (a) are not relevant here.
        
        // Passing in two pointers to non-const `char`s. 
        // In the call on the next line of code, the initialisation of the variables for the two overloads are:
        //
        // "char* = char*", (obviously allowed) and :
        // "const char* = char*" (also allowed, see [4] above).
        // 
        // So both are allowed, but the first is an exact match so this one is called.
        // 
        // Output: calc_b(char*, char*)
        cout << endl;
        ex_6_53_calc_b(pc, pc);
        cout << endl;
        
        // Passing in two pointers to const `char`s. 
        // The initialisations are of the form:
        //
        // "char* = const char*", (not allowed: we are losing a low-level const. See [5] above.)
        // "const char* = const char*" (obviously allowed). So this one will be chosen.
        //
        // Output: const char*, const char*
        ex_6_53_calc_b(pcc, pdc);
        cout << endl;
    }

    // Explanation of (c)
    {
        // When we try to follow the same logic as for (a) and (b), it doesn't work.
        // For example, what happens when we try to pass in cpc, which is a const pointer to c?
        // Then the initialisations have the following forms for the two overloads, respectively:
        // 
        // "char* =  char*" for the first one, which is an exact match.
        // "const char* = char*", which doesn't LOOK exact, but actually reduces to "char* = char*".
        // 
        // See the table in ex_2_31() about top/low-level const-ness, and lines [6] and [7] above.
        //
        // So the point is, the output of the call below will be either
        // "calc_c(char*, char*)" or calc_c(const char*, const char*), depending on which overload you have active.
        cout << endl;
        ex_6_53_calc_c(cpc, cpc);
        cout << endl;
    }
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 6.7, Pointers to Fuctions
// p250.
// --------------------------------------------------------------------------------------------------------------------

// Understanding the code examples.
// Set-up. 
bool lengthCompare(const string&, const string&) { cout << "In lengthCompare." << endl; return true; }
string::size_type sumLength(const string&, const string&) { return 0; }
bool cstringCompare(const char*, const char*) { return true; }

// Used in section "Pointers to Overloaded Functions".
void ff(int*) {}
void ff(unsigned int) {}

// Used in section "Function pointer parameters".
double squared(double x) { return x * x; }
double cubed(double x) { return x * x * x; }
double evaluate(double (*some_func)(double), double x) { cout << some_func(x) << endl; return some_func(x); } // [1] can omit the (*): see p249.

// Now write a pointer to that function. Build it up using operator precedence.
//          (*pf)                                   pf is a pointer (brackets first)
//          (*pf)()                                 to a function (then function call)
//          (*pf)(const string&, const string&)     that takes these arguments
//     bool (*pf)(const string&, const string&)     that returns a bool.

// Also build up the counter-example given on p248.
//          pf()                                    pf is a function (function call is higher than *)
//          pf(const string&, const string&)        that takes these arguments
//         *pf(const string&, const string&)        and returns a pointer
//    bool *pf(const string&, const string&)        to a bool.

int code_examples_6_7()
{
    bool (*pf)(const string&, const string&);

    pf = &lengthCompare;        // lengthCompare is a function, but it still has to be stored in memory somewhere.
                                // pf now holds the address of that memory location.
    pf = lengthCompare;         // This is an equivalent shorthand: the `&` is not necessary.

    // The three calls below do the same thing.
    lengthCompare("s1", "s2");  // This ...
    (*pf)("s1", "s2");          // ... can now be called using this. The compiler dereferences pf.
                                // This gives it a memory address, so it goes to that memory address
                                // and does what it finds there; i.e., it runs `lengthCompare()`.
    pf("s1", "s2");             // Another equivalent shorthand.

    // Possible errors.
    pf = 0;                     // ok: `pf` points to no function
    // pf = sumLength;          // error: return type differs.
                                // Compiler error: "A value of type size_t(*)(const string&, const string&) cannot 
                                //      be assigned to an entity of type bool(*)(const string&, const string&)".
                                // Note that for example, bool(*) tells you that it's a pointer to a function
                                //      and not a bool.
    // pf = cstringCompare;     // error: parameter types differ
                                // Compiler error: similar to above, except that size_t -> bool and string& -> char*.
    pf = lengthCompare;         // ok: function and pointer types match exactly


    // Pointers to Overloaded Functions.
    void (*pf1)(unsigned int) = ff;     // pf1 points to ff. Both return type and argument list match.
    // void (*pf2)(int) = ff;           // Compiler error: No instance of overloaded function matches required type.
    // double(*pf3)(int*) = ff;         // Same compiler error.

    // Function pointer parameters
    // Suppose I have a bunch of functions that take in a double and return a double. 
    // Sometimes I will want to square, sometimes I will want to cube.  What I would like, is to write something like
    // evaluate(f, x), to evaluate f() at x, where f is a previously defined function.
    // This is what evaluate(); does in the set-up.
    // The only complication is that evaluate() cannot take a function directly, but it can take a pointer to one.
    // So this is not allowed:
    // -    double evaluate(double some_func(double), double x);
    // But this is:
    // -    double evaluate(double (*some_func)(double), double x);
    //
    // Now we can do any of these equivalent calls in place of squared(x) or cubed(x):
    evaluate(&squared, 2.0);            // Expect 4.0
    evaluate(squared, 3.0);             // Expect 9.0
    
    // Now the cunning stuff.
    double (*math_func)(double);        // Define a pointer to a function that maps double to dobule.
    math_func = &squared;               // Point it to our `squared` function.
    evaluate(math_func, 4.0);           // Expect 16.0
    math_func = cubed;                  // Repoint it to our `cubed` function. Removed the `&` to show that
                                        //      this can also be done. (Makes the code look nicer, but like much
                                        //      syntactic sugar, obscures what is going on, to some extent).
    evaluate(math_func, 5.0);           // Expect 125.0. But the interesting thing here is that we used to same code
                                        //      that we used to evaluate `squared`.

    // Finally, we can simplify these long expressions by using `typedef`s or `decltype()`.
    using funcRtoR = double (*)(double);
    funcRtoR math_func2 = squared;      // etc.

    return 0;

}

// Exercise 6.54: Write a declaration for a function that takes two int parameters and
// returns an int, and declare a `vector` whose elements have this function pointer type.
int ex_6_54_f(int, int) { return 0; } // A definition rather than a declaration, to enable linking.

int ex_6_55_add(int i, int j) { return i + j; }
int ex_6_55_subtract(int i, int j) { return i - j; }
int ex_6_55_multiply(int i, int j) { return i * j; }
int ex_6_55_divide(int i, int j) { return i / j; } // Should have proper error checking here!

// Actually exercises 6.54 through 6.56.
int ex_6_54()
{
    // Exercise 6.54.
    // Explanation:
    //            (*)               a pointer to a function
    //            (*)(int, int)     that takes two ints.
    //        int (*)(int, int)     and returns an int.
    // vector<int (*)(int, int)>    A vector thereof.
    vector<int (*)(int, int)>v;

    // Exercise 6.55.
    v.push_back(&ex_6_55_add);        // Could omit the `&`. Still haven't decided which I prefer.
    v.push_back(&ex_6_55_subtract);       
    v.push_back(&ex_6_55_multiply);
    v.push_back(&ex_6_55_divide);

    // Exercise 6.56.
    using funcZ2toZ = int (*)(int, int);

    // The below for() statements (written in order of decreasing explicitness) are all equivalent.
    for (int (*func)(int, int) : v)
    // for (funcZ2toZ func : v)
    // for (auto func : v)          
    {
        cout << func(7, 3) << endl; // Expect 10, 4, 21, 2.
    }

    return 0;
}

// Exercise 6.55 : Write four functions that add, subtract, multiply, and divide two int
// values. Store pointers to these functions in your vector from the previous exercise.
//
// See ex_6_54()

// Exercise 6.56 : Call each element in the vector and print their result.
//
// See ex_6_54()


// ------------------------------------------------------MAIN----------------------------------------------------------
int main()
{
    return ex_6_54();
}
// ------------------------------------------------------MAIN----------------------------------------------------------

//int ex_6_5()
//{
//    return 0;
//}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 
// p
// --------------------------------------------------------------------------------------------------------------------

