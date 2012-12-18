#include <iostream>
using namespace std;

#include "LecteurPhraseAvecArbre.hpp"

int main(int argc, char* argv[])
{
	char nomFich[255];

	if (argc != 2) {
		cout << "Usage : " << argv[0] << " nom_fichier_source" << endl << endl;
		cout << "Entrez le nom du fichier que voulez-vous interpreter : ";
		cin.getline(nomFich, sizeof(nomFich));
	} else
		strncpy(nomFich, argv[1], sizeof(nomFich));

	LecteurPhraseAvecArbre lp(nomFich);

	lp.analyse();
	cout << endl << "Code C : " << endl;
	cout         << "================"  << endl << endl << "#include <stdlib>.h" << endl << "#include <stdio.h>" << endl << endl;
	lp.getArbre()->afficherC();

	return 0;
}

