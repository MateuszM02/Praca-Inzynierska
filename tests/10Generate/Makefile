# Folder z implemetacja
BASE_DIR = ../../src/10Generate

# Pliki wyjsciowe
OBJ = \
	Even1/EvenTests.o \
	Fibonacci2/FibonacciTests.o \
	Matrix3/MatrixTests.o

# Pliki zrodlowe
SRC = \
	$(BASE_DIR)/Even1/EvenFunctor.cpp \
	$(BASE_DIR)/Fibonacci2/FibonacciFunctor.cpp \
	$(BASE_DIR)/Matrix3/Matrix.cpp \
	$(BASE_DIR)/Matrix3/MatrixFunctor.cpp \
	Even1/EvenTests.cpp \
	Fibonacci2/FibonacciTests.cpp \
	Matrix3/MatrixTests.cpp

# Zaladuj flagi kompilacyjne z glownego Makefile'a
include ../../Makefile

# Pliki naglowkowe
HEADERS = \
	$(BASE_DIR)/Even1/EvenFunctor.hpp \
	$(BASE_DIR)/Fibonacci2/FibonacciFunctor.hpp \
	$(BASE_DIR)/Matrix3/Matrix.hpp \
	$(BASE_DIR)/Matrix3/MatrixFunctor.hpp \
	Even1/EvenTests.hpp \
	Fibonacci2/FibonacciTests.hpp \
	Matrix3/MatrixTests.hpp \
	TestFixture.hpp

# kompiluj wszystkie pliki w tym folderze
all: $(OBJ)

# Kompilator testow
Even1/EvenTests.o: $(HEADERS) Even1/EvenTests.cpp Even1/EvenTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Even1/EvenTests.cpp -o Even1/EvenTests.o

Fibonacci2/FibonacciTests.o: $(HEADERS) Fibonacci2/FibonacciTests.cpp Fibonacci2/FibonacciTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Fibonacci2/FibonacciTests.cpp -o Fibonacci2/FibonacciTests.o

Matrix3/MatrixTests.o: $(HEADERS) Matrix3/MatrixTests.cpp Matrix3/MatrixTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Matrix3/MatrixTests.cpp -o Matrix3/MatrixTests.o

# Inne metody
clean:
	rm -f $(OBJ)

.PHONY: all clean
