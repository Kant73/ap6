#include "SymboleValue.h"
#include "Valeur.h"
#include <stdlib.h>


SymboleValue::SymboleValue(Symbole s) : Symbole(s.getChaine())
{
	if (s == "<ENTIER>")
		setValeur(new ValeurEntiere(atoi(s.getChaine().c_str())));
	else if (s == "<CHAINE>")
		setValeur(new ValeurChaine(s.getChaine().c_str()));
	else {
		val = NULL;
		defini = false;
	}
}


void SymboleValue::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Feuille - Symbole value : " << getChaine() << endl; // on affiche la chaine du symbole
}


// Attention : cette fonction (operator) n'est pas membre de la classe SymboleValue
ostream & operator <<(ostream & cout, SymboleValue symb)
{
	cout << (Symbole) symb << "\t\t - Valeur=";
	if (symb.defini) {
		if (typeid(symb.val)==typeid(ValeurEntiere))
			cout << ((ValeurEntiere*)symb.val)->getValeur() << endl;
		else if (typeid(symb.val)==typeid(ValeurReelle))
			cout << ((ValeurReelle*)symb.val)->getValeur() << endl;
		else if (typeid(symb.val)==typeid(ValeurChaine))
			cout << ((ValeurChaine*)symb.val)->getValeur() << endl;
	} else
		cout << "indefinie ";
	return cout;
}
