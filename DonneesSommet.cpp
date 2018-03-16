#include "donneesSommet.h"

const unsigned DonneesSommet::LIBRE = 0u;
const unsigned DonneesSommet::OUVERT = 1u;
const unsigned DonneesSommet::FERME = 2u;

ostream & operator<<(ostream & os, const DonneesSommet & s){
	os << "Nom : " << s.nom << endl;
	os << "Position: (" << s.x << ", " << s.y << ")" << endl;
	os << "Numerotation : " << endl;
	os << "-Naturelle : " << s.numerotation << endl;
	os << "-Prefixe : " << s.numerotationPrefixe << endl;
	os << "-Sufixe : " << s.numerotationSuffixe << endl;
	return os;
}
