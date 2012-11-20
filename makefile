GCC = g++ -Wall -W -O
all: TestLecteurSymbole TestLecteurPhraseSimple TestLecteurPhraseAvecTable TestLecteurPhraseAvecArbre

######################################################################################################
# etape 1 - lecteur de symboles 
######################################################################################################
ObjTestLecteurSymbole = src/LecteurCaractere.o src/Symbole.o src/LecteurSymbole.o src/TestLecteurSymbole.o

src/LecteurCaractere.o: src/LecteurCaractere.cc src/LecteurCaractere.h
	$(GCC) -c src/LecteurCaractere.cc -o $@

src/Symbole.o: src/Symbole.cc src/Symbole.h
	$(GCC) -c src/Symbole.cc -o $@

src/LecteurSymbole.o: src/LecteurSymbole.cc src/LecteurSymbole.h src/Symbole.h src/LecteurCaractere.h
	$(GCC) -c src/LecteurSymbole.cc -o $@

src/TestLecteurSymbole.o: src/TestLecteurSymbole.cc src/LecteurSymbole.h
	$(GCC) -c src/TestLecteurSymbole.cc -o $@

TestLecteurSymbole: $(ObjTestLecteurSymbole)
	$(GCC) -o TestLecteurSymbole $(ObjTestLecteurSymbole)

######################################################################################################
# etape 2 - lecteur de phrase simple 
######################################################################################################
ObjTestLecteurPhraseSimple = src/LecteurCaractere.o src/Symbole.o src/LecteurSymbole.o src/LecteurPhraseSimple.o src/TestLecteurPhraseSimple.o

src/LecteurPhraseSimple.o: src/LecteurPhraseSimple.cc src/LecteurPhraseSimple.h src/Symbole.h src/LecteurSymbole.h
	$(GCC) -c src/LecteurPhraseSimple.cc -o $@

src/TestLecteurPhraseSimple.o: src/TestLecteurPhraseSimple.cc src/LecteurPhraseSimple.h
	$(GCC) -c src/TestLecteurPhraseSimple.cc -o $@

TestLecteurPhraseSimple: $(ObjTestLecteurPhraseSimple)
	$(GCC) -o TestLecteurPhraseSimple $(ObjTestLecteurPhraseSimple)

######################################################################################################
# etape 3 - lecteur de phrase avec table des symboles 
######################################################################################################
ObjTestLecteurPhraseAvecTable = src/LecteurCaractere.o src/Symbole.o src/LecteurSymbole.o src/SymboleValue.o src/TableSymboles.o src/LecteurPhraseAvecTable.o src/TestLecteurPhraseAvecTable.o

src/SymboleValue.o: src/SymboleValue.cc src/SymboleValue.h src/Symbole.h
	$(GCC) -c src/SymboleValue.cc -o $@

src/TableSymboles.o: src/TableSymboles.cc src/TableSymboles.h src/SymboleValue.h 
	$(GCC) -c src/TableSymboles.cc -o $@

src/LecteurPhraseAvecTable.o: src/LecteurPhraseAvecTable.cc src/LecteurPhraseAvecTable.h src/LecteurSymbole.h src/TableSymboles.h
	$(GCC) -c src/LecteurPhraseAvecTable.cc -o $@

TestLecteurPhraseAvecTable: $(ObjTestLecteurPhraseAvecTable)
	$(GCC) -o TestLecteurPhraseAvecTable $(ObjTestLecteurPhraseAvecTable)

######################################################################################################
# etape 4 - lecteur de phrase avec table des symboles et arbre
######################################################################################################
ObjTestLecteurPhraseAvecArbre = src/LecteurCaractere.o src/Symbole.o src/LecteurSymbole.o src/SymboleValue.o src/TableSymboles.o src/Arbre.o src/LecteurPhraseAvecArbre.o src/TestLecteurPhraseAvecArbre.o

src/Arbre.o: src/Arbre.h src/Arbre.cc src/Symbole.h src/SymboleValue.h
	$(GCC) -c src/Arbre.cc -o $@

src/LecteurPhraseAvecArbre.o: src/LecteurPhraseAvecArbre.cc src/LecteurPhraseAvecArbre.h src/Symbole.h src/LecteurSymbole.h src/TableSymboles.h src/Arbre.h
	$(GCC) -c src/LecteurPhraseAvecArbre.cc -o $@

src/TestLecteurPhraseAvecArbre.o: src/TestLecteurPhraseAvecArbre.cc src/LecteurPhraseAvecArbre.h
	$(GCC) -c src/TestLecteurPhraseAvecArbre.cc -o $@

TestLecteurPhraseAvecArbre: $(ObjTestLecteurPhraseAvecArbre)
	$(GCC) -o TestLecteurPhraseAvecArbre $(ObjTestLecteurPhraseAvecArbre)
