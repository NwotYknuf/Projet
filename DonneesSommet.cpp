#include "donneesSommet.h"

ostream & operator<<(ostream & os, const DonneesSommet & s){
	os << "Nom : " << s.nom << ", Marque : " << s.marque ? "oui" : "non";
	os << endl;
	return os;
}
