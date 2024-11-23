# Pliki wyjsciowe 
OBJ = \
	Points1/Points.o \
	Vector2/IntVector.o \
	# TODO 3.o

# Pliki zrodlowe
SRC = \
	Points1/Points.cpp \
	Vector2/IntVector.cpp \
	# TODO 3.cpp

# Zaladuj flagi kompilacyjne z glownego Makefile'a
include ../../Makefile

# # Pliki naglowkowe
HEADERS = \
	Points1/Points.hpp \
	Vector2/IntVector.hpp \
	# TODO 3.hpp \
	Merger.hpp

# Kompiluj wszystkie pliki w tym folderze
all: $(OBJ)

# Kompilator przykladow
Points1/Points.o: Merger.hpp Points1/Points.cpp Points1/Points.hpp
	$(COMPILE) $(CXXFLAGS) -c Points1/Points.cpp -o Points1/Points.o

Vector2/IntVector.o: Merger.hpp Vector2/IntVector.cpp Vector2/IntVector.hpp
	$(COMPILE) $(CXXFLAGS) -c Vector2/IntVector.cpp -o Vector2/IntVector.o

# TODO: 3.o:

# Inne metody
clean:
	rm -f $(OBJ)

.PHONY: all clean
