#
# Configuration de la compilation
#
CFLAGS = -Wall -W -O
CC = g++

#
# Binaires
#
BINS = TestLecteurSymbole TestLecteurPhraseSimple TestLecteurPhraseAvecTable TestLecteurPhraseAvecArbre
SRCS_TestLecteurSymbole         = src/TestLecteurSymbole.cpp src/LecteurCaractere.cpp src/Symbole.cpp src/LecteurSymbole.cpp
SRCS_TestLecteurPhraseSimple    = src/TestLecteurPhraseSimple.cpp src/LecteurCaractere.cpp src/Symbole.cpp src/LecteurSymbole.cpp src/LecteurPhraseSimple.cpp
SRCS_TestLecteurPhraseAvecTable = src/TestLecteurPhraseAvecTable.cpp src/LecteurCaractere.cpp src/Symbole.cpp src/LecteurSymbole.cpp src/SymboleValue.cpp src/TableSymboles.cpp src/LecteurPhraseAvecTable.cpp
SRCS_TestLecteurPhraseAvecArbre = src/TestLecteurPhraseAvecArbre.cpp src/LecteurCaractere.cpp src/Symbole.cpp src/LecteurSymbole.cpp src/SymboleValue.cpp src/TableSymboles.cpp src/Arbre.cpp src/LecteurPhraseAvecArbre.cpp
