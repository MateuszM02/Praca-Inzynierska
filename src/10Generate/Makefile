# Pliki wyjsciowe 
OBJ = \
	Fibonacci1/FibonacciFunctor.o \
	RandomString2/RandomStringFunctor.o \
	Matrix3/Matrix.o \
	Matrix3/MatrixFunctor.o

# Pliki zrodlowe
SRC = \
	Fibonacci1/FibonacciFunctor.cpp \
	RandomString2/RandomStringFunctor.cpp \
	Matrix3/Matrix.cpp \
	Matrix3/MatrixFunctor.cpp

# Zaladuj flagi kompilacyjne z glownego Makefile'a
include ../../Makefile

# Pliki naglowkowe
HEADERS = \
	Fibonacci1/FibonacciFunctor.hpp \
	RandomString2/RandomStringFunctor.hpp \
	Matrix3/Matrix.hpp \
	Matrix3/MatrixConcepts.hpp \
	Matrix3/MatrixFunctor.hpp \
	Functor.hpp

# Zaleznosci plikow wyjsciowych
MATRIX_DEPENDENCIES = \
	Functor.hpp \
	Matrix3/Matrix.hpp \
	Matrix3/Matrix.cpp \
	Matrix3/MatrixConcepts.hpp

# Kompiluj wszystkie pliki w tym folderze
all: $(OBJ)

# Kompilator przykladow
Fibonacci1/FibonacciFunctor.o: Functor.hpp Fibonacci1/FibonacciFunctor.cpp Fibonacci1/FibonacciFunctor.hpp
	$(COMPILE) $(CXXFLAGS) -c Fibonacci1/FibonacciFunctor.cpp -o Fibonacci1/FibonacciFunctor.o

RandomString2/RandomStringFunctor.o: Functor.hpp RandomString2/RandomStringFunctor.cpp RandomString2/RandomStringFunctor.hpp
	$(COMPILE) $(CXXFLAGS) -c RandomString2/RandomStringFunctor.cpp -o RandomString2/RandomStringFunctor.o

Matrix3/Matrix.o: $(MATRIX_DEPENDENCIES)
	$(COMPILE) $(CXXFLAGS) -c Matrix3/Matrix.cpp -o Matrix3/Matrix.o

Matrix3/MatrixFunctor.o: $(MATRIX_DEPENDENCIES) Matrix3/MatrixFunctor.hpp Matrix3/MatrixFunctor.cpp
	$(COMPILE) $(CXXFLAGS) -c Matrix3/MatrixFunctor.cpp -o Matrix3/MatrixFunctor.o

# Inne metody
clean:
	rm -f $(OBJ)

.PHONY: all clean
