#include "stdafx.h"
#include "donneesArete.h"

ostream & operator<<(ostream & os, const DonneesArete & a) {
	os << "Distance : " << a.distance << ", Duree : " << a.duree;
	return os;
}