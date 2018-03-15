#pragma once
#include <string>
#include <iostream>
#include <exception>

using namespace std;

class Erreur : public exception
{
public:
string message;
Erreur() : message("Erreur !"){}
Erreur(const string & messageErreur) : Erreur() {this->message +=" "+messageErreur;}
Erreur(const char * messageErreur) : Erreur((string)messageErreur){}

inline static void testeNonVide(const void *d, const char * message);

operator string() const {return this->message;}

virtual const char* what() const noexcept {return ((string)(*this)).c_str();}
};

inline ostream & operator << (ostream & os, const Erreur & erreur) { return os << (string) erreur; }

inline void Erreur::testeNonVide(const void *d, const char * message)
{
#ifdef DEBUG
	if (!d) throw Erreur(message);
#endif
}
