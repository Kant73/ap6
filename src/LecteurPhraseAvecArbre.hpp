#ifndef LECTEURPHRASEAVECARBRE_H_
#define LECTEURPHRASEAVECARBRE_H_

#include "Symbole.hpp"
#include "LecteurSymbole.hpp"
#include "TableSymboles.hpp"
#include "Arbre.hpp"

#include <string>
using namespace std;

class LecteurPhraseAvecArbre
{
public:
	LecteurPhraseAvecArbre(string nomFich);	 // Construit un lecteur de phrase pour interpreter
	                                         //  le programme dans le fichier nomFich

	void analyse();  // Si le contenu du fichier est conforme à la grammaire,
	                 //   cette méthode se termine normalement et affiche un message "Syntaxe correcte".
                         //   la table des symboles (ts) et l'arbre abstrait (arbre) auront été construits
	                 // Sinon, le programme sera interrompu (exit).

	inline TableSymboles getTs ()    { return ts;    } // accesseur	
	inline Noeud*        getArbre () { return arbre; } // accesseur
	

private:
	LecteurSymbole ls;    // le lecteur de symboles utilisé pour analyser le fichier
	TableSymboles  ts;    // la table des symboles valués
	Noeud*         arbre; // l'arbre abstrait

	Noeud* programme();   //   <programme> ::= debut <seqInst> fin <EOF>
	Noeud* seqInst();     //     <seqInst> ::= <inst> ; { <inst> ; }
	Noeud* inst();	      //        <inst> ::= <affectation> | <instSi> | <instTq> | <instPour> | <instRepeter> | <instLire> | <instEcrire>
	Noeud* instSi();      //      <instSi> ::= si ( <expBool ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [ sinon <seqInst> ] finsi
	Noeud* instTq();      //      <instTq> ::= tantque ( <expBool> ) <seqInst> fintantque
	Noeud* instPour();    //    <instPour> ::= pour ( <affectation> ; <expBool> ; <affectation> ) <seqInst> finpour
	Noeud* instRepeter(); // <instRepeter> ::= repeter <seqInst> jusqua ( <expBool> )
	Noeud* affectation(); // <affectation> ::= <variable> = <expression>
	Noeud* expression();  //  <expression> ::= <terme> { <opAdd> <terme> }
	Noeud* terme();       //       <terme> ::= <facteur> { <opMult> facteur> }
	Noeud* facteur();     //     <facteur> ::= [ <opNegatif> ] <entier> | <chaine> | <variable> | ( <expBool> )
	Symbole opAdd();      //       <opAdd> ::= + | -
	Symbole opMult();     //      <opMult> ::= * | /
	Symbole opNegatif();  //   <opNegatif> ::= -
	Noeud* expBool();     //     <expBool> ::= <expBoolEt> { <opBoolOu> <expBoolEt> }
	Noeud* expBoolEt();   //   <expBoolEt> ::= <expBoolNon> { <opBoolEt> <expBoolNon> }
	Noeud* expBoolNon();  //  <expBoolNon> ::= [ <opBoolNon> ] <relation>
	Symbole opBoolOu();   //    <opBoolOu> ::= ou
	Symbole opBoolEt();   //    <opBoolEt> ::= et
	Symbole opBoolNon();  //   <opBoolNon> ::= non
	Noeud* relation();    //    <relation> ::= <expression> { <opRel> <expression> }
	Symbole opRel();      //       <opRel> ::= == | != | < | <= | > | >= 
	Noeud* instLire();    //    <instLire> ::= lire ( <variable> )
	Noeud* instEcrire();  //  <instEcrire> ::= ecrire ( <expression> | <chaine> )

	// fonctions pour simplifier l'analyse syntaxique
	void testerSymCour (string ch);  // si symbole courant != ch, erreur : on arrete le programme, sinon rien
	void sauterSymCour (string ch);  // si symbole courant == ch, on passe au symbole suivant, sinon erreur : on arrete
	void erreur (string mess);      // affiche les message d'erreur mess et arrete le programme
};

#endif /* LECTEURPHRASEAVECARBRE_H_ */
