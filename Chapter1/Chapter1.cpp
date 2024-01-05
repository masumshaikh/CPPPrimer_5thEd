#include <iostream>
#include "Sales_item.h"
#include <vector>
#include <map>

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.1.1, Compiling and Executing Our Program
// p5.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.1: Review the documentation for your compiler and determine what file
// naming convention it uses. Compile and run the main program from page 2.
int ex_1_1()
{
    return 0;
}

// Exercise 1.2 : Change the program to return -1. A return value of - 1 is often treated
// as an indicator that the program failed.Recompile and rerun your program to see how
// your system treats a failure indicator from main.
int ex_1_2()
{
    return -1;
}

// Example code, p8.
// Read in two numbers and add them
void example_p31()
{
    int v1, v2;

    std::cout << "Please input two integers";
    std::cin >> v1 >> v2;
    std::cout << "The sum of the two numbers is " << v1 + v2 << std::endl;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.2, A First Look at Input/Output
// p9.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.3.
// Write a program to print "Hello, World!" on the standard output.
void ex_1_3()
{
    std::cout << "Hello, World!" << std::endl;
}

// Exercise 1.4.
// Our program used the addition operator, +, to add two
// numbers.Write a program that uses the multiplication operator,*, to print
// the product instead.
void ex_1_4()
{
    int v1, v2;
    std::cout << "Please input two integers";
    std::cin >> v1 >> v2;
    std::cout << "The product of the two numbers is " << v1 * v2 << "." << std::endl;
}

// Exercise 1.5
// We wrote the output in one large statement. Rewrite the
// program to use a separate statement to print each operand.
void ex_1_5()
{
    int v1, v2;
    std::cout << "Please input two integers";
    std::cin >> v1 >> v2;
    std::cout << "The product of the two numbers is ";
    std::cout << v1 * v2;
    std::cout << ".";
    std::cout << std::endl;
}

// Exercise 1.6
// Explain whether the following program fragment (within the block comment) is legal.
// If the program is legal, what does it do? If the program is not legal, why not?
// // How would you fix it ?
void ex_1_6()
{

    int v1 = 0, v2 = 0;
    /*    
    std::cout << "The sum of " << v1;
              << " and " << v2; 
              << " is " << v1 + v2 << std::endl;
    */

    // Answer:  this code fragment will not compile.
    //          Either put "std::cout" at the beginning of the last two lines, 
    //          or remove the semi-colon from the end of the first two lines.
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.3, A Word about Comments
// p11.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.7.
// Compile a program that has incorrectly nested comments.
void ex_1_7()
{
    // Uncomment the third line in ex_1_8() and see what happens!
}

// Exercise 1.8.
// Indicate which, if any, of the following output statements are legal :
void ex_1_8()
{
    std::cout << "/*";
    std::cout << "*/";
    // std::cout << /* "*/" */;
    std::cout << /* "*/" /* "/*" */;

    // Answer: the third one is not OK. It simplifies to the following code,
    // which has an unbalanced quote mark.
    // std::cout << " */;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.4.1, Flow of Control 
// p13.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.9.
// Write a program that uses a while to sum the numbers from 50 to 100.
void ex_1_9()
{
    int const start = 50;
    int const end = 100;

    int counter = start;
    int sum = 0;
    while (counter <= 100)
    {
        sum += counter;
        counter++;
    }

    std::cout << "The sum of numbers from " << start << " to " << end << " inclusive is " << sum << std::endl;
}

// Exercise 1.10.
// In addition to the++ operator that adds 1 to its operand,
// there is a decrement operator (--) that subtracts 1. Use the decrement
// operator to write a while that prints the numbers from ten down to zero.
void ex_1_10()
{
    int const start = 10;
    int const end = 0;

    int counter = start;
    while (counter >= end)
    {
        std::cout << counter << std::endl;
        counter--;
    }
}

// Exercise 1.11.
// Write a program that prompts the user for two integers.
// Print each number in the range specified by those two integers.
void ex_1_11()
{
    int v1, v2;
    std::cout << "Please input two integers";
    std::cin >> v1 >> v2;

    int incr = v1 < v2 ? 1 : -1;
    int counter = v1 - incr;
    while (counter != v2)
    {
        counter += incr;
        std::cout << counter << std::endl;
    }
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.4.2, The `for` Statement 
// p14.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.12.
// What does the following for loop do? What is the final value of sum?
void ex_1_12()
{
     int sum = 0;
     for (int i = -100; i <= 100; ++i)
        sum += i;

     std::cout << "The sum is " << sum << std::endl;

    // Answer; it adds the integers from -100 to 100, inclusive. The sum will be zero.
}

// Exercise 1.13: Rewrite the exercises from § 1.4.1 (ex 1.19 to 1.11) using for loops.
void ex_1_13()
{
    // Ex 1.9
    std::cout << "Exercise 1.9";
    int sum = 0;
    for (int counter = 50; counter <= 100; counter++)
        sum += counter;
    std::cout << "The sum of numbers from 50 to 100 inclusive is " << sum << std::endl << std::endl;
 
    // Ex 1.10
    std::cout << "Exercise 1.10" << std::endl;
    for (int counter = 10; counter >= 0; counter--)
        std::cout << counter << std::endl;
    std::cout << std::endl;

    // Ex 1.11
    std::cout << "Exercise 1.11 -- please input two integers" << std::endl;
    int v1, v2;
    std::cin >> v1 >> v2;

    bool v1Smaller = v1 < v2;
    int incr = v1Smaller ? 1 : -1;

    for (int counter = v1; counter != v2 + incr; counter += incr)
        std::cout << counter << std::endl;
}

// Exercise 1.14.
// Compare and contrast the loops that used a for with those
// using a while. Are there advantages or disadvantages to using either form ?
void ex_1_14()
{
    // while loop is better when the step size is variable, or when the exit condition
    // isn't a simple function of the counter.
    // 
    // for loop is better when start, end and step size are all known before
    // starting the loop.
}

// Exercise 1.15.
// Write programs that contain the common errors discussed in
// the box on page 16. Familiarize yourself with the messages the compiler generates.
void ex_1_15()
{
    // Not done.
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.4.3, Reading an Unknown Number of Inputs 
// p17.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.16.
// Write your own version of a program that prints the sum of
// a set of integers read from cin.
void ex_1_16()
{
    int value = 0;
    int sum = 0;
    std::cout << "Exercise 1.16 -- please enter some numbers." << std::endl;
    while (std::cin >> value)
        sum += value;

    std::cout << "The sum of those numbers was " << sum << std::endl;
}

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.4.4, The `if` Statement 
// p18.
// --------------------------------------------------------------------------------------------------------------------

// Code example, p18.
// Write a program to read in a few numbers from standard input,
// and output a count of how many times each of those numbers is in the set.
// For example, if the input is:
// 
//      42 42 42 42 42 55 55 62 100 100 100
// 
// then the output should be
// 
//      42 occurs 5 times
//      55 occurs 2 times
//      62 occurs 1 times
//      100 occurs 3 times
//
// Note:    the code given in the textbook is quite brittle. It doesn't work if 
//          you give it "42 65 42", for example.
void example_p18()
{
    std::cout << "Example on page 44 -- please enter a few integers." << std::endl;
    // currVal is the number we're counting; we'll read new values into val
    int currVal = 0, val = 0;
    // read first number and ensure that we have data to process
    if (std::cin >> currVal) {
        int cnt = 1; // store the count for the current value we're processing
        while (std::cin >> val) { // read the remaining numbers
            if (val == currVal) // if the values are the same
                ++cnt; // add 1 to cnt
            else { // otherwise, print the count for the previous value
                std::cout << currVal << " occurs " << cnt << " times" << std::endl;
                currVal = val; // remember the new value
                cnt = 1; // reset the counter
            }
        } // while loop ends here
        // remember to print the count for the last value in the file
        std::cout << currVal << " occurs " << cnt << " times" << std::endl;
    } // outermost if statement ends here
}

// Exercise 1.17.
// What happens in the program presented in this section if the
// input values are all equal? What if there are no duplicated values?
void ex_1_17()
{
    // The code goes into an infinite loop.
}

// Exercise 1.18.
// Compile and run the program from this section giving it only
// equal values as input. Run it again giving it values in which no number is repeated.
void ex_1_18()
{
    // As above.
}

// Exercise 1.19.
// Revise the program you wrote for the exercises in §1.4.1 (P13)
// that printed a range of numbers so that it handles input in which the first
//  number is smaller than the second.
void ex_1_19()
{
    // Already did this.
}      

// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.5.1, The `Sales_item` Class 
// p22.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.20.
// http://www.informit.com/title/032174113 contains a copy of
// Sales_item.h in the Chapter 1 code directory. Copy that file to your
// working directory.Use it to write a program that reads a set of book sales
// transactions, writing each transaction to the standard output.
void ex_1_20()
{
    // Did this. Also had to copy Version_test.h to working directory.
    // Project builds without errors.
}  

// Exercise 1.21.
// Write a program that reads two Sales_item objects that
// have the same ISBN and produces their sum.
void ex_1_21()
{
    Sales_item item1, item2;
    std::cout << "Please enter the first sales item (ISBN, units sold, average price): ";
    std::cin >> item1;
    
    std::cout << "Please enter the second sales item: ";
    std::cin >> item2;

    if (item1.isbn() == item2.isbn())
        std::cout << item1 + item2 << std::endl;
    else
        std::cout << "Two items must have the same ISBN in order to add them." << std::endl;
}  

// Exercise 1.22.
// Write a program that reads several transactions for the same
// ISBN. Write the sum of all the transactions that were read.
int ex_1_22()
{
    // Going to use vectors even though they haven't been covered yet.
    std::vector<Sales_item> sales_items;

    std::cout << "Please enter a list of sales items (ISBN, units sold, average price)." << std::endl;
    std::cout << "To show that you have completed the list, enter a sales item with an ISBN of 'end' (case-sensitive)." << std::endl;
    
    // Capture sales entries.
    Sales_item entry;
    bool still_entering = true;
    while (still_entering)
    {
        std::cin >> entry;
        if (entry.isbn() == "end")
            still_entering = false;

        if (still_entering)
            sales_items.push_back(entry);
    }

    // Edge case where no items are entered.
    if (sales_items.size() == 0)
    {
        std::cerr << "You have not entered any sales items." << std::endl;
        return -1;
    }

    // Sum up and report.
    Sales_item sum = sales_items[0];
    for (int i = 1; i < sales_items.size(); i++)
        // Ideally, we should check if the ISBN's match in the operator+() overload of Sales_item,
        // but I don't want to change that implementation because it was provided by the textbook.
        if (sum.isbn() == sales_items[i].isbn())
        {
            sum += sales_items[i];
        }
        else
        {
            std::cerr << "All the sales items must have the sales ISBN." << std::endl;
            return -1;
        }

    std::cout << "The total sales figures are (ISBN, units sold, revenue, average price): " << sum << std::endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.5.2, A First Look at Member Functions 
// p24.
// --------------------------------------------------------------------------------------------------------------------

// Exercises 1.23 and 1.24.
// Write a program that reads several transactions and counts
// how many transactions occur for each ISBN.
//
// Test the previous program by giving multiple transactions
// representing multiple ISBNs. The records for each ISBN should be grouped together.
int ex_1_23()
{
    // Going to use vectors (and maps, see later) even though they haven't been covered yet.
    std::vector<Sales_item> sales_items;

    std::cout << "Please enter a list of sales items (ISBN, units sold, average price)." << std::endl;
    std::cout << "To show that you have completed the list, enter a sales item with an ISBN of 'end' (case-sensitive)." << std::endl;

    // Capture sales entries.
    Sales_item entry;
    bool still_entering = true;
    while (still_entering)
    {
        std::cin >> entry;
        if (entry.isbn() == "end")
            still_entering = false;

        if (still_entering)
            sales_items.push_back(entry);
    }

    // Edge case where no items are entered.
    if (sales_items.size() == 0)
    {
        std::cerr << "You have not entered any sales items." << std::endl;
        return -1;
    }

    std::map<std::string, int> isbn_counts;
    for (auto& const item : sales_items)
    {
        if (isbn_counts.count(item.isbn()) == 0)
            isbn_counts[item.isbn()] = 1;
        else
            isbn_counts[item.isbn()] += 1;
    }

    for (auto& const elem : isbn_counts)
        std::cout << "ISBN <" << elem.first << "> appears in " << elem.second << " transactions." << std::endl;
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------
// EXERCISES SECTION 1.6, The Bookstore Program
// p25.
// --------------------------------------------------------------------------------------------------------------------

// Exercise 1.25.
// Using the Sales_item.h header from the Web site,
// compile and execute the bookstore program presented below.
// (Code below is from the textbook).
int ex_1_25()
{
    Sales_item total; // variable to hold data for the next transaction

    // read the first transaction and ensure that there are data to process
    if (std::cin >> total)
    {
        Sales_item trans; // variable to hold the running sum

        // read and process the remaining transactions
        while (std::cin >> trans)
        {
            // if we're still processing the same book
            if (total.isbn() == trans.isbn())
                total += trans; // update the running total
            else
            {
                // print results for the previous book
                std::cout << total << std::endl;
                total = trans; // total now refers to the next book
            }
        }
        std::cout << total << std::endl; // print the last transaction
    }
    else
    {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1; // indicate failure
    }
    return 0;
}


int main()
{

    ex_1_23();
 }