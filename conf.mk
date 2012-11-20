#
# Configuration de la compilation
#
CFLAGS = -Wall -W -O
CC = g++

#
# Binaires
#
BINS = TestLecteurSymbole TestLecteurPhraseSimple TestLecteurPhraseAvecTable TestLecteurPhraseAvecArbre
SRCS_TestLecteurSymbole         = src/TestLecteurSymbole.cc src/LecteurCaractere.cc src/Symbole.cc src/LecteurSymbole.cc
SRCS_TestLecteurPhraseSimple    = src/TestLecteurPhraseSimple.cc src/LecteurCaractere.cc src/Symbole.cc src/LecteurSymbole.cc src/LecteurPhraseSimple.cc
SRCS_TestLecteurPhraseAvecTable = src/TestLecteurPhraseAvecTable.cc src/LecteurCaractere.cc src/Symbole.cc src/LecteurSymbole.cc src/SymboleValue.cc src/TableSymboles.cc src/LecteurPhraseAvecTable.cc
SRCS_TestLecteurPhraseAvecArbre = src/TestLecteurPhraseAvecArbre.cc src/LecteurCaractere.cc src/Symbole.cc src/LecteurSymbole.cc src/SymboleValue.cc src/TableSymboles.cc src/Arbre.cc src/LecteurPhraseAvecArbre.cc
