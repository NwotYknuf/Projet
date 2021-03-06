#include "Chargement.h"
#include "TraitementGraphe.h"
#include <fstream>

void Chargement::split(string str, string splitBy, vector<string>& tokens)
{
	/* Store the original string in the array, so we can loop the rest
	* of the algorithm. */
	tokens.push_back(str);

	// Store the split index in a 'size_t' (unsigned integer) type.
	size_t splitAt;
	// Store the size of what we're splicing out.
	size_t splitLen = splitBy.size();
	// Create a string for temporarily storing the fragment we're processing.
	std::string frag;
	// Loop infinitely - break is internal.
	while (true)
	{
		/* Store the last string in the vector, which is the only logical
		* candidate for processing. */
		frag = tokens.back();
		/* The index where the split is. */
		splitAt = frag.find(splitBy);
		// If we didn't find a new split point...
		if (splitAt == string::npos)
		{
			// Break the loop and (implicitly) return.
			break;
		}
		/* Put everything from the left side of the split where the string
		* being processed used to be. */
		tokens.back() = frag.substr(0, splitAt);
		/* Push everything from the right side of the split to the next empty
		* index in the vector. */
		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
}

int Chargement::nbreLignes(const string& chemin) {
	vector<string> ligneSplit;
	int nbLignes = 0;
	string line;
	ifstream file(chemin, ios::in);
	if (file) {
		while (getline(file, line)) nbLignes++;
		file.close();
	}
	else cerr << "Impossible d'ouvrir le fichier!" << endl;
	return nbLignes;
}

void Chargement::erase(vector<string>& v, string str)
{
	auto iter = v.begin();
	while (iter != v.end())
	{
		if (*iter == str) iter = v.erase(iter);
		else iter++;
	}
}

int Chargement::trouverLigneCommencantParS(const string& s, const string& chemin) {
	bool trouve = false;
	int numeroLigne = 0;
	string line;
	vector<string> conteneur;
	ifstream file(chemin, ios::in);
	if (file) {
		while (getline(file, line) && !trouve) {
			split(line, " ", conteneur);
			numeroLigne++;
			if (conteneur[0] == s) trouve = true;
			conteneur.clear();
		}
	}
	else cerr << "Impossible d'ouvrir le fichier!" << endl;
	return numeroLigne;
}

Graphe<DonneesArete, DonneesSommet> * Chargement::charger(const string& chemin) {
	Graphe<DonneesArete, DonneesSommet> * graphe = new Graphe<DonneesArete, DonneesSommet>();
	Chargement::chargerSommetGPR(chemin, graphe);
	Chargement::chargerAreteGPR(chemin, graphe);
	chargerSourceOuPuitGPR(chemin, graphe->lSommets, "sources");
	chargerSourceOuPuitGPR(chemin, graphe->lSommets, "puits");
	return graphe;
}

void Chargement::chargerSommetGPR(const string& chemin, Graphe<DonneesArete, DonneesSommet> * graph) {
	ifstream file(chemin, ios::in);

	if (file) {
		string line;
		vector<string> ligneSplit;
		int numeroLigneCourante = 1;

		int sectionSommets = 0;
		int sources = 0;

		sectionSommets = Chargement::trouverLigneCommencantParS("sectionSommets", chemin);
		sectionSommets++;

		sources = Chargement::trouverLigneCommencantParS("sources", chemin);

		while (getline(file, line)) {
			if (sectionSommets <= numeroLigneCourante && numeroLigneCourante < sources - 1) {
				split(line, " ", ligneSplit);
				Chargement::erase(ligneSplit, "");
				DonneesSommet infoSommet(ligneSplit[0], stoi(ligneSplit[1]), stoi(ligneSplit[2]));
				graph->creeSommet(infoSommet);
				ligneSplit.clear();
			}
			if (numeroLigneCourante >= sources - 1) file.seekg(0, ios::end);
			numeroLigneCourante++;
		}
		
	}
	else
		throw Erreur("Impossible d'ouvrir le fichier !");
}

void Chargement::chargerSourceOuPuitGPR(const string& chemin, Maillon<Sommet<DonneesSommet>>* lSommets, const string& sourceOuPuit) {
	ifstream file(chemin, ios::in);

	if (file) {
		string line;
		vector<string> ligneSplit;
		int numeroLigneCourante = 1;
		Sommet<DonneesSommet> *sommetSource = NULL;

		int sources = 0;

		sources = Chargement::trouverLigneCommencantParS(sourceOuPuit, chemin);
		sources++;

		while (getline(file, line)) {
			if (numeroLigneCourante == sources) {
				split(line, " ", ligneSplit);
				Chargement::erase(ligneSplit, "");
				sommetSource = TraitementGraphe::trouverSommetParNom(lSommets, ligneSplit[0]);
				if (sourceOuPuit == "sources") sommetSource->info.source = true;
				if (sourceOuPuit == "puits") sommetSource->info.puit = true;
			}
			if (numeroLigneCourante > sources) file.seekg(0, ios::end);
			numeroLigneCourante++;
		}

	}
	else
		throw Erreur("Impossible d'ouvrir le fichier !");
}

void Chargement::chargerAreteGPR(const string& chemin, Graphe<DonneesArete, DonneesSommet> * graph) {

	ifstream file(chemin, ios::in);
	
	if (file) {
		string line2;
		vector<string> ligneSplit;
		int numeroLigneCourante = 1;

		int sectionArcs = 0;
		int sectionGraphes = 0;

		sectionArcs = Chargement::trouverLigneCommencantParS("sectionArcs", chemin);
		sectionArcs++;

		sectionGraphes = Chargement::trouverLigneCommencantParS("sectionGraphes", chemin);
		Sommet<DonneesSommet>* debut = NULL;
		Sommet<DonneesSommet>* fin = NULL;

		while (getline(file, line2)) {
			if (numeroLigneCourante >= sectionArcs && numeroLigneCourante < sectionGraphes - 1) {
				split(line2, " ", ligneSplit);
				Chargement::erase(ligneSplit, "");
				try {
					debut = TraitementGraphe::trouverSommetParNom(graph->lSommets,ligneSplit[1]);
					fin = TraitementGraphe::trouverSommetParNom(graph->lSommets, ligneSplit[2]);
				}
				catch (Erreur e) {
					cerr << e << endl;
				}

				DonneesArete infoArete(ligneSplit[0], stoi(ligneSplit[3]), stoi(ligneSplit[4]));
				graph->creeArete(infoArete, debut, fin);				
 				ligneSplit.clear();
			}
			if (numeroLigneCourante >= sectionGraphes - 1) file.seekg(0, ios::end);
			numeroLigneCourante++;
		}
		ligneSplit.clear();
		file.close();
	}

	else 
		throw Erreur("Impossible d'ouvrir le fichier !");
}

