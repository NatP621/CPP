cmake_minimum_required(VERSION 3.14)
project(TreeProject)

# Utilisation du standard C++14
set(CMAKE_CXX_STANDARD 14)

# Ajout des fichiers sources et headers (les headers sont optionnels pour la compilation mais utiles pour les IDE)
set(SOURCES main.cpp tree.hpp tree.tpp)

# Création de l'exécutable
add_executable(TreeExecutable ${SOURCES})

# Si vous souhaitez lier des bibliothèques supplémentaires, vous pouvez ajouter les lignes ci-dessous
# Par exemple, pour lier Qt, Boost, etc.
# target_link_libraries(TreeExecutable <library_name>)

# Ajoutez des répertoires supplémentaires à inclure si nécessaire
# target_include_directories(TreeExecutable PRIVATE path_to_includes)