#include "TraitementGraphe.h"
#include "Chargement.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void afficheMatrice(unsigned ** matrice, unsigned n) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)	{
			if (matrice[i][j] < TraitementGraphe::INFINI)
				cout << matrice[i][j] << " , ";
			else
				cout << "I , ";
		}
		cout << endl;
	}
}

void afficheSommets(Maillon<Sommet<DonneesSommet>>* lSommets) {
	Maillon<Sommet<DonneesSommet>>* temp = lSommets;
	while (temp != NULL) {
		cout << "Sommet " << temp->valeur->info.nom << ";   numero: " << temp->valeur->info.numerotation << ";   numerotation prefixe: " 
			<< temp->valeur->info.numerotationPrefixe << ";    numerotation suffixe: " << temp->valeur->info.numerotationSuffixe << endl;
		temp = temp->suivant;
	}
}

void afficheChemin(Sommet<DonneesSommet> * s) {
	if (s == NULL)
		cout << endl;
	else {
		cout << s->info.nom << ", ";
		afficheChemin(s->info.pere);
	}
}

void sauvegarde(string aff, string path) {
	ofstream fichier(path, ios::trunc);
	if (fichier) {
		fichier << aff;
		fichier.close();
	}
	else
		throw Erreur("Impossible de creer le fichier");
}

int main2() {
	
	Graphe<DonneesArete, DonneesSommet> graphTauro;
	DonneesArete a(1, 1);

	Sommet<DonneesSommet> * s5 = graphTauro.creeSommet(DonneesSommet("s5"));
	Sommet<DonneesSommet> * s4 = graphTauro.creeSommet(DonneesSommet("s4"));
	Sommet<DonneesSommet> * s3 = graphTauro.creeSommet(DonneesSommet("s3"));
	Sommet<DonneesSommet> * s2 = graphTauro.creeSommet(DonneesSommet("s2"));
	Sommet<DonneesSommet> * s1 = graphTauro.creeSommet(DonneesSommet("s1"));

	graphTauro.creeArete(a, s1, s2);
	graphTauro.creeArete(a, s2, s3);
	graphTauro.creeArete(a, s2, s4);	
	graphTauro.creeArete(a, s4, s3);
	graphTauro.creeArete(a, s4, s5);


	TraitementGraphe traiteTauro(&graphTauro);

	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graphTauro.lSommets);
	unsigned ** matriceAdjacence = traiteTauro.matriceAjdacence(&DonneesArete::estPresent);
	unsigned ** floyd = traiteTauro.FloydWarshall(matriceAdjacence, n);
	afficheMatrice(matriceAdjacence, n);
	cout << endl;
	afficheMatrice(floyd, n);
	cout << endl << traiteTauro.diametre() << endl;

	vector<Maillon<Sommet<DonneesSommet>>*> compConnexe = traiteTauro.composantesFortementConnexes();
	
	for (Maillon<Sommet<DonneesSommet>>* liste : compConnexe) {
		cout << "=============================================" << endl << liste << endl;
	}
	
	cout << "Circuit present : ";

	if (traiteTauro.estSansCycle())
		cout << "Non";
	else
		cout << "Oui";

	cout << endl;

	system("pause");

	return 0;
}

int main1() {

	Graphe<DonneesArete, DonneesSommet> graph22;
	DonneesArete a(1, 1);

	Sommet<DonneesSommet> * s12 = graph22.creeSommet(DonneesSommet("s12"));
	Sommet<DonneesSommet> * s11 = graph22.creeSommet(DonneesSommet("s11"));
	Sommet<DonneesSommet> * s10 = graph22.creeSommet(DonneesSommet("s10"));
	Sommet<DonneesSommet> * s9 = graph22.creeSommet(DonneesSommet("s9"));
	Sommet<DonneesSommet> * s8 = graph22.creeSommet(DonneesSommet("s8"));
	Sommet<DonneesSommet> * s7 = graph22.creeSommet(DonneesSommet("s7"));
	Sommet<DonneesSommet> * s6 = graph22.creeSommet(DonneesSommet("s6"));
	Sommet<DonneesSommet> * s5 = graph22.creeSommet(DonneesSommet("s5"));
	Sommet<DonneesSommet> * s4 = graph22.creeSommet(DonneesSommet("s4"));
	Sommet<DonneesSommet> * s3 = graph22.creeSommet(DonneesSommet("s3"));
	Sommet<DonneesSommet> * s2 = graph22.creeSommet(DonneesSommet("s2"));
	Sommet<DonneesSommet> * s1 = graph22.creeSommet(DonneesSommet("s1"));

	graph22.creeArete(a, s1, s2);
	graph22.creeArete(a, s2, s1);
	graph22.creeArete(a, s3, s5);
	graph22.creeArete(a, s3, s7);
	graph22.creeArete(a, s4, s6);
	graph22.creeArete(a, s5, s4);
	graph22.creeArete(a, s5, s7);
	graph22.creeArete(a, s6, s5);
	graph22.creeArete(a, s6, s8);
	graph22.creeArete(a, s6, s10);
	graph22.creeArete(a, s7, s9);
	graph22.creeArete(a, s8, s7);
	graph22.creeArete(a, s8, s10);
	graph22.creeArete(a, s9, s8);
	graph22.creeArete(a, s11, s12);
	graph22.creeArete(a, s12, s11);

	TraitementGraphe traitement22(&graph22);

	traitement22.NumeroteGraphe();
	traitement22.pccDijkstra(s3, &DonneesArete::getDistance);

	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graph22.lSommets);
	unsigned ** matrice = traitement22.matriceAjdacence(&DonneesArete::estPresent);
	unsigned ** floyd = traitement22.FloydWarshall(matrice, n);

	vector<Maillon<Sommet<DonneesSommet>>*> compConnexe = traitement22.composantesFortementConnexes();

	afficheMatrice(matrice, n);
	cout << endl << endl;
	
	for (Maillon<Sommet<DonneesSommet>>* liste : compConnexe) {
		cout << "=============================================" << endl << liste << endl;
	}

	cout << "Circuit present : ";

	if (traitement22.estSansCycle())
		cout << "Non";
	else
		cout << "Oui";

	cout << endl;

	system("pause");

	return 0;
}

int main3() {
	Graphe<DonneesArete, DonneesSommet>* grapheCharge;
	cout << "chargement du graphe..." << endl;
	grapheCharge = Chargement::charger("GrapheFormatGPR/Ex3.gpr");
	cout << "Numerotation du graphe..." << endl;
	TraitementGraphe traiteGraphe(grapheCharge);
	traiteGraphe.NumeroteGraphe();
	cout << "Calcul du plus cours chemin entre i1 et toutes les autres arretes..." << endl;
	Sommet<DonneesSommet> * i1, *i160;
	i1 = traiteGraphe.trouverSommetParNom(grapheCharge->lSommets, "i1");
	i160 = traiteGraphe.trouverSommetParNom(grapheCharge->lSommets,"i160");
	traiteGraphe.pccDijkstra(i1, &DonneesArete::getDistance);
	cout << "Finit ! Plus court chemin entre i1 et i160 : " << endl;
	afficheChemin(i160);
	system("pause");
	return 0;
}

int main() {

	//Chargement
	bool ok = false;
	Graphe<DonneesArete, DonneesSommet>* graphe = NULL;
	TraitementGraphe * traiteGraphe = NULL;
	Sommet<DonneesSommet>* sommet = NULL;
	string choixSommet;
	unsigned** matriceAdj = NULL;
	unsigned** matriceFloyd = NULL;
	bool presenceDeCycle = false;

	while (!ok) {
		try {
			cout << "Entrez le nom du fichier gpr a charger : " << endl;
			string chemin = "GrapheFormatGPR/";
			string nom;
			cin >> nom;

			graphe = Chargement::charger(chemin + nom);
			traiteGraphe = new TraitementGraphe(graphe);
			ok = true;

		}
		catch (Erreur e) {
			cout << e << endl << endl;
		}
	}
	
	//main menu
	int choix = 0;

	while (choix > 5 || choix < 1) {
		try {
			system("cls");
			cout << "Graphe charge avec succes" << endl
				<< "1) Plus court chemin (temps ou cout) Dijkstra" << endl
				<< "2) Presence de cycles" << endl
				<< "3) Afficher les sommets et leurs numerotations" << endl
				<< "4) Matrice d'adjacence" << endl
				<< "5) Matrice de Floyd/Warshall" << endl
				<< "6) Composantes fortement connexe" << endl;

			cin >> choix;
			if (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw Erreur("Entrez un nombre entre 1 et 5");
			}

		}
		catch (Erreur e) {
			cout << e << endl;
			system("pause");
		}

	}

	switch (choix) {
	case 1:
		//PCC
		choix = 0;
		//Critere
		while (choix > 2 || choix < 1) {
			try {
				system("cls");
				cout << "Plus court chemin" << endl
					<< "Quel critere utiliser ?" << endl
					<< "1) Cout" << endl
					<< "2) Duree" << endl;

				cin >> choix;
				if (!cin) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw Erreur("Entrez un nombre entre 1 et 2");
				}
			}
			catch (Erreur e) {
				cout << e << endl;
				system("pause");
			}
		}
		//Sommet de depart
		while (sommet == NULL) {
			try {
				system("cls");
				cout << "Entrez le nom du sommet de depart : " << endl;
				cin >> choixSommet;
				sommet = traiteGraphe->trouverSommetParNom(graphe->lSommets, choixSommet);
			}
			catch (Erreur e) {
				cout << e << endl;
				system("pause");
			}
		}
	
		if (choix == 1) {
			traiteGraphe->pccDijkstra(sommet, &DonneesArete::getDistance);
		}
		else {
			traiteGraphe->pccDijkstra(sommet, &DonneesArete::getDuree);
		}

		sommet = NULL;
		ok = false;
		//Sommet pour afficher chemin
		while (sommet == NULL || !ok) {
			try {
				system("cls");
				cout << "Entrez le nom d'un sommet pour afficher son chemin ou 'q' pour retourner au menu principale : " << endl;

				cin >> choixSommet;

				if (choixSommet == "q")
					ok = true;
				else {
					sommet = traiteGraphe->trouverSommetParNom(graphe->lSommets, choixSommet);

					afficheChemin(sommet);
					system("pause");
				}
			}
			catch (Erreur e) {
				cout << e << endl;
				system("pause");
			}
		}
			break;

	case 2:
		//Presence de cycle
		presenceDeCycle = traiteGraphe->estSansCycle();
		if (presenceDeCycle) cout << "Le graphe possede un cycle" << endl;
		else cout << "Le graphe est sans cycle" << endl;
		system("pause");
		system("cls");
		break;
	case 3:
		afficheSommets(graphe->lSommets);
		system("pause");
		system("cls");
		break;
	case 4:
		choix = 0;
		while (choix > 3 || choix < 1) {
			try {

				system("cls");
				cout << "Plus court chemin" << endl
					<< "Quel critere utiliser ?" << endl
					<< "1) Cout" << endl
					<< "2) Duree" << endl
					<< "3) Presence" << endl;

				cin >> choix;
				if (!cin) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw Erreur("Entrez un nombre entre 1 et 3");
				}
			}
			catch (Erreur e) {
				cout << e << endl;
				system("pause");
			}
		}

		matriceAdj = traiteGraphe->matriceAjdacence();
		cout << "Matrice adjacence: " << endl;
		afficheMatrice(matriceAdj, Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets));
		break;
	case 5:
		matriceAdj = traiteGraphe->matriceAjdacence();
		matriceFloyd = traiteGraphe->FloydWarshall(matriceAdj, Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets));

		system("pause");
		system("cls");
		break;
	case 6:
		system("pause");
		system("cls");
		break;
		}
	

	}

