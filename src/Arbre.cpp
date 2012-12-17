#include <stdlib.h>
#include "Arbre.hpp"
#include "Symbole.hpp"
#include "SymboleValue.hpp"
#include "Valeur.hpp"

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

	if      (this->operateur == "+")   valeur = new ValeurEntiere(og + od); 
	else if (this->operateur == "-")   valeur = new ValeurEntiere(og - od);
	else if (this->operateur == "*")   valeur = new ValeurEntiere(og * od); 
	else if (this->operateur == "et")  valeur = new ValeurEntiere(og && od); 
	else if (this->operateur == "ou")  valeur = new ValeurEntiere(og || od); 
	else if (this->operateur == "==")  valeur = new ValeurEntiere(og == od); 
	else if (this->operateur == "!=")  valeur = new ValeurEntiere(og != od); 
	else if (this->operateur == "<")   valeur = new ValeurEntiere(og < od); 
	else if (this->operateur == "<=")  valeur = new ValeurEntiere(og <= od); 
	else if (this->operateur == ">")   valeur = new ValeurEntiere(og > od); 
	else if (this->operateur == ">=")  valeur = new ValeurEntiere(og >= od); 
	else if (this->operateur == "/") {
		if (od != 0)
			valeur = new ValeurEntiere(og / od);
		else {
			cout << "Erreur pendant l'interpretation : division par zero" << endl;
			exit(0); // plus tard on levera une exception
		}
	} else {
		cout << "Opérateur binaire indéfinit : " << this->operateur << endl;
		exit(0); // plus tard on levera une exception
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


NoeudOperateurUnaire::NoeudOperateurUnaire(Symbole operateur, Noeud* operande) 
{
	this->operateur = operateur;
	this->operande = operande;
}


Valeur* NoeudOperateurUnaire::getValeur() 
{ 
	Valeur *valeur = NULL;
	int o = ((ValeurEntiere*)operande->getValeur())->getValeur();

	if      (this->operateur == "non") valeur = new ValeurEntiere(!o); 
	else if (this->operateur == "-")   valeur = new ValeurEntiere(-o); 
	else {
		cout << "Opérateur unaire indéfinit : " << this->operateur << endl;
		exit(0); // plus tard on levera une exception
	}

	return valeur;
}


void NoeudOperateurUnaire::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Operateur Unaire \"" << this->operateur.getChaine() << "\" applique a : " << endl;
	operande->afficher(indentation + 1);
}


NoeudInstLire::NoeudInstLire(Noeud* variable)
{
	this->variable = variable;
}


Valeur* NoeudInstLire::getValeur()
{
	string str;
	Valeur *valeur = NULL;

	cin >> str;
	
	valeur = new ValeurChaine(str);
	((SymboleValue*)variable)->setValeur(valeur);

	return valeur;
}

void NoeudInstLire::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Lire" << endl;
	variable->afficher(indentation + 1);   // on affiche variable et expression
}


NoeudInstEcrire::NoeudInstEcrire(Noeud* exp)
{
	this->exp = exp;
}


Valeur* NoeudInstEcrire::getValeur()
{
	Valeur *val = ((SymboleValue*)exp)->getValeur();

	if (typeid(*val) == typeid(ValeurEntiere)) {
		cout << ((ValeurEntiere*)val)->getValeur() << endl;
		return ((ValeurEntiere*)val);
	} else if (typeid(*val) == typeid(ValeurReelle)) {
		cout << ((ValeurReelle*)val)->getValeur() << endl;
		return ((ValeurReelle*)val);
	} else if (typeid(*val) == typeid(ValeurChaine)) {
		string s = ((ValeurChaine*)val)->getValeur();
		cout << s.substr(1, s.length() - 2) << endl;
		return ((ValeurChaine*)val);
	}

	return NULL;
}

void NoeudInstEcrire::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Ecrire" << endl;
	exp->afficher(indentation + 1);   // on affiche exp et expression
}


NoeudInstSi::NoeudInstSi() : tabSi()
{
	sinon = NULL;
}

Valeur* NoeudInstSi::getValeur()
{
	Valeur* valeur = NULL;

	for (unsigned int i = 0; i < tabSi.size() && valeur == NULL; i++)
		if (((ValeurEntiere*)(tabSi[i].first->getValeur()))->getValeur())
			valeur = tabSi[i].second->getValeur();

	if (valeur == NULL && sinon != NULL)
		valeur = sinon->getValeur();
	
	return valeur;
}

void NoeudInstSi::ajouteSinonSi(Noeud* condition, Noeud* seqInst)
{
	tabSi.push_back(make_pair(condition, seqInst));
}

void NoeudInstSi::definirSinon(Noeud *seqInst)
{
	this->sinon = seqInst;
}

void NoeudInstSi::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - InstSi" << endl;

	for (unsigned int i = 0; i < tabSi.size(); i++) {
		tabSi[i].first->afficher(indentation + 1);
		tabSi[i].second->afficher(indentation + 1);
	}

	if (sinon != NULL)
		sinon->afficher(indentation + 1);
}


NoeudInstRepeter::NoeudInstRepeter(Noeud* exp, Noeud *seqInst)
{
	this->exp = exp;
	this->seqInst = seqInst;
}

Valeur* NoeudInstRepeter::getValeur()
{
	Valeur *valeur = seqInst->getValeur();

	while (((ValeurEntiere*)(exp->getValeur()))->getValeur())
		valeur = seqInst->getValeur();

	return valeur;
}

void NoeudInstRepeter::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Repeter" << endl;
	exp->afficher(indentation + 1);
	seqInst->afficher(indentation + 1);
}


NoeudInstTq::NoeudInstTq(Noeud* exp, Noeud *seqInst) : NoeudInstRepeter(exp, seqInst) {}

Valeur* NoeudInstTq::getValeur()
{
	Valeur *valeur = NULL;

	if (((ValeurEntiere*)(exp->getValeur()))->getValeur())
		valeur = NoeudInstRepeter::getValeur();

	return valeur;
}

void NoeudInstTq::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Tant que" << endl;
	exp->afficher(indentation + 1);
	seqInst->afficher(indentation + 1);
}
