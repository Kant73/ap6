#ifndef LECTEURPHRASESIMPLE_H_
#define LECTEURPHRASESIMPLE_H_

#include "LecteurSymbole.hpp"

class LecteurPhraseSimple {
public:
	LecteurPhraseSimple(string nomFich); // Construit un lecteur de phrase pour vérifier
	// la syntaxe du programme dans le fichier nomFich

	void analyse();   // Si le contenu du fichier est conforme à la grammaire,
	// cette méthode se termine normalement et affiche un message "Syntaxe correcte".
	// Sinon, le programme sera interrompu (exit).
        	
private:
	LecteurSymbole ls;  // le lecteur de symboles utilisé pour lyser le fichier		

	// implémentation de la grammaire
	void programme();   //   <programme> ::= debut <seqInst> fin <EOF>
	void seqInst();	    //     <seq_ins> ::= <inst> ; { <inst> ; }
	void inst();	    //        <inst> ::= <affectation> | <instSi> | <instTq> | <instPour> | <instRepeter> | <instLire> | <instEcrire>
	void instSi();      //      <instSi> ::= si ( <expBool ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [ sinon <seqInst> ] finsi
	void instTq();      //      <instTq> ::= tantque ( <expBool> ) <seqInst> fintantque
	void instPour();    //    <instPour> ::= pour ( <affectation> ; <expBool> ; <affectation> ) <seqInst> finpour
	void instRepeter(); // <instRepeter> ::= repeter <seqInst> jusqua ( <expBool> )
	void affectation(); // <affectation> ::= <variable> = <expression>
	void expression();  //  <expression> ::= <terme> { <opAdd> <terme> }
	void facteur();     //     <facteur> ::= <entier> | <variable> | <opUnaire> <expBool> | ( <expBool> )
	void terme();       //       <terme> ::= <facteur> { <opMult> facteur> }
	void opAdd();       //       <opAdd> ::= + | -
	void opMult();      //      <opMult> ::= * | /
	void expBool();   //       <expBool> ::= <expBoolEt> { <opBoolOu> <expBoolEt> }
	void expBoolEt();   //   <expBoolEt> ::= <relation> { <opBoolEt> <relation> }
	void opBoolOu();    //    <opBoolOu> ::= ou
	void opBoolEt();    //    <opBoolEt> ::= et
	void relation();    //    <relation> ::= <expression> { <opRel> <expression> }
	void opRel();	    //       <opRel> ::= == | != | < | <= | > | >= 
	void opUnaire();    //    <opUnaire> ::= - | non
	void instLire();    //    <instLire> ::= lire ( <variable> )
	void instEcrire();  //  <instEcrire> ::= ecrire ( <expression> | <chaine> )


	// outils pour se simplifier l'analyse syntaxique
	void testerSymCour (string ch);  // si symbole courant != ch, erreur : on arrete le programme, sinon rien
	void sauterSymCour (string ch);  // si symbole courant == ch, on passe au symbole suivant, sinon erreur : on arrete
	void erreur (string mess);      // affiche les message d'erreur mess et arrete le programme
};

#endif /* LECTEURPHRASESIMPLE_H_ */
