# Kazdy Makefile ktory includuje tego musi zdefiniowac SRC, SRC_DIR, OBJ_DIR

# Kompilator
COMPILE = g++

# Flagi kompilatora
CXXFLAGS = -Wall -std=c++20 -IC:/boost_1_82_0

# Link
$(EXECUTABLE): $(OBJ)
	$(COMPILE) $(CXXFLAGS) $(SRC) -o $@

# Inne metody
run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJ) $(EXECUTABLE)

all: $(EXECUTABLE)

.PHONY: all clean
