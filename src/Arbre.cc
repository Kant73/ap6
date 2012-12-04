#include <stdlib.h>
#include "Arbre.h"
#include "Symbole.h"
#include "SymboleValue.h"

NoeudSeqInst::NoeudSeqInst() : tabInst() {}


Valeur* NoeudSeqInst::getValeur() 
{
	Valeur *valeur = NULL;
	for (unsigned int i = 0; i < tabInst.size(); i++)
		valeur = tabInst[i]->getValeur();  // on evalue chaque instruction de la séquence
	return valeur; // par convention, resultat = valeur de la derniere instruction
}


void NoeudSeqInst::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Sequence de " << tabInst.size() << " instruction(s)" << endl;
	for (unsigned int i = 0; i < tabInst.size(); i++)
		tabInst[i]->afficher(indentation + 1); // on affiche les fils en augmentant l'indentation
}


void NoeudSeqInst::ajouteInstruction(Noeud* instruction) 
{
	tabInst.push_back(instruction);
}


NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression) 
{
	this->variable = variable;
	this->expression = expression;
}


Valeur* NoeudAffectation::getValeur() 
{
	Valeur *valeur = expression->getValeur(); // on évalue l'expression
	((SymboleValue*)variable)->setValeur(valeur); // on affecte la variable
	return valeur; // par convention, une affectation a pour valeur la valeur affectée
}


void NoeudAffectation::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Affectation" << endl;
	variable->afficher(indentation + 1);   // on affiche variable et expression
	expression->afficher(indentation + 1); // en augmentant l'indentation
}


NoeudOperateurBinaire::NoeudOperateurBinaire(Symbole operateur,
                                             Noeud* operandeGauche,
                                             Noeud* operandeDroit) 
{
	this->operateur = operateur;
	this->operandeGauche = operandeGauche;
	this->operandeDroit = operandeDroit;
}


Valeur* NoeudOperateurBinaire::getValeur() 
{ 
	Valeur *valeur = NULL;
	int og = ((ValeurEntiere*)operandeGauche->getValeur())->getValeur();
	int od = ((ValeurEntiere*)operandeDroit->getValeur())->getValeur();

	if      (this->operateur == "+") valeur = new ValeurEntiere(og + od); 
	else if (this->operateur == "-") valeur = new ValeurEntiere(og - od);
	else if (this->operateur == "*") valeur = new ValeurEntiere(og * od); 
	else  /* this->operateur == "/" */ {
		if (od != 0)
			valeur = new ValeurEntiere(og / od);
		else {
			cout << "Erreur pendant l'interpretation : division par zero" << endl;
			exit(0); // plus tard on levera une exception
		}
	}

	return valeur;
}


void NoeudOperateurBinaire::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Operateur Binaire \"" << this->operateur.getChaine() << "\" applique a : " << endl;
	operandeGauche->afficher(indentation + 1);  // on affiche fils gauche et fils droit
	operandeDroit->afficher(indentation + 1);   // en augmentant l'indentation
}


NoeudOperateurBool::NoeudOperateurBool(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit) 
{
	this->operateur = operateur;
	this->operandeGauche = operandeGauche;
	this->operandeDroit = operandeDroit;
}


Valeur* NoeudOperateurBool::getValeur() 
{ 
	Valeur *valeur = NULL;
	int og = ((ValeurEntiere*)operandeGauche->getValeur())->getValeur();
	int od = ((ValeurEntiere*)operandeDroit->getValeur())->getValeur();

	if      (this->operateur == "ou") valeur = new ValeurEntiere(og || od); 
	else if (this->operateur == "et") valeur = new ValeurEntiere(og && od);
	return valeur;
}


void NoeudOperateurBool::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Operateur Booleen \"" << this->operateur.getChaine() << "\" applique a : " << endl;
	operandeGauche->afficher(indentation + 1);  // on affiche fils gauche et fils droit
	operandeDroit->afficher(indentation + 1);   // en augmentant l'indentation
}

