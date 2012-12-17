class Valeur;

/*
 * Spécification des noeuds l'arbre abstrait
 */
#ifndef ARBRE_H_
#define ARBRE_H_

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Symbole.hpp"

// classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
// Remarque : la classe ne contient aucun constructeur
class Noeud {
public:
	virtual Valeur* getValeur() = 0; // méthode pure (non implémentée) qui rend la classe abstraite
	virtual void afficher(unsigned short indentation = 0) {
		cout << setw(4 * indentation) << " ";
	}
	// pour afficher un noeud avec un décalage (indentation) proportionnel à son niveau dans l'arbre

	virtual ~Noeud() {} // présence d'un destructeur virtuel conseillée dans les classes abstraites
};


// classe pour représenter un noeud "sequence d'instruction"
// qui a autant de fils que d'instructions dans la séquence
class NoeudSeqInst : public Noeud {
public:
	NoeudSeqInst();   // construit une séquence d'instruction vide
	~NoeudSeqInst() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue chaque instruction de la séquence
	void afficher(unsigned short indentation=0); // affiche la séquence d'instructions
	void ajouteInstruction(Noeud* instruction);  // ajoute une instruction à la séquence

private:
	vector<Noeud *> tabInst; // pour stocker les instructions de la séquence
};


// classe pour représenter un noeud "affectation"
// composé de 2 fils : la variable et l'expression qu'on lui affecte
class NoeudAffectation : public Noeud {
public:
	NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation
	~NoeudAffectation() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'expression et affecte sa valeur à la variable
	void afficher(unsigned short indentation = 0); // affiche l'affectation

private:
	Noeud* variable;
	Noeud* expression;
};


// classe pour représenter un noeud "opération arithmétique" composé d'un opérateur (+-*/)
// et de 2 fils : l'opérande gauche et l'opérande droit
class NoeudOperateurBinaire : public Noeud {
public:
	// construit une opération binaire : operandeGauche operateur OperandeDroit
	NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
	~NoeudOperateurBinaire() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'operande gauche, l'operande droit et applique l'opérateur
	void afficher(unsigned short indentation = 0); // affiche l'opération

private:
	Symbole operateur;
	Noeud*  operandeGauche;
	Noeud*  operandeDroit;
};


class NoeudOperateurUnaire : public Noeud {
public:
	// construit une opération binaire : operandeGauche operateur OperandeDroit
	NoeudOperateurUnaire(Symbole operateur, Noeud* operande);
	~NoeudOperateurUnaire() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'operande gauche, l'operande droit et applique l'opérateur
	void afficher(unsigned short indentation = 0); // affiche l'opération

private:
	Symbole operateur;
	Noeud*  operande;
};


// Noeud d'instruction Lire
class NoeudInstLire : public Noeud {
public:
	NoeudInstLire(Noeud* variable);
	~NoeudInstLire() {}

	Valeur* getValeur();
	void afficher(unsigned short indentation = 0);

private:
	Noeud *variable;
};


// Noeud d'instruction Ecrire
class NoeudInstEcrire : public Noeud {
public:
	NoeudInstEcrire(Noeud* exp); // construit une affectation
	~NoeudInstEcrire() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'expression et affecte sa valeur à la variable
	void afficher(unsigned short indentation = 0); // affiche l'affectation

private:
	Noeud *exp;
};


/* Permet de gérer une suite d'instructions conditionelles */
class NoeudInstSi : public Noeud {
public:
	NoeudInstSi(); /* Il y a obligatoirement au moins une instruction conditionelle */
	~NoeudInstSi() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur();	/* Évalue le bon NoeudSi */
	void afficher(unsigned short indentation = 0);

	void ajouteSinonSi(Noeud* condition, Noeud* seqInst); /* Ajoute une instruction SinonSi */
	void definirSinon(Noeud *seqInst); /* Ajoute un code a éxécuté si tout les autre ne le sont pas */

private:
	vector< pair<Noeud*, Noeud*> > tabSi; // pour stocker les instructions de la séquence
	Noeud *sinon;
};


/* Boucle repeter : un tantque 'inversé' */
class NoeudInstRepeter : public Noeud {
public:
	NoeudInstRepeter(Noeud* exp, Noeud *seqInst); // construit une affectation
	~NoeudInstRepeter() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'expression et affecte sa valeur à la variable
	void afficher(unsigned short indentation = 0); // affiche l'affectation

protected:
	Noeud *exp, *seqInst;
};


/* Boucle 'tantque', hérite de 'repeter' pour simplifier le code */
class NoeudInstTq : public NoeudInstRepeter {
public:
	NoeudInstTq(Noeud* exp, Noeud *seqInst); // construit une affectation
	~NoeudInstTq() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'expression et affecte sa valeur à la variable
	void afficher(unsigned short indentation = 0); // affiche l'affectation
};


/* Boucle 'pour', hérite de 'tantque' pour simplifier le code */
class NoeudInstPour : public NoeudInstTq {
public:
	NoeudInstPour(Noeud *init, Noeud *exp, Noeud* aff, Noeud *seqInst); // construit une affectation
	~NoeudInstPour() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'expression et affecte sa valeur à la variable
	void afficher(unsigned short indentation = 0); // affiche l'affectation

private:
	Noeud *init, *aff;
};

#endif /* ARBRE_H_ */
