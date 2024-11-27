# Pliki wyjsciowe 
OBJ = \
	Points1/Points.o \
	Trees2/Tree.o \
	Vector3/IntVector.o \

# Pliki zrodlowe
SRC = \
	Points1/Points.cpp \
	Trees2/Tree.cpp \
	Vector3/IntVector.cpp \

# Zaladuj flagi kompilacyjne z glownego Makefile'a
include ../../Makefile

# # Pliki naglowkowe
HEADERS = \
	Points1/Points.hpp \
	Trees2/Tree.hpp \
	Vector3/IntVector.hpp \
	Merger.hpp

# Kompiluj wszystkie pliki w tym folderze
all: $(OBJ)

# Kompilator przykladow
Points1/Points.o: Merger.hpp Points1/Points.cpp Points1/Points.hpp
	$(COMPILE) $(CXXFLAGS) -c Points1/Points.cpp -o Points1/Points.o

Trees2/Tree.o: Merger.hpp Trees2/Tree.cpp Trees2/Tree.hpp
	$(COMPILE) $(CXXFLAGS) -c Trees2/Tree.cpp -o Trees2/Tree.o

Vector3/IntVector.o: Merger.hpp Vector3/IntVector.cpp Vector3/IntVector.hpp
	$(COMPILE) $(CXXFLAGS) -c Vector3/IntVector.cpp -o Vector3/IntVector.o

# Inne metody
clean:
	rm -f $(OBJ)

.PHONY: all clean
