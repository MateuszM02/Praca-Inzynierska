# Pliki wyjsciowe 
OBJ = \
	main.o \
	Even1/EvenFunctor.o \
	Fibonacci2/FibonacciFunctor.o \
	Matrix3/Matrix.o \
	Matrix3/MatrixFunctor.o

# Aplikacja odpalajaca main()
EXECUTABLE = app

include ../../common.mk

# Pliki naglowkowe
HEADERS = \
	Even1/EvenFunctor.hpp \
	Fibonacci2/FibonacciFunctor.hpp \
	Matrix3/Matrix.hpp \
	Matrix3/MatrixConcepts.hpp \
	Matrix3/MatrixFunctor.hpp \
	Functor.hpp

# Pliki zrodlowe
SRC = \
	main.cpp \
	Even1/EvenFunctor.cpp \
	Fibonacci2/FibonacciFunctor.cpp \
	Matrix3/Matrix.cpp \
	Matrix3/MatrixFunctor.cpp

# Zaleznosci plikow wyjsciowych
MATRIX_DEPENDENCIES = \
	Functor.hpp \
	Matrix3/Matrix.hpp \
	Matrix3/Matrix.cpp \
	Matrix3/MatrixConcepts.hpp

# Kompilator main
main.o: $(SRC) $(HEADERS)
	$(COMPILE) $(CXXFLAGS) -c main.cpp -o main.o

# Kompilator przykladow
EvenFunctor.o: Functor.hpp Even1/EvenFunctor.cpp Even1/EvenFunctor.hpp
	$(COMPILE) $(CXXFLAGS) -c Even1/EvenFunctor.cpp -o EvenFunctor.o

FibonacciFunctor.o: Functor.hpp Fibonacci2/FibonacciFunctor.cpp Fibonacci2/FibonacciFunctor.hpp
	$(COMPILE) $(CXXFLAGS) -c Fibonacci2/FibonacciFunctor.cpp -o FibonacciFunctor.o

Matrix.o: $(MATRIX_DEPENDENCIES)
	$(COMPILE) $(CXXFLAGS) -c Matrix3/Matrix.cpp -o Matrix.o

MatrixFunctor.o: $(MATRIX_DEPENDENCIES) Matrix3/MatrixFunctor.hpp Matrix3/MatrixFunctor.cpp
	$(COMPILE) $(CXXFLAGS) -c Matrix3/MatrixFunctor.cpp -o MatrixFunctor.o
