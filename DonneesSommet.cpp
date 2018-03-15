#include "donneesSommet.h"

ostream & operator<<(ostream & os, const DonneesSommet & s){
	os << "Nom : " << s.nom << endl;
	os << "Numerotation : " << endl;
	os << "Naturelle : " << s.numerotation << endl;
	os << "-Prefixe : " << s.numerotationPrefixe << endl;
	os << "-Sufixe : " << s.numerotationSuffixe << endl;
	return os;
}
