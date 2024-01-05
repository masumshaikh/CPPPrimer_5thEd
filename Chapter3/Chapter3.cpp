// Chapter3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip> // Not required for this chapter. I added it to use std::setw() in the exercises on 2d arrays.
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 3.1, Namespace `using` Declarations.
// p83.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.1: Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.
//
// Answer: can't be bothered. Cliff notes version:
// - Add `using std::blah` at the top of a .cpp file.
// - In the code, change `std::blah` to `blah`.
// - Do this for every name `blah`, ie., separate `using` statements for std::cout and std::cin.
// - DON'T put `using` in .h files!


// --------------------------------------------------------------------------------------------------------------------
// Exercises Section 3.2.2, Operations on `string`s.
// p90.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.2: Write a program to read the standard input a line at a time.
// Modify your program to read a word at a time.
int ex_3_2_line_at_a_time()
{
    std::cout
        << "Please input some lines so that I can repeat them back to you!" << std::endl
        << "You can enter ctrl-Z to exit." << std::endl
        << std::endl;
    
    std::string line;
    while (getline(std::cin, line)) 
        std::cout << "You just input: '" << line << "'!" << std::endl << std::endl;
    return 0;
}

int ex_3_2_word_at_a_time()
{
    std::cout
        << "Please input some words so that I can repeat them back to you!" << std::endl
        << "You can enter ctrl-Z to exit." << std::endl
        << std::endl;

    std::string word;
    while (std::cin >> word)
        std::cout << word << " ";
    return 0;
}

// Exercise 3.3 : Explain how whitespace characters are handled in the string
// input operator and in the getline function.
//
// Answer: The string input operator is this one:
// `std::cin >> s`
// It reads and discards any leading whitespace(e.g., spaces, newlines, tabs).
// It then characters until the next whitespace character is encountered.
//
// The `getline()` function consumes everything including whitespace up until,
// but not including, the first newline. It then returns this.

// Exercise 3.4 : Write a program to read two strings and report whether the
// strings are equal. If not, report which of the two is larger. Now, change
// the program to report whether the strings have the same length, and if
// not, report which is longer.

int ex_3_4()
{
    std::string s1, s2;
    std::cout << "Please enter first string.  ";  getline(std::cin, s1);
    std::cout << "Please enter second string. "; getline(std::cin, s2);

    // First part.
    if (s1 == s2)
        std::cout << "The two strings are equal." << std::endl;
    else
        std::cout << "String " << (s1 > s2 ? "s1" : "s2") << " is larger (lexically)." << std::endl;

    // Second part.
    if (s1.size() == s2.size())
        std::cout << "The two strings are of equal length." << std::endl;
    else
        std::cout << "String " << (s1.size() > s2.size() ? "s1" : "s2") << " is Longer." << std::endl;

    return 0;
}

// Exercise 3.5 : Write a program to read strings from the standard input,
// concatenating what is read into one large string. Print the concatenated
// string. Next, change the program to separate adjacent input strings by a space.
int ex_3_5()
{
    std::cout << "Please enter some strings." << std::endl;
    std::string s;
    std::string without_spaces;
    std::string with_spaces;
    
    while (std::cin >> s)
    {
        without_spaces += s;        // Concatenate to one large string.
        with_spaces += " " + s;     // Concatenate including spaces.
    }

    std::cout << "Concatenated without spaces: " << without_spaces << std::endl;
    std::cout << "Concatenated with spaces:    " << with_spaces    << std::endl;

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.2.3
// p96.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.6: Use a range for to change all the characters in a string to X.
int ex_3_6()
{
    string s;
    std::cout << "Please enter some words." << std::endl;
    getline(std::cin, s);

    for (char& c : s)   // We iterate over a string using the `char` type. Equivalent to using `auto`.
    {                   // We use a reference so that each c really is that character in the string, not a copy.
        c = 'X';

        // c = "X"      // A common mistake is to pass the letter in double quotes.
                        // But that's a string literal, which is an array of `char`s, not a `char`. 
                        // Hence the compiler error:
                        // A value of type const char* cannot be assigned to an entity of type char.
                        // 
                        // Here, the `const char*` is actually the array of `char`s representing "X"
                        // (C-style arrays are actually pointers with pointer arithmetic), 
                        // whereas c is a char.
    }

    std::cout << "Your string, with all characters changed to 'X', is: " << s << std::endl;
    return 0;
}

// Exercise 3.7 : What would happen if you define the loop control variable in the previous exercise as type char ?
// Predict the results and then change your program to use a
// char to see if you were right.
int ex_3_7()
{
    string s;
    std::cout << "Please enter some words." << std::endl;
    getline(std::cin, s);

    for (char c : s)    // Note that we are iterating over `char`s, not references to `char`.
    {                   // c is thus a copy of the current char, not the actual one in `s`.

        c = 'X';        // We're currently on some `char` in `s`.
                        // We copied it to this variable `c`.
                        // And now we're changing `c`. The original `char` in `s` is unchanged.
                        // 
                        // Prediction: when we print `s`, it will be unchanged.
    }

    std::cout << std::endl;
    std::cout << "Your string is: " << s << std::endl;
    std::cout << "Indeed, the characters have not been changed to 'X'" << std::endl;
    return 0;
}

// Exercise 3.8 : Rewrite the program in the first exercise, first using a while and again
// using a traditional for loop. Which of the three approaches do you prefer and why ?
int ex_3_8()
{
    string s;
    std::cout << "Please enter some words." << std::endl;
    getline(std::cin, s);

    // While loop.
    int i = 0;
    while (i < s.size())
    {
        s[i] = 'X';
        i++;
    }
    std::cout << std::endl << "Your 'X' string is: " << s << std::endl;

    // For loop. We change to a different letter instead of 'X', to make sure we did something.
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = 'Y';
        i++;
    }
    std::cout << std::endl << "Your 'Y' string is: " << s << std::endl;

    // Which of these approaches do you prefer?
    // Answer: obviously, the `range for` construct.
    return 0;
}

// Exercise 3.9 : What does the following program do ? Is it valid ? If not, why not?
int ex_3_9()
{
    string s;
    std::cout << s[0] << std::endl; // This compiles and runs in Visual Studio, but is not valid.

    // In general, s[size()] compiles and runs in Visual Studio 2019, but the result is undefined by the standard.
    // Visual Studio has an additional quirk in that it does warn you when trying to access the NEXT one.
    // That is, the one after s[s.size()].
    std::cout << "0"[1] << std::endl;   // s[s.size()]     Compiles and runs in Visual Studio with no issues.
    std::cout << "0"[2] << std::endl;   // s[s.size() + 1] Compiles and runs also.
                                        // But you do get an out-of-range warning from Visual Studio.
                                        // Reading invalid data from "0".
    return 0;
}

// Exercise 3.10: Write a program that reads a string of characters including punctuation
// and writes what was read but with the punctuation removed.
int ex_3_10()
{
    // Method 1.
    string s;
    std::cout << "Method 1: please enter some words." << std::endl;
    getline(std::cin, s);

    for (auto& c : s)
    {                 
        if (ispunct(c))
            c = '\0';
    }

    std::cout << std::endl;
    std::cout << "Your string is: " << s << std::endl;

    // Note: the above solution doesn't really remove the characters; it just changes them to the null character.
    // We can check that the length of the string is unchanged:
    std::cout << "Its length: " << s.size() << std::endl;

    // A possibly better solution is to remove each character that is a punctuation, but 
    // in a `range for` loop, you shouldn't change the thing you're iterating over (see later).
    // In Method 2, we build up the final string, excluding each character that is a punctuation
    // and check the length at the end.

    // Method 2.
    std::cout << std::endl << "Method 2: please enter some words." << std::endl;
    getline(std::cin, s);
    string out_s;
    for (const auto& c : s) // We iterate using const because we're changing the chars in the original string s.
    {                       // We use references to save copying (not that it matters with things as small as chars).
        if (!ispunct(c))
            out_s += c;
    }

    std::cout << std::endl;
    std::cout << "Your string is: " << out_s << std::endl;
    std::cout << "Its length: " << out_s.size() << std::endl; // Correct length.

    // Method 3.
    // If we don't need to keep the final string, just print every char that's not a punct.
    std::cout << std::endl << "Method 3: directly using the last input." << std::endl;
    for (const auto& c : s)
        if (!ispunct(c))
            std::cout << c;
    return 0;
}

// Exercise 3.11 : Is the following range for legal ? If so, what is the type of c ?
int ex_3_11()
{
    const string s = "Keep out!";
    for (auto& c : s) { /* ... */ }   

    // Answer: the above is legal. Because we are iterating over a const string,
    // so each c is a const char& (reference to const char).
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.3.1
// p100.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.12: Which, if any, of the following vector definitions are in error ? For
// those that are legal, explain what the definition does. For those that are not legal,
// explain why they are illegal.
int ex_3_12()
{
    // (a)
    vector<vector<int>> ivec;           // Legal: ivec is a vector, each element of which is a vector of `int`s.
                                        // (Commonly used to represent "jagged arrays").

    // (b)
    // vector<string> svec = ivec;      // Not legal. ivec is clearly not compatible with a vector containing strings!

    // (c)
    vector<string> svec(10, "null");    // Legal. svec is a vector of 10 elements,
                                        // each of which is a string that says "null".
    return 0;
}

// Exercise 3.13: How many elements are there in each of the following vectors ? What
// are the values of the elements ?
int ex_3_13()
{
    
    // (a)
    vector<int> v1;                 // Zero elements.

    // (b)
    vector<int> v2(10);             // Constructor initialisation. 10 elements, all zero.

    // (c)
    vector<int> v3(10, 42);         // Constructor initialisation. 10 elements, all 42.

    // (d)
    vector<int> v4{ 10 };           // List initialisation. 1 element, an `int` equal to 10.

    // (e)
    vector<int> v5{ 10, 42 };       // List initialisation. 2 elements, 10 and 42.

    // (f)
    vector <string> v6{ 10 };       // Constructor initialisation. 10 elements, all empty strings.
                                    // List initialisation doesn't work, as 10 is not a string.
                                    // So we fall back to constructor initialisation.

    // (g)
    vector<string> v7{ 10, "hi" };  // Constructor initialisation. 10 elements, all "hi".
                                    // List initialisation doesn't work, as 10 is not a string.
                                    // So we fall back to constructor initialisation.

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.3.2
// p102.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.14: Write a program to read a sequence of ints from cin and store those
// values in a vector.
int ex_3_14()
{
    int elem;
    vector<int> vec;

    std::cout << "Please input some numbers, finishing with ^Z to show taht you're done." << std::endl;
    while (std::cin >> elem)
        vec.push_back(elem);

    // Check to see we did it right.
    std::cout << "The numbers you input are ..." << std::endl;
    for (const auto& elem : vec)
        std::cout << elem << " ";
    std::cout << std::endl;
    return 0;
}

// Exercise 3.15 : Repeat the previous program but read strings this time
int ex_3_15()
{
    // These are the only two lines we have to change.
    string elem;
    vector<string> vec;

    std::cout << "Please input some words, finishing with ^Z to show that you're done." << std::endl;
    while (std::cin >> elem)
        vec.push_back(elem);

    // Check to see we did it right.
    std::cout << "The words you input are ..." << std::endl;
    for (const auto& elem : vec)
        std::cout << elem << " ";
    std::cout << std::endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.3.3
// p105.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.16: Write a program to print the size and contents of the vectors from exercise 3.13.
// Check whether your answers to that exercise were correct. If not, restudy
// § 3.3.1 (p. 97) until you understand why you were wrong.
int ex_3_16()
{
    // (a)
    vector<int> v1;
    std::cout << std::endl;
    std::cout << "vector<int> v1;" << std::endl;
    std::cout << "Size: " << v1.size() << std::endl;
    std::cout << "Elements: ";
    for (const auto& elem : v1)
        std::cout << elem << " ";
    std::cout << std::endl;

    // (b)
    vector<int> v2(10);
    std::cout << std::endl;
    std::cout << "vector<int> v2(10);" << std::endl;
    std::cout << "Size: " << v2.size() << std::endl;
    std::cout << "Elements: ";
    for (const auto& elem : v2)
        std::cout << elem << " ";
    std::cout << std::endl;

    // (c)
    vector<int> v3(10, 42);
    std::cout << std::endl;
    std::cout << "vector<int> v3(10, 42);" << std::endl;
    std::cout << "Size: " << v3.size() << std::endl;
    std::cout << "Elements: ";
    for (const auto& elem : v3)
        std::cout << elem << " ";
    std::cout << std::endl;

    // (d)
    vector<int> v4{ 10 };
    std::cout << std::endl;
    std::cout << "vector<int> v4{ 10 };" << std::endl;
    std::cout << "Size: " << v4.size() << std::endl;
    std::cout << "Elements: ";
    for (const auto& elem : v4)
        std::cout << elem << " ";
    std::cout << std::endl;

    // (e)
    vector<int> v5{ 10, 42 };
    std::cout << std::endl;
    std::cout << "vector<int> v5{ 10, 42 };" << std::endl;
    std::cout << "Size: " << v5.size() << std::endl;
    std::cout << "Elements: ";
    for (const auto& elem : v5)
        std::cout << elem << " ";
    std::cout << std::endl;

    // (f)
    vector <string> v6{ 10 };
    std::cout << std::endl;
    std::cout << "vector <string> v6{ 10 };" << std::endl;
    std::cout << "Size: " << v6.size() << std::endl;
    std::cout << "Elements: ";
    for (const auto& elem : v6)
        std::cout << elem << " ";
    std::cout << std::endl;


    // (g)
    vector<string> v7{ 10, "hi" };
    std::cout << std::endl;
    std::cout << "vector<string> v7{ 10, \"hi\" };" << std::endl;
    std::cout << "Size: " << v7.size() << std::endl;
    std::cout << "Elements: ";
    for (const auto& elem : v7)
        std::cout << elem << " ";
    std::cout << std::endl;

    // If only there were a way that we could avoid having to rewrite the same code so many times 
    // and just use some sort of template...
    return 0;
}

// Exercise 3.17 : Read a sequence of words from cin and store the values a vector.
// After you’ve read all the words,
// process the vector and change each word to uppercase.
// Print the transformed elements, eight words to a line.
int ex_3_17()
{
    std::cout << "Please input some words, finishing with ^Z to show that you're done." << std::endl;
    string s;
    vector<string> words;
    while (std::cin >> s)
        words.push_back(s);

    for (auto& word : words) // We're going to be changing the words, so use references, and don't use const.
        for (auto& c : word) // Ditto.
            c = toupper(c);

    std::cout << std::endl << "Your words in upper case are:" << std::endl;
    int idx = 0;
    for (const auto& word : words)
    {
        std::cout << word << " ";
        if (idx == 8)
        {
            std::cout << std::endl;
            idx = 0;
        }
        idx++;
    }
    return 0;
}

// Exercise 3.18 : Is the following program legal ? If not, how might you fix it ?
int ex_3_18()
{
    vector<int> ivec;
    // ivec[0] = 42;    // Will compile, but it's not good. ivec[0] doesn't exist yet.
    ivec.push_back(42); // This is the correct version.

    return 0;
}

// Exercise 3.19: List three ways to define a vector and give it ten elements, each with
// the value 42. Indicate whether there is a preferred way to do so and why.
int ex_3_19()
{
    vector<int> v1(10, 42);         // Constructor initialisation. Best method when all elements the same.
    
    vector<int> v2;                 
    for (int i = 0; i < 10; i++)
        v2.push_back(42);           // No point doing this loop when all elements are the same.
                                    // But useful method when the elements need to be different.
    
    vector<int> v3{ 42, 42, 42, 42, 42, 42, 42, 42, 42, 42 }; // Pretty rubbish.

    return 0;
}

// Exercise 3.20 : Read a set of integers into a vector. Print the sum of each pair of
// adjacent elements. Change your program so that it prints the sum of the first and last
// elements, followed by the sum of the second and second - to - last, and so on.
int ex_3_20()
{
    std::cout << "Please input some numbers, finishing with ^Z to show that you're done." << std::endl;
    int i;
    vector<int> numbers;
    while (std::cin >> i)
        numbers.push_back(i);
    std::cout << std::endl;
    
    if (numbers.size() == 0)
    {
        std::cerr << "You didn't enter any numbers!" << std::endl;
        return -1;
    }

    // Print the sum of each pair of adjacent elements.
    // Note: Specification is unclear if "each pair of adjacent elements" means to include overlaps or not.
    // If the numbers are 1, 2, 3, 4 -- do we output 1+2 and 3+4, or 1+2, 2+3, and 3+4?
    // I chose the former, as it requires a little bit more thought.
    std::cout << "Sums of adjacent pairs: " << std::endl;
    for (
        decltype(numbers.size()) i = 0; // See https://stackoverflow.com/questions/43006863/when-do-you-require-to-use-decltype-in-c
        i < numbers.size();
        i += 2
        )
        
    {
        if (i == numbers.size() - 1)    // We have an odd number of elements, and this is the last one.
                                        // numbers[i+1] will give an error.
            std::cout << numbers[i] << " ";
        else
            std::cout << numbers[i] + numbers[i + 1] << " ";
    }

    // Sum of the first and last elements, followed by the sum of the second and second - to - last, and so on.
    // Note: The specification is unclear here as well: if we have an odd number of entries, eg: {1, 2, 3}
    // is the middle number added to itself, or left as it is because there is nothing to add to it?
    // That is, do we output 1+3 and 2+2, or 1+3 and 2?
    // Again, I chose the one that requires a bit more thought.
    std::cout << std::endl;
    std::cout << "Sums of pairs working inwards: " << std::endl;
    for (decltype(numbers.size()) i = 0;    // See https://stackoverflow.com/questions/43006863/when-do-you-require-to-use-decltype-in-c
        i <= numbers.size() / 2;            // Note the <=. We need this to catch the middle number 
                                            // when we have an odd number of entries. But see [1] below.
        i++
        )
    {
        if (i == numbers.size() - i - 1)
            std::cout << numbers[i] << " ";
        else if (i < numbers.size() - i - 1)    // [1] But then we have to make sure we don't print the sum of the middle pair twice,
                                                // when we have an even number of entries.
            std::cout << numbers[i] + numbers[numbers.size() - i - 1] << " ";
    }
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.4.1
// p110.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.21: Redo the first exercise from § 3.3.3 (p. 105) using iterators.
// I didn't follow-up on my tongue-in-cheek comment about templates, since they haven't been covered yet :-)
int ex_3_21()
{
    // (a)
    vector<int> v1;
    std::cout << std::endl;
    std::cout << "vector<int> v1;" << std::endl;
    std::cout << "Size: " << v1.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = v1.cbegin(); it != v1.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    // (b)
    vector<int> v2(10);
    std::cout << std::endl;
    std::cout << "vector<int> v2(10);" << std::endl;
    std::cout << "Size: " << v2.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = v2.cbegin(); it != v2.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    // (c)
    vector<int> v3(10, 42);
    std::cout << std::endl;
    std::cout << "vector<int> v3(10, 42);" << std::endl;
    std::cout << "Size: " << v3.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = v3.cbegin(); it != v3.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    // (d)
    vector<int> v4{ 10 };
    std::cout << std::endl;
    std::cout << "vector<int> v4{ 10 };" << std::endl;
    std::cout << "Size: " << v4.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = v4.cbegin(); it != v4.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    // (e)
    vector<int> v5{ 10, 42 };
    std::cout << std::endl;
    std::cout << "vector<int> v5{ 10, 42 };" << std::endl;
    std::cout << "Size: " << v5.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = v5.cbegin(); it != v5.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    // (f)
    vector <string> v6{ 10 };
    std::cout << std::endl;
    std::cout << "vector <string> v6{ 10 };" << std::endl;
    std::cout << "Size: " << v6.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = v6.cbegin(); it != v6.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;


    // (g)
    vector<string> v7{ 10, "hi" };
    std::cout << std::endl;
    std::cout << "vector<string> v7{ 10, \"hi\" };" << std::endl;
    std::cout << "Size: " << v7.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = v7.cbegin(); it != v7.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}

// Code example on p110: Code to print each line in text up to the first blank line:
int code_example_p110()
{
    vector<string> text = { "Hello world", "", "This is some text."}; 

    // Prints out "Hello world" only.
    for (auto it = text.cbegin(); it != text.cend() && !it->empty(); ++it)
        std::cout << *it << std::endl;

    return 0;
}

// Exercise 3.22 : Revise the loop that printed the first paragraph in `text` to instead
// change the elements in `text` that correspond to the first paragraph to all uppercase.
// After you’ve updated `text`, print its contents.
int ex_3_22()
{
    vector<string> text = { "Hello world", "", "This is some text." };

    for (auto it = text.cbegin(); it != text.cend() && !it->empty(); ++it)
        for (auto c : *it)
            // std::cout << toupper(c) ;    // This just prints out a bunch of char codes.
            std::cout << (char)toupper(c);  // You need tocast to `char`.
                                            // The cast was done implicitly in Ex 3.17.

    return 0;
}

// Exercise 3.23 : Write a program to create a vector with ten int elements. Using an
// iterator, assign each element a value that is twice its current value.Test your program
// by printing the vector.
int ex_3_23()
{
    vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (auto it = v.begin(); it != v.end(); it++)
        *it *= 2;

    for (auto num : v)
        std::cout << num << " ";

    std::cout << std::endl;
    return 0;
}

// We test the warning on p110. The warning is:
// It is important to realize that loops that use iterators should not
// add elements to the container to which the iterators refer.
int test_warning_p110()
{
    vector<int> v{ 1, 2, 3};

    for (auto it = v.begin(); it != v.end(); it++) // Runtime error here on the iteration after the push_back(18).
    {
        *it *= 2;
        if (*it == 4)
            v.push_back(18);
    }

    for (auto num : v)
        std::cout << num << " ";

    std::cout << std::endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.4.2, Iterator Arithmetic
// p113.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.24: Redo the last exercise from § 3.3.3 (p. 105) using iterators.
// Read a set of integers into a vector.Print the sum of each pair of
// adjacent elements. Change your program so that it prints the sum of the first and last
// elements, followed by the sum of the second and second - to - last, and so on.
int ex_3_24()
{
    std::cout << "Please input some numbers, finishing with ^Z to show that you're done." << std::endl;
    int i;
    vector<int> numbers;
    while (std::cin >> i)
        numbers.push_back(i);
    std::cout << std::endl;

    if (numbers.size() == 0)
    {
        std::cerr << "You didn't enter any numbers!" << std::endl;
        return -1;
    }
    
    // Print the sum of each pair of adjacent elements.
    // Same note re. unclear specificaiton as before.
    std::cout << "Sums of adjacent pairs: " << std::endl;
    for (auto it = numbers.cbegin(); it != numbers.cend(); it += 2)
    {
        if (it == numbers.cend() - 1)    // We have an odd number of elements, and this is the last one.
        {                               // *(i+1) will give an error.
            std::cout << *it << " ";
            break;                      // THIS IS DIFFERENT to the last solution.
                                        // When i was an int, we could add two to it with no issues:
                                        // we just skipped past the body of the loop to finish it.
                                        // Now that it is an iterator, we can't add 2 to it, because an iterator
                                        // can't point past the end of the collection. 
                                        // So we manually break out of the loop before we get that far.
        }
        else
            std::cout << *it + *(it + 1) << " ";
    }

    // Sum of the first and last elements, followed by the sum of the second and second - to - last, and so on.
    // Same note as previous exercise re. unclear spec.
    std::cout << std::endl;
    std::cout << "Sums of pairs working inwards: " << std::endl;
    auto mid = numbers.cbegin() + numbers.size() / 2;
    for (auto it = numbers.cbegin(); it != mid + 1; it++)
    {
        // When using subscripts, the subscript for the "number on the other side" was:
        // numbers.size() - 1 - i
        // See the next function to see where the next line came from.
        auto right_position = numbers.cbegin() + (numbers.cend() - it - 1);
        if (it == right_position)
            std::cout << *it << " ";
        else if (it < right_position)  
            std::cout << *it + *right_position << " ";
    }
    return 0;
}

// Explanation for the calculation of right_position above
int explanation_of_3_24()
{
    // Set up some stuff for testing.
    vector<int> v{ 1, 2, 3, 4, 5 };
    unsigned int i = 1;
    auto beg = v.cbegin();
    auto end = v.cend();
    auto it = beg + i;

    // Suppose we have an iterator `it` that is pointing to index `i` in the vector `v`.
    // This means that:
    //      `i == it - beg`, or equivalently,
    //      `it == beg + i.

    // The element "on the other side" of `i` is:
    std::cout << *(end - 1 - i) << std::endl;                       // ........[0]
    // Remember that the `-1` is required because `end` actually
    // points to one past the actual last element of the vector.
    
    // All of the expressions below correspond to the same thing.
    std::cout << v[v.size() - 1 - i] << std::endl; 

    // Now, end == beg + v.size(), and 
    // v.size() == (end - beg), so [0] becomes:
    std::cout << *(beg + (end - beg) - 1 - i) << std::endl;

    // `1` and `i` are just (unsigned) `int`s, so we can switch them round.
    std::cout << *(beg + (end - beg) - i - 1) << std::endl;

    // And we can use normal arithmetic manipulation to write this:
    std::cout << *(beg + (end - (beg + i) - 1)) << std::endl;

    // And finally, `it == beg + i`, to give:
    std::cout << *(beg + (end - it - 1)) << std::endl;              // ........[1]
    // This corresponds to our defintion of right_position:
    // auto right_position = numbers.cbegin() + (numbers.cend() - it - 1);

    // BUT!! Iterator/pointer arithmetic isn't exactly like normal arithmetic. The following rules apply.
    // 
    // (1): You can't add two iterators, so starting from [1], you can't write this:
    // std::cout << *(beg + end - it - 1)) << std::endl;
    //
    // (2): You can add or subtract an int from/to an iterator, but only if you don't exceed the bounds of the array.
    //      So you can't write, for example:
    // std::cout << *(beg - 1 + (end - it)) << std::endl;
    //      It compiles, but `beg - 1` gives a runtime out-of-bounds error.
    //      (C++ expressions are calculated from left to right).
    //
    // (3): You can subtract a iterator from an iterator, it - jt, but only if jt points to an element before it.
    //      You get something called a pointer_diff (pedantically, a `ptrdiff_t`): iterators are pointers.
    // 
    // (4): You can have an expression of the form "pointer + pointer_diff" (at least you can in that order:
    //      haven't yet tried "pointer_diff + pointer".

    // Note: you can use normal arithmetic with the above rule to also get to:
    std::cout << *(end - 1 - (it - beg)) << std::endl;

    // Proof: start from [0] again:
    std::cout << *(end - 1 - i) << std::endl;

    // Use i = it - beg:
    std::cout << *(end - 1 - (it - beg)) << std::endl;
    // Actually, that was a lot shorter. But I only figured it out while I was writing the above explanation,
    // which I will keep because I'm bound to forget (1) and (2).

    return 0;
}

// Exercise 3.25 : Rewrite the grade clustering program from § 3.3.3 (p. 104) using iterators instead of subscripts.
int ex_3_25()
{
    vector<unsigned int> v{ 42, 65, 95, 100, 39, 67, 95, 76, 88, 76, 83, 92, 76, 93 };
    vector<unsigned int> scores(11, 0);
    for (auto it_grade = v.cbegin(); it_grade != v.cend(); it_grade++)
        if (*it_grade <= 100)
            ++scores[*it_grade / 10];

    for (auto it_bucket = scores.cbegin(); it_bucket != scores.cend(); it_bucket++)
        std::cout << *it_bucket << " ";

    std::cout << std::endl;
    return 0;
}

// Exercise 3.26 : In the binary search program on page 112, why did we write mid = beg + (end - beg) / 2; 
// instead of mid = (beg + end) / 2; ?
int ex_3_26()
{
    // Some setup:
    vector<string> text{"Attacked", "By", "Crazy", "Delinquent", "Elephant"}; // text must be sorted
    string sought = "Crazy";

    // The code referred to in the question.
    // beg and end will denote the range we’re searching
    auto beg = text.begin(), end = text.end();
    auto mid = text.begin() + (end - beg) / 2; // original midpoint

    // while there are still elements to look at and we haven’t yet found sought
    while (mid != end && *mid != sought)
    {
        if (sought < *mid)              // is the element we want in the first half?
            end = mid;                  // if so, adjust the range to ignore the second half
        else                            // the element we want is in the second half
            beg = mid + 1;              // start looking with the element just after mid
        mid = beg + (end - beg) / 2;    // new midpoint
    }

    // ANSWER 
    // auto mid = (beg + end) / 2;      // Does not work because '+' is not overloaded for iterators
                                        // (ie., you can't add iterators.)
                                        // Also, even if you couldn't, `beg + end` would be evaluated first
                                        // and that's not a valid iterator as it's way past the end of the vector.
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.5.1, Defining and Initializing Built - in Arrays
// p115.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.27: Assuming txt_size is a function that takes no arguments and returns
// an int value, which of the following definitions are illegal ? Explain why.
int txt_size()
{
    return 0;
}

int ex_3_27()
{
    unsigned buf_size = 1024;

    // (a) 
    // int ia[buf_size];            // Not allowed: buf_size is not a `constexpr`.

    // (b)
    int ia[4 * 7 - 14];             // Allowed: the bit inside the square brackets is known at compile time.
    
    // (c)
    // int ia[txt_size()];          // Not allowed: txt_size() is not a `constexpr`.
    
    // (d)
    // char st[11] = "fundamental";// Not allowed; no room for the null terminator at the end.

    return 0;
}

// Exercise 3.28: What are the values in the following arrays ?
// ANSWER: same as for single strings and ints;
// - strings are always constructed as empty strings.
// - ints are initialised to zero outside of any function, undefined inside a function.
string sa[10];  // 10 empty strings.
int ia[10];     // 10 ints equal to 0.
int ex_3_28() // is int main() in the textbook.
{
    string sa2[10]; // 10 empty strings.
    int ia2[10];    // 10 undefined `ints`.
    return 0;
}

// Exercise 3.29: List some of the drawbacks of using an array instead of a vector.
int ex_3_29()
{
    // - Size is fixed and must be known at compile time. (Section: Explicitly Initializing Array Elements).
    // - Character arrays initialised from string literals: need an extra element to hold the null terminator.
    //   (Section: Character Arrays Are Special).
    // - No Copy or Assignment (that's the name of the section).
    
    // Other stuff not in the book:
    // - Arrays are just sequences of pointers, so they don't have any member functions.
    //   In particular, they don't have size(), begin() or end() methods.
    //   So you have to use something like `sizeof(v) / sizeof(v[0]) to count the elements*,
    //   and the <iterator> header to get the begin and end iterators.
    //
    //   * Btw, this doesn't always work. Doesn't work with arrays created with `new`, or with arrays passed to methods.
    //
    // - You can't pass arrays to functions. You can _write_ something like `void act_on(int arr[]) { /**/}`,
    //   but what actually gets passed is just the pointer to the first element. This means that there's no way
    //   to find the size of the array within the function.

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.5.2, Accessing the Elements of an Array
// p117.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.30: Identify the indexing errors in the following code :
int ex_3_30()
{
    constexpr size_t array_size = 10;
    int ia[array_size];
    for (size_t ix = 1; ix <= array_size; ++ix) // Error is here: array indexation is zero-based.
                                                // Loop should say `for (size_t ix = 0; ix < array_size; ++ix)`.
        ia[ix] = ix;

    return 0;
}

// Exercise 3.31: Write a program to define an array of ten ints. Give each element the
// same value as its position in the array.
int ex_3_31()
{
    // This answer is the same as the corrected code above!
    constexpr size_t array_size = 10;
    int ia[array_size];
    for (size_t ix = 0; ix != array_size; ++ix) // We use != instead of <, as per the box on p108.
        ia[ix] = ix;

    return 0;
}

// Exercise 3.32 : Copy the array you defined in the previous exercise into another array.
// Rewrite your program to use vectors.
int ex_3_32()
{
    // Set up the arrays and the vectors.
    constexpr size_t array_size = 10;
    int source_a[array_size], receiving_a[array_size];
    vector<int> source_v(array_size), receiving_v(array_size);
    for (size_t ix = 0; ix != array_size; ++ix)
    {
        source_a[ix] = ix;
        source_v[ix] = ix;
    }

    // Copy the array.
    for (size_t ix = 0; ix != array_size; ++ix)
        receiving_a[ix] = source_a[ix];

    // Copy the vector.
    receiving_v = source_v;         // First method.
    auto receiving_v2{ source_a };  // Second method
    auto receiving_v3( source_a );  // Third method.

    return 0;
}

// Note on exercise 3.32: let's check that the copies are deep.
void prt_iv(vector<int> v, string name)
{
    std::cout << name << ": ";
    for (const auto elem : v) std::cout << elem << " ";
    std::cout << std::endl;
}

int check_vectors_deep_copy()
{
    vector<int> v(3, 42);
    vector<int> w1;
    w1 = v;
    vector<int> w2{ v };
    vector<int> w3(v);

    // Check what they contain initially.
    prt_iv(v, "v");
    prt_iv(w1, "w1");
    prt_iv(w2, "w2");
    prt_iv(w3, "w3");

    // Change the first elements of w1, w2, and w3, and check again.
    w1[0] = 1;
    w2[0] = 2;
    w3[0] = 3;
    std::cout << std::endl;
    prt_iv(w1, "w1");
    prt_iv(w2, "w2");
    prt_iv(w3, "w3");

    // We see that modifying the copies does not modify the source vector, so the copies are indeed deep.
    // But note, if they were pointers, then the _pointers_ would be deep-copied, but not the underlying obejcts.
    return 0;
}

// Exercise 3.33 : What would happen if we did not initialize the scores array in the
// program on page 116 ?
int ex_3_33()
{
    // This is the code, with the initialisation commented out.
    // count the number of grades by clusters of ten: 0--9, 10--19, . . . 90--99, 100
    unsigned scores[11]; // = {}; // 11 buckets, initialised since we are in a function.
    unsigned grade;
    while (std::cin >> grade)
    {
        if (grade <= 100)
            ++scores[grade / 10]; // [1] increment the counter for the current cluster
    }

    // ANSWER: what would happen is that the buckets would all contain garbage unitialised values.
    // Could Line [1] cause a runtime overflow error, if an unitialised bucket happened to contain MAX_INT? Dunno.
    // Check:
    std::cout << "scores: ";
    for (const auto elem : scores) std::cout << elem << " ";
    std::cout << std::endl;

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.5.3, Pointers and Arrays
// p121.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.34: Given that p1 and p2 point to elements in the same array, what does
// the following code do ? Are there values of p1 or p2 that make this code illegal ?
// p1 += p2 - p1;
int ex_3_34()
{
    int arr[6] = { 10, 1, 12, 4, 2, 25};
    int* p1 = &arr[1];
    int* p2 = &arr[4];

    // ANSWER
    // p1 += p2 - p1. This code is legal, and changes p1 to point to the same element as p2.

    // Check:
    p1 += p2 - p1;
    std::cout << "Pointer expression `p1 + (p2 - p1)`: " << p1  << std::endl;
    std::cout << "`p2`                               : " << p2  << std::endl;
    std::cout << "Value at that address              : " << *p1 << std::endl;

    // Other notes
    // p1 = p1 + (p2 - p1) is also legal:
    //      the bracket is done first, which gives a pointer_diff
    //      so the expression has the form pointer + pointer_diff, which is allowed.
    // 
    // p1 = p1 + p2 - p1 is NOT legal:
    //      The expression is evaluated left-to-right in the absence of brackets,
    //      so it has the form (pointer + pointer) - pointer, and you can't add pointers. 
    // 
    // Pointer arithmetic is the same as iterator arithmetic, which is explained in method `explanation_of_3_24()`.
    return 0;
}

// Exercise 3.35: Using pointers, write a program to set the elements in an array to zero.
int ex_3_35()
{
    // Set up the array first. Wrote this code in ex_3_31().
    constexpr size_t array_size = 10;
    int ia[array_size];
    for (size_t ix = 0; ix != array_size; ++ix)
        ia[ix] = ix;

    // Use pointers to set all elements to 0.
    // for (int* p = ia; p != ia + array_size; p++)         // This is error-prone. 
                                                            // Don't try and get the bounds yourself.
    for (int* p = std::begin(ia); p != std::end(ia); p++)
        *p = 0;

    // Check:
    std::cout << "ia: ";
    for (const auto elem : ia) std::cout << elem << " ";
    std::cout << std::endl;

    // Final notes.
    // - `int* p = ia`      : Initialising a pointer with an array is equivalent to ...
    // - `int* p = &ia[0]   : ...setting it to the address of its first element.
    // - `p + 1`            : A pointer to the next element of the array.
    // - `p + n`            : A pointer to the nth next element, as long as its not out-of-bounds.
    return 0;
}

// Exercise 3.36 : Write a program to coompare two arrays for equality. Write a similar
// program to compare two vectors.
int ex_3_36()
{
    // Set up two arrays and two vectors.
    int ia1[]{ 1, 2 };
    int ia2[]{ 1, 2 };       // Equal.
    // int ia2[]{1, 3};         // Different elements, same sizes.
    // int ia2[]{ 1, 2, 3 };    // Different sizes.

    vector<int> iv1{ 1, 2 };
    // vector<int> iv2{ 1, 2 };       // Equal.
    vector<int> iv2{1, 3};         // Different elements, same sizes.
    // vector<int> iv2{ 1, 2, 3 };    // Different sizes.
    
    // Equality check for arrays.
    // First check length: if lengths are not equal then we can stop right there.
    bool are_equal;
    are_equal = std::end(ia1) - std::begin(ia1) == std::end(ia2) - std::begin(ia2); 

    // If same length, then loop through and check each element.
    if (are_equal)
    {
        auto array_size = std::end(ia1) - std::begin(ia1);
        for (size_t ix = 0; ix != array_size; ++ix)
        {
            if (ia1[ix] != ia2[ix])
                are_equal = false;

            if (!are_equal)
                break;
        }
    }
    std::cout << "Arrays are " << (are_equal ? "" : "not ") << "equal." << std::endl;

    // Equality check for vectors. This is much simpler, and another reason to prefer vectors over arrays.
    are_equal = (iv1 == iv2);
    std::cout << "Vectors are " << (are_equal ? "" : "not ") << "equal." << std::endl;

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.5.4, C-Style Character Strings
// p
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.37: What does the following program do ?
int ex_3_37()
{
    const char ca[] = { 'h', 'e', 'l', 'l', 'o' };
    const char* cp = ca;
    while (*cp)
    {
        std::cout << *cp << std::endl;
        ++cp;
    }
    
    // ANSWER.  It prints h, then e, etc, until it gets to 'o', but it doesn't stop there!
    //          *cp is only false when it is the null terminator '\0'. So cp gets on being increased,
    //          and the loop carries on printing rubbish until cp finally points to a bit of memory
    //          that happens to contain a null terminator.
    return 0;
}

// Exercise 3.38: In this section, we noted that it was not only illegal but meaningless to
// try to add two pointers.Why would adding two pointers be meaningless ?
int ex_3_38()
{
    // What would it even mean? You might as well add two street addresses.
    // In the words of Charles Babbage, 
    // I am not able rightly to apprehend the kind of confusion of ideas that could provoke such a question.
    return 0;
}

// Exercise 3.39 : Write a program to compare two strings. Now write a program to
// compare the values of two C - style character strings.
int ex_3_39()
{
    // Create two strings and compare.
    string s1 = "abc", s2 = "def";
    std::cout << s1.compare(s2) << std::endl;   // -1 means s1 is less than s2, 0 means they are the same
                                                // 1 means s1 is larger than s2.

    // Create two C-style strings and compare.
    // strcmp() needs the <cstring> header.
    char ca1[] = { 'a', 'b', 'c', '\0' }, ca2[] = { 'd', 'b', 'c', '\0' };
    std::cout << strcmp(ca1, ca2) << std::endl; // Same interpretation as before.

    return 0;
}

// Exercise 3.40 : Write a program to define two character arrays initialized from string
// literals. Now define a third character array to hold the concatenation of the two arrays.
// Use strcpy and strcat to copy the two arrays into the third.
int ex_3_40()
{
    char ca1[]{ 'H', 'e', 'l', 'l', 'o', ' ', '\0' };
    char ca2[]{ 'W', 'o', 'r', 'l', 'd', '\0' };

    const auto size1 = std::end(ca1) - std::begin(ca1);
    const auto size2 = std::end(ca2) - std::begin(ca2);
    char result[size1 + size2];

    // strcpy() does not compile in Visual Studio with the default compilation options.
    // See  https://stackoverflow.com/questions/32136185/difference-between-strcpy-and-strcpy-s
    // strcpy(result, ca1);
    // strcat(result, ca2);
    // Alternative using strcpy_s()
    strcpy_s(result, size1 + size2, ca1);
    strcat_s(result, size1 + size2, ca2);

    std::cout << result << std::endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.5.5, Interfacing to Older Code
// p126.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.41: Write a program to initialize a vector from an array of ints.
int ex_3_41()
{
    int a[]{ 1, 2, 3, 4 };

    // vector<int> v(a); // doesn't work even though it looks like it does.
    vector<int> v(std::begin(a), std::end(a));
    return 0;
}

// Exercise 3.42 : Write a program to copy a vector of ints into an array of ints
int ex_3_42()
{
    // Create two vectors to demonstrate with.
    int a[]{ 0, 0, 0 };
    vector<int> v(1, 42);
    
    // Calculate how many elements we can copy.
    auto size_a = std::end(a) - std::begin(a);
    auto size_v = v.size();
    auto lim = size_a < size_v ? size_a : size_v;

    // The actual copying.
    for (int i = 0; i < lim; i++)
        a[i] = v[i];

    // Check.
    for (const auto& elem : a)
        std::cout << elem << " ";
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 3.6, Multidimensional Arrays
// p130.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 3.43: Write three different versions of a program to print the elements of ia.
// One version should use a range for to manage the iteration, the other two should use
// an ordinary for loop in one case using subscripts and in the other using pointers. In
// all three programs write all the types directly. That is, do not use a type alias, auto, or
// decltype to simplify the code.
int ex_3_43()
{
    // First create a 2d array to work with.
    constexpr int num_rows = 3, num_cols = 4;
    int mat[num_rows][num_cols] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    // Use a range for.
    // 
    // Each element of `mat` is an array of `num_cols` ints.
    // So we try `int row[num_cols]` as the type of the loop variable.
    // But that doesn't compile, as per the explanation of array-collapse on p128.
    // The note on that page says that we have to use references.
    // So the type of the loop variable must be a reference to an array of `num_cols` ints.
    // We will call the loop variable `row`.
    //           (&row)             <-- row is a reference ...
    //           (&row)[]           <-- to an array ...
    //           (&row)[num_cols]   <-- ... of `num_cols` ...
    //       int (&row)[num_cols]   <-- ... ints.
    // const int (&row)[num_cols]   <-- And we make the ints const to promise we won't change them 
    //                                  (we're just printing).
    // 
    // Note: the book says to read these complicated types "inside out". 
    // Maybe a better way to think of it is in terms of operator precedence.
    // - brackets first
    // - then subscripts
    // - then read the bits on the left from right to left as previously described.
    // (Not confirmed that this will always work).
    // Edit: this is in fact a correct way to think about it: see // https://www.embedded.com/references-and-const/
    for (const int (&row)[num_cols] : mat) 
    {
        for (const int& j : row)
            std::cout << std::setw(5) << j << " "; // setw() not covered in book yet.
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Use a normal for loop with subscripts.
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
            std::cout << std::setw(5) << mat[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Use a normal for loop with pointers, but don't use auto.
    // If we were using auto, the loop declaration would look like:
    // 
    // for (auto[2] i = mat; i != ???[1]; p++)
    //     for (auto[3] j = ???[4]; j != ???[5]; i++)
    // 
    // [1]: mat is an array of num_rows arrays.
    //      **When we iterate over arrays, the loop variable is a pointer to the type of stuff that the array holds.**
    //      i = mat initialises i as a pointer to the first element of mat (see p118).
    //      i++ points to the next element, and so on, until i + num_rows points to one-past-the-end.
    //      That's where we stop: i + num_rows.
    // 
    // [2]  Outer loop: auto is iterating over rows of mat. Each row of mat is an array of ints.
     //     **When we iterate over arrays, the loop variable is a pointer to the type of stuff that the array holds.**
     //     so auto is deduced as a pointer to an array of num_cols ints.
    //          (*i)             <-- i is a pointer ...
    //          (*i)[num_cols]   <-- ... to an array of num_cols ...
    //      int (*i)[num_cols]   <-- ints.
    //
    // [3]  Inner loop: i is a _pointer_ to an array of ints, so we need to loop over *i, the actual array which is being pointed to.
    //      But it's again an array that we're looping over, so the loop variable is again a pointer. But since the array holds ints
    //      the loop varialble is a pointer to int.
    // 
    // [4] Initialise the inner loop with the address of the first element of the row. 
    //
    for (const int(*i)[num_cols] = mat; i != mat + num_rows; i++)
    {
        for (const int* j = *i; j != *i + num_cols; j++)
            std::cout << std::setw(5) << *j << " ";
        std::cout << std::endl;
    }

    return 0;
}

// Exercise 3.44: Rewrite the programs from the previous exercises using a type alias for
//     the type of the loop control variables.
int ex_3_44()
{
    // First create a 2d array to work with.
    constexpr int num_rows = 3, num_cols = 4;
    int mat[num_rows][num_cols] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    using matrix_row = int[num_cols];
    for (matrix_row* i = mat; i != mat + num_rows; i++)
    {
        for (int* j = *i; j != *i + num_cols; j++)
            // We have to dereference j, because it is now a pointer to the element rather than a ref to it.
            std::cout << std::setw(5) << *j << " ";
        std::cout << std::endl;
    }

    return 0;
}

// Exercise 3.45 : Rewrite the programs again, this time using auto.
int ex_3_45()
{
    // First create a 2d array to work with.
    constexpr int num_rows = 3, num_cols = 4;
    int mat[num_rows][num_cols] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    for (auto& i : mat)
    {
        for (auto& j : i)
            std::cout << std::setw(5) << j << " "; 
        std::cout << std::endl;
    }

    return 0;
}

int main()
{
    return ex_3_45();
}
