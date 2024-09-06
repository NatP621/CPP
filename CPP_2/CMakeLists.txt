cmake_minimum_required(VERSION 3.10)
project(TreeExecutable)

set(CMAKE_CXX_STANDARD 14)

# Ajouter les fichiers sources
add_executable(TreeExecutable main.cpp)

# Trouver SFML (assurez-vous que SFML est installé sur votre système)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Lier SFML à votre projet
target_link_libraries(TreeExecutable sfml-graphics sfml-window sfml-system)