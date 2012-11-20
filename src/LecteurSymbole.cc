#include <ctype.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "LecteurSymbole.h"

#define IS_NEWLIGNE(c) ((c) == '\n' || (c) == '\r')
#define IS_SEPARATEUR(c) (IS_NEWLIGNE(c) || (c) == ' ' || (c) == '\t')

LecteurSymbole::LecteurSymbole(string nomFich) :
	lc(nomFich), symCour("") {
	suivant(); // pour lire le premier symbole
}


void LecteurSymbole::suivant() {
	sauterSeparateurs();
	sauterCommentaires();
	// on est maintenant positionne sur le premier caractère d'un symbole
	ligne = lc.getLigne();
	colonne = lc.getColonne();
	symCour = Symbole(motSuivant()); // on reconstruit symCour avec le nouveau mot lu
}


void LecteurSymbole::sauterSeparateurs() {
	while (IS_SEPARATEUR(lc.getCarCour()))
		lc.suivant();
}


string LecteurSymbole::motSuivant() {
	static string s;
	s = "";

	if (isdigit(lc.getCarCour())) {
		// c'est le début d'un entier
		do {
			s += lc.getCarCour();
			lc.suivant();
		} while (isdigit(lc.getCarCour()));

	} else if (isalpha(lc.getCarCour())) {
		// c'est le début d'un mot
		do {
			s += lc.getCarCour();
			lc.suivant();
		} while (isalpha(lc.getCarCour())  || 
			 isdigit(lc.getCarCour()) || 
			 lc.getCarCour() == '_');

	} else if (lc.getCarCour() == '"') {
		// c'est le début d'une chaîne de caractères
		s += lc.getCarCour();
		do {
			lc.suivant();
			if (IS_NEWLIGNE(lc.getCarCour()))
				exit(0);
			s += lc.getCarCour();
		} while (lc.getCarCour() != '"');
		lc.suivant();
	} else if (lc.getCarCour() != EOF) {
		// c'est un caractere special
		s = lc.getCarCour();
		lc.suivant();

		if ((s == "=" || s == "<" || s == ">" || s == "!") && lc.getCarCour() == '=') {
			s += lc.getCarCour();
			lc.suivant();
		}
	}
	return s;
}


void LecteurSymbole::sauterCommentaires()
{
	while(lc.getCarCour() == '#') {
		while(!IS_NEWLIGNE(lc.getCarCour()))
			lc.suivant();
		sauterSeparateurs();
	}
}
