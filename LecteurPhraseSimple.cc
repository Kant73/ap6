#include <stdlib.h>
#include <iostream>
using namespace std;

#include "LecteurPhraseSimple.h"


LecteurPhraseSimple::LecteurPhraseSimple(string nomFich) :
	ls(nomFich)
{
}


void LecteurPhraseSimple::analyse()
{
	programme();
	cout << "Syntaxe correcte." << endl;
}


// <programme> ::= debut <seqInst> fin FIN_FICHIER
void LecteurPhraseSimple::programme()
{
	
	sauterSymCour("debut");
	seqInst();
	sauterSymCour("fin");
	testerSymCour("<FINDEFICHIER>");
}


// <seqInst> ::= <inst> ; { <inst> ; }
void LecteurPhraseSimple::seqInst()
{
	do {
		inst();
		sauterSymCour(";");
	} while (ls.getSymCour() == "<VARIABLE>");
	// tant que le symbole courant est un debut possible d'instruction...
}


// <inst> ::= <affectation>
void LecteurPhraseSimple::inst()
{
	affectation();
}


// <affectation> ::= <variable> = <expression>
void LecteurPhraseSimple::affectation()
{
	sauterSymCour("<VARIABLE>");
	sauterSymCour("=");
	expression();
}

//<expression> ::= <terme> { <opAdd> <terme> }
void LecteurPhraseSimple::expression()
{
	terme();
	while (ls.getSymCour() == "+" || ls.getSymCour() == "-") {
		opAdd();
		terme();
	}
}


//<terme> ::= <facteur> { <opMult> facteur> }
void LecteurPhraseSimple::terme()
{
	facteur();
	while (ls.getSymCour() == "*" || ls.getSymCour() == "/") {
		opMult();
		facteur();
	}
}


// <facteur> ::= <entier>  |  <variable>  |  - <facteur>  |  ( <expression> )
void LecteurPhraseSimple::facteur()
{
	if (ls.getSymCour() == "<VARIABLE>" || ls.getSymCour() == "<ENTIER>")
		ls.suivant();
	else if (ls.getSymCour() == "-") {
		ls.suivant();
		facteur();
	} else if (ls.getSymCour() == "(") {
		ls.suivant();
		expression();
		sauterSymCour(")");
	} else
		erreur("<facteur>");
}


//<opAdd> ::= + | -
void LecteurPhraseSimple::opAdd()
{
	if (ls.getSymCour() == "+" || ls.getSymCour() == "-")
		ls.suivant();
	else
		erreur("<opAdd>");
}


//<opMult> ::= * | /
void LecteurPhraseSimple::opMult()
{
	if (ls.getSymCour() == "*" || ls.getSymCour() == "/")
		ls.suivant();
	else
		erreur("<opMult>");
}


void LecteurPhraseSimple::testerSymCour(string ch) {
	if (ls.getSymCour() != ch) {
		cout << endl << "-------- Erreur ligne " << ls.getLigne()
		     << " - Colonne " << ls.getColonne() << endl << "   Attendu : "
		     << ch << endl << "   Trouve  : " << ls.getSymCour() << endl
		     << endl;
		exit(0); // plus tard, on levera une exception
	}
}


void LecteurPhraseSimple::sauterSymCour(string ch)
{
	testerSymCour(ch);
	ls.suivant();
}


void LecteurPhraseSimple::erreur(string mess)
{
	cout << endl << "-------- Erreur ligne " << ls.getLigne() << " - Colonne "
	     << ls.getColonne() << endl << "   Attendu : " << mess << endl
	     << "   Trouve  : " << ls.getSymCour() << endl << endl;
	exit(0); // plus tard, on levera une exception
}
