#include "LecteurPhraseAvecArbre.h"

#include <stdlib.h>
#include <iostream>
using namespace std;


LecteurPhraseAvecArbre::LecteurPhraseAvecArbre(string nomFich) : ls(nomFich), ts() {}


void LecteurPhraseAvecArbre::analyse()
{
	arbre = programme();
	cout << "Syntaxe correcte." << endl;
}


// <programme> ::= debut <seq_inst> fin FIN_FICHIER
Noeud* LecteurPhraseAvecArbre::programme()
{
	sauterSymCour("debut");
	Noeud* si = seqInst();
	sauterSymCour("fin");
	testerSymCour("<FINDEFICHIER>");
	return si;
}


// <seqInst> ::= <inst> ; { <inst> ; }
Noeud* LecteurPhraseAvecArbre::seqInst()
{
	NoeudSeqInst* si = new NoeudSeqInst();

	// Boucle tant que le symbole courant est un début possible d'instruction
	do {
		si->ajouteInstruction(inst());
		sauterSymCour(";");
	} while (ls.getSymCour() == "<VARIABLE>");

	return si;
}


// <inst> ::= <affectation> | <inst_condi>
Noeud* LecteurPhraseAvecArbre::inst()
{
	return affectation();
}


// <affectation> ::= <variable> = <expression>
Noeud* LecteurPhraseAvecArbre::affectation()
{
	testerSymCour("<VARIABLE>");
	Noeud* var = ts.chercheAjoute(ls.getSymCour());
	ls.suivant();
	sauterSymCour("=");
	Noeud* exp = expression();
	return new NoeudAffectation(var, exp);
}


// <expression> ::= <facteur> { <opBinaire> <facteur> }
Noeud* LecteurPhraseAvecArbre::expression()
{
	Noeud* fact = facteur();

	while (ls.getSymCour() == "+" || ls.getSymCour() == "-" ||
	       ls.getSymCour() == "*" || ls.getSymCour() == "/") {
		Symbole operateur = opBinaire(); // on stocke le symbole de l'opérateur
		Noeud* factDroit = facteur(); // lecture de l'operande droit
		fact = new NoeudOperateurBinaire(operateur, fact, factDroit); // const. du noeud
	}

	return fact;
}


// <facteur> ::= <entier>  |  <variable>  |  - <facteur>  |  ( <expression> )
Noeud* LecteurPhraseAvecArbre::facteur()
{
	Noeud* fact = NULL;

	if (ls.getSymCour() == "<VARIABLE>" || ls.getSymCour() == "<ENTIER>") {
		fact = ts.chercheAjoute(ls.getSymCour());
		ls.suivant();
	} else if (ls.getSymCour() == "-") {
		ls.suivant();
		// on représente le moins unaire (- facteur) par une soustractin binaire (0 - facteur)
		fact = new NoeudOperateurBinaire(Symbole("-"), ts.chercheAjoute(Symbole("0")), facteur());
	} else if (ls.getSymCour() == "(") {
		ls.suivant();
		fact = expression();
		sauterSymCour(")");
	} else
		erreur("<facteur>");

	return fact;
}


// <opBinaire> ::= + | - | *  | /
Symbole LecteurPhraseAvecArbre::opBinaire()
{
	Symbole operateur;

	if (ls.getSymCour() == "+" || ls.getSymCour() == "-" || 
	    ls.getSymCour() == "*" || ls.getSymCour() == "/" ) {
		operateur = ls.getSymCour();
		ls.suivant();
	} else
		erreur("<opBinaire>");

	return operateur;
}


void LecteurPhraseAvecArbre::testerSymCour(string ch)
{
	if (ls.getSymCour() != ch) {
		cout << endl << "-------- Erreur ligne " << ls.getLigne()
		     << " - Colonne " << ls.getColonne() << endl << "   Attendu : "
		     << ch << endl << "   Trouve  : " << ls.getSymCour() << endl
		     << endl;
		exit(0); // plus tard, on levera une exception
	}
}


void LecteurPhraseAvecArbre::sauterSymCour(string ch)
{
	testerSymCour(ch);
	ls.suivant();
}


void LecteurPhraseAvecArbre::erreur(string mess)
{
	cout << endl << "-------- Erreur ligne " << ls.getLigne() << " - Colonne "
	     << ls.getColonne() << endl << "   Attendu : " << mess << endl
	     << "   Trouve  : " << ls.getSymCour() << endl << endl;
	exit(0); // plus tard, on levera une exception
}
