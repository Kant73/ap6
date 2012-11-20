#include <stdlib.h>
#include <iostream>
using namespace std;

#include "LecteurPhraseSimple.h"

// Permet de tester le type d'un opérateur
#define IS_OPBOOL(s) ((s) == "et" || (s) == "ou")
#define IS_OPREL(s)  ((s) == "==" || (s) == "!=" || (s) == "<" || (s) == ">" || (s) == "<=" || (s) == ">=")
#define IS_OPUNAIRE(s) ((s) == "-" || (s) == "non")


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
    } while (ls.getSymCour() != "fin" && ls.getSymCour() != "finsi" && ls.getSymCour() != "sinonsi" && ls.getSymCour() != "sinon");
	// tant que le symbole courant est un debut possible d'instruction...
}


// <inst> ::= <affectation> | <instSi>
void LecteurPhraseSimple::inst()
{
    if (ls.getSymCour() == "si")
    {
        instSi();
    }
    else
    {
        affectation();
    }
}
//<instSi> ::= si ( <expBool ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [ sinon <seqInst> ] finsi
void LecteurPhraseSimple::instSi()
{
    sauterSymCour("si");
    sauterSymCour("(");
    expBool();
    sauterSymCour(")");
    seqInst();
    while (ls.getSymCour() == "sinonsi")
    {
        sauterSymCour("sinonsi");
        sauterSymCour("(");
        expBool();
        sauterSymCour(")");
        seqInst();
    }
    if (ls.getSymCour() == "sinon")
    {
        sauterSymCour("sinon");
        seqInst();
    }
    sauterSymCour("finsi");
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


//<terme> ::= <facteur> { <opMult> <facteur> }
void LecteurPhraseSimple::terme()
{
	facteur();
	while (ls.getSymCour() == "*" || ls.getSymCour() == "/") {
		opMult();
		facteur();
	}
}


// <facteur> ::= <entier> | <variable> | <opUnaire> <expBool> | ( <expBool> )
void LecteurPhraseSimple::facteur()
{
	if (ls.getSymCour() == "<VARIABLE>" || ls.getSymCour() == "<ENTIER>" || ls.getSymCour() == "<CHAINE>")
		ls.suivant();
	else if (IS_OPUNAIRE(ls.getSymCour())) {
		ls.suivant();
		expBool();
	} else if (ls.getSymCour() == "(") {
		ls.suivant();
		expBool();
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


//     <expBool> ::= <relation> { <opBool> <relation> }
void LecteurPhraseSimple::expBool()
{
	relation();
	while (IS_OPBOOL(ls.getSymCour())) {
		opBool();
		relation();
	}
}


//      <opBool> ::= et | ou
void LecteurPhraseSimple::opBool()
{
	if (IS_OPBOOL(ls.getSymCour()))
		ls.suivant();
	else
		erreur("<opBool>");
}


//    <relation> ::= <expression> { <opRel> <expression> }
void LecteurPhraseSimple::relation()
{
	expression();
	while (IS_OPREL(ls.getSymCour())) {
		opRel();
		expression();
	}
}


//       <opRel> ::= == | != | < | <= | > | >= 
void LecteurPhraseSimple::opRel()
{
	if (IS_OPREL(ls.getSymCour()))
		ls.suivant();
	else
		erreur("<opRel>");
}


//    <opUnaire> ::= - | non
void LecteurPhraseSimple::opUnaire()
{
	if (IS_OPUNAIRE(ls.getSymCour()))
		ls.suivant();
	else
		erreur("<opUnaire>");
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
