#ifndef VALEUR_H
#define	VALEUR_H


#include <typeinfo>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


class Valeur {
public:
	virtual ~Valeur() {};
};


class ValeurEntiere : public Valeur {
public:
	ValeurEntiere(int val = 0) {
		this->val=val;
	}
	int getValeur() { return val; }
private:
	int val;
};


class ValeurReelle : public Valeur {
public:
	ValeurReelle(float val=0.0) {this->val=val;}
	float getValeur() { return val; }
private:
	float val;
};


class ValeurChaine : public Valeur {
public:
	ValeurChaine(string val="") {
		this->val=val;
	}
	string getValeur() { return val; }
private:
	string val;
};


#endif	/* VALEUR_H */

