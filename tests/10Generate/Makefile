# Folder z implemetacja
BASE_DIR = ../../src/10Generate

# Pliki wyjsciowe
OBJ = \
	Fibonacci1/FibonacciTests.o \
	RandomString2/RandomStringTests.o \
	Matrix3/MatrixTests.o

# Pliki zrodlowe
SRC = \
	$(BASE_DIR)/Fibonacci1/FibonacciFunctor.cpp \
	$(BASE_DIR)/RandomString2/RandomStringFunctor.cpp \
	$(BASE_DIR)/Matrix3/Matrix.cpp \
	$(BASE_DIR)/Matrix3/MatrixFunctor.cpp \
	Fibonacci1/FibonacciTests.cpp \
	RandomString2/RandomStringTests.cpp \
	Matrix3/MatrixTests.cpp

# Zaladuj flagi kompilacyjne z glownego Makefile'a
include ../../Makefile

# Pliki naglowkowe
HEADERS = \
	$(BASE_DIR)/Fibonacci1/FibonacciFunctor.hpp \
	$(BASE_DIR)/RandomString2/RandomStringFunctor.hpp \
	$(BASE_DIR)/Matrix3/Matrix.hpp \
	$(BASE_DIR)/Matrix3/MatrixFunctor.hpp \
	Fibonacci1/FibonacciTests.hpp \
	RandomString2/RandomStringTests.hpp \
	Matrix3/MatrixTests.hpp \
	TestFixture.hpp

# kompiluj wszystkie pliki w tym folderze
all: $(OBJ)

# Kompilator testow
Fibonacci1/FibonacciTests.o: $(HEADERS) Fibonacci1/FibonacciTests.cpp Fibonacci1/FibonacciTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Fibonacci1/FibonacciTests.cpp -o Fibonacci1/FibonacciTests.o

RandomString2/RandomStringTests.o: $(HEADERS) RandomString2/RandomStringTests.cpp RandomString2/RandomStringTests.hpp
	$(COMPILE) $(CXXFLAGS) -c RandomString2/RandomStringTests.cpp -o RandomString2/RandomStringTests.o

Matrix3/MatrixTests.o: $(HEADERS) Matrix3/MatrixTests.cpp Matrix3/MatrixTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Matrix3/MatrixTests.cpp -o Matrix3/MatrixTests.o

# Inne metody
clean:
	rm -f $(OBJ)

.PHONY: all clean
