# Kompilator
COMPILE = g++

# Biblioteki
LIBRARIES = -I C:/boost_1_82_0

# Flagi kompilatora
CXXFLAGS = -Wall -std=c++20 $(LIBRARIES)

# TODO: odkomentowac kiedy stworze globalna metode main()

# # kompiluj wszystkie pliki w tym folderze
# all: $(EXECUTABLE)

# # Kompilator main
# main.o: $(SRC) $(HEADERS)
# 	$(COMPILE) $(CXXFLAGS) -c main.cpp -o main.o

# # Aplikacja odpalajaca main()
# EXECUTABLE = app

# run: $(EXECUTABLE)
# 	./$(EXECUTABLE)

# # Linker
# $(EXECUTABLE): $(OBJ)
# 	$(COMPILE) $(CXXFLAGS) $(SRC) -o $@

# # Inne metody
# clean:
# 	rm -f $(OBJ) $(EXECUTABLE)

# .PHONY: all clean
