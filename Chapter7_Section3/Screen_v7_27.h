#pragma once
#include <string>

using std::string;

// We should separate out the defintions into a .cpp file, but I can't be bothered.
// See https://stackoverflow.com/questions/31665257/the-whole-class-in-header-file-without-cpp-file
class Screen_v7_27
{
public:
    typedef string::size_type pos;

private:
    pos fCursor = 0; 
    pos fHeight = 0, fWidth = 0;
    string fContents;

public:
    Screen_v7_27() = default;
    Screen_v7_27(pos ht, pos wd) :
        fHeight{ ht },
        fWidth{ wd }
    {
        fContents = string(ht * wd, ' ');
    }

    Screen_v7_27(pos ht, pos wd, char c) :
        fHeight{ ht },
        fWidth{ wd },
        fContents(ht* wd, c)
    {}

    void display(std::ostream& cout) const
    {
        cout << string(fWidth + 2, '-') << std::endl << "|";
        for (int i = 0; i < fContents.size(); i++)
        {
            cout << fContents[i];
            if (((i + 1) % fWidth == 0) && i < fHeight * fWidth - fWidth)
                cout << "|\n|";
            if (i == fHeight * fWidth - 1)
                cout << "|" << std::endl;
        }
        cout << string(fWidth + 2, '-') << std::endl;
    }

    char get() const
    {
        return fContents[fCursor];
    }

    Screen_v7_27& set(char ch)
    {
        fContents[fCursor] = ch;
        return *this;
    }

    // NOTE: for the rest of these functions, we really should do some bounds checking!
    inline char get(pos r, pos c) const
    {
        // If we have a 3x4 screen, this is represented by a string 12 characters long.
        // Characters 0 to 3 are in the 0th row, 4 to 7 in the 2nd row, and 8 to 11 in the 3rd row.
        return fContents[r * fWidth + c];
    }

    Screen_v7_27& move(pos r, pos c)
    {
        fCursor = r * fWidth + c;
        return *this;
    }

    Screen_v7_27& set(pos r, pos col, char ch)
    {
        fContents[r * fWidth + col] = ch;
        return *this;
    }
};
