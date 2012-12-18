#include <stdlib.h>
#include "Arbre.hpp"
#include "Symbole.hpp"
#include "SymboleValue.hpp"
#include "Valeur.hpp"



//Séquence d'instuctions
void NoeudSeqInst::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Sequence de " << tabInst.size() << " instruction(s)" << endl;
	for (unsigned int i = 0; i < tabInst.size(); i++)
		tabInst[i]->afficher(indentation + 1); // on affiche les fils en augmentant l'indentation
}

void NoeudSeqInst::afficherC(unsigned short indentation) 
{
	for (unsigned int i = 0; i < tabInst.size(); i++) {
		tabInst[i]->afficherC(indentation + 1); // on affiche les fils en augmentant l'indentation
		cout << endl;
	}
}


//Affectation
void NoeudAffectation::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Affectation" << endl;
	variable->afficher(indentation + 1);   // on affiche variable et expression
	expression->afficher(indentation + 1); // en augmentant l'indentation
}

void NoeudAffectation::afficherC(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	variable->afficherC();
	cout << " = ";
	expression->afficherC();
	cout << ";";
}


//Opérateur binaire
void NoeudOperateurBinaire::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Operateur Binaire \"" << this->operateur.getChaine() << "\" applique a : " << endl;
	operandeGauche->afficher(indentation + 1);  // on affiche fils gauche et fils droit
	operandeDroit->afficher(indentation + 1);   // en augmentant l'indentation
}

void NoeudOperateurBinaire::afficherC() 
{
	operandeGauche->afficherC();
	cout << operateur.getChaine();
	operandeDroit->afficherC();
}


//Opérateur unaire
void NoeudOperateurUnaire::afficher(unsigned short indentation) 
{
	Noeud::afficher(indentation);
	cout << "Noeud - Operateur Unaire \"" << this->operateur.getChaine() << "\" applique a : " << endl;
	operande->afficher(indentation + 1);
}

void NoeudOperateurUnaire::afficherC() 
{
	cout << operateur.getChaine();
	operande->afficherC();
}


//Lire
void NoeudInstLire::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Lire" << endl;
	variable->afficher(indentation + 1);   // on affiche variable et expression
}

void NoeudInstLire::afficherC(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "scanf(\"%s\",";
	variable->afficherC();
	cout << ");";
}


//Ecrire
void NoeudInstEcrire::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Ecrire" << endl;
	exp->afficher(indentation + 1);   // on affiche exp et expression
}

void NoeudInstEcrire::afficherC(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "printf(\"%s\",";
	exp->afficherC();
	cout << ");";
}


//Si
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

void NoeudInstSi::afficherC(unsigned short indentation)
{
	Noeud::afficher(indentation);
	for (unsigned int i = 1; i < tabSi.size(); i++) {
		cout << "if(";
		tabSi[i].first->afficherC();
		cout << ")" << endl;
		Noeud::afficher(indentation + 1);
		tabSi[i].second->afficherC();
		Noeud::afficher(indentation);
		cout << "else ";
	}

	if (sinon != NULL)
		sinon->afficherC();
}


//Switch
void NoeudInstSwitch::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - InstSwitch" << endl;

	for (unsigned int i = 0; i < tabSi.size(); i++) {
		tabSi[i].first->afficher(indentation + 1);
		tabSi[i].second->afficher(indentation + 1);
	}

	if (defaut != NULL)
		defaut->afficher(indentation + 1);
}

void NoeudInstSwitch::afficherC(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "switch" << endl;
	Noeud::afficher(indentation);
	cout << "{" << endl;
	for (unsigned int i = 0; i < tabSi.size(); i++) {
		Noeud::afficher(indentation + 1);
		cout << "case ";
		tabSi[i].first->afficherC();
		cout << ":" << endl;
		tabSi[i].second->afficherC(indentation);
		Noeud::afficher(indentation + 2);
		cout << "break;" << endl;
	}
	
	if (defaut != NULL) {
		Noeud::afficher(indentation + 1);
		cout << "case default:" << endl;
		defaut->afficherC(indentation);
		Noeud::afficher(indentation + 2);
		cout << "break;";
	}
	cout << endl;
	Noeud::afficher(indentation);
	cout << "}";
	
}


//Répéter
void NoeudInstRepeter::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Repeter" << endl;
	exp->afficher(indentation + 1);
	seqInst->afficher(indentation + 1);
}

void NoeudInstRepeter::afficherC(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "do" << endl;
	Noeud::afficher(indentation);
	cout << "{" << endl;
	seqInst->afficherC(indentation);
	Noeud::afficher(indentation);
	cout << "} " << "while(";
	exp->afficherC();
	cout << ")";
}


//Tantque
void NoeudInstTq::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Tant que" << endl;
	exp->afficher(indentation + 1);
	seqInst->afficher(indentation + 1);
}

void NoeudInstTq::afficherC(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "while (";
	exp->afficherC();
	cout << ")" << endl;
	Noeud::afficherC(indentation);
	cout << "{" << endl;
	seqInst->afficherC(indentation);
	Noeud::afficherC(indentation);
	cout << "}";
}


//Pour
void NoeudInstPour::afficher(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "Noeud - Pour" << endl;
	init->afficher(indentation + 1);
	exp->afficher(indentation + 1);
	aff->afficher(indentation + 1);
	seqInst->afficher(indentation + 1);
}

void NoeudInstPour::afficherC(unsigned short indentation)
{
	Noeud::afficher(indentation);
	cout << "for (";
	init->afficherC();
	aff->afficherC();
	exp->afficherC();
	cout << ")" << endl;
	Noeud::afficher(indentation);
	cout << "{" << endl;
	seqInst->afficherC(indentation + 1);
	Noeud::afficher(indentation);
	cout << "}";
}