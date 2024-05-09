#pragma once
#include <iostream>

struct Student
{
    std::string name;
    int score;
    bool operator < (const Student &t) const { return score < t.score; }
    friend std::ostream& operator<<(std::ostream &cout, const Student &t)
    {
        cout << "my name is " << t.name << "\n";
        return cout;
    }
};