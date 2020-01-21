cmake_minimum_required(VERSION 2.8.9)
project (chuckie_egg)
include (../../32blit.cmake)
blit_executable (chuckie_egg chuckie_egg.cpp game.cpp sprite_sheet.cpp)
