#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class AElement
{
public:
int clef;

explicit AElement(const int clef): clef(clef) {}
operator string() const { ostringstream o; o <<"clef = " << clef ; return o.str(); }

friend ostream & operator << (ostream & os, const AElement& aElement) {return os << (string) aElement;}
};
