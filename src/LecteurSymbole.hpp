#ifndef LECTEURSYMBOLE_H_
#define LECTEURSYMBOLE_H_

#include <fstream>
#include <string>
using namespace std;

#include "LecteurCaractere.hpp"
#include "Symbole.hpp"

class LecteurSymbole {
public:
	LecteurSymbole(string nomFich);    // résultat : symCour = premier symbole du fichier nomFich
	void suivant();                    // passe au symbole suivant du fichier
	inline Symbole getSymCour()      { return symCour; }
	inline unsigned int getLigne()   { return ligne;   }
	inline unsigned int getColonne() { return colonne; }
	
private:
	LecteurCaractere lc;         // le lecteur de caracteres
	Symbole symCour;             // le symbole courant du lecteur de symboles
	unsigned int ligne, colonne; // coordonnees, dans le fichier, du symbole courant
	void sauterSeparateurs();    // saute dans lc une suite de separateurs consecutifs
	void sauterCommentaires();   // saute dans lc une commentaire
	string motSuivant();         // lit dans lc la chaine du prochain symbole et la renvoie en resultat
};

#endif /* LECTEURSYMBOLE_H_ */ 
