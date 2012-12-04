class Valeur;

#ifndef SYMBOLEVALUE_H
#define SYMBOLEVALUE_H

#include <string.h>
#include <iostream>
using namespace std;

#include "Symbole.h"
#include "Arbre.h"

class SymboleValue : public Noeud, public Symbole {
public:
	SymboleValue(Symbole s); // construit un symbole valué à partir d'un symbole existant s
	~SymboleValue() {}
	
	void    afficher (unsigned short indentation = 0); // affiche le symbole en tant que noeud de l'arbre
	Valeur* getValeur() { return val; }
	
	void setValeur(Valeur *val);
	inline bool estDefini()              { return defini; }
	
	friend ostream & operator << (ostream & cout, SymboleValue symb); // affiche un symbole value sur cout

private:
	bool defini;	// indique si la valeur du symbole est définie
	Valeur* val;	// valeur du symbole si elle est définie, zéro sinon
};

#endif /* SYMBOLEVALUE_H */
