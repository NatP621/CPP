cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(CPP_Project)

# Utilisation de la norme C++14
set(CMAKE_CXX_STANDARD 14)

# Ajout des fichiers sources
set(SOURCES
        Test.cpp
        tree.hpp
        Complex.hpp
        doctest.h
)

# Recherche des packages SFML requis
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Ajout de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Lien avec les bibliothèques SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Ajout des chemins d'inclusion (inclure le dossier courant)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})