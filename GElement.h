#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "AElement.h"

using namespace std;

template <class infoSommet>
class GElement : public AElement
{
public:
infoSommet v;
GElement(const int clef, const infoSommet & v): AElement(clef), v(v) {}
operator string() const { ostringstream o; o << this->AElement::operator string() <<endl << "valeur = " << v; return o.str();}

friend ostream & operator << (ostream & os, const GElement<infoSommet>& gElement) {return os << (string) gElement;}
};


