// Chapter5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// iomanip
using std::boolalpha;
using std::setw;

// iostream
using std::cin;
using std::cout;
using std::endl;

// string and vector
using std::string;
using std::vector;

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.1
// p
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.1: What is a null statement ? When might you use a null statement ?
// 
// ANSWER: A null statement is a statement that doesn't do anything.
// Either a single semi-colon, or a pair of curly braces.
// Often used in loops.

// Exercise 5.2 : What is a block ? When might you might use a block ?
//
// ANSWER: A sequence of statements and declarations surrounded by a pair of curly braces.
// Used where the language requires a single statement but the logic of the program needs more than one.

// Exercise 5.3 : Use the comma operator (§ 4.10, p. 157) to rewrite the while loop from
// § 1.4.1 (p. 11) so that it no longer requires a block.
// Explain whether this rewrite improves or diminishes the readability of this code
int while_loop_from_1_4_1()
{
    int sum = 0, val = 1;

    // keep executing the while as long as val is less than or equal to 10
    while (val <= 10) {
        sum += val; // assigns sum + val to sum
        ++val;      // add 1 to val
    }

    return 0;
}

int ex_5_3()
{
    int sum = 0, val = 0;

    // Probably less readable than the original.
    // - val is initialised to 1 before the first term in the sum.
    // - The comma operator is not immediately obvious.
    while (++val, val <= 10)
        sum += val;

    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;

    // The block -- the pair of curly braces -- has been removed in the last loop.
    // But by using the assoicative property of the comma operator, we can remove the remaining statement as well!
    // But the resulting code is terrible.
    sum = 0, val = 0;
    while (++val, sum += val, val < 10)
        ; // Comment on null statement, as per "Best Practices" advice on p172.
    
    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.2, Statement Scope
// p174.
// --------------------------------------------------------------------------------------------------------------------


// Exercise 5.4: Explain each of the following examples, and correct any problems you
// detect.
// (a)  while (string::iterator iter != s.end()) { /* ... */ }
// (b)  while (bool status = find(word)) { /* ... */ }
//      if (!status) { /* ... */ }
bool find(string word)
{
    return false;
}
int ex_5_4()
{
    // (a) Set up.
    string s = "Hello world.";

    // while (string::iterator iter != s.end()) // Does not compile: iter is not initialised.
                                                // Compiler error: 
                                                // "A condition declaration must include an initialiser".
    // Correct code:
    string::iterator iter = s.begin();
    while (iter != s.end())
    {
        /* ... */
        ++iter;                         // Inifinte loop without this line!.
    }

    // (b) Set up.
    string word = "hello";
    while (bool status = find(word))    // [1] Note that = as opposed to == is plausible here,
                                        // Especially if `find()` returns a bool.
    { /**/ }

    // if (!status)                     // Compiler error: `status` is out of scope. 
                                        // Only defined inside the while loop at [1].

    // Code that compiles.
    bool status;                        // Declare bool outside while loop so that 
                                        // it exists when we get tot the if() check.
    while (status = find(word))
    { /**/ }
    if (!status)                        // This compiles now, but ... why??
                                        // We would only have exited the while loop if status were assigned false,
                                        // so this if() check is unnecessary.
    { /**/ }
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.3.1, The `if` Statement
// p178.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.5: Using an if–else statement, write your own version of the program to
// generate the letter grade from a numeric grade.
//
// Program specs:
// - Numeric grades range from zero to 100 inclusive.
// - A grade of 100 gets an A++
// - 90 to 99: A
// - 80 to 89: B
// - 70 to 79: C
// - 60 to 69: D
// - Grades below 60 get an F #
// 
// Also, for Grades A to D,
// - if the numeric grade ends in 8 or 9, add a plus, eg 98 -> A+
// - if the numeric grade ends in 0, 1, or 2, add a minus, eg 82 -> B-
int ex_5_5()
{
    int numeric_grade;
    string letter_grade;

    cout << "Please enter some numeric grades between 0 and 100 inclusive." << endl;
    vector<string> letter_grades        // A very brittle implementation!
    {
        "F", "F", "F", "F", "F", "F",   // 0 to 50.
        "D", "C", "B", "A"              // 60, 70, etc. 
    };

    while (cin >> numeric_grade)
    {
        if (numeric_grade == 100)
            letter_grade = "A++";
        else
        {
            int bucket = numeric_grade / 10;
            int units_digit = numeric_grade % 10;
            letter_grade = letter_grades[bucket];

            if (letter_grade < "F")         // Less than means a better grade.
            {
                if (units_digit <= 2)
                    letter_grade += "-";
                else if (units_digit >= 8)
                    letter_grade += "+";
                else
                    ; // Nothing to append.
            }
        }

        cout << letter_grade << endl << endl;
    }

    return 0;
}

// Exercise 5.6 : Rewrite your grading program to use the conditional operator 
// (§ 4.7, p. 151) in place of the if–else statement.
int ex_5_6()
{
    int numeric_grade;
    string letter_grade;

    cout << "Please enter some numeric grades between 0 and 100 inclusive." << endl;
    vector<string> letter_grades        // A very brittle implementation!
    {
        "F", "F", "F", "F", "F", "F",   // 0 to 50.
        "D", "C", "B", "A", "A"         // 60, 70, etc. 
    };

    while (cin >> numeric_grade)
    {
        int bucket = numeric_grade / 10;
        int units_digit = numeric_grade % 10;

        // The code below is a terrible idea. May God have mercy on my soul, because my technical reviewer will not.
        letter_grade =
            (numeric_grade == 100) ? "A++"
            : letter_grades[bucket] + (
                (letter_grade < "F") && (units_digit <= 2) ? "-"
                : (letter_grade < "F") && (units_digit >= 8) ? "+" : "");

        cout << letter_grade << endl << endl;
    }
    return 0;
}

// Exercise 5.7 : Correct the errors in each of the following code fragments :
// (a)  if (ival1 != ival2)
//          ival1 = ival2
//      else ival1 = ival2 = 0;
// 
// (b)  if (ival < minval)
//          minval = ival;
//          occurs = 1;
// 
// (c)  if (int ival = get_value())
//          cout << "ival = " << ival << endl;
//      if (!ival)
//          cout << "ival = 0\n";
// 
// (d)  if (ival = 0)
//          ival = get_value();
//
// ANSWERS and corrected code below.
int get_value() { return 1; }
int ex_5_7()
{
    // (a): Needs a semi-colon after the assignment.
    {
        int ival1 = 3, ival2 = 4;
        if (ival1 != ival2)
            ival1 = ival2;          // If you comment out the semi-colon you get a compiler error "Expected a ';'".
        else ival1 = ival2 = 0;     // This is fine. 0 is assigned to ival2 -- this operation returns 0,
        // which is then assigned to ival1.
    }

    // (b): Code as given will compile, but braces probably need to go around both assignments.
    {
        int ival = 5, minval = 10, occurs = 0;
        if (ival < minval)
        {
            minval = ival;
            occurs = 1;
        }
    }

    // (c): The error is that ival is defined in the first if clause but is out of scope by the second.
    //      Minimal change to correct the code is below,
    //      but you probably just want to change the second if check to `else`.
    {
        int ival;
        if (ival = get_value())
            cout << "ival = " << ival << endl;
        if (!ival)
            cout << "ival = 0\n";
    }

    // (d): You probably want an equality check not an assignment.
    {
        int ival = 0;
        if (ival = 0)               // Assignemnt returns the value assigned, which here is 0. if(0) is false  
            ival = get_value();     // ... so this line is never executed.
        return 0;
    }
}

// Exercise 5.8: What is a “dangling else” ? How are else clauses resolved in C++ ?
int ex_5_8()
{
    int i = 10;
    int j = 20;
    if (i == 10)    // it is.
        if (j == 40) // it's not.
            cout << "1." << endl;   // We definitely won't do this.
    else
        cout << "2." << endl;       // Will we do this?
                                    // - If the `else` is matched to the nested `if (j == 40)` then we will.
                                    // - If the `else` is matched to the outer  `if (i == 10)`,
                                    //      as implied by the indentation, then we won't.
                                    // This is a dangling else.

    // (When run, "2." is indeed printed). C++ pairs any dangling elses with the closest unmatched if before it.
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.3.2, The `switch` Statement
// p183.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.9: Write a program using a series of if statements to count the number of
// vowels in text read from cin.
int ex_5_9()
{
    string text;
    int count_a = 0, count_e = 0, count_i = 0, count_o = 0, count_u = 0;
    
    cout << "Please enter some text." << endl;
    getline(cin, text);
    for (const char c : text)
    {
        if (c == 'a')
            ++count_a;
        else if (c == 'e')
            ++count_e;
        else if (c == 'i')
            ++count_i;
        else if (c == 'o')
            ++count_o;
        else if (c == 'u')
            ++count_u;
    }

    cout << "That text had " << endl;
    cout << "  " << count_a << " a's" << endl;
    cout << "  " << count_e << " e's" << endl;
    cout << "  " << count_i << " i's" << endl;
    cout << "  " << count_o << " o's" << endl;
    cout << "  " << count_u << " u's" << endl;

    return 0;
}

// Exercise 5.10 : There is one problem with our vowel - counting program as we’ve implemented it : It doesn’t count capital letters as vowels.Write a program that counts
// both lower - and uppercase letters as the appropriate vowel—that is, your program
// should count both ’a’ and ’A’ as part of aCnt, and so forth.
int ex_5_10()
{
    string text;
    int count_a = 0, count_e = 0, count_i = 0, count_o = 0, count_u = 0;

    cout << "Please enter some text." << endl;
    getline(cin, text);
    for (const char c : text)
    {
        switch (c)
        {
        case ('a'): case('A'):
            count_a++;
            break;
        case ('e'): case('E'):
            count_e++;
            break;
        case ('i'): case('I'):
            count_i++;
            break;
        case ('o'): case('O'):
            count_o++;
            break;
        case ('u'): case('U'):
            count_u++;
            break;
        }
    }

    cout << "That text had " << endl;
    cout << "  " << count_a << " a's and A's" << endl;
    cout << "  " << count_e << " e's and E's" << endl;
    cout << "  " << count_i << " i's and I's" << endl;
    cout << "  " << count_o << " o's and O's" << endl;
    cout << "  " << count_u << " u's and U's" << endl;

    return 0;
}

// Exercise 5.11 : Modify our vowel - counting program so that it also counts the number
// of blank spaces, tabs, and newlines read.
int ex_5_11()
{
    string text;
    int count_a = 0, count_e = 0, count_i = 0, count_o = 0, count_u = 0, count_spc = 0;

    cout << "Please enter some text." << endl;
    getline(cin, text);
    for (const char c : text)
    {
        if (isspace(c))         // Catches space, form feed, line feed, carriage return, horizontal and vertical tab.
            ++count_spc;

        switch (c)              // c can't be both whitespace and a vowel, 
        {                       // So there's no need to wrap the `switch` in an `else` clause.
        case ('a'): case('A'):
            count_a++;
            break;
        case ('e'): case('E'):
            count_e++;
            break;
        case ('i'): case('I'):
            count_i++;
            break;
        case ('o'): case('O'):
            count_o++;
            break;
        case ('u'): case('U'):
            count_u++;
            break;
        }
    }

    cout << "That text had " << endl;
    cout << "  " << count_a << " a's and A's" << endl;
    cout << "  " << count_e << " e's and E's" << endl;
    cout << "  " << count_i << " i's and I's" << endl;
    cout << "  " << count_o << " o's and O's" << endl;
    cout << "  " << count_u << " u's and U's" << endl;
    cout << "  " << count_spc << " whitespace characters" << endl;

    return 0;
}

// Exercise 5.12 : Modify our vowel - counting program so that it counts the number of
// occurrences of the following two - character sequences : ff, fl, and fi.
//
// Note: spec should make it clear if 'fff' is one count of 'ff' or two. Assume it counts for two.
// Also  note: assuming case-sensitivity, eg., that 'Fl' does not increase the count for 'fl'.
// Finally, we'll stop counting vowels, since the question doesn't say
// " ... so that it _also_ counts ...", as the previous question did.
int ex_5_12()
{
    string text;
    int count_ff = 0, count_fl = 0, count_fi = 0;

    cout << "Please enter some text." << endl;
    getline(cin, text);
    for (auto iter = text.cbegin(); iter != text.end() - 1; // text.end() - 1 because if you're on the last char,
                                                            // there's no need to check the next one.
        ++iter)  
    {
        if (*iter == 'f')
        {
            switch (*(iter + 1))
            {
            case ('f'):
                ++count_ff;
                break;
            case ('l'):
                ++count_fl;
                break;
            case ('i'):
                ++count_fi;
                break;
            }
        }
    }

    cout << "That text had " << endl;
    cout << "  " << count_ff << " occurences of 'ff'" << endl;
    cout << "  " << count_fl << " occurences of 'fl'"  << endl;
    cout << "  " << count_fi << " occurences of 'fi'"  << endl;

    return 0;
}

// Exercise 5.13 : Each of the programs in the highlighted text on page 184 contains a
// common programming error.Identify and correct each error.
//
// ANSWERS below. Only corrected code shown.
char next_text() { return 'a'; }
unsigned some_value() { return '7'; }
int get_num() { return '4'; }
unsigned get_bufCnt() { return 100; }
int ex_5_13()
{
    // (a) No break statements. Correct code is:
    {
        unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
        char ch = next_text();
        switch (ch)
        {
        case 'a': 
            aCnt++;
            break;                      // Original code doesn't have this.
        case 'e':
            eCnt++;
            break;                      // Original code doesn't have this.
        default: iouCnt++;
        }
    }

    // (b)
    {
        vector<int> ivec(10);
        unsigned index = some_value();
        int ix;                         // [1] Added to correct (b).
        switch (index) {
        case 1:
            // int ix = get_value();    // Error here. If we don't have the case 1, then code jumps to `default`
                                        // where ix is used without having gone through here, ie., without having 
                                        // been initialised.
                                        // Correction below.
            ix = get_value();           // Code now compiles with the addition of line [1] and this one.
            ivec[ix] = index;
            break;
        default:
            ix = ivec.size() - 1;
            ivec[ix] = index;
        }
    }

    // (c) Not the right syntax for stacking cases. We don't use commas in C++. Also, a couple of typos.
    {
        unsigned evenCnt = 0, oddCnt = 0;
        int digit = get_num() % 10;
        switch (digit) {
        // case 1, 3, 5, 7, 9:              // Wrong syntax.
        case 1: case 3: case 5: case 7: case 9:
            // oddcnt++;                        // Typo.
            oddCnt++;
            break;
        // case 2, 4, 6, 8, 10:                 // Wrong syntax.
        case 2: case 4: case 6: case 8: case 10:
            // evencnt++;                       // Typo.
            evenCnt++;
            break;
        }
    }

    // (d)
    {
        // unsigned ival = 512, jval = 1024, kval = 4096;   // Must be const and known at compile-time 
                                                            // if we want to use these as cases in a switch statement.
                                                            // So make them constexpr.
        constexpr unsigned ival = 512, jval = 1024, kval = 4096;

        unsigned bufsize;
        unsigned swt = get_bufCnt();
        switch (swt)
        {
        case ival:
            bufsize = ival * sizeof(int);
            break;
        case jval:
            bufsize = jval * sizeof(int);
            break;
        case kval:
            bufsize = kval * sizeof(int);
            break;
        }
    }

    // Note about (d). Remember that constexpr means known at compile-time, whereas const just means
    // read-only after creation during run-time. const is not sufficient for use in a switch case, as shown below.
    {
        unsigned input;
        cin >> input;

        const unsigned ival{ input };   // Not known at compile time, 
                                        // but is read-only after having been created and initialised during run-time.
        unsigned swt = get_bufCnt();
        switch (swt)
        {
        // case ival:                   // Does not compile if uncommented.
            break;
        }
    }

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.4.1, The `while` Statement
// p185.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.14: Write a program to read strings from standard input looking for duplicated words.
// The program should find places in the input where one word is followed immediately by itself.
// Keep track of the largest number of times a single repetition occurs and which word is repeated.
// Print the maximum number of duplicates, or
// else print a message saying that no word was repeated. For example, if the input is
// 
// how now now now brown cow cow
// 
// the output should indicate that the word now occurred three times.
int ex_5_14()
{
    string prev_word = "";
    string word;
    string most_consec_duplicated_word = "";
    unsigned longest_run = 1;
    unsigned current_run = 1;

    while (cin >> word)
    {
        if (word == prev_word)
        {
            ++current_run;
            if (current_run > longest_run)
            {
                longest_run = current_run;
                most_consec_duplicated_word = word;
            }
        }
        else
            current_run = 1;

        prev_word = word;
    }

    if (longest_run > 1)
        cout
            << "The longest run of consecutive duplications was for: '" << most_consec_duplicated_word
            << "', which occurred " << longest_run << " times in a row." << endl;
    else
        cout << "No word was repeated immediately after iteself." << endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.4.2, Traditional `for` Statement
// p188.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.15: Explain each of the following loops. Correct any problems you detect.
// (a)  for (int ix = 0; ix != sz; ++ix) { /* ... */ }
//      if (ix != sz)
//          // ...
// 
// ANSWER:  ix is out of scope at the if() check. Define ix before the `for` loop to correct.
// 
// (b)  int ix;
//      for (ix != sz; ++ix) { /* ... */ }
// 
// ANSWER:  There is no initialisation statement in the `for()` statement.
//          To correct: put a null statement at the beginning of the statement.
// 
//          Also, ix is undefined if this is within a function. Initialise it to 0.
// 
// (c)  for (int ix = 0; ix != sz; ++ix, ++sz) { /* ... */ }
//
// ANSWER:  ix and sz are both being increased by 1 through each pass of the loop: ix will never "catch up" with sz.
//          We have an infinite lop.
//          Not clear what the intention was here, but --sz might be correct, under certain circumstances.

// Exercise 5.16: The while loop is particularly good at executing while some condition
// holds; for example, when we need to read values until end - of - file.The for loop is
// generally thought of as a step loop : An index steps through a range of values in a
// collection.Write an idiomatic use of each loop and then rewrite each using the other
// loop construct.If you could use only one loop, which would you choose ? Why ?
int ex_5_16()
{
    // Idiomatic use of for loop.
    vector<int> v{ 1, 5, 2 };
    int sum = 0;
    for (int i = 0; i != v.size(); ++i)
        sum += v[i];
    cout << "Sum using idiomatic for loop: " << sum << endl;

    // Replicated using while loop.
    int i = 0;
    sum = 0;
    while (i != v.size())
    {
        sum += v[i];
        ++i;
    }
    cout << "Sum using while loop to mimic for loop: " << sum << endl << endl;

    // Idiomatic use of while loop.
    // Find sum of elements of v up until but not including the first even number.
    auto iter = v.cbegin();
    sum = 0;
    while ((iter != v.cend()) && (*iter % 2 == 1))
    {
        sum += *iter;
        ++iter;
    }
    cout << "Sum of the odd numbers that v starts with, using while loop: " << sum << endl << endl;

    // For loop to mimic while loop.
    cout << "Please enter some numbers." << endl;
    sum = 0;
    for (auto iter2 = v.cbegin(); (iter2 != v.cend()) && (*iter2 % 2 == 1); ++iter2)
        sum += *iter2;

    cout << "Sum of the odd numbers that v starts with, using for loop: " << sum << endl << endl;

    // In general, can easily convert between these two:
    //
    //      initialise counter
    //      while (condition)
    //      {     
    //          loop action;
    //          update counter (doesn't necessarily have to be increment).
    //      }
    //
    // ... and 
    //
    //      for (initialise counter; condition; update counter)
    //          loop action;
    //
    // If I could only choose one, I would choose the while loop, because the order of the 
    // initialise / condition / action / update statements is more intuitive.
    return 0;
}

// Exercise 5.17 : Given two vectors of ints, write a program to determine whether
// one vector is a prefix of the other. 
// For vectors of unequal length, compare the number of elements of the smaller 
// vector. For example, given the vectors containing 
// {0, 1, 1, 2}           and 
// {0, 1, 1, 2, 3, 5, 8}, respectively your program should return true.
int ex_5_17()
{
    vector<int> v1{ 0, 1, 1, 2 };
    vector<int> v2;
    string s;
    int i;
    
    cout << "First vector is {0, 1, 1, 2}." << endl;
    cout << "Please enter the second vector." << endl;
    while (cin >> i)
        v2.push_back(i);

    int smaller_size = v1.size() < v2.size() ? v1.size() : v2.size();
    bool is_prefix = true;
    
    for (int i = 0; i < smaller_size; ++i)
    {
        if (v1[i] != v2[i])
        {
            is_prefix = false;
            break;
        }
    }

    string result = is_prefix ? "is " : "is not ";
    cout << "One vector " << result << "a prefix of the other." << endl;

    return is_prefix;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.4.4, The `do while` Statement
// p190.
// --------------------------------------------------------------------------------------------------------------------
// Exercise 5.18: Explain each of the following loops.Correct any problems you detect.
// (a)  do
//          int v1, v2;
//          cout << "Please enter two numbers to sum:";
//          if (cin >> v1 >> v2)
//          cout << "Sum is: " << v1 + v2 << endl;
//      while (cin);
// 
// ANSWER: no braces between `do` and `while`.
// 
// (b)  do {
//          // . . .
//      } while (int ival = get_response());
// 
// ANSWER: cannot declare in a `do` condition.
// 
// (c)  do {
//          int ival = get_response();
//      } while (ival);
//  
// ANSWER: `ival` has to be defined before the loop begins. As written, it is out of scope in the `while` condition.
int get_response() { return 0; }
int ex_5_18()
{
    // (b)
    {
        do {
            // . . .
        // } while (int ival = get_response());      // Compiler errors:- type name not allowed (when hovering over `int`).
                                                     //                 - Expected a ')' (hovering over `ival`).
        } while (false);                             // Comment this and uncomment previous line to see compiler error.
    }

    // (c)
    {
        do {
            int ival = get_response();
            // } while (ival);                      // Compiler error: identifier 'ival' is undefined.
        } while (false);                            // Comment this and uncomment previous line to see compiler error.
    }

    return 0;
}

// Exercise 5.19: Write a program that uses a dowhileloop to repetitively request two
// strings from the user and report which stringis less than the other.
int ex_5_19()
{
    string s1, s2;
    do
    {
        cout << "Please enter string 1, or 'x' to exit: "; getline(cin, s1);
        cout << "Please enter string 2, or 'x' to exit: "; getline(cin, s2);
        cout << endl;

        int s1_is_bigger = s1.compare(s2);
        switch (s1_is_bigger)
        {
        case 0: 
            cout << "The two strings are the same." << endl;
            break;
        case -1:
            cout << "String 1 is smaller (lexically)." << endl;
            break;
        case 1:
            cout << "String 1 is larger (lexically)." << endl;
            break;
        }
        cout << endl << endl;
    } while ((s1 != "x") && (s2 != "x"));
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.5.1, The `break` Statement
// p191.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.20: Write a program to read a sequence of strings from the standard input
// until either the same word occurs twice in succession or all the words have been read.
// Use a while loop to read the text one word at a time. 
// Use the break statement to terminate the loop if a word occurs twice in succession.
// Print the word if it occurs twice in succession, or else print a message saying that no word was repeated.
int ex_5_20()
{
    string word;
    string prev_word = "";
    bool duplicated_found = false;

    cout << "Please enter some words, finishing with ^Z." << endl;
    while (cin >> word)
    {
        if (word == prev_word)
        {
            duplicated_found = true;
            break;
        }
        else
            prev_word = word;
    }
    
    if (duplicated_found)
        cout << "You entered '" << word << "' twice in a row!" << endl;
    else
        cout << "You didn't enter any word twice in succession." << endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.5.2, The `continue` Statement
// p192.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.21: Revise the program from the exercise in § 5.5.1 (p. 191) so that it looks
// only for duplicated words that start with an uppercase letter.
//
// Note: I think this means ignore all words that don't start with an uppercase letter, so
// -    "A b A" will print "A"
// -    "A B A" will print no repeats.
int ex_5_21()
{
    string word;
    string prev_word = "";
    bool duplicated_found = false;

    cout << "Please enter some words, finishing with ^Z." << endl;
    while (cin >> word)
    {
        if (word == prev_word)
        {
            duplicated_found = true;
            break;
        }
        if (isupper(word[0]))
        {
            prev_word = word;
            continue;
        }
    }

    if (duplicated_found)
        cout << "You entered '" << word << "' twice in a row!" << endl;
    else
        cout << "You didn't enter any word starting with an uppercase character twice in succession." << endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.5.3, The `goto` Statement
// p193.
// --------------------------------------------------------------------------------------------------------------------

//Exercise 5.22: The last example in this section that jumped back to begin could be
//better written using a loop.Rewrite the code to eliminate the goto.
int get_size() { return (rand() % 2) == 1 ? 1 + rand() % 10 : -1 - rand() % 10; } // Just a func to give random numbers
int ex_5_22()
{
    // Seed rand
    srand(time(NULL));

    // Original code
begin:
    int sz = get_size();
    if (sz <= 0)
    {
        cout << sz << " ";
        goto begin;
    }
    else
        cout << sz << endl;

    // Code without goto
    cout << endl << endl;

    int sz2 = -1;
    while (sz2 <= 0)
    {
        cout << sz2 << " "; // We do print an extra -1 at the beginning, which the original code doesn't.
                            // But the final result is the same: repeat get_size() until it gives a +ve number.
        sz2 = get_size();
    }
    cout << sz2 << endl; 
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 5.6.3, Standard Exceptions
// p198.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 5.23: Write a program that reads two integers from the standard input and
// prints the result of dividing the ﬁrst number by the second.
int ex_5_23()
{
    int i1, i2;

    cout << "Please enter two integers." << endl;
    cin >> i1 >> i2;
    
    cout << i1 / i2 << endl; // Error checking will be added later.
    return 0;
}

// Exercise 5.24 : Revise your program to throw an exception if the second number is
// zero. Test your program with a zero input to see what happens on your system if you
// don’t catchan exception.
int ex_5_24()
{
    int i1, i2;

    cout << "Please enter two integers." << endl;
    cin >> i1 >> i2;

    if (i2 == 0)
        throw std::runtime_error("Divisor cannot be zero.");
    
    cout << i1 / i2 << endl; // Don't need an else: we have already exit the function if i2 == 0;

    return 0;
}

// Exercise 5.25 : Revise your program from the previous exercise to use a tryblock to
// catch the exception.The catch clause should print a message to the user and ask
// them to supply a new number and repeat the code inside the try.
int ex_5_25()
{
    int i1, i2;

    cout << "Please enter two integers." << endl;
    while (cin >> i1 >> i2)
    {
        try
        {
            // It seems a bit weird to have to throw this error manually, but actually
            // division by zero is not an error in C++: it's undefined behaviour. See:
            // https://stackoverflow.com/questions/30898013/exception-catching-for-int-divided-by-0
            if (i2 == 0)
                throw std::runtime_error("Divisor cannot be zero.");

            cout << i1 / i2 << endl;
        }
        catch (std::runtime_error err)
        {
            cout << err.what() << endl;
            cout << "Try again? Enter Y or N" << endl;
            char c;
            if (!(cin >> c) || toupper(c) == 'N')
                break;                                // Out of while loop right up top.
        }
    }
    return 0;
}

int main()
{
    return ex_5_25();
}


int ex_5_()
{
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 
// p
// --------------------------------------------------------------------------------------------------------------------

