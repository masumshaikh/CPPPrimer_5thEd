//
//  ex7_32.h
//  Exercise 7.32
//
//  Created by pezy on 11/18/14.
//  Copyright (c) 2014 pezy. All rights reserved.
//
//  @See ex7_27.h

#ifndef CP5_ex7_32_h
#define CP5_ex7_32_h

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Screen_v7_33; // [1]

class ToyWindowManager {
public:
    // We only declare clear() here. It's going to clear ToyScreen.
    // We can't define it here, because we still don't know what's inside ToyScreen.
    inline void clear(); 

    // Similarly, we can only declare the constructor.
    // Note that we only needed a constructor to write the harness in the method ex_7_32().
    ToyWindowManager();

    // We can only declare a pointer to ToyScreen here, because the size in memory of a pointer is known,
    // as all pointers are the same size. But the size of an actual ToyScreen object is not known, 
    // because it hasn't been defined yet.
    Screen_v7_33* fScreenPtr;
};

// Why forward declare ToyScreen? 
// To find out, replace line [1] with the full definition of ToyScreen below.
// You will get the error documented at line [2].
class Screen_v7_33 {
    friend void ToyWindowManager::clear();

public:
    // Note that we only needed this method to write the harness in the method ex_7_32().
    std::string ToString()
    {
        std::stringstream ss = std::stringstream();
        ss << fContents;
        return ss.str();
    }

private:
    int fContents = 100;
};

// Fill in the definition of the constructor.
ToyWindowManager::ToyWindowManager()
{
    fScreenPtr = new Screen_v7_33(); // Very bad: new without delete!!
}

// Fill in this definition too.
inline void ToyWindowManager::clear()
{
    fScreenPtr->fContents = 0; // [2]. Error: "ToyScreen::fContents is inaccessible."
}


#endif