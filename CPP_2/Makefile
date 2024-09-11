# Nom des exécutables (renommés pour éviter les conflits avec les cibles)
MAIN_EXEC = tree_exec
TEST_EXEC = test_exec

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror

# Liens SFML (ajustez les chemins si nécessaire)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Fichiers source
MAIN_SRCS = main.cpp
TEST_SRCS = Test.cpp

# Fichiers d'en-tête
HEADERS_MAIN = tree.hpp
HEADERS_TEST = tree.hpp doctest.h

# Règles pour compiler et exécuter l'exécutable principal
.PHONY: tree
tree: $(MAIN_EXEC)
	./$(MAIN_EXEC)

$(MAIN_EXEC): $(MAIN_SRCS) $(HEADERS_MAIN)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) $(MAIN_SRCS) $(SFML_LIBS)

# Règles pour compiler et exécuter l'exécutable de test
.PHONY: test
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRCS) $(HEADERS_TEST)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRCS) $(SFML_LIBS)

# Règle pour tout compiler
all: tree test

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC)

# Générer les fichiers de dépendance
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< > $@