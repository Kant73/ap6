#include "LecteurPhraseAvecTable.h"

#include <stdlib.h>
#include <iostream>
using namespace std;

// Permet de tester le type d'un opérateur
#define IS_OPBOOL(s)   ((s) == "et" || (s) == "ou")
#define IS_OPREL(s)    ((s) == "==" || (s) == "!=" || (s) == "<" || (s) == ">" || (s) == "<=" || (s) == ">=")
#define IS_OPUNAIRE(s) ((s) == "-"  || (s) == "non")
#define IS_OPADD(s)    ((s) == "+"  || (s) == "-")
#define IS_OPMULT(s)   ((s) == "*"  || (s) == "/")

LecteurPhraseAvecTable::LecteurPhraseAvecTable(string nomFich) : ls(nomFich), ts() {}

void LecteurPhraseAvecTable::analyse()
{
	programme();
	cout << "Syntaxe correcte." << endl;
}


// <programme> ::= debut <seqInst> fin FIN_FICHIER
void LecteurPhraseAvecTable::programme()
{
	sauterSymCour("debut");
	seqInst();
	sauterSymCour("fin");
	testerSymCour("<FINDEFICHIER>");
}


// <seqInst> ::= <inst> ; { <inst> ; }
void LecteurPhraseAvecTable::seqInst()
{
	// tant que le symbole courant est un debut possible d'instruction...
	do {
		inst();
		sauterSymCour(";");
	} while (ls.getSymCour() != "fin" &&
		 ls.getSymCour() != "finsi" &&
		 ls.getSymCour() != "sinonsi" &&
		 ls.getSymCour() != "sinon" &&
		 ls.getSymCour() != "fintantque" &&
		 ls.getSymCour() != "jusqua" &&
		 ls.getSymCour() != "finpour");
}


// <inst> ::= <affectation> | <instSi> | <instTq> | <instRepeter>
void LecteurPhraseAvecTable::inst()
{
	if (ls.getSymCour() == "si")
		instSi();
	else if (ls.getSymCour() == "tantque")
		instTq();
	else if (ls.getSymCour() == "repeter")
		instRepeter();
	else if (ls.getSymCour() == "lire")
		instLire();
	else if (ls.getSymCour() == "ecrire")
		instEcrire();
	else if (ls.getSymCour() == "pour")
		instPour();
	else
		affectation();
}


//<instSi> ::= si ( <expBool ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [ sinon <seqInst> ] finsi
void LecteurPhraseAvecTable::instSi()
{
	sauterSymCour("si");
	sauterSymCour("(");
	expBool();
	sauterSymCour(")");
	seqInst();

	while (ls.getSymCour() == "sinonsi") {
		sauterSymCour("sinonsi");
		sauterSymCour("(");
		expBool();
		sauterSymCour(")");
		seqInst();
	}

	if (ls.getSymCour() == "sinon") {
		sauterSymCour("sinon");
		seqInst();
	}

	sauterSymCour("finsi");
}


//<instTq> ::= tantque ( <expBool> ) <seqInst> fintantque
void LecteurPhraseAvecTable::instTq()
{
	sauterSymCour("tantque");
	sauterSymCour("(");
	expBool();
	sauterSymCour(")");
	seqInst();
	sauterSymCour("fintantque");
}


//<instPour> ::= pour ( <affectation> ; <expBool> ; <affectation> ) <seqInst> finpour
void LecteurPhraseAvecTable::instPour()
{
	sauterSymCour("pour");
	sauterSymCour("(");
	affectation();
	sauterSymCour(";");
	expBool();
	sauterSymCour(";");
	affectation();
	sauterSymCour(")");
	seqInst();
	sauterSymCour("finpour");
}


//<instRepeter> ::= repeter <seqInst> jusqua ( <expBool> )
void LecteurPhraseAvecTable::instRepeter()
{
	sauterSymCour("repeter");
	seqInst();
	sauterSymCour("jusqua");
	sauterSymCour("(");
	expBool();
	sauterSymCour(")");
}


// <affectation> ::= <variable> = <expression>
void LecteurPhraseAvecTable::affectation()
{
	sauterSymCour("<VARIABLE>");
	sauterSymCour("=");
	expression();
}


//<expression> ::= <terme> { <opAdd> <terme> }
void LecteurPhraseAvecTable::expression()
{
	terme();
	while (IS_OPADD(ls.getSymCour())) {
		opAdd();
		terme();
	}
}


//<terme> ::= <facteur> { <opMult> <facteur> }
void LecteurPhraseAvecTable::terme()
{
	facteur();
	while (IS_OPMULT(ls.getSymCour())) {
		opMult();
		facteur();
	}
}


// <facteur> ::= <entier> | <variable> | <opUnaire> <expBool> | ( <expBool> )
void LecteurPhraseAvecTable::facteur()
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
void LecteurPhraseAvecTable::opAdd()
{
	if (IS_OPADD(ls.getSymCour()))
		ls.suivant();
	else
		erreur("<opAdd>");
}


//<opMult> ::= * | /
void LecteurPhraseAvecTable::opMult()
{
	if (IS_OPMULT(ls.getSymCour()))
		ls.suivant();
	else
		erreur("<opMult>");
}


//<expBool> ::= <expBoolEt> { <opBoolOu> <expBoolEt> }
void LecteurPhraseAvecTable::expBool()
{
	expBoolEt();
	while (ls.getSymCour() == "ou") {
		opBoolOu();
		expBoolEt();
	}
}


//<expBoolEt> ::= <relation> { <opBoolEt> <relation> }
void LecteurPhraseAvecTable::expBoolEt()
{
	relation();
	while ((ls.getSymCour() == "et")) {
		opBoolEt();
		relation();
	}
}


//<opBool> ::= ou
void LecteurPhraseAvecTable::opBoolOu()
{
	if (ls.getSymCour() == "ou")
		ls.suivant();
	else
		erreur("<opBool>");
}

//<opBoolEt> ::= et
void LecteurPhraseAvecTable::opBoolEt()
{
	if (ls.getSymCour() == "et")
		ls.suivant();
	else
		erreur("<opBool>");
}


//    <relation> ::= <expression> { <opRel> <expression> }
void LecteurPhraseAvecTable::relation()
{
	expression();
	while (IS_OPREL(ls.getSymCour())) {
		opRel();
		expression();
	}
}


//       <opRel> ::= == | != | < | <= | > | >= 
void LecteurPhraseAvecTable::opRel()
{
	if (IS_OPREL(ls.getSymCour()))
		ls.suivant();
	else
		erreur("<opRel>");
}


//    <opUnaire> ::= - | non
void LecteurPhraseAvecTable::opUnaire()
{
	if (IS_OPUNAIRE(ls.getSymCour()))
		ls.suivant();
	else
		erreur("<opUnaire>");
}


//    <instLire> ::= lire ( <variable> )
void LecteurPhraseAvecTable::instLire()
{
	sauterSymCour("lire");
	sauterSymCour("(");
	sauterSymCour("<VARIABLE>");
	sauterSymCour(")");
}


//  <instEcrire> ::= ecrire ( <expression> | <chaine> )
void LecteurPhraseAvecTable::instEcrire()
{
	sauterSymCour("ecrire");
	sauterSymCour("(");
	if (ls.getSymCour() == "<CHAINE>")
		ls.suivant();
	else
		expression();
	sauterSymCour(")");
}


void LecteurPhraseAvecTable::testerSymCour(string ch)
{
	if (ls.getSymCour() != ch) {
		cout << endl << "-------- Erreur ligne " << ls.getLigne()
		     << " - Colonne " << ls.getColonne() << endl << "   Attendu : "
		     << ch << endl << "   Trouve  : " << ls.getSymCour() << endl
		     << endl;
		exit(0); // plus tard, on levera une exception
	}
}


void LecteurPhraseAvecTable::sauterSymCour(string ch)
{
	testerSymCour(ch);
	ls.suivant();
}


void LecteurPhraseAvecTable::erreur(string mess)
{
	cout << endl << "-------- Erreur ligne " << ls.getLigne() << " - Colonne "
	     << ls.getColonne() << endl << "   Attendu : " << mess << endl
	     << "   Trouve  : " << ls.getSymCour() << endl << endl;
	exit(0); // plus tard, on levera une exception
}

/*void LecteurPhraseAvecTable::facteur() {
// <facteur> ::= <entier>  |  <variable>  |  - <facteur>  |  ( <expression> )

if (ls.getSymCour()=="<VARIABLE>" || ls.getSymCour()=="<ENTIER>") {
ts.chercheAjoute(ls.getSymCour());
ls.suivant();
} else if (ls.getSymCour()=="-") {
ls.suivant();
facteur();
} else if (ls.getSymCour()=="(") {
ls.suivant();
expression();
sauterSymCour(")");
} else
erreur("<facteur>");
}

void LecteurPhraseAvecTable::affectation() {
// <affectation> ::= <variable> = <expression>

//sauterSymCour("<VARIABLE>");
testerSymCour("<VARIABLE>");
ts.chercheAjoute(ls.getSymCour());
ls.suivant();
sauterSymCour("=");
expression();
}*/
