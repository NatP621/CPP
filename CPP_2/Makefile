# Nom de l'exécutable
TARGET = test_exec

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror

# Fichiers source et d'en-tête
SRCS = Test.cpp
HEADERS = Complex.hpp doctest.h tree.hpp

# Options de linkage pour SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Règle par défaut pour compiler l'exécutable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(SFML_LIBS)

# Règle pour exécuter les tests automatiquement après compilation
run_tests: $(TARGET)
	./$(TARGET)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET) $(SRCS:.cpp=.d)

# Inclusion des dépendances
-include $(SRCS:.cpp=.d)

# Génération des fichiers de dépendances
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< > $@