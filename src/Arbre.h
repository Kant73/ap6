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

#include "Symbole.h"

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


// classe pour représenter un noeud "expBool"
// composé d'un opérateur (ou et) et de 2 fils : l'opérande gauche et l'opérande droit
class NoeudOperateurBool : public Noeud {
public:
	NoeudOperateurBool(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
	~NoeudOperateurBool() {} // à cause du destructeur virtuel de la classe Noeud

	Valeur* getValeur(); // évalue l'operande gauche, l'operande droit et applique l'opérateur (0 pour faux et 1 pour vrai)
	void afficher(unsigned short indentation = 0); // affiche l'opération

private:
	Symbole operateur;
	Noeud*  operandeGauche;
	Noeud*  operandeDroit;
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

#endif /* ARBRE_H_ */
