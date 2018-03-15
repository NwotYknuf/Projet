#include "donneesSommet.h"

ostream & operator<<(ostream & os, const DonneesSommet & s){
	os << "Nom : " << s.nom << endl;
	return os;
}
