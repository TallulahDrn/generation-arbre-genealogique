cmake_minimum_required(VERSION 3.25)
project(Projet_family_tree C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_family_tree main.c familyTree.c person.c region.c Together.c export.c)
