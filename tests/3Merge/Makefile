# Folder z implemetacja
BASE_DIR = ../../src/3Merge

# Pliki wyjsciowe
OBJ = \
	Points1/PointsTests.o \
	Trees2/TreeTests.o \
	Vector3/VectorTests.o

# Pliki zrodlowe
SRC = \
	$(BASE_DIR)/Points1/Points.cpp \
	$(BASE_DIR)/Trees2/Tree.cpp \
	$(BASE_DIR)/Vector3/IntVector.cpp \
	Points1/PointsTests.cpp \
	Trees2/TreeTests.cpp \
	Vector3/VectorTests.cpp

# Zaladuj flagi kompilacyjne z glownego Makefile'a
include ../../Makefile

# Pliki naglowkowe
HEADERS = \
	$(BASE_DIR)/Points1/Points.hpp \
	$(BASE_DIR)/Trees2/Tree.hpp \
	$(BASE_DIR)/Vector3/IntVector.hpp \
	Points1/PointsTests.hpp \
	Trees2/TreeTests.hpp \
	Vector3/VectorTests.hpp \
	MergeTestFixture.hpp

# kompiluj wszystkie pliki w tym folderze
all: $(OBJ)

# Kompilator testow
Points1/PointsTests.o: $(HEADERS) Points1/PointsTests.cpp Points1/PointsTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Points1/PointsTests.cpp -o Points1/PointsTests.o

Trees2/TreeTests.o: $(HEADERS) Trees2/TreeTests.cpp Trees2/TreeTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Trees2/TreeTests.cpp -o Trees2/TreeTests.o

Vector3/VectorTests.o: $(HEADERS) Vector3/VectorTests.cpp Vector3/VectorTests.hpp
	$(COMPILE) $(CXXFLAGS) -c Vector3/VectorTests.cpp -o Vector3/VectorTests.o

# Inne metody
clean:
	rm -f $(OBJ)

.PHONY: all clean
